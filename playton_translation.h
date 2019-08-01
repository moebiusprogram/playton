#ifndef PLAYTON_TRANSLATION_H
#define PLAYTON_TRANSLATION_H

#include "common.h"
#include "enumerations.h"

class playton_translation
{
    public:
        playton_translation();
        virtual ~playton_translation();
        typedef irr::core::map<irr::core::stringw, irr::core::stringw> translation;
        typedef irr::core::map<IGUIElement*, irr::core::stringw> localized;
        void localizedText( IGUIElement* element, irr::core::stringw text  );
        void setLanguage( languages lang );
        void translationSpanish();
        void translationEnglish();
        void translationFrench();
        irr::core::stringw getText( irr::core::stringw text );
        void changeLanguage();
        void setActiveLang( languages activeLang ) { this->activeLang = activeLang; }
        translation frances;
        translation ingles;
        translation espanol;
        localized local;
        languages activeLang;
    protected:

    private:
};

#endif // PLAYTON_TRANSLATION_H
