#!/bin/sh

CLANG_28="$HOME/Downloads/clang+llvm-2.8-x86_64-apple-darwin10/"
INCLUDE_SEARCH_PATH="-I../cocos2dx/include -I../cocos2dx -I../cocos2dx/platform"
SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator5.1.sdk

${CLANG_28}/bin/clang++ -cc1 -ast-print-xml ${INCLUDE_SEARCH_PATH} -isysroot ${SYSROOT} -DTARGET_IPHONE_SIMULATOR -x c++ ../cocos2dx/include/cocos2d.h -o cocos2d.xml
