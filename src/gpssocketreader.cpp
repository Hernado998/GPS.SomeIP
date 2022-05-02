#include "gpssocketreader.h"
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <assert.h>
#include <fcntl.h> 
#include <errno.h>
#include <exception>
#include <termios.h>
using namespace std;
#define TERMINAL    "/dev/ttyAMA0"
int fd;
int rdlen;
int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0)
        printf("Error tcsetattr: %s\n", strerror(errno));
}

GpsSocketReader::GpsSocketReader()
	: m_listener(nullptr)
{
	
}

void GpsSocketReader::init()
{
	connect();
}

void GpsSocketReader::connect()
{
	char *portname = TERMINAL;
    int wlen;
    

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
    }
    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, B9600);
    //set_mincount(fd, 0);                /* set to pure timed read */

   
    tcdrain(fd);    /* delay for output */


    
	
}

std::string GpsSocketReader::readLine()
{
	static std::string l_buf;
	while (true)
	{
		// 1. if there is a \n in l_buf, return it
		size_t l_pos = l_buf.find("\n");
		if (l_pos != std::string::npos)
		{
			std::string l_ret = l_buf.substr(0, l_pos); // \n is not returned
			l_buf = l_buf.substr(l_pos+1);
			if (l_ret.back() == '\r')
			{
				l_ret.pop_back();
			}
			return l_ret;
		}
		
		// 2. read something
		l_buf += internalRead();
	}
}

std::string GpsSocketReader::internalRead()
{
    int r = 0;
	char buf[1000];
	std::string l_ret;
	r = (int)read(fd, buf, sizeof(buf));
	int i = 0;
	for (i = 0; i < r; i++) {
		char c = buf[i];
		l_ret += c;
	}
	return l_ret;

}

void GpsSocketReader::run()
{
	assert(m_listener != nullptr);
	std::thread l_thread(&GpsSocketReader::task, this);
	l_thread.detach();
	
	//task();
	
}

void GpsSocketReader::task()
{
	while (true)
	{
		try{
			usleep(100000);
			std::string l_line;
			l_line = readLine();
			//l_line ="$GPGGA,082819.00,4503.93047,N,00741.21221,E,1,03,3.02,320.5,M,47.2,M,,*5A";
			if (l_line.size() == 0 || l_line[0] != '$')
			{
				continue;
			}		
			//std::cout << l_line << std::endl;
			BB.addToTrackingFile(l_line+"\n");
			m_listener->onSentenceReceived(l_line);
		}
		catch(exception& e){
			cout << e.what() << '\n';
		}
	
	}
}

void GpsSocketReader::setListener(IGpsSocketReaderListener *p_listener)
{
	m_listener = p_listener;
}
