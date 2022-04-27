#include "gpssocketreader.h"
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <assert.h>
#include <fcntl.h>    /* For O_RDWR */
  /* For open(), creat() */
#include <errno.h>


#include <termios.h>


GpsSocketReader::GpsSocketReader()
	: m_listener(nullptr)
{
	
}

void GpsSocketReader::init()
{
	connect();
}
int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        if (tcgetattr (fd, &tty) != 0)
        {
                //error_message ("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                //error_message ("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}
bool GpsSocketReader::connect()
{
	char *source_server = NULL;
	char *source_port = NULL;
	int fd;
	if (fd=open("/dev/ttyAMA0",O_RDWR | O_NOCTTY | O_SYNC) != 0) {
		(void)fprintf(stderr,
		  "gpspipe: could not connect to gpsd %s:%s, %s(%d)\n",
		  source_server, source_port, strerror(errno), errno);
		return false;
	}
	set_interface_attribs (fd, B9600, 0);
	unsigned int flags = WATCH_ENABLE | WATCH_NMEA;
	char *source_device = NULL;
	
	return true;
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
	fd_set fds;	
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100000;
	FD_ZERO(&fds);
	FD_SET(gpsdata.gps_fd, &fds);
	errno = 0;
	int r = 0;
	r = select(gpsdata.gps_fd+1, &fds, NULL, NULL, &tv);
	if (r == -1 && errno != EINTR)
	{
		std::cout << "ERROR: gpspipe select error " << strerror(errno) << " (" << errno << ")" << std::endl;
		return "";
	}
	else if (r == 0)
	{
		return "";
	}
	
	char buf[256];
	std::string l_ret;
	r = (int)read(gpsdata.gps_fd, buf, sizeof(buf));
	int i = 0;
	for (i = 0; i < r; i++) {
		char c = buf[i];
		l_ret += c;
	}
	std::cout<<l_ret<<std::endl;
	return l_ret;
}

void GpsSocketReader::run()
{
	assert(m_listener != nullptr);
	std::thread l_thread(&GpsSocketReader::task, this);
	l_thread.detach();
}

void GpsSocketReader::task()
{
	while (true)
	{
		std::string l_line;
		l_line = readLine();
		
		if (l_line.size() == 0 || l_line[0] != '$')
		{
			continue;
		}
		
		std::cout << l_line << std::endl;
		m_listener->onSentenceReceived(l_line);
	}
}

void GpsSocketReader::setListener(IGpsSocketReaderListener *p_listener)
{
	m_listener = p_listener;
}
