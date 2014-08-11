#ifndef LUA_EXTENSIONS_CRYPTO_LUA_CRYPTO_H_
#define LUA_EXTENSIONS_CRYPTO_LUA_CRYPTO_H_

#if __cplusplus
extern "C" {
#endif
    
#include "lauxlib.h"
    
int luaopen_crypto(lua_State *L);

#if __cplusplus
}
#endif



#endif  // LUA_EXTENSIONS_CRYPTO_LUA_CRYPTO_H_

