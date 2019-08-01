#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

//#include <string>
#include <map>
#include <irrlicht.h>

namespace irr
{
namespace gui
{
    class IGUIFont;
};
};
class CGUITTFace;

class FontManager
{
public:
    FontManager(irr::IrrlichtDevice* device);
    ~FontManager();
    IGUIFont* GetTtFont( const char* filename_, unsigned int size_, bool antiAlias_=true, bool transparency_=true);

protected:
    irr::core::stringc MakeFontIdentifier(const char* filename_, unsigned int size_, bool antiAlias_, bool transparency_);

private:
    irr::IrrlichtDevice* device;
    typedef std::map<irr::core::stringc, CGUITTFace*> FaceMap;
    FaceMap mFaceMap;

    typedef std::map<irr::core::stringc, IGUIFont*> FontMap;
    FontMap mFontMap;
};

#endif // FONT_MANAGER_H