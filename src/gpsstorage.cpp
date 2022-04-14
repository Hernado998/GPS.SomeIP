#include "gpsstorage.h"

GpsStorage::GpsStorage()
	: m_latitude(0),
	  m_longitude(0),
	  m_hour(0),
	  m_minute(0),
	  m_second(0),
	  m_fix(false)
{
	
}

void GpsStorage::setCoordinates(double p_latitude, double p_longitude)
{
	m_latitude = p_latitude;
	m_longitude = p_longitude;
}

void GpsStorage::setTime(int p_hour,int p_minute,int p_second){
	m_hour = p_hour;
	m_minute = p_minute;
	m_second = p_second;
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
