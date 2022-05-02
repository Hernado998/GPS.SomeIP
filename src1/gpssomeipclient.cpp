#include "gpssomeipclient.h"
#include <thread>
#include <assert.h>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421

GpsSomeIpClient::GpsSomeIpClient()
	: m_listener(nullptr)
{
}

void GpsSomeIpClient::run()
{
	assert(m_listener != nullptr);
	app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, std::bind(&GpsSomeIpClient::onMessageReceived, this, std::placeholders::_1));
	app->start();
}

void GpsSomeIpClient::init()
{
	app = vsomeip::runtime::get()->create_application("Hello");
    app->init();
	app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID,
									   std::bind(&GpsSomeIpClient::onAvailability, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void GpsSomeIpClient::setListener(IGpsSomeIpClientListener *p_listener)
{
	m_listener = p_listener;
}

void GpsSomeIpClient::requestData()
{
	if (m_serviceAvailable == false)
	{
		return;
	}
	
	std::shared_ptr< vsomeip::message > request;
	request = vsomeip::runtime::get()->create_request();
	request->set_service(SAMPLE_SERVICE_ID);
	request->set_instance(SAMPLE_INSTANCE_ID);
	request->set_method(SAMPLE_METHOD_ID);
	
//	std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
//	its_payload->set_data(its_payload_data);
//	request->set_payload(its_payload);
	app->send(request);
}

void GpsSomeIpClient::onMessageReceived(const std::shared_ptr<vsomeip::message> &_response)
{
	std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
  
	tData* l_data = (tData*) its_payload->get_data();
	m_listener->onDataReceived(l_data->lat, l_data->lon,l_data->hour,l_data->minute,l_data->second,l_data->day,l_data->month,l_data->year,l_data->speed);
}

void GpsSomeIpClient::onAvailability(vsomeip_v3::service_t _service, vsomeip_v3::instance_t _instance, bool _is_available)
{
	std::cout << "Service ["
            << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
            << "] is " << (_is_available ? "available." : "NOT available.")  << std::endl;
	
	if(_is_available) condition.notify_one();
	
	
	m_serviceAvailable = _is_available;
	cout<<m_serviceAvailable<<endl;
}
