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

#include "CCLabel.h"
#include "CCFontAtlasCache.h"
#include "sprite_nodes/CCSprite.h"
#include "effects/CCGrid.h"
#include "CCLabelTextFormatter.h"
#include "support/ccUTF8.h"
#include "support/TransformUtils.h"
#include "platform/CCFileUtils.h"
#include "CCFont.h"
#include "CCDirector.h"
#include "cocoa/CCString.h"
#include "shaders/CCShaderCache.h"
// external
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

const int Label::DistanceFieldFontSize = 50;

// The return value needs to be deleted by CC_SAFE_DELETE_ARRAY.
static unsigned short* copyUTF16StringN(unsigned short* str)
{
    int length = str ? cc_wcslen(str) : 0;
    unsigned short* ret = new unsigned short[length+1];
    for (int i = 0; i < length; ++i) {
        ret[i] = str[i];
    }
    ret[length] = 0;
    return ret;
}

Label* Label::create()
{
    Label* ret = new Label();

    if (ret)
    {
        ret->autorelease();
    }

    return ret;
}

Label* Label::create(const std::string& text, const std::string& font, float fontSize, const CCSize& dimensions /* = Size::ZERO */, CCTextAlignment hAlignment /* = kCCTextAlignmentLeft */, CCVerticalTextAlignment vAlignment /* = kCCVerticalTextAlignmentTop */)
{
    if (CCFileUtils::sharedFileUtils()->isFileExist(font))
    {
        return createWithTTF(text,font,fontSize,dimensions,hAlignment,vAlignment);
    } 
    else
    {
        return createWithSystemFont(text,font,fontSize,dimensions,hAlignment,vAlignment);
    }
}

Label* Label::createWithSystemFont(const std::string& text, const std::string& font, float fontSize, const CCSize& dimensions /* = Size::ZERO */, CCTextAlignment hAlignment /* = kCCTextAlignmentLeft */, CCVerticalTextAlignment vAlignment /* = kCCVerticalTextAlignmentTop */)
{
    Label* ret = new Label(NULL,hAlignment,vAlignment);

    if (ret)
    {
        ret->setSystemFontName(font);
        ret->setSystemFontSize(fontSize);
        ret->setDimensions(dimensions.width, dimensions.height);
        ret->setString(text);

        ret->autorelease();

        return ret;
    }

    delete ret;
    return NULL;
}

Label* Label::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const CCSize& dimensions /* = Size::ZERO */, CCTextAlignment hAlignment /* = kCCTextAlignmentLeft */, CCVerticalTextAlignment vAlignment /* = kCCVerticalTextAlignmentTop */)
{
    Label* ret = new Label(NULL,hAlignment,vAlignment);

    if (ret && CCFileUtils::sharedFileUtils()->isFileExist(fontFile))
    {
        TTFConfig ttfConfig(fontFile.c_str(),fontSize,kGlyphCollectionDYNAMIC);
        if (ret->setTTFConfig(ttfConfig))
        {
            ret->setDimensions(dimensions.width,dimensions.height);
            ret->setString(text);

            ret->autorelease();

            return ret;
        }
    }

    delete ret;
    return NULL;
}

Label* Label::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, CCTextAlignment alignment /* = kCCTextAlignmentCenter */, int maxLineWidth /* = 0 */)
{
    Label* ret = new Label(NULL,alignment);

    if (ret && CCFileUtils::sharedFileUtils()->isFileExist(ttfConfig.fontFilePath) && ret->setTTFConfig(ttfConfig))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        ret->autorelease();

        return ret;
    }

    delete ret;
    return NULL;
}

Label* Label::createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const CCTextAlignment& alignment /* = kCCTextAlignmentLeft */, int maxLineWidth /* = 0 */, const CCPoint& imageOffset /* = Vec2::ZERO */)
{
    Label* ret = new Label(NULL,alignment);

    if (ret && ret->setBMFontFilePath(bmfontFilePath,imageOffset))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        ret->autorelease();

        return ret;
    }
    
    delete ret;
    return NULL;
}

Label* Label::createWithCharMap(const std::string& plistFile)
{
    Label* ret = new Label();

    if (ret && ret->setCharMap(plistFile))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return NULL;
}

