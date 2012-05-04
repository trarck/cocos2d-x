#include "simple_native_generated.hpp"

JSClass* S_SimpleNativeClass::jsClass = NULL;
JSObject* S_SimpleNativeClass::jsObject = NULL;

JSBool S_SimpleNativeClass::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_SimpleNativeClass::jsClass, S_SimpleNativeClass::jsObject, NULL);
	S_SimpleNativeClass *cobj = new S_SimpleNativeClass(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_SimpleNativeClass::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_SimpleNativeClass *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_SimpleNativeClass::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_SimpleNativeClass *cobj; JSGET_PTRSHELL(S_SimpleNativeClass, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kSomeField:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSomeField(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kSomeOtherField:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSomeOtherField(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAnotherMoreComplexField:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAnotherMoreComplexField(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_SimpleNativeClass::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_SimpleNativeClass *cobj; JSGET_PTRSHELL(S_SimpleNativeClass, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kSomeField:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setSomeField(tmp); } while (0);
		break;
	case kSomeOtherField:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setSomeOtherField(tmp); } while (0);
		break;
	case kAnotherMoreComplexField:
		do {
			char *tmp = JS_EncodeString(cx, *val);
			if (tmp) { cobj->setAnotherMoreComplexField(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_SimpleNativeClass::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"someField", kSomeField, JSPROP_PERMANENT | JSPROP_SHARED, S_SimpleNativeClass::jsPropertyGet, S_SimpleNativeClass::jsPropertySet},
			{"someOtherField", kSomeOtherField, JSPROP_PERMANENT | JSPROP_SHARED, S_SimpleNativeClass::jsPropertyGet, S_SimpleNativeClass::jsPropertySet},
			{"anotherMoreComplexField", kAnotherMoreComplexField, JSPROP_PERMANENT | JSPROP_SHARED, S_SimpleNativeClass::jsPropertyGet, S_SimpleNativeClass::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("doSomeProcessing", S_SimpleNativeClass::jsdoSomeProcessing, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_SimpleNativeClass::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_SimpleNativeClass::jsdoSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleNativeClass* self = NULL; JSGET_PTRSHELL(S_SimpleNativeClass, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "**", &arg0, &arg1);
		int ret = self->doSomeProcessing(*narg0, *narg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

