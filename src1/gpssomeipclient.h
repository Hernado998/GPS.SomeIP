#ifndef GPSCLIENT_H
#define GPSCLIENT_H

#include <vsomeip/vsomeip.hpp>
#include <condition_variable>
#include "igpssomeipclientlistener.h"
#include <iostream>
#include <iomanip>

using namespace std;
class GpsSomeIpClient
{
public:
	GpsSomeIpClient();
	
	void run();
	void init();
	void setListener(IGpsSomeIpClientListener* p_listener);
	void requestCoordinates();
	
private:
	struct tData {
		double lat;
		double lon;
		int hour;
		int minute;
		int second;
	};
	
	void onMessageReceived(const std::shared_ptr<vsomeip::message> &_response);
	void onAvailability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);
	
	std::shared_ptr< vsomeip::application > app;
	std::mutex mutex;
	std::condition_variable condition;
	
	bool m_serviceAvailable;
	IGpsSomeIpClientListener* m_listener;
};

#endif // GPSCLIENT_H