Label* Label::createWithCharMap(CCTexture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    Label* ret = new Label();

    if (ret && ret->setCharMap(texture,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return NULL;
}

Label* Label::createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    Label* ret = new Label();

    if (ret && ret->setCharMap(charMapFile,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return NULL;
}

bool Label::setCharMap(const std::string& plistFile)
{
    FontAtlas * newAtlas = FontAtlasCache::getFontAtlasCharMap(plistFile);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = kLabelTypeCHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setCharMap(CCTexture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    FontAtlas * newAtlas = FontAtlasCache::getFontAtlasCharMap(texture,itemWidth,itemHeight,startCharMap);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = kLabelTypeCHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    FontAtlas * newAtlas = FontAtlasCache::getFontAtlasCharMap(charMapFile,itemWidth,itemHeight,startCharMap);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = kLabelTypeCHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

Label::Label(FontAtlas *atlas /* = NULL */, CCTextAlignment hAlignment /* = kCCTextAlignmentLeft */, 
             CCVerticalTextAlignment vAlignment /* = kCCVerticalTextAlignmentTop */,bool useDistanceField /* = false */,bool useA8Shader /* = false */)
: _reusedLetter(NULL)
, _commonLineHeight(0.0f)
, _additionalKerning(0.0f)
, _lineBreakWithoutSpaces(false)
, _maxLineWidth(0)
, _labelWidth(0)
, _labelHeight(0)
, _labelDimensions(CCSizeZero)
, _hAlignment(hAlignment)
, _vAlignment(vAlignment)
, _horizontalKernings(NULL)
, _fontAtlas(atlas)
, _isOpacityModifyRGB(false)
, _useDistanceField(useDistanceField)
, _useA8Shader(useA8Shader)
, _fontScale(1.0f)
, _uniformEffectColor(0)
, _currNumLines(-1)
, _textSprite(NULL)
, _contentDirty(false)
, _shadowDirty(false)
, _compatibleMode(false)
, _insideBounds(true)
, _effectColorF(ccc4f(0, 0, 0, 255))
{
    setAnchorPoint(CCPoint(0.5,0.5));
    reset();

//    auto purgeTextureListener = EventListenerCustom::create(FontAtlas::EVENT_PURGE_TEXTURES, [this](EventCustom* event){
//        if (_fontAtlas && _currentLabelType == LabelType::TTF && event->getUserData() == _fontAtlas)
//        {
//            Node::removeAllChildrenWithCleanup(true);
//            _batchNodes.clear();
//            _batchNodes.push_back(this);
//
//            alignText();
//        }
//    });
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(purgeTextureListener, this);
}

Label::~Label()
{
    delete [] _horizontalKernings;

    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }

    CC_SAFE_RELEASE_NULL(_reusedLetter);
}

void Label::reset()
{
    TTFConfig temp;
    _fontConfig = temp;

    _systemFontDirty = false;
    _systemFont = "Helvetica";
    _systemFontSize = 12;

    _batchNodes.clear();
    _batchNodes.push_back(this);

    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = NULL;
    }

    _currentLabelType = kLabelTypeSTRING_TEXTURE;
    _currLabelEffect = kLabelEffectNORMAL;
    _shadowBlurRadius = 0;

    CCNode::removeAllChildrenWithCleanup(true);
    _textSprite = NULL;
    _shadowNode = NULL;

    CC_SAFE_RELEASE_NULL(_reusedLetter);

    _textColor = ccc4(255, 255, 255, 255);
    _textColorF = ccc4f(1.0, 1.0, 1.0, 1.0);
    setColor(ccc3(255, 255, 255));

    _shadowEnabled = false;
    _clipEnabled = false;
    _blendFuncDirty = false;
}

void Label::updateShaderProgram()
{
    switch (_currLabelEffect)
    {
    case cocos2d::kLabelEffectNORMAL:
        if (_useDistanceField)
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_LABEL_DISTANCEFIELD_NORMAL));
        else if (_useA8Shader)
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_LABEL_NORMAL));
        else
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

        break;
    case cocos2d::kLabelEffectOUTLINE:
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_LABEL_OUTLINE));
        _uniformEffectColor = glGetUniformLocation(getShaderProgram()->getProgram(), "u_effectColor");
        break;
    case cocos2d::kLabelEffectGLOW:
        if (_useDistanceField)
        {
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_LABEL_DISTANCEFIELD_GLOW));
            _uniformEffectColor = glGetUniformLocation(getShaderProgram()->getProgram(), "u_effectColor");
        }
        break;
    default:
        return;
    }
    
    _uniformTextColor = glGetUniformLocation(getShaderProgram()->getProgram(), "u_textColor");
}

void Label::setFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled /* = false */, bool useA8Shader /* = false */)
{
    if (atlas == _fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(atlas);
        return;
    }

    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = NULL;
    }

    _fontAtlas = atlas;

    if (m_pobTextureAtlas)
    {
        m_pobTextureAtlas->setTexture(_fontAtlas->getTexture(0));
    }
    else
    {
        CCSpriteBatchNode::initWithTexture(_fontAtlas->getTexture(0), 30);
    }

    if (_reusedLetter == NULL)
    {
        _reusedLetter = CCSprite::create();
        _reusedLetter->setOpacityModifyRGB(_isOpacityModifyRGB);            
        _reusedLetter->retain();
        _reusedLetter->setAnchorPoint(CCPoint(0,1.0));
    }
    _reusedLetter->setBatchNode(this);

    if (_fontAtlas)
    {
        _commonLineHeight = _fontAtlas->getCommonLineHeight();
        _contentDirty = true;
    }
    _useDistanceField = distanceFieldEnabled;
    _useA8Shader = useA8Shader;

    if (_currentLabelType != kLabelTypeTTF)
    {
        _currLabelEffect = kLabelEffectNORMAL;
        updateShaderProgram();
    }
}

