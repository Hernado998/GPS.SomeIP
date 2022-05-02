#ifndef IGPSSTORAGELISTENER_H
#define IGPSSTORAGELISTENER_H

class IGpsStorageListener 
{
public:
	virtual void onDataChanged(double p_latitude, double p_longitude,int p_hour,int p_minute,int p_seconde,int p_day,int p_month,int p_year) = 0;
	virtual void onFixReceived() = 0;
	virtual void onFixLost() = 0;
};

#endif // IGPSSTORAGELISTENER_H
