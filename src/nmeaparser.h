#ifndef NMEAPARSER_H
#define NMEAPARSER_H

#include <string>

struct tNmeaPos {
	double  lat;
    double  lon;
};

enum eNmeaMessageType{
	NMEA_MSG_INVALID,
	NMEA_MSG_FIX,
	NMEA_MSG_DIFFERENTIAL,
	NMEA_MSG_SENSITIVE
};

struct tNmeaMessage {
	eNmeaMessageType type;
	tNmeaPos position;
};

class NmeaParser
{
public:
	NmeaParser();
	bool init();
	void deinit();
	bool parseMessage(const std::string& p_message, tNmeaMessage& p_parsing);
	
private:
	nmeaPARSER m_parser;
	
};

#endif // NMEAPARSER_H
