#include "gpsservice.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <assert.h>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421

struct tCoordinates {
	double lat;
	double lon;
};
struct tTime {
	int hour,minute,second;
};

GpsService::GpsService(GpsStorage *p_storage)
	: m_storage(p_storage)
{
	assert(m_storage != nullptr);
}

void GpsService::init()
{
	app = vsomeip::runtime::get()->create_application("World");
	app->init();
	app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, std::bind(&GpsService::getCoordinates, this, std::placeholders::_1));
	app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
}

void GpsService::start()
{
	app->start();
}

void GpsService::getCoordinates(const std::shared_ptr<vsomeip_v3::message> &_request)
{
	std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
	
	// Create response
	std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
	its_payload = vsomeip::runtime::get()->create_payload();
	
	
	tCoordinates l_coordinates;
	l_coordinates.lat = m_storage->getLatitude();
	l_coordinates.lon = m_storage->getLongitude();
	
	its_payload->set_data((vsomeip_v3::byte_t*) &l_coordinates, sizeof(l_coordinates));
	its_response->set_payload(its_payload);
	app->send(its_response);
}
void GpsService::getTime(const std::shared_ptr<vsomeip_v3::message> &_request){
	std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
	
	// Create response
	std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
	its_payload = vsomeip::runtime::get()->create_payload();
	
	
	tTime l_time;
	l_time.hour = m_storage->getHour();
	l_time.minute = m_storage->getMinute();
	l_time.second = m_storage->getSecond();

	its_payload->set_data((vsomeip_v3::byte_t*) &l_time, sizeof(l_time));
	its_response->set_payload(its_payload);
	app->send(its_response);
}
