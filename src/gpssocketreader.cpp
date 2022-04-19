#include "gpssocketreader.h"
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <assert.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */


GpsSocketReader::GpsSocketReader()
	: m_listener(nullptr)
{
	
}

void GpsSocketReader::init()
{
	connect();
}

bool GpsSocketReader::connect()
{
	char *source_server = NULL;
	char *source_port = NULL;

	if (open("/dev/ttyAMA0")) {
		(void)fprintf(stderr,
		  "gpspipe: could not connect to gpsd %s:%s, %s(%d)\n",
		  source_server, source_port, strerror(errno), errno);
		return false;
	}

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
