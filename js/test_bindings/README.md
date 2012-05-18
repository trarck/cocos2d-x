# How to create my own bindings

While the `generate_bindings.rb` ruby script is mainly used to create the cocos2d-x bindings, the idea
is that it can be used to wrap more C++ classes needed by your game.

This document will try to explain how to use this script and what tools you need in order to make it
work.

Please note that this script is a preliminary effort and it won't work in all cases. Here's what is
**not** working:

* variable number of arguments - This is not working yet
* overloaded methods - It will call only the last method defined
* enums - they will only work if added outside a class

## Required tools

* clang 2.8 - the script will download it for you if you don't have it. Check the script for more
  info on this.
* ruby 1.9 and nokogiri gem
    * You can download ruby from http://www.ruby-lang.org
    * After you have ruby installed, you can install nokogiri: `sudo gem install nokogiri`
    * Alternatively you can use (rvm)[https://rvm.io/] - Highly suggested!

## Making it work

The first thing you need to create, is the (AST)[http://en.wikipedia.org/wiki/Abstract_syntax_tree] for your class.
Since you're using clang, you can safely point the script to your main header, for instance, for cocos2d-x we
point the script to the `cocos2d.h` header file. Take into account though, that files should be reachable or you
should modify the header search paths (`-I` in the script).

    ./generate_ast_xml.sh test_bindings/simple_class.h

This process is the exact same process as if you were "compiling" your code, so if you need to pass special search
paths for the headers, you can do so:

    INCLUDE_SEARCH_PATH="-IsomeDir -Isome/other/dir" ./generate_ast_xml.sh test_bindings/simple_class.h

That will create the XML for the AST in the current working directory, in this case `simple_class.xml`. Now you need
to pass this to the ruby script that will parse the tree and then generate the proper bindings:

    CXX_CLASSES=SimpleNativeClass ruby generate_bindings.rb simple_class.xml simple_native_generated

What this is doing, is specifying what classes are going to be binded (`CXX_CLASSES` is a colon separated string, and
is being passed as a environmental variable to the script), the two arguments for the script specify the XML file and
what is the name of the generated output. If no second argument is passed, it will generate `out.cpp` and `out.hpp`.

Once you run this, it should generate the files `simple_native_generated.cpp` and `simple_native_generated.hpp`. You
can then include those files in your project.

Please note that if the class you're binding is namespaced, then the scripting class (`S_SimpleNativeClass` in this
example) is not inheriting from the right class, so you should add the proper namespace. That should be the only
thing you would need to do in order to compile that file.

## What is doing internally

Explain here how it's wrapping the classes