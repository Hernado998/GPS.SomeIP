#ifndef IGPSSOMEIPCLIENTLISTENER_H
#define IGPSSOMEIPCLIENTLISTENER_H

class IGpsSomeIpClientListener
{
public:
	IGpsSomeIpClientListener() = default;
	virtual ~IGpsSomeIpClientListener() {}
	
	virtual void onDataReceived(double p_lat, double p_lon,int p_hour,int p_minute,int p_second,int p_day,int p_month,int p_year,int p_speed) = 0;
	virtual void onFixStatusChanged(bool p_valid) = 0;
};

#endif // IGPSSOMEIPCLIENTLISTENER_H
