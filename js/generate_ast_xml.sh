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
# By default it will try to download clang_28 from the default repository and use
# the precompiled binary (only works of Mac OS X). It will store the clang binary
# in the clang_28 in the current $PWD. If you are on another platform, or don't
# want to download again the binary, place a copy of the clang 2.8 in the same
# directory as this script and rename it as "clang_28" (basically the script tests
# that there's a directory named like that)

CLANG_28="./clang_28"
CLANG_28_URL="http://llvm.org/releases/2.8/clang+llvm-2.8-x86_64-apple-darwin10.tar.gz"
SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator5.1.sdk

if [ ! -d "clang_28" ]; then
	echo "No clang_28 found on ${PWD}, downloading a new copy..."
	curl -LO "${CLANG_28_URL}"
	tar xzf clang+llvm-2.8-x86_64-apple-darwin10.tar.gz
	rm -f clang+llvm-2.8-x86_64-apple-darwin10.tar.gz
	mv clang+llvm-2.8-x86_64-apple-darwin10 clang_28
fi

if [ -z "$INCLUDE_SEARCH_PATH" ]; then
	INCLUDE_SEARCH_PATH="-I../cocos2dx/include -I../cocos2dx -I../cocos2dx/platform"
fi

if [ -e $1 ]; then
	OUT=$(basename $1 .h).xml
	${CLANG_28}/bin/clang++ -cc1 -ast-print-xml ${INCLUDE_SEARCH_PATH} -isysroot ${SYSROOT} -DTARGET_IPHONE_SIMULATOR -x c++ $1 -o $OUT
fi
