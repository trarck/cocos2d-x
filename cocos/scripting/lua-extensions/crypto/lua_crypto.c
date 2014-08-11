#include "lua_crypto.h"
#include "aes.h"
#include <stdlib.h>

#if __cplusplus
extern "C" {
#endif

static const int kContentLengthSize=4;

static unsigned char* pad(const char* data,size_t size,size_t* newSize)
{
    size_t fixedSize=size;
    
    //fix size to 16 times
    if ( size & 0xF) {
        fixedSize +=16;
        fixedSize &=-16;
    }
    
    unsigned char* buff=(unsigned char*)malloc(fixedSize);
    
    if (buff) {
        memcpy(buff, data, size);
        memset(buff+size, 0, fixedSize-size);
    }
    
    if (newSize) {
        *newSize=fixedSize;
    }
    
    return  buff;
}

static int encrypt(lua_State* L)
{
    size_t dataSize=0;
    size_t keySize=0;
    
    const char* data=luaL_checklstring(L, 1, &dataSize);
    const char* key=luaL_checklstring(L, 2, &keySize);
    
    
    if (keySize>16) {
        lua_pushnil(L);
        return 1;
    }
    
    //pack content length to buffer
    size_t newDataSize=dataSize+kContentLengthSize;
    if (newDataSize & 0xF) {
        newDataSize += 16;
        newDataSize &=-16;
    }
    
    unsigned char* outData=NULL;
    unsigned char* padKey=NULL;
    
    unsigned char* newData=(unsigned char*)malloc(newDataSize);
    
    if (newData) {
        
        //data size save as little byte;
        *newData= dataSize & 0xFF;
        *(newData+1)= (dataSize >> 8) & 0xFF;
        *(newData+2)= (dataSize >> 16) & 0xFF;
        *(newData+3)= (dataSize >> 24) & 0xFF;
        
        //copy data
        memcpy(newData+kContentLengthSize, data, dataSize);
        //reset other zero
        memset(newData+kContentLengthSize+dataSize, 0, newDataSize-dataSize-kContentLengthSize);
        
        //fix key as 16 times
        padKey=pad(key, keySize,0);
        
        if (padKey) {
            
            aes_context ctx;
            
            unsigned char iv[16]={0};
            
            if(aes_setkey_enc(&ctx, padKey, 128)==0){
                
                outData=(unsigned char* )malloc(newDataSize);
                
                if(aes_crypt_cbc(&ctx, AES_ENCRYPT, newDataSize, iv, newData, outData)==0){
                    lua_pushlstring(L, (const char*)outData, newDataSize);
                }else{
                    lua_pushnil(L);
                }
            }else{
                lua_pushnil(L);
            }

        }else{
            lua_pushnil(L);
        }
    }else{
        lua_pushnil(L);
    }
    
    if (padKey) {
        free(padKey);
    }
    
    if (newData) {
        free(newData);
    }
    
    if (outData) {
        free(outData);
    }

    return 1;
}

static int decrypt(lua_State* L)
{
    size_t dataSize=0;
    size_t keySize=0;
    
    const char* data=luaL_checklstring(L, 1, &dataSize);
    const char* key=luaL_checklstring(L, 2, &keySize);
    
    
    if (keySize>16) {
        lua_pushnil(L);
        return 1;
    }
    
    unsigned char* outData=NULL;
    unsigned char* padKey=pad(key, keySize,0);
    
    if (padKey) {
        
        aes_context ctx;
        
        unsigned char iv[16]={0};
        
        if(aes_setkey_dec(&ctx, padKey, 128)==0){
            
            outData=(unsigned char* )malloc(dataSize);
            
            if(aes_crypt_cbc(&ctx, AES_DECRYPT, dataSize, iv, (const unsigned char*)data, outData)==0){
                //get real data
                size_t realSize=(*(outData+3) << 24)
                +(*(outData+2) << 16)
                +(*(outData+1) << 8)
                +*outData;
                
                lua_pushlstring(L, (const char*)(outData+kContentLengthSize), realSize);
            }else{
                lua_pushnil(L);
            }
            
        }else{
            lua_pushnil(L);
        }

    }else{
        lua_pushnil(L);
    }
    
    if (padKey) {
        free(padKey);
    }
    
    if (outData) {
        free(outData);
    }
    
    return 1;
}

static int show(lua_State* L)
{
    size_t dataSize=0;
    
    const char* name=luaL_checkstring(L, 1);
    const char* data=luaL_checklstring(L, 2, &dataSize);
    
    puts(name);
    
    if (dataSize>0) {
        
        for (int i=0; i<dataSize; ++i) {
            printf("%02x",(unsigned char)data[i]);
        }
    }else{
        putchar(0xA);
    }
    
    return 0;
}


static luaL_Reg crypto_lib[] = {
    {"encrypt", encrypt},
    {"decrypt", decrypt},
    {"show", show},
    {NULL, NULL}
};


int luaopen_crypto(lua_State *L)
{
    luaL_register(L, "crypto", crypto_lib);
    return 1;
}
    
#if __cplusplus
}
#endif