bool Label::setTTFConfig(const TTFConfig& ttfConfig)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasTTF(ttfConfig);

    if (!newAtlas)
    {
        reset();
        return false;
    }
    _systemFontDirty = false;

    _currentLabelType = kLabelTypeTTF;
    setFontAtlas(newAtlas,ttfConfig.distanceFieldEnabled,true);

    _fontConfig = ttfConfig;
    if (_fontConfig.outlineSize > 0)
    {
        _fontConfig.distanceFieldEnabled = false;
        _useDistanceField = false;
        _useA8Shader = false;
        _currLabelEffect = kLabelEffectOUTLINE;
        updateShaderProgram();
    }
    else 
    {
        _currLabelEffect = kLabelEffectNORMAL;
        updateShaderProgram();
        if(ttfConfig.distanceFieldEnabled)
        {
            this->setFontScale(1.0f * ttfConfig.fontSize / DistanceFieldFontSize);
        }
    }

    return true;
}

bool Label::setBMFontFilePath(const std::string& bmfontFilePath, const CCPoint& imageOffset /* = Vec2::ZERO */)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath,imageOffset);

    if (!newAtlas)
    {
        reset();
        return false;
    }
    _bmFontPath = bmfontFilePath;
    _currentLabelType = kLabelTypeBMFONT;
    setFontAtlas(newAtlas);

    return true;
}

void Label::setString(const std::string& text)
{
    if (text.compare(_originalUTF8String))
    {
        _originalUTF8String = text;
        _contentDirty = true;

        unsigned short* utf16String=cc_utf8_to_utf16(text.c_str());
        setCurrentUTF16String(utf16String);
        CC_SAFE_DELETE_ARRAY(utf16String);
    }
}

void Label::setString(const char *label)
{
    setString(std::string(label));
}

void Label::setCurrentUTF16String(unsigned short* newString)
{
    unsigned short* tmp = _currentUTF16String;
    _currentUTF16String = copyUTF16StringN(newString);
    CC_SAFE_DELETE_ARRAY(tmp);
}

void Label::setAlignment(CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
    if (hAlignment != _hAlignment || vAlignment != _vAlignment)
    {
        _hAlignment = hAlignment;
        _vAlignment = vAlignment;

        _contentDirty = true;
    }
}

void Label::setMaxLineWidth(unsigned int maxLineWidth)
{
    if (_labelWidth == 0 && _maxLineWidth != maxLineWidth)
    {
        _maxLineWidth = maxLineWidth;
        _contentDirty = true;
    }
}

void Label::setDimensions(unsigned int width,unsigned int height)
{
    if (height != _labelHeight || width != _labelWidth)
    {
        _labelWidth = width;
        _labelHeight = height;
        _labelDimensions.width = width;
        _labelDimensions.height = height;

        _maxLineWidth = width;
        _contentDirty = true;
    }  
}

void Label::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
    if (breakWithoutSpace != _lineBreakWithoutSpaces)
    {
        _lineBreakWithoutSpaces = breakWithoutSpace;
        _contentDirty = true;     
    }
}

void Label::setScale(float scale)
{
    if (_useDistanceField)
    {
        scale *= _fontScale;
    } 
    CCNode::setScale(scale);
}

void Label::setScaleX(float scaleX)
{
    if (_useDistanceField)
    {
        scaleX *= _fontScale;
    } 
    CCNode::setScaleX(scaleX);
}

void Label::setScaleY(float scaleY)
{
    if (_useDistanceField)
    {
        scaleY *= _fontScale;
    } 
    CCNode::setScaleY(scaleY);
}

float Label::getScaleY() const
{
    if (_useDistanceField)
    {
        return m_fScaleY / _fontScale;
    }
    else
    {
        return m_fScaleY;
    }
}

float Label::getScaleX() const
{
    if (_useDistanceField)
    {
        return m_fScaleX / _fontScale;
    }
    else
    {
        return m_fScaleX;
    }
}

void Label::alignText()
{
    if (_fontAtlas == NULL || _currentUTF16String==NULL)
    {
        return;
    }

    for (std::vector<CCSpriteBatchNode*>::iterator batchNodeIter=_batchNodes.begin();batchNodeIter!=_batchNodes.end();++batchNodeIter)
    {
        (*batchNodeIter)->getTextureAtlas()->removeAllQuads();
    }
    _fontAtlas->prepareLetterDefinitions(_currentUTF16String);
    std::map<ssize_t, CCTexture2D*> textures = _fontAtlas->getTextures();
    if (textures.size() > _batchNodes.size())
    {
        for (int index = _batchNodes.size(); index < textures.size(); ++index)
        {
            CCSpriteBatchNode* batchNode = CCSpriteBatchNode::createWithTexture(textures[index]);
            batchNode->setAnchorPoint(CCPoint(0,1.0));
            batchNode->setPosition(CCPointZero);
            CCNode::addChild(batchNode,0,kCCNodeTagInvalid);
            _batchNodes.push_back(batchNode);
        }
    }
    LabelTextFormatter::createStringSprites(this);    
    if(_maxLineWidth > 0 && m_obContentSize.width > _maxLineWidth && LabelTextFormatter::multilineText(this) )
        LabelTextFormatter::createStringSprites(this);

    if(_labelWidth > 0 || (_currNumLines > 1 && _hAlignment != kCCTextAlignmentLeft))
        LabelTextFormatter::alignText(this);

    int strLen = cc_wcslen(_currentUTF16String);
    CCRect uvRect;
    CCSprite* letterSprite;
    
    CCObject* pObj;
    CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCNode* child = (CCNode*) pObj;

        int tag = child->getTag();
        if(tag >= strLen)
        {
            CCSpriteBatchNode::removeChild(child, true);
        }
        else if(tag >= 0)
        {
            letterSprite = dynamic_cast<CCSprite*>(child);
            if (letterSprite)
            {
                uvRect.size.height = _lettersInfo[tag].def.height;
                uvRect.size.width  = _lettersInfo[tag].def.width;
                uvRect.origin.x    = _lettersInfo[tag].def.U;
                uvRect.origin.y    = _lettersInfo[tag].def.V;

                letterSprite->setTexture(textures[_lettersInfo[tag].def.textureID]);
                letterSprite->setTextureRect(uvRect);
            }          
        }
    }

    updateQuads();

    updateColor();
}

