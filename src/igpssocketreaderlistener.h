#ifndef IGPSSOCKETREADERLISTENER_H
#define IGPSSOCKETREADERLISTENER_H

class IGpsSocketReaderListener 
{
public:
	virtual void onSentenceReceived(const std::string& p_sentence) = 0;
};

#endif // IGPSSOCKETREADERLISTENER_H
