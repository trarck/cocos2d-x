#ifndef __CCCACHEDICTIONARY_H__
#define __CCCACHEDICTIONARY_H__

#include "cocoa/CCDictionary.h"

NS_CC_BEGIN

#define kCCCacheDictionaryDefaultRemoveCount 10

class CC_DLL CCCacheDictionary:public CCDictionary
{

public:
	
	CCCacheDictionary();
	
	// ~CCCacheDictionary();
	
	void gc(float delta,unsigned int removeCount);
	
	void setGCTime(float gcTime)
	{
		m_gcTime=gcTime;
	}
	
public:
	
	inline void setGcTime(float gcTime)
	{
	    m_gcTime = gcTime;
	}

	inline float getGcTime()
	{
	    return m_gcTime;
	}

	inline void setInterval(float interval)
	{
	    m_interval = interval;
	}

	inline float getInterval()
	{
	    return m_interval;
	}

	inline void setElapsed(float elapsed)
	{
	    m_elapsed = elapsed;
	}

	inline float getElapsed()
	{
	    return m_elapsed;
	}
	
protected:
	//0x14 CCDictElement* m_pElements
	//0x18 CCDictType m_eDictType
	//gc time
	float m_gcTime;			//0x1C
	//min gc interval
	float m_interval;		//0x20
	//update elapsed
	float m_elapsed;		//0x24 
	
	
	

};


NS_CC_END

#endif //__CCCACHEDICTIONARY_H__
