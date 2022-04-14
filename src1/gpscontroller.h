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
	void onCoordinatesReceived(double p_lat, double p_lon) override;
	void onFixStatusChanged(bool p_valid) override;
	void run();
	
private:
	void task();
	GpsSomeIpClient* m_client;
	std::ofstream m_logFile;
	
};

#endif // GPSCONTROLLER_H
