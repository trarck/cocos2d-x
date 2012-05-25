//
//  cocos2d_manual_bindings.hpp
//  GDKDemoApp
//
//  Created by Rolando Abarca on 5/22/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef GDKDemoApp_cocos2d_manual_bindings_hpp
#define GDKDemoApp_cocos2d_manual_bindings_hpp

#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

// the object that will be scheduled
class JSScheduleCallback : public CCObject
{
public:
	JSScheduleCallback() : CCObject(), callback(NULL), thisObject(NULL) {};
	virtual ~JSScheduleCallback();
	JSObject* callback;
	JSObject* thisObject;
	int id;

	void timerCallBack(ccTime dt);
};

struct cmp_objects
{
	bool operator()(const int &a, const int &b)
	{
		return (unsigned long)a < (unsigned long)b;
	}
};

typedef std::map<int, JSScheduleCallback *> callback_map;

class S_CCScheduler
{
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsschedule(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunschedule(JSContext *cx, uint32_t argc, jsval *vp);
};

#endif
