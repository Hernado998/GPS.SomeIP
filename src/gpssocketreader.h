#ifndef GPSSOCKET_H
#define GPSSOCKET_H

#include <string>
#include "gps.h"
#include "igpssocketreaderlistener.h"

class GpsSocketReader
{
public:
	GpsSocketReader();
	
	void init();
	void run();
	void setListener(IGpsSocketReaderListener* p_listener);
	
	
private:
	bool connect();
	void task();
	std::string readLine();
	std::string internalRead();
	struct gps_data_t gpsdata;
	IGpsSocketReaderListener* m_listener;
	
};

#endif // GPSSOCKET_H
