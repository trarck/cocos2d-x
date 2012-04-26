#!/bin/sh

# if you want to use this script you might want to specify the include search path
# otherwise it will set the default cocos2dx search path, which might not be what
# you want. To do so, you can set the variable INCLUDE_SEARCH_PATH before calling
# the script, like so:
#
# INCLUDE_SEARCH_PATH="-IsomeDir -Isome/other/dir" ./generate_ast_xml.sh my_header.h
#
# The default invocation will create a file named my_header.xml and if some other
# file named like that exists, it will overwrite that, so be careful
#
# You might also need to set the CLANG_28 path, but since that's something that will
# probably not change too much, ideally you just want to replace that bit
#
# NOTE: you can download clang-2.8 from here:
# http://llvm.org/releases/download.html

CLANG_28="$HOME/Downloads/clang+llvm-2.8-x86_64-apple-darwin10/"
SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator5.1.sdk
if [ -z "$INCLUDE_SEARCH_PATH" ]; then
	INCLUDE_SEARCH_PATH="-I../cocos2dx/include -I../cocos2dx -I../cocos2dx/platform"
fi

if [ -e $1 ]; then
	OUT=$(basename $1 .h).xml
	${CLANG_28}/bin/clang++ -cc1 -ast-print-xml ${INCLUDE_SEARCH_PATH} -isysroot ${SYSROOT} -DTARGET_IPHONE_SIMULATOR -x c++ $1 -o $OUT
fi
