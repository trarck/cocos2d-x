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
#include "CCFontAtlasCache.h"

#include <iostream>
#include <sstream>

#include "CCFontFNT.h"
#include "CCFontFreeType.h"
#include "CCFontAtlas.h"
#include "CCFontCharMap.h"
#include "CCDirector.h"

NS_CC_BEGIN

std::map<std::string, FontAtlas *> FontAtlasCache::_atlasMap;

void FontAtlasCache::purgeCachedData()
{
    for (std::map<std::string, FontAtlas *>::iterator iter=_atlasMap.begin();iter!=_atlasMap.end();++iter)
    {
        iter->second->purgeTexturesAtlas();
    }
}

FontAtlas * FontAtlasCache::getFontAtlasTTF(const TTFConfig & config)
{  
    bool useDistanceField = config.distanceFieldEnabled;
    if(config.outlineSize > 0)
    {
        useDistanceField = false;
    }
    int fontSize = config.fontSize;
    float contentScaleFactor = CC_CONTENT_SCALE_FACTOR();

    if (useDistanceField)
    {
        fontSize = Label::DistanceFieldFontSize / contentScaleFactor;
    }

    std::string atlasName = generateFontName(config.fontFilePath, fontSize, kGlyphCollectionDYNAMIC, useDistanceField);
    atlasName.append("_outline_");
    std::stringstream ss;
    ss << config.outlineSize;
    atlasName.append(ss.str());

    std::map<std::string, FontAtlas *>::iterator it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        FontFreeType* font = FontFreeType::create(config.fontFilePath, fontSize, config.glyphs,
            config.customGlyphs, useDistanceField, config.outlineSize);
        if (font)
        {
            FontAtlas* tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return NULL;
}

FontAtlas * FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName, const CCPoint& imageOffset /* = CCPointZero */)
{
    std::string atlasName = generateFontName(fontFileName, 0, kGlyphCollectionCUSTOM,false);
    std::map<std::string, FontAtlas *>::iterator it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        FontFNT* font = FontFNT::create(fontFileName,imageOffset);

        if(font)
        {
            FontAtlas* tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }
    
    return NULL;
}

FontAtlas * FontAtlasCache::getFontAtlasCharMap(const std::string& plistFile)
{
    std::string atlasName = generateFontName(plistFile, 0, kGlyphCollectionCUSTOM,false);
    std::map<std::string, FontAtlas *>::iterator it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        FontCharMap* font = FontCharMap::create(plistFile);

        if(font)
        {
            FontAtlas* tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return NULL;
}

FontAtlas * FontAtlasCache::getFontAtlasCharMap(CCTexture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    char tmp[30];
    sprintf(tmp,"name:%u_%d_%d_%d",texture->getName(),itemWidth,itemHeight,startCharMap);
    std::string atlasName = generateFontName(tmp, 0, kGlyphCollectionCUSTOM,false);

    std::map<std::string, FontAtlas *>::iterator it = _atlasMap.find(atlasName);
    if ( it == _atlasMap.end() )
    {
        FontCharMap* font = FontCharMap::create(texture,itemWidth,itemHeight,startCharMap);

        if(font)
        {
            FontAtlas* tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return NULL;
}

FontAtlas * FontAtlasCache::getFontAtlasCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    char tmp[255];
    snprintf(tmp,250,"name:%s_%d_%d_%d",charMapFile.c_str(),itemWidth,itemHeight,startCharMap);

    std::string atlasName = generateFontName(tmp, 0, kGlyphCollectionCUSTOM,false);

    std::map<std::string, FontAtlas *>::iterator it = _atlasMap.find(atlasName);
    if ( it == _atlasMap.end() )
    {
        FontCharMap* font = FontCharMap::create(charMapFile,itemWidth,itemHeight,startCharMap);

        if(font)
        {
            FontAtlas* tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return NULL;
}

std::string FontAtlasCache::generateFontName(const std::string& fontFileName, int size, GlyphCollection theGlyphs, bool useDistanceField)
{
    std::string tempName(fontFileName);
    
    switch (theGlyphs)
    {
        case kGlyphCollectionDYNAMIC:
            tempName.append("_DYNAMIC_");
        break;
            
        case kGlyphCollectionNEHE:
            tempName.append("_NEHE_");
            break;
            
        case kGlyphCollectionASCII:
            tempName.append("_ASCII_");
            break;
            
        case kGlyphCollectionCUSTOM:
            tempName.append("_CUSTOM_");
            break;
            
        default:
            break;
    }
    if(useDistanceField)
        tempName.append("df");
    // std::to_string is not supported on android, using std::stringstream instead.
    std::stringstream ss;
    ss << size;
    return  tempName.append(ss.str());
}

bool FontAtlasCache::releaseFontAtlas(FontAtlas *atlas)
{
    if (NULL != atlas)
    {
        for( std::map<std::string, FontAtlas *>::iterator iter=_atlasMap.begin();iter!=_atlasMap.end();++iter )
        {
            if ( iter->second == atlas )
            {
                if (atlas->retainCount() == 1)
                {
                  _atlasMap.erase(iter->first);
                }
                
                atlas->release();
                
                return true;
            }
        }
    }
    
    return false;
}

NS_CC_END
