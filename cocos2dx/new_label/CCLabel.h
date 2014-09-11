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


#ifndef _COCOS2D_CCLABEL_H_
#define _COCOS2D_CCLABEL_H_

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "CCFontAtlas.h"
#include <vector>

NS_CC_BEGIN

enum GlyphCollection {
    
    kGlyphCollectionDYNAMIC,
    kGlyphCollectionNEHE,
    kGlyphCollectionASCII,
    kGlyphCollectionCUSTOM
};

enum LabelEffect {

    kLabelEffectNORMAL,
    kLabelEffectOUTLINE,
    kLabelEffectSHADOW,
    kLabelEffectGLOW
};

typedef struct _ttfConfig
{
    std::string fontFilePath;
    int fontSize;
    GlyphCollection glyphs;
    const char *customGlyphs;
    bool distanceFieldEnabled;
    int outlineSize;

    _ttfConfig(const char* filePath = "",int size = 12, const GlyphCollection& glyphCollection = kGlyphCollectionDYNAMIC,
        const char *customGlyphCollection = NULL,bool useDistanceField = false,int outline = 0)
        :fontFilePath(filePath)
        ,fontSize(size)
        ,glyphs(glyphCollection)
        ,customGlyphs(customGlyphCollection)
        ,distanceFieldEnabled(useDistanceField)
        ,outlineSize(outline)
    {
        if(outline > 0)
        {
            distanceFieldEnabled = false;
        }
    }
}TTFConfig;

class CC_DLL Label : public CCSpriteBatchNode, public CCLabelProtocol
{
public:
    static const int DistanceFieldFontSize;

    static Label* create();

