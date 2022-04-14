#ifndef IGPSSTORAGELISTENER_H
#define IGPSSTORAGELISTENER_H

class IGpsStorageListener 
{
public:
	virtual void onDataChanged(double p_latitude, double p_longitude) = 0;
	virtual void onFixReceived() = 0;
	virtual void onFixLost() = 0;
};

#endif // IGPSSTORAGELISTENER_H
