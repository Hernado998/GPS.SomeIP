#include "gpscontroller.h"
#include "gpssomeipclient.h"
#include <bits/stdc++.h>

int main(int argc, char** argv)
{
	std::string l_logFile("/tmp/gps_pos.log");
	std::this_thread::sleep_for (std::chrono::milliseconds(1500));
	int i;
	for(i = 1; i < argc; i++)
	{

		printf("%d: %s", i, argv[i]);
	}
	
	GpsSomeIpClient l_client;
    GpsController l_controller(&l_client, l_logFile);
	l_client.setListener(&l_controller);
	l_client.init();
	std::this_thread::sleep_for (std::chrono::milliseconds(1500));
	l_controller.run();
	l_client.run(); // blocks
}