    /** Creates a label with an initial string,font[font name or font file],font size, dimension in points, horizontal alignment and vertical alignment.
     * @warning It will generate texture by the platform-dependent code
     */
    static Label* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const CCSize& dimensions = CCSizeZero, CCTextAlignment hAlignment = kCCTextAlignmentLeft,
        CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop);

    /** Creates a label with an initial string,font file,font size, dimension in points, horizontal alignment and vertical alignment.
     * @warning Not support font name.
     * @warning Cache textures for each different font size or font file.
     */
    static Label * createWithTTF(const std::string& text, const std::string& fontFile, float fontSize,
        const CCSize& dimensions = CCSizeZero, CCTextAlignment hAlignment = kCCTextAlignmentLeft,
        CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop);

    /** Create a label with TTF configuration
     * @warning Not support font name.
     * @warning Cache textures for each different font file when enable distance field.
     * @warning Cache textures for each different font size or font file when disable distance field.
     */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, CCTextAlignment hAlignment = kCCTextAlignmentLeft, int maxLineWidth = 0);
    
    /* Creates a label with an FNT file,an initial string,horizontal alignment,max line width and the offset of image*/
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,
        const CCTextAlignment& alignment = kCCTextAlignmentLeft, int maxLineWidth = 0,
        const CCPoint& imageOffset = CCPointZero);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(CCTexture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    /** set TTF configuration for Label */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);
    virtual const TTFConfig& getTTFConfig() const { return _fontConfig;}

    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const CCPoint& imageOffset = CCPointZero);
    const std::string& getBMFontFilePath() const { return _bmFontPath;}

    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(CCTexture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(const std::string& plistFile);

    /* Sets the system font[font name or font file] of label*/
    virtual void setSystemFontName(const std::string& systemFont);
    virtual const std::string& getSystemFontName() const { return _systemFont;}

    /* Sets the system font size of label.*/
    virtual void setSystemFontSize(float fontSize);
    virtual float getSystemFontSize() const { return _systemFontSize;}

    /** changes the string to render
    * @warning It is as expensive as changing the string if you haven't set up TTF/BMFont/CharMap for the label.
    */
    virtual void setString(const std::string& text);

    virtual const std::string& getString() const {  return _originalUTF8String; }
    
    virtual void setString(const char *label);
    
    virtual const char* getString(void) {return _originalUTF8String.c_str();};
    

    /** Sets the text color of the label
     * Only support for TTF and system font
     * @warning Different from the color of Node.
     */
    virtual void setTextColor(const ccColor4B &color);
    /** Returns the text color of this label
     * Only support for TTF and system font
     * @warning Different from the color of Node.
     */
    const ccColor4B& getTextColor() const { return _textColor;}

    /**
     * Enable shadow for the label
     *
     * @todo support blur for shadow effect
     */
    virtual void enableShadow(const ccColor4B& shadowColor = ccc4(0, 0, 0, 255),const CCSize &offset = CCSize(2,-2), int blurRadius = 0);

    /** only support for TTF */
    virtual void enableOutline(const ccColor4B& outlineColor,int outlineSize = -1);

    /** only support for TTF */
    virtual void enableGlow(const ccColor4B& glowColor);

    /** disable shadow/outline/glow rendering */
    virtual void disableEffect();

    void setAlignment(CCTextAlignment hAlignment) { setAlignment(hAlignment,_vAlignment);}
    CCTextAlignment getTextAlignment() const { return _hAlignment;}

    void setAlignment(CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment);

    void setHorizontalAlignment(CCTextAlignment hAlignment) { setAlignment(hAlignment,_vAlignment); }
    CCTextAlignment getHorizontalAlignment() const { return _hAlignment; }

    void setVerticalAlignment(CCVerticalTextAlignment vAlignment) { setAlignment(_hAlignment,vAlignment); }
    CCVerticalTextAlignment getVerticalAlignment() const { return _vAlignment; }

    void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /** Sets the max line width of the label.
     * The label's max line width be used for force line breaks if the set value not equal zero.
     * The label's width and max line width has not always to be equal.
     */
    void setMaxLineWidth(unsigned int maxLineWidth);
    unsigned int getMaxLineWidth() { return _maxLineWidth;}

    /** Sets the untransformed size of the label.
     * The label's width be used for text align if the set value not equal zero.
     * The label's max line width will be equal to the same value.
     */
    void setWidth(unsigned int width) { setDimensions(width,_labelHeight);}
    unsigned int getWidth() const { return _labelWidth; }  

    /** Sets the untransformed size of the label.
     * The label's height be used for text align if the set value not equal zero.
     * The text will display of incomplete when the size of label not enough to support display all text.
     */
    void setHeight(unsigned int height){ setDimensions(_labelWidth,height);}
    unsigned int getHeight() const { return _labelHeight;}   

    /** Sets the untransformed size of the label in a more efficient way. */
    void setDimensions(unsigned int width,unsigned int height);
    const CCSize& getDimensions() const{ return _labelDimensions;}

    /** update content immediately.*/
    virtual void updateContent();

    virtual CCSprite * getLetter(int lettetIndex);

    /** clip upper and lower margin for reduce height of label.
     */
    void setClipMarginEnabled(bool clipEnabled) { _clipEnabled = clipEnabled; }
    bool isClipMarginEnabled() const { return _clipEnabled; }

    /** Sets the line height of the label
      @warning Not support system font
      @since v3.2.0
     */
    void setLineHeight(float height);
    /** Returns the line height of this label
      @warning Not support system font
     */
    float getLineHeight() const;

    /** Sets the additional kerning of the label
      @warning Not support system font
      @since v3.2.0
     */
    void setAdditionalKerning(float space);
    /** Returns the additional kerning of this label
      @warning Not support system font
      @since v3.2.0
     */
    float getAdditionalKerning() const;

    // string related stuff
    int getStringNumLines() const { return _currNumLines;}
    int getStringLength() const;

    FontAtlas* getFontAtlas() { return _fontAtlas; }
    
    virtual void setBlendFunc(const ccBlendFunc &blendFunc);

    virtual bool isOpacityModifyRGB() const;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);
    virtual void updateDisplayedColor(const ccColor3B& parentColor);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);

    virtual void setScale(float scale);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    virtual float getScaleX() const;
    virtual float getScaleY() const;

    virtual void addChild(CCNode * child, int zOrder=0, int tag=0);
    virtual void sortAllChildren();

    virtual std::string getDescription() const;

    virtual const CCSize& getContentSize() const;

    virtual CCRect getBoundingBox();

    virtual void visit();
    virtual void draw();

    CC_DEPRECATED_ATTRIBUTE static Label* create(const std::string& text, const std::string& font, float fontSize,
        const CCSize& dimensions = CCSizeZero, CCTextAlignment hAlignment = kCCTextAlignmentLeft,
        CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop);

    CC_DEPRECATED_ATTRIBUTE virtual void setFontDefinition(const ccFontDefinition& textDefinition);
    CC_DEPRECATED_ATTRIBUTE const ccFontDefinition& getFontDefinition() const { return _fontDefinition; }

    CC_DEPRECATED_ATTRIBUTE int getCommonLineHeight() const { return getLineHeight();}

