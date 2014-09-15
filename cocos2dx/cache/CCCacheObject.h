#ifndef __CCCACHEOBJECT_H__
#define __CCCACHEOBJECT_H__

#include "CCObject.h"

NS_CC_BEGIN



class CCCacheObject:public CCObject
{
public:
	
    CCCacheObject(void)
	:m_drawTime(0)
	{
		
	}
    
	void updateLastDrawTime(float delta)
	{
		m_drawTime+=delta;
	}
    
	float getLastDrawTime()
	{
		return m_drawTime;
	}
    
protected:
	float m_drawTime;
};

NS_CC_END

#endif //__CCCACHEOBJECT_H__
