#include "font_manager.h"
#include "gui_freetype_font.h"

FontManager::FontManager(irr::IrrlichtDevice* device)
: device(device)
{
}

FontManager::~FontManager()
{
    FontMap::iterator itFont = mFontMap.begin();
    for ( ; itFont != mFontMap.end(); ++itFont )
    {
        itFont->second->drop();
    }

    FaceMap::iterator itFace = mFaceMap.begin();
    for ( ; itFace != mFaceMap.end(); ++itFace )
    {
        itFace->second->drop();
    }
}

IGUIFont* FontManager::GetTtFont( const char* filename_, unsigned int size_, bool antiAlias_, bool transparency_)
{
    if ( !filename_ || !strlen(filename_) )
        return NULL;

    irr::core::stringc fontString(MakeFontIdentifier(filename_, size_, antiAlias_, transparency_));
    FontMap::iterator itFont = mFontMap.find(fontString);
    if  (itFont != mFontMap.end() )
        return itFont->second;

    irr::core::stringc faceName(filename_);
    CGUITTFace * face = NULL;
    FaceMap::iterator itFace = mFaceMap.find(faceName);
    if  (itFace != mFaceMap.end() )
    {
        face = itFace->second;
    }

    if ( !face )
    {
        face = new CGUITTFace(device);
        if ( !face->load(filename_) )
        {
            face->drop();
            return NULL;
        }
        mFaceMap[faceName] = face;
    }

    CGUIFreetypeFont * font = new CGUIFreetypeFont(device);

    font->attach(face, size_);
    font->AntiAlias = antiAlias_;
    font->Transparency = transparency_;
    mFontMap[fontString] = font;

    return font;
}

irr::core::stringc FontManager::MakeFontIdentifier(const char* filename_, unsigned int size_, bool antiAlias_, bool transparency_)
{
    irr::core::stringc strValue("");

    strValue += filename_;
    strValue += " ";
    strValue += size_;

    if ( antiAlias_ )
        strValue += 'a';

    if ( transparency_ )
        strValue += 'a';

    return strValue;
}