protected:
    /**
     * @js NA
     */
    Label(FontAtlas *atlas = NULL, CCTextAlignment hAlignment = kCCTextAlignmentLeft,
      CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop,bool useDistanceField = false,bool useA8Shader = false);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Label();

protected:
    
    void setCurrentUTF16String(unsigned short* newString);
    
    void shadowTransform();
    
    void onDraw(/*const CCAffineTransform& transform, bool transformUpdated*/);
    
    struct LetterInfo
    {
        FontLetterDefinition def;

        CCPoint position;
        CCSize  contentSize;
        int   atlasIndex;
    };
    enum  LabelType {

        kLabelTypeTTF,
        kLabelTypeBMFONT,
        kLabelTypeCHARMAP,
        kLabelTypeSTRING_TEXTURE
    };

    virtual void setFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    bool recordLetterInfo(const CCPoint& point,const FontLetterDefinition& letterDef, int spriteIndex);
    bool recordPlaceholderInfo(int spriteIndex);

    void setFontScale(float fontScale);
    
    virtual void alignText();
    
    //bool computeHorizontalKernings(const std::u16string& stringToRender);
    bool computeHorizontalKernings(unsigned short* stringToRender);

    void computeStringNumLines();

    void updateQuads();

    virtual void updateColor();

    virtual void updateShaderProgram();

    void drawShadowWithoutBlur();

    void drawTextSprite();

    void createSpriteWithFontDefinition();

    void updateFont();
    void reset();

    std::string _bmFontPath;

    bool _isOpacityModifyRGB;
    bool _contentDirty;

    bool _systemFontDirty;
    std::string _systemFont;
    float         _systemFontSize;
    LabelType _currentLabelType;

    std::vector<CCSpriteBatchNode*> _batchNodes;
    FontAtlas *                   _fontAtlas;
    std::vector<LetterInfo>       _lettersInfo;

    TTFConfig _fontConfig;

    //compatibility with older LabelTTF
    CCSprite* _textSprite;
    ccFontDefinition _fontDefinition;
    bool  _compatibleMode;

    //! used for optimization
    CCSprite *_reusedLetter;
    CCRect _reusedRect;
    int _limitShowCount;

    float _additionalKerning;
    float _commonLineHeight;
    bool  _lineBreakWithoutSpaces;
    int * _horizontalKernings;

    unsigned int _maxLineWidth;
    CCSize         _labelDimensions;
    unsigned int _labelWidth;
    unsigned int _labelHeight;
    CCTextAlignment _hAlignment;
    CCVerticalTextAlignment _vAlignment;

    int           _currNumLines;
    unsigned short* _currentUTF16String;
    std::string          _originalUTF8String;

    float _fontScale;

    bool _useDistanceField;
    bool _useA8Shader;

    LabelEffect _currLabelEffect;
    ccColor4B _effectColor;
    ccColor4F _effectColorF;

    GLuint _uniformEffectColor;
    GLuint _uniformTextColor;
//    CustomCommand _customCommand;   

    bool    _shadowDirty;
    bool    _shadowEnabled;
    CCSize    _shadowOffset;
    int     _shadowBlurRadius;
    CCAffineTransform  _shadowTransform;
    ccColor3B _shadowColor;
    ccColor4F _shadowColorF;
    float   _shadowOpacity;
    CCSprite*   _shadowNode;

    int     _outlineSize;

    ccColor4B _textColor;
    ccColor4F _textColorF;

    bool _clipEnabled;
    bool _blendFuncDirty;
    bool _insideBounds;                     /// whether or not the sprite was inside bounds the previous frame

private:
    //CC_DISALLOW_COPY_AND_ASSIGN(Label);
    
    Label(const Label&);
    Label& operator =(const Label&);

    friend class LabelTextFormatter;
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