//bool Label::computeHorizontalKernings(const std::u16string& stringToRender)
bool Label::computeHorizontalKernings(unsigned short* stringToRender)
{
    if (_horizontalKernings)
    {
        delete [] _horizontalKernings;
        _horizontalKernings = NULL;
    }

    int letterCount = 0;
    _horizontalKernings = _fontAtlas->getFont()->getHorizontalKerningForTextUTF16(stringToRender, letterCount);

    if(!_horizontalKernings)
        return false;
    else
        return true;
}

void Label::updateQuads()
{
    int index;
    for (int ctr = 0; ctr < _limitShowCount; ++ctr)
    {
        FontLetterDefinition letterDef = _lettersInfo[ctr].def;

        if (letterDef.validDefinition)
        {
            _reusedRect.size.height = letterDef.height;
            _reusedRect.size.width  = letterDef.width;
            _reusedRect.origin.x    = letterDef.U;
            _reusedRect.origin.y    = letterDef.V;
            _reusedLetter->setTextureRect(_reusedRect,false,_reusedRect.size);

            _reusedLetter->setPosition(_lettersInfo[ctr].position);
            index = static_cast<int>(_batchNodes[letterDef.textureID]->getTextureAtlas()->getTotalQuads());
            _lettersInfo[ctr].atlasIndex = index;
            _batchNodes[letterDef.textureID]->insertQuadFromSprite(_reusedLetter,index);
        }     
    }
}

