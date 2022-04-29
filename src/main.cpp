#include "gpsdconnector.h"
#include "gpsstorage.h"
#include "gpsservice.h"
#include "gpssocketreader.h"
#include <unistd.h>

int main() {

	GpsSocketReader l_socket;
	GpsStorage l_storage;
	GpsdConnector l_gpsd(&l_storage);
	l_socket.setListener(&l_gpsd);
	l_gpsd.init();
	l_socket.init();
	l_socket.task();
	return 0;
	//GpsService l_service(&l_storage);
	//l_service.init();
	//l_service.start();
}
