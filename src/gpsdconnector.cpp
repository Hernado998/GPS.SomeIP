#include "gpsdconnector.h"
#include <iostream>
#include <assert.h>

GpsdConnector::GpsdConnector(GpsStorage* p_storage)
	: m_storage(p_storage),
	  gps(parser)
{
	assert(m_storage != nullptr);
}

void GpsdConnector::init()
{
	gps.onUpdate += [&](){
		m_storage->setTime(gps.fix.timestamp.hour,gps.fix.timestamp.min,gps.fix.timestamp.sec);
		std::cout << "Setting time: " << gps.fix.timestamp.hour << ":" << gps.fix.timestamp.min << ":" << gps.fix.timestamp.sec << std::endl;
		m_storage->setCoordinates(gps.fix.latitude, gps.fix.longitude);
		std::cout << "Setting coordinates: " << gps.fix.latitude << ", " << gps.fix.longitude << std::endl;
	};
	gps.onLockStateChanged += [&](bool p_valid){
		m_storage->setFix(p_valid);
		if (p_valid)
		{
			std::cout << "Fix received" << std::endl;
		}
		else
		{
			std::cout << "Fix lost" << std::endl;
		}
	};
}

void GpsdConnector::onSentenceReceived(const std::string &p_sentence)
{
	parser.readLine(p_sentence);
}
