/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef _CCFontAtlas_h_
#define _CCFontAtlas_h_

#include "platform/CCPlatformMacros.h"
#include "cocoa/CCObject.h"
#include "CCStdC.h" // ssize_t on windows
#include <string>
#include <map>

NS_CC_BEGIN

//fwd
class Font;
class CCTexture2D;

class EventCustom;
class EventListenerCustom;

struct FontLetterDefinition
{
    unsigned short  letteCharUTF16;
    float U;//point //TODO change to piexls
    float V;//point
    float width;//point
    float height;//point
    float offsetX;//piexls
    float offsetY;//piexls
    int textureID;
    bool validDefinition;
    int xAdvance;//piexls

    int clipBottom;
};

class CC_DLL FontAtlas : public CCObject
{
public:
    static const int CacheTextureWidth;
    static const int CacheTextureHeight;
    static const char* EVENT_PURGE_TEXTURES;
    /**
     * @js ctor
     */
    FontAtlas(Font &theFont);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FontAtlas();
    
    void addLetterDefinition(const FontLetterDefinition &letterDefinition);
//    bool getLetterDefinitionForChar(char16_t letteCharUTF16, FontLetterDefinition &outDefinition);
    bool getLetterDefinitionForChar(unsigned short letteCharUTF16, FontLetterDefinition &outDefinition);
    
    //bool prepareLetterDefinitions(const std::u16string& utf16String);
    bool prepareLetterDefinitions(unsigned short * utf16String);

    inline const std::map<ssize_t, CCTexture2D*>& getTextures() const{ return _atlasTextures;}
    void  addTexture(CCTexture2D *texture, int slot);
    float getCommonLineHeight() const;
    void  setCommonLineHeight(float newHeight);
    
    CCTexture2D* getTexture(int slot);
    const Font* getFont() const;

    /** listen the event that renderer was recreated on Android/WP8
     It only has effect on Android and WP8.
     */
    void listenRendererRecreated(EventCustom *event);
    
    /** Removes textures atlas.
     It will purge the textures atlas and if multiple texture exist in the FontAtlas.
     */
    void purgeTexturesAtlas();

    /** sets font texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     */
     void setAntiAliasTexParameters();

     /** sets font texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_NEAREST
     - GL_TEXTURE_MAG_FILTER = GL_NEAREST
     */
     void setAliasTexParameters();

private:

    void relaseTextures();
    std::map<ssize_t, CCTexture2D*> _atlasTextures;
    std::map<unsigned short, FontLetterDefinition> _fontLetterDefinitions;
    float _commonLineHeight;
    Font * _font;

    // Dynamic GlyphCollection related stuff
    int _currentPage;
    unsigned char *_currentPageData;
    int _currentPageDataSize;
    float _currentPageOrigX;
    float _currentPageOrigY;
    float _letterPadding;
    bool  _makeDistanceMap;

    int _fontAscender;
    EventListenerCustom* _rendererRecreatedListener;
    bool _antialiasEnabled;
    bool _rendererRecreate;
};


NS_CC_END


#endif /* defined(__cocos2d_libs__CCFontAtlas__) */
