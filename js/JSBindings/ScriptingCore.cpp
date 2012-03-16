//
//  ScriptingCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class S_CCPoint : public CCPoint
{
	JSObject *m_obj;
	static JSClass*  jsClassDef;
	static JSObject* jsClassObj;
public:
	enum {
		kX = 1,
		kY
	};
	
	
	bool initWithContext(JSContext *cx, JSObject *obj, uint32_t argc, jsval *vp)
	{
		double arg0 = 0.0f;
		double arg1 = 0.0f;
		if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "/dd", &arg0, &arg1) == JS_TRUE) {
			this->initWith(arg0, arg1);
			return true;
		}
		return false;
		
	};
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCPoint *cobj = (S_CCPoint *)JS_GetPrivate(obj);
		if (!cobj) return JS_FALSE;
		
		switch(propId) {
			case kX:
				JS_NewNumberValue(cx, cobj->x, val);
				return JS_TRUE;
				break;
			case kY:
				JS_NewNumberValue(cx, cobj->y, val);
				return JS_TRUE;
				break;
			default:
				break;
		}
		
		return JS_FALSE;
	};
	
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCPoint *cobj = (S_CCPoint *)JS_GetPrivate(obj);
		if (!cobj) return JS_FALSE;
		
		double tmpDbl;
		JSBool ret = JS_FALSE;
		switch(propId) {
			case kX:
				JS_ValueToNumber(cx, *val, &tmpDbl);
				cobj->x = tmpDbl;
				ret = JS_TRUE;
				break;
			case kY:
				JS_ValueToNumber(cx, *val, &tmpDbl);
				cobj->y = tmpDbl;
				ret = JS_TRUE;
				break;
			default:
				break;
		}
		return ret;
		
	};
	
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
	{
		jsClassDef = (JSClass *)calloc(1, sizeof(JSClass));
		jsClassDef->name = name;
		jsClassDef->addProperty = JS_PropertyStub;
		jsClassDef->delProperty = JS_PropertyStub;
		jsClassDef->getProperty = JS_PropertyStub;
		jsClassDef->setProperty = JS_StrictPropertyStub;
		jsClassDef->enumerate = JS_EnumerateStub;
		jsClassDef->resolve = JS_ResolveStub;
		jsClassDef->convert = JS_ConvertStub;
		jsClassDef->finalize = jsFinalize;
		jsClassDef->flags = JSCLASS_HAS_PRIVATE;
		
		static JSPropertySpec properties[] = {
			{"x", kX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet},
			{"y", kY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet}
		};
		
		
		jsClassObj = JS_InitClass(cx,globalObj,NULL,jsClassDef,S_CCPoint::jsConstructor,0,properties,NULL,NULL,NULL);
	};
	
	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		CCLog("js finalize object: %p", obj);
	};
	
	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCPoint::jsClassDef, S_CCPoint::jsClassObj, NULL);
		S_CCPoint *cobj = new S_CCPoint();
		if (cobj->initWithContext(cx, obj, argc, vp)) {
			JS_SetPrivate(obj, cobj);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
			return JS_TRUE;
		}
		delete cobj;
		return JS_FALSE;
	};
	
};
JSClass*  S_CCPoint::jsClassDef = NULL;
JSObject* S_CCPoint::jsClassObj = NULL;

