# How to build spidermonkey

1. Clone the cocos2d-x project
2. <code>cd /path/to/cocos2d-x</code>
3. <code>git submodule init && git submodule update</code>
4. <code>cd js/spidermonkey/js/src</code>
4. <code>autoconf213</code>
   * For OS X, macports or homebrew can be used to install autoconf213
5. <code>cd build-ios</code>
6. <code>sh build\_ios\_fat.sh</code>
   * If you are using Xcode older than 4.3, you will need to edit the SDK paths and Clang path in the ../configure file

# How to use the JS scripting

While we create the template, the easiest way would be to:

1. Create a new cocos2d-x project
2. cd into that directory and create the following link
  * <code>ln -s /path/to/cocos2d-x/js/spidermonkey/js/src/build-ios/dist spidermonkey</code>
3. add <code>"$(PROJECT_NAME)/spidermonkey/include"</code> as a header search path
4. add <code>"$(PROJECT_NAME)/spidermonkey/lib"</code> as a library search path
5. add <code>-ljs_static</code> as Other Linker Flags
6. add the JSBindings folder to your xcode project (as a group)
7. create a new "JS" folder in your project somewhere and add it as a **folder reference** to the xcode project
8. modify your AppDelegate to look like this:

```c++
# FILE: AppDelegate.h

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "ScriptingCore.h"

class  AppDelegate : private cocos2d::CCApplication
{
	ScriptingCore *m_scripting;
...
};

# FILE: AppDelegate.cpp

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

	// sets landscape mode
	// pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
	pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = HelloWorld::scene();

	// run
	pDirector->runWithScene(pScene);

	m_scripting = new ScriptingCore();
	m_scripting->runScript("JS/main.js");

	return true;
}
```

That code will run JS/main.js, in there you can put your game code.
