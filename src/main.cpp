#include "gpsdconnector.h"
#include "gpsstorage.h"
#include "gpsservice.h"
#include "gpssocketreader.h"
#include <unistd.h>
#include <iostream>
int main() {

	GpsSocketReader l_socket;
	GpsStorage l_storage;
	GpsdConnector l_gpsd(&l_storage);
	l_socket.setListener(&l_gpsd);
	l_socket.init();
	try{
		l_socket.task();
	}
	catch(int e){
		std::cout << "An exception occurred. Exception Nr. " << e << '\n';
	}


	//GpsService l_service(&l_storage);
	//l_service.init();
	//l_service.start();
	return 0;
}
