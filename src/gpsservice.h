#ifndef GPSSERVICE_H
#define GPSSERVICE_H

#include <memory>
#include <vsomeip/vsomeip.hpp>
#include "gpsstorage.h"

class GpsService
{
public:
	GpsService(GpsStorage* p_storage);
	
	void init();
	void start();
	
private:
	void getCoordinates(const std::shared_ptr<vsomeip::message> &_request);
	void getTime(const std::shared_ptr<vsomeip::message> &_request);
	std::shared_ptr<vsomeip::application> app;
	GpsStorage* m_storage;
	
};

#endif // GPSSERVICE_H
