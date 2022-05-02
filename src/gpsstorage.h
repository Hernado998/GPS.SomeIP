#ifndef GPSSTORAGE_H
#define GPSSTORAGE_H

class GpsStorage
{
public:
	GpsStorage();
	
public:
	void setData(double p_latitude, double p_longitude,int p_hour,int p_minute, int p_second,int p_day,int p_month,int p_year,int p_speed);
	void setFix(bool p_valid);
	double getLatitude();
	bool getFix();
	double getLongitude();
	int getHour(); int getMinute();int getSecond();
	int getDay();int getMonth();int getYear();
	int getSpeed();
	
private:
	double m_latitude;
	double m_longitude;
	int m_hour,m_minute,m_second;
	int m_day, m_month, m_year;
	bool m_fix;
	int m_speed;
};

#endif // GPSSTORAGE_H
