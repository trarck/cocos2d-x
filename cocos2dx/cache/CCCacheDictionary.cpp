#include "CCCacheDictionary.h"
#include "CCCacheObject.h"

NS_CC_BEGIN
	
CCCacheDictionary::CCCacheDictionary()
:m_gcTime(10.0f)
,m_interval(2.0f)
,m_elapsed(0.0f)
{
	
}

void CCCacheDictionary::gc(float delta,unsigned int removeCount)
{
	if(m_pElements && HASH_COUNT(m_pElements)){
		
		m_elapsed+=delta;
		
		if(m_elapsed > m_interval){
			
			list<CCDictElement*> elementToRemove;
			CCDictElement *pElement, *tmp;
			
			CCCacheObject* cacheObject=NULL;
			float lastDrawTime=0.0f;
			int i=0;
			
	        HASH_ITER(hh, m_pElements, pElement, tmp) 
	        {
				cacheObject=(CCCacheObject*)pElement->m_pObject;
				if(cacheObject){
					cacheObject->updateLastDrawTime(m_elapsed);
					lastDrawTime=cacheObject->getLastDrawTime();
				
					if(lastDrawTime > m_gcTime){
						elementToRemove.push_back(pElement);
						if(++i>removeCount){
							break;
						}
					}
				}
	        }
			
	        for (list<CCDictElement*>::iterator iter = elementToRemove.begin(); iter != elementToRemove.end(); ++iter)
	        {
	            removeObjectForElememt(*iter);
	        }
		}
	}
}

NS_CC_END