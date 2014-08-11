#ifndef LUA_EXTENSIONS_BITLIB_LBITLIB_H_
#define LUA_EXTENSIONS_BITLIB_LBITLIB_H_


#if __cplusplus
extern "C" {
#endif

#include <lua.h>
#include "lauxlib.h"
    
int luaopen_bit(lua_State *L);

#if __cplusplus
}
#endif



#endif  // LUA_EXTENSIONS_BITLIB_LBITLIB_H_

