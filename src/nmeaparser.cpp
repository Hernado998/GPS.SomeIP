#include "nmeaparser.h"

NmeaParser::NmeaParser()
{
}

bool NmeaParser::init()
{
	int l_res = nmea_parser_init(&m_parser);
	return (l_res != 0);
}

void NmeaParser::deinit()
{
	nmea_parser_destroy(&m_parser);
}

bool NmeaParser::parseMessage(const std::string &p_message, tNmeaMessage &p_parsing)
{
	nmeaINFO l_info;
	nmea_zero_INFO(&l_info);
	std::string l_message = p_message;
	l_message += "\r\n";
	int l_res = nmea_parse(&m_parser, l_message.c_str(), l_message.size(), &l_info);
	if (l_res == 0)
	{
		return false;
	}
	
	assert(l_info.sig <= 3);
	p_parsing.type = (eNmeaMessageType) l_info.sig;
	p_parsing.position.lat = l_info.lat;
	p_parsing.position.lon = l_info.lon;
}
