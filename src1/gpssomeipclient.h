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
	
	void changeID(int id, shared_ptr< vsomeip::message > request);

	void run();
	void init();
	void setListener(IGpsSomeIpClientListener* p_listener);
	void requestCoordinates();
	void requestTime();
	
private:
	struct tCoordinates {
		double lat;
		double lon;
	};
	struct tTime {
		int hour;
		int minute;
		int seconde;
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