bool Label::recordLetterInfo(const cocos2d::CCPoint& point,const FontLetterDefinition& letterDef, int spriteIndex)
{
    if (static_cast<std::size_t>(spriteIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }

    _lettersInfo[spriteIndex].def = letterDef;
    _lettersInfo[spriteIndex].position = point;
    _lettersInfo[spriteIndex].contentSize.width = _lettersInfo[spriteIndex].def.width;
    _lettersInfo[spriteIndex].contentSize.height = _lettersInfo[spriteIndex].def.height;
    _limitShowCount++;

    return _lettersInfo[spriteIndex].def.validDefinition;
}

bool Label::recordPlaceholderInfo(int spriteIndex)
{
    if (static_cast<std::size_t>(spriteIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }

    _lettersInfo[spriteIndex].def.validDefinition = false;
    _limitShowCount++;

    return false;
}

void Label::addChild(CCNode * child, int zOrder/* =0 */, int tag/* =0 */)
{
    CCAssert(0, "addChild: is not supported on Label.");
}

void Label::sortAllChildren()
{
    // Label ignore sort children
}

void Label::enableGlow(const ccColor4B& glowColor)
{
    if (_currentLabelType == kLabelTypeTTF)
    {
        if (_fontConfig.distanceFieldEnabled == false)
        {
            TTFConfig config = _fontConfig;
            config.outlineSize = 0;
            config.distanceFieldEnabled = true;
            setTTFConfig(config);
            _contentDirty = true;
        }
        _currLabelEffect = kLabelEffectGLOW;
        _effectColor = glowColor;
        _effectColorF.r = _effectColor.r / 255.0f;
        _effectColorF.g = _effectColor.g / 255.0f;
        _effectColorF.b = _effectColor.b / 255.0f;
        _effectColorF.a = _effectColor.a / 255.0f;
        updateShaderProgram();
    }
}

void Label::enableOutline(const ccColor4B& outlineColor,int outlineSize /* = -1 */)
{
    CCAssert(_currentLabelType == kLabelTypeSTRING_TEXTURE || _currentLabelType == kLabelTypeTTF, "Only supported system font and TTF!");

    _effectColor = outlineColor;
    _effectColorF.r = _effectColor.r / 255.0f;
    _effectColorF.g = _effectColor.g / 255.0f;
    _effectColorF.b = _effectColor.b / 255.0f;
    _effectColorF.a = _effectColor.a / 255.0f;

    if (outlineSize > 0)
    {
        _outlineSize = outlineSize;
        if (_currentLabelType == kLabelTypeTTF)
        {
            if (_fontConfig.outlineSize != outlineSize)
            { 
                TTFConfig config = _fontConfig;
                config.outlineSize = outlineSize;
                setTTFConfig(config);
                updateShaderProgram();
            }
        }

        _currLabelEffect = kLabelEffectOUTLINE;
        _contentDirty = true;
    }
}

void Label::enableShadow(const ccColor4B& shadowColor /* = Color4B::BLACK */,const CCSize &offset /* = Size(2 ,-2)*/, int blurRadius /* = 0 */)
{
    _shadowEnabled = true;
    _shadowDirty = true;

    _shadowColor.r = shadowColor.r;
    _shadowColor.g = shadowColor.g;
    _shadowColor.b = shadowColor.b;
    _shadowOpacity = shadowColor.a / 255.0f;
    
    _shadowColorF.r = _shadowColor.r / 255.0f;
    _shadowColorF.g = _shadowColor.g / 255.0f;
    _shadowColorF.b = _shadowColor.b / 255.0f;
    _shadowColorF.a = _shadowOpacity;

    float contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
    _shadowOffset.width = offset.width * contentScaleFactor;
    _shadowOffset.height = offset.height * contentScaleFactor;
    //TODO: support blur for shadow
    _shadowBlurRadius = 0;

    if (_textSprite && _shadowNode)
    {
        _shadowNode->setColor(_shadowColor);
        _shadowNode->setOpacity(_shadowOpacity * _displayedOpacity);
        _shadowNode->setPosition(CCPoint(_shadowOffset.width, _shadowOffset.height));
    }
}

void Label::disableEffect()
{
    if (_currLabelEffect == kLabelEffectOUTLINE)
    {
        _fontConfig.outlineSize = 0;
        setTTFConfig(_fontConfig);
    }
    _currLabelEffect = kLabelEffectNORMAL;
    updateShaderProgram();
    _contentDirty = true;
    _shadowEnabled = false;
    if (_shadowNode)
    {
        CCNode::removeChild(_shadowNode,true);
        _shadowNode = NULL;
    }
}

void Label::setFontScale(float fontScale)
{
    _fontScale = fontScale * CC_CONTENT_SCALE_FACTOR();
    CCNode::setScale(_fontScale);
}

void Label::shadowTransform()
{
    kmMat4 transfrom4x4;
    
    // Convert 3x3 into 4x4 matrix
    CGAffineToGL(&_shadowTransform, transfrom4x4.mat);
    
    // Update Z vertex manually
    transfrom4x4.mat[14] = m_fVertexZ;
    
    kmGLMultMatrix( &transfrom4x4 );
}

void Label::onDraw(/*const CCAffineTransform& transform, bool transformUpdated*/)
{
    CC_PROFILER_START("Label - draw");

    // Optimization: Fast Dispatch
    if( _batchNodes.size() == 1 && m_pobTextureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    CCGLProgram* glprogram = getShaderProgram();
    glprogram->use();
    
    ccGLBlendFunc(m_blendFunc.src,m_blendFunc.dst);

    if(_shadowEnabled && _shadowBlurRadius <= 0)
    {
        drawShadowWithoutBlur();
    }
    
    if (_currentLabelType == kLabelTypeTTF)
    {
        glprogram->setUniformLocationWith4f(_uniformTextColor,
                                            _textColorF.r,_textColorF.g,_textColorF.b,_textColorF.a);
    }
    
    if (_currLabelEffect == kLabelEffectOUTLINE || _currLabelEffect == kLabelEffectGLOW)
    {
        glprogram->setUniformLocationWith4f(_uniformEffectColor,
                                            _effectColorF.r,_effectColorF.g,_effectColorF.b,_effectColorF.a);
    }

    glprogram->setUniformsForBuiltins();

    
//    CCNode* child = NULL;
//    unsigned int i = 0;
//    
//    if(m_pChildren && m_pChildren->count() > 0)
//    {
//        ccArray *arrayData = m_pChildren->data;
//        for( ; i < arrayData->num; i++ )
//        {
//            child = (CCNode*) arrayData->arr[i];
//            
//            if(child->getTag() >= 0)
//                child->updateTransform();
//        }
//    }

    for (std::vector<CCSpriteBatchNode*>::iterator batchNodeIter=_batchNodes.begin();batchNodeIter!=_batchNodes.end();++batchNodeIter)
    {
        (*batchNodeIter)->getTextureAtlas()->drawQuads();
    }

    CC_PROFILER_STOP("Label - draw");
}

void Label::drawShadowWithoutBlur()
{
    ccColor3B oldColor = _realColor;
    GLubyte oldOPacity = _displayedOpacity;
    _displayedOpacity = _shadowOpacity * _displayedOpacity;
    setColor(_shadowColor);
    
    kmGLPushMatrix();
    
    shadowTransform();
    
    getShaderProgram()->setUniformsForBuiltins();
    getShaderProgram()->setUniformLocationWith4f(_uniformTextColor,
                                        _shadowColorF.r,_shadowColorF.g,_shadowColorF.b,_shadowColorF.a);
    
//    CCNode* child = NULL;
//    unsigned int i = 0;
//    
//    if(m_pChildren && m_pChildren->count() > 0)
//    {
//        ccArray *arrayData = m_pChildren->data;
//        for( ; i < arrayData->num; i++ )
//        {
//            child = (CCNode*) arrayData->arr[i];
//            child->updateTransform();
//        }
//    }
    
    for (std::vector<CCSpriteBatchNode*>::iterator batchNodeIter=_batchNodes.begin();batchNodeIter!=_batchNodes.end();++batchNodeIter)
    {
        (*batchNodeIter)->getTextureAtlas()->drawQuads();
    }
    
    kmGLPopMatrix();
    
    _displayedOpacity = oldOPacity;
    setColor(oldColor);
}

void Label::draw(/*Renderer *renderer, const Mat4 &transform, uint32_t flags*/)
{
    // Don't do calculate the culling if the transform was not updated
//    bool transformUpdated = flags & FLAGS_TRANSFORM_DIRTY;
//    _insideBounds = transformUpdated ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
//
//    if(_insideBounds) {
//        _customCommand.init(_globalZOrder);
//        _customCommand.func = CC_CALLBACK_0(Label::onDraw, this, transform, transformUpdated);
//        renderer->addCommand(&_customCommand);
//    }
    
//    CCSpriteBatchNode::draw();
    
    onDraw();
}

void Label::setColor(const ccColor3B& color3)
{
    _displayedColor = _realColor = color3;
    
    ccColor3B parentColor = ccWHITE;
    CCRGBAProtocol *parent = dynamic_cast<CCRGBAProtocol*>(m_pParent);
    if (parent && parent->isCascadeColorEnabled())
    {
        parentColor = parent->getDisplayedColor();
    }
    
    updateDisplayedColor(parentColor);
}

void Label::createSpriteWithFontDefinition()
{
    _currentLabelType = kLabelTypeSTRING_TEXTURE;

    CCTexture2D* texture = new CCTexture2D();
    texture->initWithString(_originalUTF8String.c_str(),&_fontDefinition);

    _textSprite = CCSprite::createWithTexture(texture);
    _textSprite->setAnchorPoint(CCPoint(0,0));
    this->setContentSize(_textSprite->getContentSize());
    texture->release();
    if (_blendFuncDirty)
    {
        _textSprite->setBlendFunc(m_blendFunc);
    }

    CCNode::addChild(_textSprite,0,kCCNodeTagInvalid);

    _textSprite->updateDisplayedColor(_displayedColor);
    _textSprite->updateDisplayedOpacity(_displayedOpacity);
}

void Label::setFontDefinition(const ccFontDefinition& textDefinition)
{
    _fontDefinition = textDefinition;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    if (_fontDefinition._stroke._strokeEnabled)
    {
        CCLOGERROR("Currently only supported on iOS and Android!");
    }
    _fontDefinition._stroke._strokeEnabled = false;
#endif
    if (_fontDefinition.m_shadow.m_shadowEnabled)
    {
        _fontDefinition.m_shadow.m_shadowEnabled = false;
        enableShadow(ccc4(0,0,0,255 * _fontDefinition.m_shadow.m_shadowOpacity),_fontDefinition.m_shadow.m_shadowOffset,_fontDefinition.m_shadow.m_shadowBlur);
    }
    _compatibleMode = true;
}

void Label::updateContent()
{
    unsigned short* utf16String=cc_utf8_to_utf16(_originalUTF8String.c_str());
    setCurrentUTF16String(utf16String);
    CC_SAFE_DELETE_ARRAY(utf16String);

    computeStringNumLines();
    if (_fontAtlas)
    {
        computeHorizontalKernings(_currentUTF16String);
    }

    if (_textSprite)
    {
        CCNode::removeChild(_textSprite,true);
        _textSprite = NULL;
        if (_shadowNode)
        {
            CCNode::removeChild(_shadowNode,true);
            _shadowNode = NULL;
        }
    }

    if (_fontAtlas)
    {
        alignText();
    }
    else
    {
        if (!_compatibleMode)
        {
            _fontDefinition.m_fontName = _systemFont;
            _fontDefinition.m_fontSize = _systemFontSize;

            _fontDefinition.m_alignment = _hAlignment;
            _fontDefinition.m_vertAlignment = _vAlignment;

            _fontDefinition.m_dimensions.width = _labelWidth;
            _fontDefinition.m_dimensions.height = _labelHeight;

            _fontDefinition.m_fontFillColor.r = _textColor.r;
            _fontDefinition.m_fontFillColor.g = _textColor.g;
            _fontDefinition.m_fontFillColor.b = _textColor.b;

            _fontDefinition.m_shadow.m_shadowEnabled = false;

            if (_currLabelEffect == kLabelEffectOUTLINE && _outlineSize > 0)
            {
                _fontDefinition.m_stroke.m_strokeEnabled = true;
                _fontDefinition.m_stroke.m_strokeSize = _outlineSize;
                _fontDefinition.m_stroke.m_strokeColor.r = _effectColor.r;
                _fontDefinition.m_stroke.m_strokeColor.g = _effectColor.g;
                _fontDefinition.m_stroke.m_strokeColor.b = _effectColor.b;
            }
            else
            {
                _fontDefinition.m_stroke.m_strokeEnabled = false;
            }

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
            if (_fontDefinition.m_stroke.m_strokeEnabled)
            {
                CCLOGERROR("Currently only supported on iOS and Android!");
            }
            _fontDefinition.m_stroke.m_strokeEnabled = false;
#endif
        }

        createSpriteWithFontDefinition();
    }
    _contentDirty = false;
}

void Label::updateFont()
{
    if (_fontAtlas)
    {
        _batchNodes.clear();
        _batchNodes.push_back(this);

        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = NULL;
    }

    _contentDirty = true;
    _systemFontDirty = false;
}

void Label::drawTextSprite()
{
    if (_fontDefinition.m_fontFillColor.r != _textColor.r || _fontDefinition.m_fontFillColor.g != _textColor.g
        || _fontDefinition.m_fontFillColor.b != _textColor.b)
    {
        updateContent();
    }
    
    if (_shadowEnabled && _shadowNode == NULL)
    {
        _shadowNode = CCSprite::createWithTexture(_textSprite->getTexture());
        if (_shadowNode)
        {
            if (_blendFuncDirty)
            {
                _shadowNode->setBlendFunc(m_blendFunc);
            }
            _shadowNode->setAnchorPoint(CCPoint(0,0));
            _shadowNode->setColor(_shadowColor);
            _shadowNode->setOpacity(_shadowOpacity * _displayedOpacity);
            _shadowNode->setPosition(CCPoint(_shadowOffset.width, _shadowOffset.height));
            CCNode::addChild(_shadowNode,0,kCCNodeTagInvalid);
        }
    }
    if (_shadowNode)
    {
        _shadowNode->visit();
    }
    _textSprite->visit();
}

void Label::visit()
{
    if (! m_bVisible || _originalUTF8String.empty())
    {
        return;
    }
    
    if (_systemFontDirty)
    {
        updateFont();
    }
    
    if (_contentDirty)
    {
        updateContent();
    }
    
    kmGLPushMatrix();
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        transformAncestors();
    }
    
    sortAllChildren();
    
    transform();

//    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    if (_shadowEnabled && _shadowBlurRadius <= 0 && (_shadowDirty /*|| (flags & FLAGS_DIRTY_MASK)*/))
    {
//        m_obPosition.x += _shadowOffset.width;
//        m_obPosition.y += _shadowOffset.height;
//        m_bTransformDirty = m_bInverseDirty = true;

        _shadowTransform =CCAffineTransformTranslate(CCAffineTransformIdentity, _shadowOffset.width, _shadowOffset.height);

//        m_obPosition.x -= _shadowOffset.width;
//        m_obPosition.y -= _shadowOffset.height;
//        m_bTransformDirty = m_bInverseDirty = true;

        _shadowDirty = false;
    }

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
//    Director* director = Director::getInstance();
//    CCAssert(NULL != director, "Director is null when seting matrix stack");
//    
//    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    

    if (_textSprite)
    {
        drawTextSprite();
    }
    else
    {
        draw();
    }
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }
    
    kmGLPopMatrix();

//    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    // FIX ME: Why need to set _orderOfArrival to 0??
    // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
    // setOrderOfArrival(0);
}

void Label::setSystemFontName(const std::string& systemFont)
{
    if (systemFont != _systemFont)
    {
        _systemFont = systemFont;
        _systemFontDirty = true;
    }
}

void Label::setSystemFontSize(float fontSize)
{
    if (_systemFontSize != fontSize)
    {
        _systemFontSize = fontSize;
        _systemFontDirty = true;
    }
}

///// PROTOCOL STUFF
CCSprite * Label::getLetter(int letterIndex)
{
    if (_systemFontDirty || _currentLabelType == kLabelTypeSTRING_TEXTURE)
    {
        return NULL;
    }

    if (_contentDirty)
    {
        updateContent();
    }
    
    if (! _textSprite && letterIndex < _limitShowCount)
    {
        const LetterInfo letter = _lettersInfo[letterIndex];

        if(! letter.def.validDefinition)
            return NULL;

        CCSprite* sp = static_cast<CCSprite*>(this->getChildByTag(letterIndex));

        if (!sp)
        {
            CCRect uvRect;
            uvRect.size.height = letter.def.height;
            uvRect.size.width  = letter.def.width;
            uvRect.origin.x    = letter.def.U;
            uvRect.origin.y    = letter.def.V;

            sp = CCSprite::createWithTexture(_fontAtlas->getTexture(letter.def.textureID),uvRect);
            sp->setBatchNode(_batchNodes[letter.def.textureID]);
            sp->setPosition(CCPoint(letter.position.x + uvRect.size.width / 2,
                letter.position.y - uvRect.size.height / 2));
            sp->setOpacity(_realOpacity);

            _batchNodes[letter.def.textureID]->addSpriteWithoutQuad(sp, letter.atlasIndex, letterIndex);
        }
        return sp;
    }

    return NULL;
}

void Label::setLineHeight(float height)
{
    CCAssert(_currentLabelType != kLabelTypeSTRING_TEXTURE, "Not supported system font!");

    if (_commonLineHeight != height)
    {
        _commonLineHeight = height;
        _contentDirty = true;
    }
}

float Label::getLineHeight() const
{
    CCAssert(_currentLabelType != kLabelTypeSTRING_TEXTURE, "Not supported system font!");
    return _textSprite ? 0.0f : _commonLineHeight;
}

void Label::setAdditionalKerning(float space)
{
    CCAssert(_currentLabelType != kLabelTypeSTRING_TEXTURE, "Not supported system font!");
    if (_additionalKerning != space)
    {
        _additionalKerning = space;
        _contentDirty = true;
    }
}

float Label::getAdditionalKerning() const
{
    CCAssert(_currentLabelType != kLabelTypeSTRING_TEXTURE, "Not supported system font!");

    return _additionalKerning;
}

void Label::computeStringNumLines()
{
    int quantityOfLines = 1;

    if (_currentUTF16String)
    {
        _currNumLines = 0;
        return;
    }

    // count number of lines
    size_t stringLen =cc_wcslen(_currentUTF16String);
    for (size_t i = 0; i < stringLen-1; ++i)
    {
        if (_currentUTF16String[i] == '\n')
        {
            quantityOfLines++;
        }
    }

    _currNumLines = quantityOfLines;
}

int Label::getStringLength() const
{
    return _currentUTF16String?cc_wcslen(_currentUTF16String):0;
}

// RGBA protocol
bool Label::isOpacityModifyRGB() const
{
    return _isOpacityModifyRGB;
}

void Label::setOpacityModifyRGB(bool isOpacityModifyRGB)
{
    _isOpacityModifyRGB = isOpacityModifyRGB;

    CCObject* pObj=NULL;
    CCNodeRGBA* child;
    
    CCARRAY_FOREACH(m_pChildren, pObj){
        child=dynamic_cast<CCNodeRGBA*>(pObj);
        if (child) {
            child->setOpacityModifyRGB(_isOpacityModifyRGB);
        }
    }
    _reusedLetter->setOpacityModifyRGB(true);
}

void Label::updateDisplayedColor(const ccColor3B& parentColor)
{
    _displayedColor.r = _realColor.r * parentColor.r/255.0;
    _displayedColor.g = _realColor.g * parentColor.g/255.0;
    _displayedColor.b = _realColor.b * parentColor.b/255.0;
    updateColor();

    if (_textSprite)
    {
        _textSprite->updateDisplayedColor(_displayedColor);
        if (_shadowNode)
        {
            _shadowNode->updateDisplayedColor(_displayedColor);
        }
    }
}

void Label::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
    updateColor();

    if (_textSprite)
    {
        _textSprite->updateDisplayedOpacity(_displayedOpacity);
        if (_shadowNode)
        {
            _shadowNode->updateDisplayedOpacity(_displayedOpacity);
        }
    }
}

