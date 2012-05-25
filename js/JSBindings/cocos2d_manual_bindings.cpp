#include "cocos2d_generated.hpp"
#include "cocos2d_manual_bindings.hpp"

// will fetch the scheduled functions for that object and execute them
// void S_runScheduledFunctions(JSObjectRef object, cocos2d::ccTime delta);
std::map<int, JSScheduleCallback *, cmp_objects> _globalCallback;

JSClass* S_CCScheduler::jsClass = NULL;
JSObject* S_CCScheduler::jsObject = NULL;

JSBool S_CCScheduler::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
}

void S_CCScheduler::jsFinalize(JSContext *cx, JSObject *obj)
{
}

JSBool S_CCScheduler::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	return JS_TRUE;
}

JSBool S_CCScheduler::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	return JS_TRUE;
}

void S_CCScheduler::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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

	static JSFunctionSpec st_funcs[] = {
		JS_FN("schedule", S_CCScheduler::jsschedule, 2, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FN("unschedule", S_CCScheduler::jsunschedule, 0, JSPROP_PERMANENT | JSPROP_SHARED),
		JS_FS_END
	};
	
	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCScheduler::jsConstructor,0,NULL,NULL,NULL,st_funcs);
}

// ported from the old bindings
JSBool S_CCScheduler::jsschedule(JSContext *cx, uint32_t argc, jsval *vp) {
	static int nextTimerId = 1;
	if (argc >= 2) {
		// turn the scheduling arguments into a JSScheduleCallback
		JSScheduleCallback *cb = new JSScheduleCallback();
		double interval;
		if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "od/o", &cb->callback, &interval, &cb->thisObject)) {
			JS_AddObjectRoot(cx, &cb->callback);
			if (cb->thisObject) {
				JS_AddObjectRoot(cx, &cb->thisObject);
			}
			cb->id = nextTimerId++;
			// save the timer callback in our list of global timer callbacks
			_globalCallback[cb->id] = cb;
			
			// schedule the event
			interval = interval / 1000.0f; // convert ms to seconds
			CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(JSScheduleCallback::timerCallBack), cb, interval, false);
			jsval ret; JS_NewNumberValue(cx, cb->id, &ret);
			JS_SET_RVAL(cx, vp, ret);
		}
	}
	return JS_TRUE;
}

JSBool S_CCScheduler::jsunschedule(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		/**
		 * what this should do: remove the key from the list of scheduled methods for that object
		 * if there are no more scheduled objects, unschedule this object
		 */
		int32_t timerIdToRemove;
		if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "i", &timerIdToRemove)) {
			callback_map::iterator it = _globalCallback.find(timerIdToRemove);
			if (it != _globalCallback.end()) {
				JSScheduleCallback* cb = (*it).second;
				// unschedule the callback
				CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(JSScheduleCallback::timerCallBack), cb);
				_globalCallback.erase(it);
				JS_RemoveObjectRoot(cx, &cb->callback);
				cb->callback = NULL;
				if (cb->thisObject) JS_RemoveObjectRoot(cx, &cb->thisObject);
				cb->release(); // we created it, we need to release our reference
			}
		}
	}
	return JS_TRUE;
}

JSScheduleCallback::~JSScheduleCallback()
{
}

void JSScheduleCallback::timerCallBack(ccTime dt)
{
	if (this->callback) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		// convert delta to milliseconds
		jsval delta, rval; JS_NewNumberValue(cx, dt * 1000.0f, &delta);
		jsval callback = OBJECT_TO_JSVAL(this->callback);
		JS_CallFunctionValue(cx, this->thisObject, callback, 1, &delta, &rval);
	}
}

