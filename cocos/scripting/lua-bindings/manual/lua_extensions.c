
#include "lua_extensions.h"

#if __cplusplus
extern "C" {
#endif
// socket
#include "luasocket/luasocket.h"
#include "luasocket/mime.h"
#include "bitlib/lbitlib.h"
#include "cjson/lua_cjson.h"
#include "crypto/lua_crypto.h"
#include "gzio/lgziolib.h"
#include "lpeg/lptree.h"
#include "md5/md5.h"
#include "struct/struct.h"

static luaL_Reg luax_exts[] = {
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},
    {"md5.core",luaopen_md5_core},
    {"cjson",luaopen_cjson_safe},
//    {"gzio",luaopen_gzio},
    {"lpeg",luaopen_lpeg},
    {NULL, NULL}
};

static void register_package_preload(lua_State *L)
{
    // load extensions
    luaL_Reg* lib = luax_exts;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);
}
    
static void register_libs(lua_State *L)
{
    luaopen_bit(L);
    luaopen_struct(L);
    luaopen_crypto(L);
    luaopen_gzio(L);
}
    
void luaopen_lua_extensions(lua_State *L)
{
    register_libs(L);
    
    // load extensions
    register_package_preload(L);
}

#if __cplusplus
} // extern "C"
#endif
