#ifndef GPSDCONNECTOR_H
#define GPSDCONNECTOR_H

#include "gpssocketreader.h"
#include "gpsstorage.h"
#include "nmeaparse/nmea.h"
#include "igpssocketreaderlistener.h"
#include <iostream>
#include "bbox.h"
using namespace bbox;

class GpsdConnector : public IGpsSocketReaderListener
{
public:
	GpsdConnector(GpsStorage* p_storage);
	black_box BB;
	void init();
	void onSentenceReceived(const std::string &p_sentence) override;
	
private:
	void task();
	
	nmea::NMEAParser parser;
	nmea::GPSService gps;
	GpsSocketReader* m_socket;
	GpsStorage* m_storage;
	
};

#endif // GPSDCONNECTOR_H
