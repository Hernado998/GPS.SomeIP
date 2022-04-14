#ifndef IGPSSOMEIPCLIENTLISTENER_H
#define IGPSSOMEIPCLIENTLISTENER_H

class IGpsSomeIpClientListener
{
public:
	IGpsSomeIpClientListener() = default;
	virtual ~IGpsSomeIpClientListener() {}
	
	virtual void onCoordinatesReceived(double p_lat, double p_lon) = 0;
	virtual void onFixStatusChanged(bool p_valid) = 0;
};

#endif // IGPSSOMEIPCLIENTLISTENER_H
