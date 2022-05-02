#ifndef GPSCONTROLLER_H
#define GPSCONTROLLER_H

#include <thread>
#include <fstream>
#include "igpssomeipclientlistener.h"
#include "gpssomeipclient.h"

class GpsController : public IGpsSomeIpClientListener
{
public:
	GpsController(GpsSomeIpClient* p_client, const std::string& p_logFile);
	void onDataReceived(double p_lat, double p_lon,int p_hour,int p_minute,int p_second,int p_day,int p_month,int p_year,int p_speed) override;
	void onFixStatusChanged(bool p_valid) override;
	void run();
	
private:
	void task();
	GpsSomeIpClient* m_client;
	std::ofstream m_logFile;
	
};

#endif // GPSCONTROLLER_H