class S_CCSize : public CCSize
{
	JSObject *m_obj;
	static JSClass*  jsClassDef;
	static JSObject* jsClassObj;
public:
	enum {
		kWidth = 1,
		kHeight
	};
	
	
	bool initWithContext(JSContext *cx, JSObject *obj, uint32_t argc, jsval *vp)
	{
		double arg0 = 0.0f;
		double arg1 = 0.0f;
		if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "/dd", &arg0, &arg1) == JS_TRUE) {
			this->initWith(arg0, arg1);
			return true;
		}
		return false;
		
	};
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCSize *cobj = (S_CCSize *)JS_GetPrivate(obj);
		if (!cobj) return JS_FALSE;
		
		switch(propId) {
			case kWidth:
				JS_NewNumberValue(cx, cobj->width, val);
				return JS_TRUE;
				break;
			case kHeight:
				JS_NewNumberValue(cx, cobj->height, val);
				return JS_TRUE;
				break;
			default:
				break;
		}
		
		return JS_FALSE;
	};
	
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCSize *cobj = (S_CCSize *)JS_GetPrivate(obj);
		if (!cobj) return JS_FALSE;
		
		double tmpDbl;
		JSBool ret = JS_FALSE;
		switch(propId) {
			case kWidth:
				JS_ValueToNumber(cx, *val, &tmpDbl);
				cobj->width = tmpDbl;
				ret = JS_TRUE;
				break;
			case kHeight:
				JS_ValueToNumber(cx, *val, &tmpDbl);
				cobj->height = tmpDbl;
				ret = JS_TRUE;
				break;
			default:
				break;
		}
		return ret;
		
	};
	
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
	{
		jsClassDef = (JSClass *)calloc(1, sizeof(JSClass));
		jsClassDef->name = name;
		jsClassDef->addProperty = JS_PropertyStub;
		jsClassDef->delProperty = JS_PropertyStub;
		jsClassDef->getProperty = JS_PropertyStub;
		jsClassDef->setProperty = JS_StrictPropertyStub;
		jsClassDef->enumerate = JS_EnumerateStub;
		jsClassDef->resolve = JS_ResolveStub;
		jsClassDef->convert = JS_ConvertStub;
		jsClassDef->finalize = jsFinalize;
		jsClassDef->flags = JSCLASS_HAS_PRIVATE;
		
		static JSPropertySpec properties[] = {
			{"width", kWidth, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet},
			{"height", kHeight, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet}
		};
		
		
		jsClassObj = JS_InitClass(cx,globalObj,NULL,jsClassDef,S_CCSize::jsConstructor,0,properties,NULL,NULL,NULL);
	};
	
	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		CCLog("js finalize object: %p", obj);
	};
	
	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCSize::jsClassDef, S_CCSize::jsClassObj, NULL);
		S_CCSize *cobj = new S_CCSize();
		if (cobj->initWithContext(cx, obj, argc, vp)) {
			JS_SetPrivate(obj, cobj);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
			return JS_TRUE;
		}
		delete cobj;
		return JS_FALSE;
	};
	
};
JSClass*  S_CCSize::jsClassDef = NULL;
JSObject* S_CCSize::jsClassObj = NULL;

