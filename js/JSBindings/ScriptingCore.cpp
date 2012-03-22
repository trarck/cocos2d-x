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

typedef struct {
	uint32_t flags;
	void* data;
} pointerShell_t;

typedef enum {
	kPointerTemporary = 1
} pointerShellFlags;

#define JSGET_PTRSHELL(type, cobj, jsobj) do { \
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(jsobj); \
	if (pt) { \
		cobj = (type *)pt->data; \
	} else { \
		cobj = NULL; \
	} \
} while (0)

class S_CCPoint : public CCPoint
{
	JSObject *m_obj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;
	
	enum {
		kX = 1,
		kY
	};
	
	S_CCPoint(JSObject *obj) : CCPoint(), m_obj(obj) {};
	
	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
		S_CCPoint *cobj = new S_CCPoint(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;		JS_SetPrivate(obj, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	};
	
	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCPoint *)pt->data;
			JS_free(cx, pt);
		}
	};
	
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCPoint *cobj; JSGET_PTRSHELL(S_CCPoint, cobj, obj);
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
		S_CCPoint *cobj; JSGET_PTRSHELL(S_CCPoint, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
			case kX:
				do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->x = tmp; } while (0);
				ret = JS_TRUE;
				break;
			case kY:
				do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->y = tmp; } while (0);
				ret = JS_TRUE;
				break;
			default:
				break;
		}
		return ret;
	};
	
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
	{
		jsClass = (JSClass *)calloc(1, sizeof(JSClass));
		jsClass->name = name;
		jsClass->addProperty = JS_PropertyStub;
		jsClass->delProperty = JS_PropertyStub;
		jsClass->getProperty = JS_PropertyStub;
		jsClass->setProperty = JS_StrictPropertyStub;
		jsClass->enumerate = JS_EnumerateStub;
		jsClass->resolve = JS_ResolveStub;
		jsClass->convert = JS_ConvertStub;
		jsClass->finalize = jsFinalize;
		jsClass->flags = JSCLASS_HAS_PRIVATE;
		static JSPropertySpec properties[] = {
			{"x", kX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet},
			{"y", kY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet}
		};
		
		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCPoint::jsConstructor,0,properties,NULL,NULL,NULL);
	};
};
JSClass* S_CCPoint::jsClass = NULL;
JSObject* S_CCPoint::jsObject = NULL;
class S_CCSize : public CCSize
{
	JSObject *m_obj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;
	
	enum {
		kWidth = 1,
		kHeight
	};
	
	S_CCSize(JSObject *obj) : CCSize(), m_obj(obj) {};
	
	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
		S_CCSize *cobj = new S_CCSize(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;		JS_SetPrivate(obj, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	};
	
	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSize *)pt->data;
			JS_free(cx, pt);
		}
	};
	
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCSize *cobj; JSGET_PTRSHELL(S_CCSize, cobj, obj);
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
		S_CCSize *cobj; JSGET_PTRSHELL(S_CCSize, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
			case kWidth:
				do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->width = tmp; } while (0);
				ret = JS_TRUE;
				break;
			case kHeight:
				do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->height = tmp; } while (0);
				ret = JS_TRUE;
				break;
			default:
				break;
		}
		return ret;
	};
	
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
	{
		jsClass = (JSClass *)calloc(1, sizeof(JSClass));
		jsClass->name = name;
		jsClass->addProperty = JS_PropertyStub;
		jsClass->delProperty = JS_PropertyStub;
		jsClass->getProperty = JS_PropertyStub;
		jsClass->setProperty = JS_StrictPropertyStub;
		jsClass->enumerate = JS_EnumerateStub;
		jsClass->resolve = JS_ResolveStub;
		jsClass->convert = JS_ConvertStub;
		jsClass->finalize = jsFinalize;
		jsClass->flags = JSCLASS_HAS_PRIVATE;
		static JSPropertySpec properties[] = {
			{"width", kWidth, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet},
			{"height", kHeight, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet}
		};
		
		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCSize::jsConstructor,0,properties,NULL,NULL,NULL);
	};
};
JSClass* S_CCSize::jsClass = NULL;
JSObject* S_CCSize::jsObject = NULL;
class S_CCRect : public CCRect
{
	JSObject *m_obj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;
	
	enum {
		kOrigin = 1,
		kSize
	};
	
	S_CCRect(JSObject *obj) : CCRect(), m_obj(obj) {};
	
	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
		S_CCRect *cobj = new S_CCRect(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;		JS_SetPrivate(obj, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	};
	
	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCRect *)pt->data;
			JS_free(cx, pt);
		}
	};
	
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCRect *cobj; JSGET_PTRSHELL(S_CCRect, cobj, obj);
		if (!cobj) return JS_FALSE;
		switch(propId) {
			case kOrigin:
				do {
					JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
					pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
					pt->flags = kPointerTemporary;
					pt->data = &cobj->origin;
					JS_SetPrivate(tmp, pt);
					JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
				} while (0);
				return JS_TRUE;
				break;
			case kSize:
				do {
					JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
					pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
					pt->flags = kPointerTemporary;
					pt->data = &cobj->size;
					JS_SetPrivate(tmp, pt);
					JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
				} while (0);
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
		S_CCRect *cobj; JSGET_PTRSHELL(S_CCRect, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
			case kOrigin:
				do {
					S_CCPoint* tmp; JSGET_PTRSHELL(S_CCPoint, tmp, JSVAL_TO_OBJECT(*val));
					if (tmp) { cobj->origin = *tmp; }
				} while (0);
				ret = JS_TRUE;
				break;
			case kSize:
				do {
					S_CCSize* tmp; JSGET_PTRSHELL(S_CCSize, tmp, JSVAL_TO_OBJECT(*val));
					if (tmp) { cobj->size = *tmp; }
				} while (0);
				ret = JS_TRUE;
				break;
			default:
				break;
		}
		return ret;
	};
	
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
	{
		jsClass = (JSClass *)calloc(1, sizeof(JSClass));
		jsClass->name = name;
		jsClass->addProperty = JS_PropertyStub;
		jsClass->delProperty = JS_PropertyStub;
		jsClass->getProperty = JS_PropertyStub;
		jsClass->setProperty = JS_StrictPropertyStub;
		jsClass->enumerate = JS_EnumerateStub;
		jsClass->resolve = JS_ResolveStub;
		jsClass->convert = JS_ConvertStub;
		jsClass->finalize = jsFinalize;
		jsClass->flags = JSCLASS_HAS_PRIVATE;
		static JSPropertySpec properties[] = {
			{"origin", kOrigin, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet},
			{"size", kSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet}
		};
		
		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCRect::jsConstructor,0,properties,NULL,NULL,NULL);
	};
};
JSClass* S_CCRect::jsClass = NULL;
JSObject* S_CCRect::jsObject = NULL;

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
	JS_DefineFunction(this->cx, cocos, "forceGC", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);
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