void Label::setTextColor(const ccColor4B &color)
{
    CCAssert(_currentLabelType == kLabelTypeTTF || _currentLabelType == kLabelTypeSTRING_TEXTURE, "Only supported system font and ttf!");

    _textColor = color;
    _textColorF.r = _textColor.r / 255.0f;
    _textColorF.g = _textColor.g / 255.0f;
    _textColorF.b = _textColor.b / 255.0f;
    _textColorF.a = _textColor.a / 255.0f;
}

void Label::updateColor()
{
    if (NULL == m_pobTextureAtlas)
    {
        return;
    }

    ccColor4B color4=ccc4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );

    // special opacity for premultiplied textures
    if (_isOpacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }

    CCTextureAtlas* textureAtlas;
    ccV3F_C4B_T2F_Quad *quads;
    for (std::vector<CCSpriteBatchNode*>::iterator batchNodeIter=_batchNodes.begin();batchNodeIter!=_batchNodes.end();++batchNodeIter)
    {
        textureAtlas = (*batchNodeIter)->getTextureAtlas();
        quads = textureAtlas->getQuads();
        unsigned int count = textureAtlas->getTotalQuads();

        for (int index = 0; index < count; ++index)
        {
            quads[index].bl.colors = color4;
            quads[index].br.colors = color4;
            quads[index].tl.colors = color4;
            quads[index].tr.colors = color4;
            textureAtlas->updateQuad(&quads[index], index);
        }
    }
}

std::string Label::getDescription() const
{
//    std::string utf8str;
//    StringUtils::UTF16ToUTF8(_currentUTF16String, utf8str);
    return CCString::createWithFormat("<Label | Tag = %d, Label = '%s'>", m_nTag, _originalUTF8String.c_str())->getCString();
}

const CCSize& Label::getContentSize() const
{
    if (_systemFontDirty)
    {
        const_cast<Label*>(this)->updateFont();
    }
    if (_contentDirty)
    {
        const_cast<Label*>(this)->updateContent();
    }
    return m_obContentSize;
}

CCRect Label::getBoundingBox()
{
    const_cast<Label*>(this)->getContentSize();

    return CCNode::boundingBox();
}

void Label::setBlendFunc(const ccBlendFunc &blendFunc)
{
    m_blendFunc = blendFunc;
    _blendFuncDirty = true;
    if (_textSprite)
    {
        _textSprite->setBlendFunc(blendFunc);
        if (_shadowNode)
        {
            _shadowNode->setBlendFunc(blendFunc);
        }
    }
}

NS_CC_END
