#include "common.h"
#include "playton_translation.h"


playton_translation::playton_translation()
{
    translationFrances();
    translationenglish();
    translationspanish();
}

playton_translation::~playton_translation()
{
    //dtor
}

void playton_translation::localizedText( IGUIElement* element, irr::core::stringw text  )
{
    local.insert( element, text  );
}

void playton_translation::setLanguage( languages lang )
{
    activeLang = lang;
}

void playton_translation::translationspanish()
{
    spanish.insert(L"instrutions",L"INSTRUCCIONES");
    spanish.insert(L"setup",L"CONFIGURACION");
    spanish.insert(L"play",L"JUGAR");
    spanish.insert(L"ilustration",L"ILUSTRACION");
    spanish.insert(L"credits",L"CREDITOS");
    spanish.insert(L"quit",L"SALIR");
}

void playton_translation::translationenglish()
{
    english.insert(L"instrutions",L"INSTRUCTIONS");
    english.insert(L"setup",L"CONFIGURATIONS");
    english.insert(L"play",L"PLAY");
    english.insert(L"ilustration",L"ILUSTRATION");
    english.insert(L"credits",L"CREDITS");
    english.insert(L"quit",L"QUIT");
}

void playton_translation::translationFrances()
{
    french.insert(L"instrutions",L"instrutions");
    french.insert(L"setup",L"setup");
    french.insert(L"play",L"play");
    french.insert(L"ilustration",L"ilustration");
    french.insert(L"credits",L"credits");
    french.insert(L"quit",L"quit");
}

irr::core::stringw playton_translation::getText( irr::core::stringw text )
{
    irr::core::stringw translatedText = L"";

    switch( activeLang )
    {
        case PLAYTON_ENGLISH:
        {
            translation::Node* n = english.find( text );

            if( n )
            {
                translatedText = n->getValue();
            }

        }
        break;
        case PLAYTON_SPANISH:
        {
            translation::Node* n = spanish.find( text );

            if( n )
            {
                translatedText = n->getValue();
            }
        }
        break;
        case PLAYTON_FRENCH:
        {
            translation::Node* n = french.find( text );

            if( n )
            {
                translatedText = n->getValue();
            }
        }
        break;
        default:
            break;
    }

    return translatedText;
}

void playton_translation::changeLanguage()
{
    localized::Iterator i = local.getIterator();
    for(; !i.atEnd(); i++)
    {
        IGUIElement* element = i->getKey();
        irr::core::stringw text = getText( i->getValue() );

        element->setText( text.c_str() );
    }
}
