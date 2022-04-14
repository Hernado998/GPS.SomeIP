#ifndef GPSSTORAGE_H
#define GPSSTORAGE_H

class GpsStorage
{
public:
	GpsStorage();
	
public:
	void setCoordinates(double p_latitude, double p_longitude);
	void setTime(int p_hour,int p_minute, int second);
	void setFix(bool p_valid);
	double getLatitude();
	bool getFix();
	double getLongitude();
	int getHour(); int getMinute();int getSecond();
	
private:
	double m_latitude;
	double m_longitude;
	int m_hour,m_minute,m_second;
	bool m_fix;
};

#endif // GPSSTORAGE_H
