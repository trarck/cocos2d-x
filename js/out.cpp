class S_CCPoint : public CCPoint
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kX = 1,
		kY
	};

	S_CCPoint(JSObject *obj) : CCPoint(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
		S_CCPoint *cobj = new S_CCPoint(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;
		JS_SetPrivate(obj, pt);
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
			do { jsval tmp; JS_NewNumberValue(cx, cobj->x, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kY:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->y, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
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
			{"y", kY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("CCPointEqualToPoint", S_CCPoint::jsCCPointEqualToPoint, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCPoint::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	static JSBool jsCCPointEqualToPoint(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
			bool ret = CCPoint::CCPointEqualToPoint(*narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};

};

JSClass* S_CCPoint::jsClass = NULL;
JSObject* S_CCPoint::jsObject = NULL;

class S_CCSize : public CCSize
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kWidth = 1,
		kHeight
	};

	S_CCSize(JSObject *obj) : CCSize(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
		S_CCSize *cobj = new S_CCSize(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;
		JS_SetPrivate(obj, pt);
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
			do { jsval tmp; JS_NewNumberValue(cx, cobj->width, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kHeight:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->height, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
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
			{"height", kHeight, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("CCSizeEqualToSize", S_CCSize::jsCCSizeEqualToSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCSize::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	static JSBool jsCCSizeEqualToSize(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCSize* narg0; JSGET_PTRSHELL(CCSize, narg0, arg0);
			CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
			bool ret = CCSize::CCSizeEqualToSize(*narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};

};

JSClass* S_CCSize::jsClass = NULL;
JSObject* S_CCSize::jsObject = NULL;

class S_CCRect : public CCRect
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kOrigin = 1,
		kSize
	};

	S_CCRect(JSObject *obj) : CCRect(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
		S_CCRect *cobj = new S_CCRect(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;
		JS_SetPrivate(obj, pt);
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
				pt->data = (void *)&cobj->origin;
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
				pt->data = (void *)&cobj->size;
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
				CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->origin = *tmp; }
			} while (0);
			ret = JS_TRUE;
			break;
		case kSize:
			do {
				CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
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
			{"size", kSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("CCRectGetMinX", S_CCRect::jsCCRectGetMinX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMaxX", S_CCRect::jsCCRectGetMaxX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMidX", S_CCRect::jsCCRectGetMidX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMinY", S_CCRect::jsCCRectGetMinY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMaxY", S_CCRect::jsCCRectGetMaxY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMidY", S_CCRect::jsCCRectGetMidY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectEqualToRect", S_CCRect::jsCCRectEqualToRect, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectContainsPoint", S_CCRect::jsCCRectContainsPoint, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectIntersectsRect", S_CCRect::jsCCRectIntersectsRect, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCRect::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	static JSBool jsCCRectGetMinX(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			float ret = CCRect::CCRectGetMinX(*narg0);
			do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectGetMaxX(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			float ret = CCRect::CCRectGetMaxX(*narg0);
			do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectGetMidX(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			float ret = CCRect::CCRectGetMidX(*narg0);
			do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectGetMinY(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			float ret = CCRect::CCRectGetMinY(*narg0);
			do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectGetMaxY(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			float ret = CCRect::CCRectGetMaxY(*narg0);
			do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectGetMidY(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			float ret = CCRect::CCRectGetMidY(*narg0);
			do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectEqualToRect(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
			bool ret = CCRect::CCRectEqualToRect(*narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectContainsPoint(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
			bool ret = CCRect::CCRectContainsPoint(*narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsCCRectIntersectsRect(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
			CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
			bool ret = CCRect::CCRectIntersectsRect(*narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};

};

JSClass* S_CCRect::jsClass = NULL;
JSObject* S_CCRect::jsObject = NULL;

class S_CCNode : public CCNode
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kZOrder = 1,
		kVertexZ,
		kRotation,
		kScaleX,
		kScaleY,
		kPosition,
		kPositionInPixels,
		kSkewX,
		kSkewY,
		kChildren,
		kCamera,
		kGrid,
		kIsVisible,
		kAnchorPoint,
		kAnchorPointInPixels,
		kContentSize,
		kContentSizeInPixels,
		kIsRunning,
		kParent,
		kIsRelativeAnchorPoint,
		kTag,
		kUserData,
		kTransform,
		kInverse,
		kTransformGL,
		kIsTransformDirty,
		kIsInverseDirty,
		kIsTransformGLDirty,
		kScriptHandler
	};

	S_CCNode(JSObject *obj) : CCNode(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
		S_CCNode *cobj = new S_CCNode(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;
		JS_SetPrivate(obj, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	};

	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCNode *)pt->data;
			JS_free(cx, pt);
		}
	};

	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCNode *cobj; JSGET_PTRSHELL(S_CCNode, cobj, obj);
		if (!cobj) return JS_FALSE;
		switch(propId) {
		case kZOrder:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getZOrder(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kVertexZ:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getVertexZ(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kRotation:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getRotation(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kScaleX:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getScaleX(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kScaleY:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getScaleY(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kPosition:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&cobj->getPosition();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kPositionInPixels:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&cobj->getPositionInPixels();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kSkewX:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getSkewX(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kSkewY:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getSkewY(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		// case kChildren:
		// 	do {
		// 		JSObject *tmp = JS_NewObject(cx, S_CCArray::jsClass, S_CCArray::jsObject, NULL);
		// 		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		// 		pt->flags = kPointerTemporary;
		// 		pt->data = (void *)cobj->getChildren();
		// 		JS_SetPrivate(tmp, pt);
		// 		JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		// 	} while (0);
		// 	return JS_TRUE;
		// 	break;
		// case kCamera:
		// 	do {
		// 		JSObject *tmp = JS_NewObject(cx, S_CCCamera::jsClass, S_CCCamera::jsObject, NULL);
		// 		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		// 		pt->flags = kPointerTemporary;
		// 		pt->data = (void *)cobj->getCamera();
		// 		JS_SetPrivate(tmp, pt);
		// 		JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		// 	} while (0);
		// 	return JS_TRUE;
		// 	break;
		case kIsVisible:
			JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsVisible()));
			return JS_TRUE;
			break;
		case kAnchorPoint:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&cobj->getAnchorPoint();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kAnchorPointInPixels:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&cobj->getAnchorPointInPixels();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kContentSize:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&cobj->getContentSize();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kContentSizeInPixels:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&cobj->getContentSizeInPixels();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kIsRunning:
			JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsRunning()));
			return JS_TRUE;
			break;
		case kParent:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)cobj->getParent();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kIsRelativeAnchorPoint:
			JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsRelativeAnchorPoint()));
			return JS_TRUE;
			break;
		case kTag:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getTag(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kUserData:
			
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
		S_CCNode *cobj; JSGET_PTRSHELL(S_CCNode, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
		case kVertexZ:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setVertexZ(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kRotation:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRotation(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kScaleX:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setScaleX(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kScaleY:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setScaleY(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kPosition:
			do {
				CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setPosition(*tmp); }
			} while (0);
			ret = JS_TRUE;
			break;
		case kPositionInPixels:
			do {
				CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setPositionInPixels(*tmp); }
			} while (0);
			ret = JS_TRUE;
			break;
		case kSkewX:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSkewX(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kSkewY:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSkewY(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kIsVisible:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsVisible(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kAnchorPoint:
			do {
				CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setAnchorPoint(*tmp); }
			} while (0);
			ret = JS_TRUE;
			break;
		case kContentSize:
			do {
				CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setContentSize(*tmp); }
			} while (0);
			ret = JS_TRUE;
			break;
		case kContentSizeInPixels:
			do {
				CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setContentSizeInPixels(*tmp); }
			} while (0);
			ret = JS_TRUE;
			break;
		case kParent:
			do {
				CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setParent(tmp); }
			} while (0);
			ret = JS_TRUE;
			break;
		case kIsRelativeAnchorPoint:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsRelativeAnchorPoint(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kTag:
			do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setTag(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kUserData:
			do {
				void* tmp; JSGET_PTRSHELL(void, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setUserData(tmp); }
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
			{"zOrder", kZOrder, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"vertexZ", kVertexZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"rotation", kRotation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scaleX", kScaleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scaleY", kScaleY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"positionInPixels", kPositionInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"skewX", kSkewX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"skewY", kSkewY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"children", kChildren, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"camera", kCamera, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"grid", kGrid, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isVisible", kIsVisible, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"anchorPoint", kAnchorPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"anchorPointInPixels", kAnchorPointInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"contentSize", kContentSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"contentSizeInPixels", kContentSizeInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isRunning", kIsRunning, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"parent", kParent, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isRelativeAnchorPoint", kIsRelativeAnchorPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"tag", kTag, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"userData", kUserData, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"transform", kTransform, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"inverse", kInverse, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"transformGL", kTransformGL, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isTransformDirty", kIsTransformDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isInverseDirty", kIsInverseDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isTransformGLDirty", kIsTransformGLDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scriptHandler", kScriptHandler, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("registerScriptHandler", S_CCNode::jsregisterScriptHandler, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unregisterScriptHandler", S_CCNode::jsunregisterScriptHandler, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addChild", S_CCNode::jsaddChild, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeFromParentAndCleanup", S_CCNode::jsremoveFromParentAndCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChild", S_CCNode::jsremoveChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChildByTag", S_CCNode::jsremoveChildByTag, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllChildrenWithCleanup", S_CCNode::jsremoveAllChildrenWithCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reorderChild", S_CCNode::jsreorderChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("cleanup", S_CCNode::jscleanup, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCNode::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("visit", S_CCNode::jsvisit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("transform", S_CCNode::jstransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("transformAncestors", S_CCNode::jstransformAncestors, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("boundingBox", S_CCNode::jsboundingBox, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("boundingBoxInPixels", S_CCNode::jsboundingBoxInPixels, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("runAction", S_CCNode::jsrunAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("stopAllActions", S_CCNode::jsstopAllActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("stopAction", S_CCNode::jsstopAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("stopActionByTag", S_CCNode::jsstopActionByTag, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("numberOfRunningActions", S_CCNode::jsnumberOfRunningActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("isScheduled", S_CCNode::jsisScheduled, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("scheduleUpdate", S_CCNode::jsscheduleUpdate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("scheduleUpdateWithPriority", S_CCNode::jsscheduleUpdateWithPriority, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unscheduleUpdate", S_CCNode::jsunscheduleUpdate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("schedule", S_CCNode::jsschedule, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("unschedule", S_CCNode::jsunschedule, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("unscheduleAllSelectors", S_CCNode::jsunscheduleAllSelectors, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resumeSchedulerAndActions", S_CCNode::jsresumeSchedulerAndActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pauseSchedulerAndActions", S_CCNode::jspauseSchedulerAndActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("parentToNodeTransform", S_CCNode::jsparentToNodeTransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("worldToNodeTransform", S_CCNode::jsworldToNodeTransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToNodeSpace", S_CCNode::jsconvertToNodeSpace, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToWorldSpace", S_CCNode::jsconvertToWorldSpace, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToNodeSpaceAR", S_CCNode::jsconvertToNodeSpaceAR, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToWorldSpaceAR", S_CCNode::jsconvertToWorldSpaceAR, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertTouchToNodeSpace", S_CCNode::jsconvertTouchToNodeSpace, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertTouchToNodeSpaceAR", S_CCNode::jsconvertTouchToNodeSpaceAR, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCNode::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	void onEnter() {
		if (m_jsobj) {
			JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
			JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
			if (found == JS_TRUE) {
				jsval rval, fval;
				JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
				JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
			}
		}
	};
	void onEnterTransitionDidFinish() {
		if (m_jsobj) {
			JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
			JSBool found; JS_HasProperty(cx, m_jsobj, "onEnterTransitionDidFinish", &found);
			if (found == JS_TRUE) {
				jsval rval, fval;
				JS_GetProperty(cx, m_jsobj, "onEnterTransitionDidFinish", &fval);
				JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
			}
		}
	};
	void onExit() {
		if (m_jsobj) {
			JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
			JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
			if (found == JS_TRUE) {
				jsval rval, fval;
				JS_GetProperty(cx, m_jsobj, "onExit", &fval);
				JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
			}
		}
	};
	static JSBool jsregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			int arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
			self->registerScriptHandler(arg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsunregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->unregisterScriptHandler();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsaddChild(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
			self->addChild(narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsremoveFromParentAndCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			bool arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
			self->removeFromParentAndCleanup(arg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			JSObject *arg0;
			bool arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ob", &arg0, &arg1);
			CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
			self->removeChild(narg0, arg1);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsremoveChildByTag(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			int arg0;
			bool arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ib", &arg0, &arg1);
			self->removeChildByTag(arg0, arg1);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			bool arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
			self->removeAllChildrenWithCleanup(arg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			JSObject *arg0;
			int arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
			CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
			self->reorderChild(narg0, arg1);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jscleanup(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->cleanup();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->draw();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsvisit(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->visit();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jstransform(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->transform();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jstransformAncestors(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->transformAncestors();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsboundingBox(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			CCRect ret = self->boundingBox();
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsboundingBoxInPixels(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			CCRect ret = self->boundingBoxInPixels();
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	// static JSBool jsrunAction(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 1) {
	// 		JSObject *arg0;
	// 		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
	// 		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
	// 		CCAction* ret = self->runAction(narg0);
	// 		do {
	// 			JSObject *tmp = JS_NewObject(cx, S_CCAction::jsClass, S_CCAction::jsObject, NULL);
	// 			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	// 			pt->flags = kPointerTemporary;
	// 			pt->data = (void *)ret;
	// 			JS_SetPrivate(tmp, pt);
	// 			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
	// 		} while (0);
	// 		
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsstopAllActions(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 0) {
	// 		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
	// 		self->stopAllActions();
	// 		
	// 		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsstopAction(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 1) {
	// 		JSObject *arg0;
	// 		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
	// 		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
	// 		self->stopAction(narg0);
	// 		
	// 		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsstopActionByTag(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 1) {
	// 		int arg0;
	// 		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
	// 		self->stopActionByTag(arg0);
	// 		
	// 		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsnumberOfRunningActions(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 0) {
	// 		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
	// 		unsigned int ret = self->numberOfRunningActions();
	// 		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
	// 		
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsisScheduled(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 1) {
	// 		JSObject *arg0;
	// 		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "*", &arg0);
	// 		bool ret = self->isScheduled(*narg0);
	// 		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
	// 		
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	static JSBool jsscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->scheduleUpdate();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsscheduleUpdateWithPriority(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			int arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
			self->scheduleUpdateWithPriority(arg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsunscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->unscheduleUpdate();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	// static JSBool jsschedule(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 1) {
	// 		JSObject *arg0;
	// 		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "*", &arg0);
	// 		self->schedule(*narg0);
	// 		
	// 		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsunschedule(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 1) {
	// 		JSObject *arg0;
	// 		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "*", &arg0);
	// 		self->unschedule(*narg0);
	// 		
	// 		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsunscheduleAllSelectors(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 0) {
	// 		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
	// 		self->unscheduleAllSelectors();
	// 		
	// 		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	static JSBool jsresumeSchedulerAndActions(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->resumeSchedulerAndActions();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jspauseSchedulerAndActions(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->pauseSchedulerAndActions();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	// static JSBool jsparentToNodeTransform(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 0) {
	// 		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
	// 		CCAffineTransform ret = self->parentToNodeTransform();
	// 		do {
	// 			JSObject *tmp = JS_NewObject(cx, S_CCAffineTransform::jsClass, S_CCAffineTransform::jsObject, NULL);
	// 			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	// 			pt->flags = kPointerTemporary;
	// 			pt->data = (void *)&ret;
	// 			JS_SetPrivate(tmp, pt);
	// 			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
	// 		} while (0);
	// 		
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	// static JSBool jsworldToNodeTransform(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 0) {
	// 		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
	// 		CCAffineTransform ret = self->worldToNodeTransform();
	// 		do {
	// 			JSObject *tmp = JS_NewObject(cx, S_CCAffineTransform::jsClass, S_CCAffineTransform::jsObject, NULL);
	// 			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	// 			pt->flags = kPointerTemporary;
	// 			pt->data = (void *)&ret;
	// 			JS_SetPrivate(tmp, pt);
	// 			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
	// 		} while (0);
	// 		
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	static JSBool jsconvertToNodeSpace(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint ret = self->convertToNodeSpace(*narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertToWorldSpace(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint ret = self->convertToWorldSpace(*narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertToNodeSpaceAR(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint ret = self->convertToNodeSpaceAR(*narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertToWorldSpaceAR(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint ret = self->convertToWorldSpaceAR(*narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertTouchToNodeSpace(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCTouch* narg0; JSGET_PTRSHELL(CCTouch, narg0, arg0);
			CCPoint ret = self->convertTouchToNodeSpace(narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertTouchToNodeSpaceAR(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCTouch* narg0; JSGET_PTRSHELL(CCTouch, narg0, arg0);
			CCPoint ret = self->convertTouchToNodeSpaceAR(narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	virtual void update(ccTime delta) {
		if (m_jsobj) {
			JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
			JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
			if (found == JS_TRUE) {
				jsval rval, fval;
				JS_GetProperty(cx, m_jsobj, "update", &fval);
				jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
				JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
			}
		}
	};

};

JSClass* S_CCNode::jsClass = NULL;
JSObject* S_CCNode::jsObject = NULL;

class S_CCScene : public CCScene
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {

	};

	S_CCScene(JSObject *obj) : CCScene(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCScene::jsClass, S_CCScene::jsObject, NULL);
		S_CCScene *cobj = new S_CCScene(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;
		JS_SetPrivate(obj, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	};

	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCScene *)pt->data;
			JS_free(cx, pt);
		}
	};

	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCScene *cobj; JSGET_PTRSHELL(S_CCScene, cobj, obj);
		if (!cobj) return JS_FALSE;
		switch(propId) {
		default:
			break;
		}
		return JS_FALSE;
	};

	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCScene *cobj; JSGET_PTRSHELL(S_CCScene, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCScene::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCScene::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCScene* self = NULL; JSGET_PTRSHELL(S_CCScene, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->init();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	virtual void update(ccTime delta) {
		if (m_jsobj) {
			JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
			JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
			if (found == JS_TRUE) {
				jsval rval, fval;
				JS_GetProperty(cx, m_jsobj, "update", &fval);
				jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
				JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
			}
		}
	};

};

JSClass* S_CCScene::jsClass = NULL;
JSObject* S_CCScene::jsObject = NULL;

class S_CCDirector : public CCDirector
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kPurgeDirecotorInNextLoop = 1,
		kObOpenGLView,
		kLandscape,
		kDisplayFPS,
		kAccumDt,
		kFrameRate,
		kFPSLabel,
		kPaused,
		kRunningScene,
		kNextScene,
		kSendCleanupToScene,
		kObScenesStack,
		kLastUpdate,
		kDeltaTime,
		kNextDeltaTimeZero,
		kContentScaleFactor,
		kSzFPS,
		kNotificationNode,
		kProjectionDelegate,
		kIsContentScaleSupported,
		kRetinaDisplay
	};

	S_CCDirector(JSObject *obj) : CCDirector(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		return JS_FALSE;
	};

	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCDirector *)pt->data;
			JS_free(cx, pt);
		}
	};

	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCDirector *cobj; JSGET_PTRSHELL(S_CCDirector, cobj, obj);
		if (!cobj) return JS_FALSE;
		switch(propId) {
		case kRunningScene:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCScene::jsClass, S_CCScene::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)cobj->getRunningScene();
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} while (0);
			return JS_TRUE;
			break;
		case kContentScaleFactor:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getContentScaleFactor(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
			return JS_TRUE;
			break;
		case kNotificationNode:
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)cobj->getNotificationNode();
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
		S_CCDirector *cobj; JSGET_PTRSHELL(S_CCDirector, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
		case kDisplayFPS:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDisplayFPS(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kNextDeltaTimeZero:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setNextDeltaTimeZero(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kContentScaleFactor:
			do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setContentScaleFactor(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kNotificationNode:
			do {
				CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
				if (tmp) { cobj->setNotificationNode(tmp); }
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
			{"purgeDirecotorInNextLoop", kPurgeDirecotorInNextLoop, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"obOpenGLView", kObOpenGLView, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"landscape", kLandscape, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"displayFPS", kDisplayFPS, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"accumDt", kAccumDt, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"frameRate", kFrameRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"fPSLabel", kFPSLabel, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"paused", kPaused, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"runningScene", kRunningScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"nextScene", kNextScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"sendCleanupToScene", kSendCleanupToScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"obScenesStack", kObScenesStack, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"lastUpdate", kLastUpdate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"deltaTime", kDeltaTime, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"nextDeltaTimeZero", kNextDeltaTimeZero, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"contentScaleFactor", kContentScaleFactor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"szFPS", kSzFPS, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"notificationNode", kNotificationNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"projectionDelegate", kProjectionDelegate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"isContentScaleSupported", kIsContentScaleSupported, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"retinaDisplay", kRetinaDisplay, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCDirector::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDisplayFPS", S_CCDirector::jsisDisplayFPS, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isNextDeltaTimeZero", S_CCDirector::jsisNextDeltaTimeZero, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isPaused", S_CCDirector::jsisPaused, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isSendCleanupToScene", S_CCDirector::jsisSendCleanupToScene, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reshapeProjection", S_CCDirector::jsreshapeProjection, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToGL", S_CCDirector::jsconvertToGL, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToUI", S_CCDirector::jsconvertToUI, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("runWithScene", S_CCDirector::jsrunWithScene, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pushScene", S_CCDirector::jspushScene, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("popScene", S_CCDirector::jspopScene, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("replaceScene", S_CCDirector::jsreplaceScene, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("endToLua", S_CCDirector::jsendToLua, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("end", S_CCDirector::jsend, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pause", S_CCDirector::jspause, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resume", S_CCDirector::jsresume, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopAnimation", S_CCDirector::jsstopAnimation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startAnimation", S_CCDirector::jsstartAnimation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("drawScene", S_CCDirector::jsdrawScene, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("purgeCachedData", S_CCDirector::jspurgeCachedData, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("mainLoop", S_CCDirector::jsmainLoop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("showProfilers", S_CCDirector::jsshowProfilers, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("applyOrientation", S_CCDirector::jsapplyOrientation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("enableRetinaDisplay", S_CCDirector::jsenableRetinaDisplay, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isRetinaDisplay", S_CCDirector::jsisRetinaDisplay, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedDirector", S_CCDirector::jssharedDirector, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCDirector::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->init();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisDisplayFPS(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isDisplayFPS();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisNextDeltaTimeZero(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isNextDeltaTimeZero();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisPaused(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isPaused();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisSendCleanupToScene(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isSendCleanupToScene();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsreshapeProjection(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCSize* narg0; JSGET_PTRSHELL(CCSize, narg0, arg0);
			self->reshapeProjection(*narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertToGL(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint ret = self->convertToGL(*narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsconvertToUI(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
			CCPoint ret = self->convertToUI(*narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)&ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsrunWithScene(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCScene* narg0; JSGET_PTRSHELL(CCScene, narg0, arg0);
			self->runWithScene(narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jspushScene(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCScene* narg0; JSGET_PTRSHELL(CCScene, narg0, arg0);
			self->pushScene(narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jspopScene(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->popScene();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsreplaceScene(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCScene* narg0; JSGET_PTRSHELL(CCScene, narg0, arg0);
			self->replaceScene(narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsendToLua(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->endToLua();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsend(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->end();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jspause(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->pause();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsresume(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->resume();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsstopAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->stopAnimation();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsstartAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->startAnimation();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsdrawScene(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->drawScene();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jspurgeCachedData(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->purgeCachedData();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsmainLoop(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->mainLoop();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsshowProfilers(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->showProfilers();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsapplyOrientation(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->applyOrientation();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsenableRetinaDisplay(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			bool arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
			bool ret = self->enableRetinaDisplay(arg0);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisRetinaDisplay(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isRetinaDisplay();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jssharedDirector(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			CCDirector* ret = CCDirector::sharedDirector();
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCDirector::jsClass, S_CCDirector::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};

};

JSClass* S_CCDirector::jsClass = NULL;
JSObject* S_CCDirector::jsObject = NULL;

class S_CCSprite : public CCSprite
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kOpacity = 1,
		kObTextureAtlas,
		kObBatchNode,
		kDirty,
		kRecursiveDirty,
		kHasChildren,
		kObTexture,
		kUsesBatchNode,
		kRectRotated,
		kOpacityModifyRGB,
		kFlipX,
		kFlipY
	};

	S_CCSprite(JSObject *obj) : CCSprite(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JSObject *obj = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
		S_CCSprite *cobj = new S_CCSprite(obj);
		pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = 0; pt->data = cobj;
		JS_SetPrivate(obj, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	};

	static void jsFinalize(JSContext *cx, JSObject *obj)
	{
		pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
		if (pt) {
			if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSprite *)pt->data;
			JS_free(cx, pt);
		}
	};

	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
	{
		int32_t propId = JSID_TO_INT(_id);
		S_CCSprite *cobj; JSGET_PTRSHELL(S_CCSprite, cobj, obj);
		if (!cobj) return JS_FALSE;
		switch(propId) {
		case kOpacity:
			do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
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
		S_CCSprite *cobj; JSGET_PTRSHELL(S_CCSprite, cobj, obj);
		if (!cobj) return JS_FALSE;
		JSBool ret = JS_FALSE;
		switch(propId) {
		case kOpacity:
			do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setOpacity(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kDirty:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDirty(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kFlipX:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setFlipX(tmp); } while (0);
			ret = JS_TRUE;
			break;
		case kFlipY:
			do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setFlipY(tmp); } while (0);
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
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"obTextureAtlas", kObTextureAtlas, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"obBatchNode", kObBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"dirty", kDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"recursiveDirty", kRecursiveDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"hasChildren", kHasChildren, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"obTexture", kObTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"usesBatchNode", kUsesBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rectRotated", kRectRotated, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"opacityModifyRGB", kOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"flipX", kFlipX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"flipY", kFlipY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("draw", S_CCSprite::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDirty", S_CCSprite::jsisDirty, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isTextureRectRotated", S_CCSprite::jsisTextureRectRotated, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isUsesBatchNode", S_CCSprite::jsisUsesBatchNode, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("init", S_CCSprite::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChild", S_CCSprite::jsremoveChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllChildrenWithCleanup", S_CCSprite::jsremoveAllChildrenWithCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reorderChild", S_CCSprite::jsreorderChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addChild", S_CCSprite::jsaddChild, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFlipX", S_CCSprite::jsisFlipX, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFlipY", S_CCSprite::jsisFlipY, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateColor", S_CCSprite::jsupdateColor, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTexture", S_CCSprite::jsinitWithTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithSpriteFrame", S_CCSprite::jsinitWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithSpriteFrameName", S_CCSprite::jsinitWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithFile", S_CCSprite::jsinitWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithBatchNode", S_CCSprite::jsinitWithBatchNode, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithBatchNodeRectInPixels", S_CCSprite::jsinitWithBatchNodeRectInPixels, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateTransform", S_CCSprite::jsupdateTransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("useSelfRender", S_CCSprite::jsuseSelfRender, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("useBatchNode", S_CCSprite::jsuseBatchNode, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFrameDisplayed", S_CCSprite::jsisFrameDisplayed, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			// JS_FN("displayedFrame", S_CCSprite::jsdisplayedFrame, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("spriteWithTexture", S_CCSprite::jsspriteWithTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithSpriteFrame", S_CCSprite::jsspriteWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithSpriteFrameName", S_CCSprite::jsspriteWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithFile", S_CCSprite::jsspriteWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithBatchNode", S_CCSprite::jsspriteWithBatchNode, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCSprite::jsConstructor,0,properties,funcs,NULL,st_funcs);
	};

	static JSBool jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->draw();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisDirty(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isDirty();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisTextureRectRotated(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isTextureRectRotated();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisUsesBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isUsesBatchNode();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsspriteWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
			CCSprite* ret = CCSprite::spriteWithTexture(narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsspriteWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
			CCSprite* ret = CCSprite::spriteWithSpriteFrame(narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsspriteWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSString *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
			char *narg0 = JS_EncodeString(cx, arg0);
			CCSprite* ret = CCSprite::spriteWithSpriteFrameName(narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsspriteWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 1) {
			JSString *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
			char *narg0 = JS_EncodeString(cx, arg0);
			CCSprite* ret = CCSprite::spriteWithFile(narg0);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsspriteWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
			CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
			CCSprite* ret = CCSprite::spriteWithBatchNode(narg0, *narg1);
			do {
				JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)ret;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
			} while (0);
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->init();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			JSObject *arg0;
			bool arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ob", &arg0, &arg1);
			CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
			self->removeChild(narg0, arg1);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			bool arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
			self->removeAllChildrenWithCleanup(arg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			JSObject *arg0;
			int arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
			CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
			self->reorderChild(narg0, arg1);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsaddChild(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
			self->addChild(narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisFlipX(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isFlipX();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisFlipY(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			bool ret = self->isFlipY();
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsupdateColor(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->updateColor();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
			bool ret = self->initWithTexture(narg0);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinitWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
			bool ret = self->initWithSpriteFrame(narg0);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinitWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSString *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
			char *narg0 = JS_EncodeString(cx, arg0);
			bool ret = self->initWithSpriteFrameName(narg0);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinitWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSString *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
			char *narg0 = JS_EncodeString(cx, arg0);
			bool ret = self->initWithFile(narg0);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinitWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
			CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
			bool ret = self->initWithBatchNode(narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsinitWithBatchNodeRectInPixels(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 2) {
			JSObject *arg0;
			JSObject *arg1;
			JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
			CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
			CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
			bool ret = self->initWithBatchNodeRectInPixels(narg0, *narg1);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsupdateTransform(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->updateTransform();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsuseSelfRender(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 0) {
			JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
			self->useSelfRender();
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsuseBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
			self->useBatchNode(narg0);
			
			JS_SET_RVAL(cx, vp, JSVAL_TRUE);
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	static JSBool jsisFrameDisplayed(JSContext *cx, uint32_t argc, jsval *vp) {
		JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
		S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
		if (self == NULL) return JS_FALSE;
		if (argc == 1) {
			JSObject *arg0;
			JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
			CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
			bool ret = self->isFrameDisplayed(narg0);
			JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
			
			return JS_TRUE;
		}
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	};
	// static JSBool jsdisplayedFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	// 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	// 	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	// 	if (self == NULL) return JS_FALSE;
	// 	if (argc == 0) {
	// 		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
	// 		CCSpriteFrame* ret = self->displayedFrame();
	// 		do {
	// 			JSObject *tmp = JS_NewObject(cx, S_CCSpriteFrame::jsClass, S_CCSpriteFrame::jsObject, NULL);
	// 			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	// 			pt->flags = kPointerTemporary;
	// 			pt->data = (void *)ret;
	// 			JS_SetPrivate(tmp, pt);
	// 			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
	// 		} while (0);
	// 		
	// 		return JS_TRUE;
	// 	}
	// 	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	// 	return JS_TRUE;
	// };
	virtual void update(ccTime delta) {
		if (m_jsobj) {
			JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
			JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
			if (found == JS_TRUE) {
				jsval rval, fval;
				JS_GetProperty(cx, m_jsobj, "update", &fval);
				jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
				JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
			}
		}
	};

};

JSClass* S_CCSprite::jsClass = NULL;
JSObject* S_CCSprite::jsObject = NULL;

