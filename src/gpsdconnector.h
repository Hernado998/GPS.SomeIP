#ifndef GPSDCONNECTOR_H
#define GPSDCONNECTOR_H

#include "gpssocketreader.h"
#include "gpsstorage.h"
#include "nmeaparse/nmea.h"
#include "igpssocketreaderlistener.h"



class GpsdConnector : public IGpsSocketReaderListener
{
public:
	GpsdConnector(GpsStorage* p_storage);
	
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
