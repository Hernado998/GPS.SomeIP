#include "gpscontroller.h"
#include <unistd.h>
#include <assert.h>
#include <iostream>

GpsController::GpsController(GpsSomeIpClient *p_client, const std::string& p_logFile)
	: m_client(p_client),
	  m_logFile(p_logFile)
{
	assert(m_client != nullptr);
}

void GpsController::onDataReceived(double p_lat, double p_lon,int p_hour,int p_minute,int p_second,int p_day,int p_month,int p_year)
{
	std::cout << "Data received: " << p_lat << ", " << p_lon <<" ||| "<<p_hour<<":"<<p_minute<<":"<<p_second<< std::endl;
	m_logFile << p_lat << ", " << p_lon <<" ||| "<<p_hour<<":"<<p_minute<<":"<<p_second<< " ||| "<<p_day<<"/"<<p_month<<"/"<<p_year<<std::endl;
}

void GpsController::onFixStatusChanged(bool p_valid)
{
	std::cout << "Fix status changed: " << p_valid << std::endl;
}

void GpsController::run()
{
	std::thread l_thread(&GpsController::task, this);
	l_thread.detach();
}

void GpsController::task()
{
	if (m_logFile.is_open() == false)
	{
		std::cout << "Unable to open log file" << std::endl;
		return;
	}
	
	while (true)
	{
		std::this_thread::sleep_for (std::chrono::milliseconds(3000));
		std::cout << "Requesting data" << std::endl;
		m_client->requestData();
		
	}
	m_logFile.close();
}