JSBool S_CCNode::jsaddChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc >= 1) {
		JSObject *arg0;
		int zorder = 0;
		int tag = 0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o/ii", &arg0, &zorder, &tag);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		// call the proper method
		if (argc == 1) {
			self->addChild(narg0);
		} else if (argc == 2) {
			self->addChild(narg0, zorder);
		} else {
			self->addChild(narg0, zorder, tag);
		}

		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCMenuItemSprite::jsinitFromNormalSprite(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemSprite* self = NULL; JSGET_PTRSHELL(S_CCMenuItemSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc >= 2) {
		JSObject *arg0;
		JSObject *arg1;
		JSObject *arg2 = NULL;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "oo/o", &arg0, &arg1, &arg2);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		CCNode* narg1; JSGET_PTRSHELL(CCNode, narg1, arg1);
		CCNode* narg2 = NULL; if (argc == 3) JSGET_PTRSHELL(CCNode, narg2, arg2);
		bool ret = self->initFromNormalSprite(narg0, narg1, narg2, self, menu_selector(S_CCMenuItemSprite::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCMenuItemImage::jsinitFromNormalImage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemImage* self = NULL; JSGET_PTRSHELL(S_CCMenuItemImage, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc >= 2) {
		JSString *arg0;
		JSString *arg1;
		JSString *arg2 = NULL;
		JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "SS/S", &arg0, &arg1, &arg2);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		char *narg2 = (arg2) ? JS_EncodeString(cx, arg2) : NULL;
		bool ret = self->initFromNormalImage(narg0, narg1, narg2, self, menu_selector(S_CCMenuItemImage::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCSequence::jsactions(JSContext *cx, uint32_t argc, jsval *vp) {
	// just like CCSequence::actions
	if (argc > 0) {
		jsval* argv = JS_ARGV(cx, vp);
		// get first element
		S_CCSequence* prev;
		JSGET_PTRSHELL(S_CCSequence, prev, JSVAL_TO_OBJECT(argv[0]));
		for (int i=1; i < argc; i++) {
			CCFiniteTimeAction *next; JSGET_PTRSHELL(CCFiniteTimeAction, next, JSVAL_TO_OBJECT(argv[i]));
			prev = (S_CCSequence *)CCSequence::actionOneTwo(prev, next);
		}
		// wrap prev in an action
		// temporary because it's just a wrapper for an autoreleased object
		// or worst case, it's an already binded object (if it's just one item in the array)
		pointerShell_t* pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = kPointerTemporary;
		pt->data = prev;
		JSObject* out = JS_NewObject(cx, S_CCSequence::jsClass, S_CCSequence::jsObject, NULL);
		prev->jsObject = out;
		JS_SetPrivate(out, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(out));
		return JS_TRUE;
	}
	JS_ReportError(cx, "must call with at least one element");
	return JS_FALSE;
}

JSBool S_CCParticleSystem::jsparticleWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCParticleSystem* ret = ARCH_OPTIMAL_PARTICLE_SYSTEM::particleWithFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCParticleSystem::jsClass, S_CCParticleSystem::jsObject, NULL);
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
}

JSBool S_CCFileUtils::jsgetFileData(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		unsigned long len;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		unsigned char *ret = CCFileUtils::getFileData(narg0, narg1, &len);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		JSString *str = JS_NewStringCopyN(cx, (const char *)ret, len);
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCFileUtils::jsfullPathFromRelativePath(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		const char *ret = CCFileUtils::fullPathFromRelativePath(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		JSString *str = JS_NewStringCopyN(cx, ret, strlen(ret));
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCFileUtils::jsfullPathFromRelativeFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		const char *ret = CCFileUtils::fullPathFromRelativeFile(narg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		JSString *str = JS_NewStringCopyN(cx, ret, strlen(ret));
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));		
		return JS_TRUE;
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCLabelTTF::jslabelWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 5) {
		JSString *arg0;
		JSObject *arg1;
		int arg2;
		JSString *arg3;
		double arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SoiSd", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
		char *narg3 = JS_EncodeString(cx, arg3);
		CCLabelTTF *ret = CCLabelTTF::labelWithString(narg0, *narg1, (CCTextAlignment)arg2, narg3, arg4);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLabelTTF::jsClass, S_CCLabelTTF::jsObject, NULL);
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
}

JSBool S_CCLabelTTF::jsinitWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLabelTTF* self = NULL; JSGET_PTRSHELL(S_CCLabelTTF, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 5) {
		JSString *arg0;
		JSObject *arg1;
		int arg2;
		JSString *arg3;
		double arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SoiSd", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
		char *narg3 = JS_EncodeString(cx, arg3);
		bool ret = self->initWithString(narg0, *narg1, (CCTextAlignment)arg2, narg3, arg4);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCMenuItem::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->initWithTarget(self, menu_selector(S_CCMenuItem::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCRenderTexture::jsrenderTextureWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		int arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
		CCRenderTexture* ret = CCRenderTexture::renderTextureWithWidthAndHeight(arg0, arg1);
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRenderTexture::jsClass, S_CCRenderTexture::jsObject, NULL);
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
}

JSBool S_CCRenderTexture::jsinitWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		int arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
		bool ret = self->initWithWidthAndHeight(arg0, arg1, kCCTexture2DPixelFormat_RGBA8888);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCMenuItemLabel::jsitemWithLabel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		CCMenuItemLabel *ret = CCMenuItemLabel::itemWithLabel(narg0, self, menu_selector(S_CCMenuItemLabel::menuAction));
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMenuItemLabel::jsClass, S_CCMenuItemLabel::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)ret;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
		} while(0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCMenuItemLabel::jsinitWithLabel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		bool ret = self->initWithLabel(narg0, self, menu_selector(S_CCMenuItemLabel::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCApplication::jsgetCurrentLanguage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	CCApplication* self = NULL; JSGET_PTRSHELL(CCApplication, self, obj);
	if (self == NULL) return JS_FALSE;
	jsval result; JS_NewNumberValue(cx, self->getCurrentLanguage(), &result);
	JS_SET_RVAL(cx, vp, result);
	return JS_TRUE;
}

JSBool S_CCUserDefault::jsgetStringForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		std::string narg1(JS_EncodeString(cx, arg1));
		std::string ret = self->getStringForKey(narg0, narg1);
		JSString *jsret = JS_NewStringCopyZ(cx, ret.c_str());
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsret));
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool S_CCUserDefault::jssetStringForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		std::string narg1(JS_EncodeString(cx, arg1));
		self->setStringForKey(narg0, narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
