#include "playtonGame.h"

void playtonGame::createNumberCharts()
{
    number1 = guienv->addStaticText(L"0",rect<s32>(0,0,1,1));
    number1->setRelativePositionProportional( rect<f32>(0.137,0.84,0.266,0.95 ) );
    number1->setOverrideFont( pt_Menu->getBigFont() );
    number1->setVisible( false );
    number1->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER );
    numbers[0] = number1;  //verificar para que se usa este array
    numberCharts.push_back( number1 );

    number2 = guienv->addStaticText(L"0",rect<s32>(0,0,1,1));
    number2->setRelativePositionProportional( rect<f32>(0.266,0.84,0.395,0.95 ) );
    number2->setOverrideFont( pt_Menu->getBigFont() );
    number2->setVisible( false );
    number2->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER );
    numbers[1] = number2;
    numberCharts.push_back( number2 );

    number3 = guienv->addStaticText(L"0",rect<s32>(0,0,1,1));
    number3->setRelativePositionProportional( rect<f32>(0.395,0.84,0.524,0.95 ) );
    number3->setOverrideFont( pt_Menu->getBigFont() );
    number3->setVisible( false );
    number3->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER );
    numberCharts.push_back( number3 );

    numbers[2] = number3;

    number4 = guienv->addStaticText(L"0",rect<s32>(0,0,1,1));
    number4->setRelativePositionProportional( rect<f32>(0.524,0.84,0.653,0.95 ) );
    number4->setOverrideFont( pt_Menu->getBigFont() );
    number4->setVisible( false );
    number4->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER );
    numberCharts.push_back( number4 );

    numbers[3] = number4;

    number5 = guienv->addStaticText(L"0",rect<s32>(0,0,1,1));
    number5->setRelativePositionProportional( rect<f32>(0.654,0.84,0.782,0.95 ) );
    number5->setOverrideFont( pt_Menu->getBigFont() );
    number5->setVisible( false );
    number5->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER );
    numberCharts.push_back( number5 );

    numbers[4] = number5;
}

void playtonGame::fillNumberCharts()
{
    list<IGUIStaticText*>::Iterator itCharts = numberCharts.begin();

    for(list<IMeshSceneNode*>::Iterator Iterator = cards.begin(); Iterator != cards.end(); ++Iterator) {
		IMeshSceneNode* Object = *Iterator;
    }

    filled = true;
}
