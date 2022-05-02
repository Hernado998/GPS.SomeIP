#include "gpsstorage.h"

GpsStorage::GpsStorage()
	: m_latitude(0),
	  m_longitude(0),
	  m_hour(0),
	  m_minute(0),
	  m_second(0),
	  m_day(0),
	  m_fix(false)
{
	
}

void GpsStorage::setData(double p_latitude, double p_longitude,int p_hour,int p_minute, int p_second, int p_day, int p_month, int p_year)
{
	m_latitude = p_latitude;
	m_longitude = p_longitude;
	m_hour = p_hour;
	m_minute = p_minute;
	m_second = p_second;
	m_day=p_day;
	m_month=p_month;
	m_year=p_year;
}



void GpsStorage::setFix(bool p_valid)
{
	m_fix = p_valid;
}

double GpsStorage::getLatitude()
{
	return m_latitude;
}

bool GpsStorage::getFix()
{
	return m_fix;
}

double GpsStorage::getLongitude()
{
	return m_longitude;
}

int GpsStorage::getHour(){
	return m_hour;
}

int GpsStorage::getMinute(){
	return m_minute;
}

int GpsStorage::getSecond(){
	return m_second;
}
int GpsStorage::getDay(){
	return m_day;
}
int GpsStorage::getMonth(){
	return m_month;
}
int GpsStorage::getYear(){
	return m_year;
}