class S_CCRect : public CCRect
{
	JSObject *m_obj;
	static JSClass*  jsClassDef;
	static JSObject* jsClassObj;
public:
	enum {
		kOrigin = 1,
		kSize
	};
	
	
	bool initWithContext(JSContext *cx, JSObject *obj, uint32_t argc, jsval *vp)
	{
		double arg0 = 0.0f;
		double arg1 = 0.0f;
		double arg2 = 0.0f;
		double arg3 = 0.0f;
		if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "/dddd", &arg0, &arg1, &arg2, &arg3) == JS_TRUE) {
			this->initWith(arg0, arg1, arg2, arg3);
			return true;
		}
		return false;
		
	};
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCRect *cobj = (S_CCRect *)JS_GetPrivate(obj);
		if (!cobj) return JS_FALSE;
		
		switch(propId) {
			case kOrigin:
				return JS_TRUE;
				break;
			case kSize:
				return JS_TRUE;
				break;
			default:
				break;
		}
		
		return JS_FALSE;
	};
	
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCRect *cobj = (S_CCRect *)JS_GetPrivate(obj);
		if (!cobj) return JS_FALSE;
		
		double tmpDbl;
		JSBool ret = JS_FALSE;
		switch(propId) {
			case kOrigin:
				ret = JS_TRUE;
				break;
			case kSize:
				ret = JS_TRUE;
				break;
			default:
				break;
		}
		return ret;
		
	};
	
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
	{
		jsClassDef = (JSClass *)calloc(1, sizeof(JSClass));
		jsClassDef->name = name;
		jsClassDef->addProperty = JS_PropertyStub;
		jsClassDef->delProperty = JS_PropertyStub;
		jsClassDef->getProperty = JS_PropertyStub;
		jsClassDef->setProperty = JS_StrictPropertyStub;
		jsClassDef->enumerate = JS_EnumerateStub;
		jsClassDef->resolve = JS_ResolveStub;
		jsClassDef->convert = JS_ConvertStub;
		jsClassDef->finalize = jsFinalize;
		jsClassDef->flags = JSCLASS_HAS_PRIVATE;
		
		static JSPropertySpec properties[] = {
			{"origin", kOrigin, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet},
			{"size", kSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet}
		};
		
		
		jsClassObj = JS_InitClass(cx,globalObj,NULL,jsClassDef,S_CCRect::jsConstructor,0,properties,NULL,NULL,NULL);
	};
	
	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		CCLog("js finalize object: %p", obj);
	};
	
	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCRect::jsClassDef, S_CCRect::jsClassObj, NULL);
		S_CCRect *cobj = new S_CCRect();
		if (cobj->initWithContext(cx, obj, argc, vp)) {
			JS_SetPrivate(obj, cobj);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
			return JS_TRUE;
		}
		delete cobj;
		return JS_FALSE;
	};
	
};
JSClass*  S_CCRect::jsClassDef = NULL;
JSObject* S_CCRect::jsClassObj = NULL;

static JSClass global_class = {
	"global", JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
	JSCLASS_NO_OPTIONAL_MEMBERS
};

ScriptingCore::ScriptingCore()
{
	this->rt = JS_NewRuntime(8 * 1024 * 1024);
	this->cx = JS_NewContext(rt, 8192);
	JS_SetOptions(this->cx, JSOPTION_VAROBJFIX);
	JS_SetVersion(this->cx, JSVERSION_LATEST);
	JS_SetErrorReporter(this->cx, ScriptingCore::reportError);
	global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
	if (!JS_InitStandardClasses(cx, global)) {
		CCLog("js error");
	}
	// create the cocos namespace
	JSObject *cocos = JS_NewObject(cx, NULL, NULL, NULL);
	jsval cocosVal = OBJECT_TO_JSVAL(cocos);
	JS_SetProperty(cx, global, "cocos", &cocosVal);

	// register the internal classes
	S_CCPoint::jsCreateClass(this->cx, cocos, "Point");
	S_CCSize::jsCreateClass(this->cx, cocos, "Size");
	S_CCRect::jsCreateClass(this->cx, cocos, "Rect");

	// register some global functions
	JS_DefineFunction(this->cx, cocos, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

void ScriptingCore::evalString(const char *string)
{
	jsval rval;
	JSString *str;
	JSBool ok;
	const char *filename = "noname";
	uint32_t lineno = 0;
	ok = JS_EvaluateScript(cx, global, string, strlen(string), filename, lineno, &rval);
	if (JSVAL_IS_NULL(rval) || rval == JSVAL_FALSE) {
		CCLog("error evaluating script:\n%s", string);
	}
	str = JS_ValueToString(cx, rval);
	printf("js result: %s\n", JS_EncodeString(cx, str));
}

void ScriptingCore::runScript(const char *path)
{
	const char *realPath = CCFileUtils::fullPathFromRelativePath(path);
	unsigned char *content = NULL;
	size_t contentSize = CCFileUtils::ccLoadFileIntoMemory(realPath, &content);
	if (contentSize) {
		JSBool ok;
		jsval rval;
		ok = JS_EvaluateScript(this->cx, this->global, (char *)content, contentSize, path, 1, &rval);
		if (JSVAL_IS_NULL(rval) || rval == JSVAL_FALSE) {
			CCLog("error evaluating script:\n%s", content);
		}
		free(content);
	}
}

ScriptingCore::~ScriptingCore()
{
	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
}
