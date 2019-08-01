#include "playtonMenu.h"

playtonMenu::playtonMenu()
{
    fontMgr = new FontManager( device );

    tt_font = fontMgr->GetTtFont("fonts/Exo-ExtraBold.ttf",35,true,true);
    tt_font2 = fontMgr->GetTtFont("fonts/neuropolitical.ttf",10,true,true);

    driver = device->getVideoDriver();
    guienv = device->getGUIEnvironment();

    IGUISkin* wrmbSkin;
    wrmbSkin = guienv->createSkin(EGST_WINDOWS_METALLIC);
    wrmbSkin->setFont(tt_font2);
    wrmbSkin->setColor(EGDC_BUTTON_TEXT, irr::video::SColor(255,255,255,255));
    guienv->setSkin(wrmbSkin);
}

playtonMenu::~playtonMenu()
{
    //dtor
}

void playtonMenu::hideWindows()
{
    for(u32 i = 0; i < windowList.size(); i++)
    {
        windowList[i]->setVisible(false);
    }
}

void playtonMenu::hideCheckedButtons()
{
    for(list<IGUIButton*>::Iterator Iterator = checkedGroup.begin(); Iterator != checkedGroup.end(); ++Iterator) {

        IGUIButton* node = *Iterator;
        node->setVisible(false);
    }
}

void playtonMenu::hideCheckedColorButtons()
{
    for(list<IGUIButton*>::Iterator Iterator = colorGroup.begin(); Iterator != colorGroup.end(); ++Iterator) {

        IGUIButton* node = (IGUIButton*)(*Iterator)->getParent();

        node->setEnabled(true);
        node->setImage(0);
    }
}

void playtonMenu::hideCheckedWinnerButtons()
{
    for(list<IGUIButton*>::Iterator Iterator = winnerColorGroup.begin(); Iterator != winnerColorGroup.end(); ++Iterator) {

        IGUIButton* node = (IGUIButton*)(*Iterator)->getParent();

        node->setEnabled(true);
    }
}

IGUIButton* playtonMenu::addCheckedButton( IGUIElement* parent, s32 ID )
{
    IGUIButton* checked = guienv->addButton(rect<s32>(-15,-15,15,15),parent,ID,L"");
    checked->setImage( driver->getTexture("4366657967.png") );
    checked->setScaleImage( true );
    checked->setNotClipped(true);
    checked->setUseAlphaChannel(true);
    checked->setDrawBorder( false );
    checked->setVisible( false );

    return checked;
}

IGUIButton* playtonMenu::addCloseButton( IGUIElement* parent )
{
    IGUIButton* closeWindow = device->getGUIEnvironment()->addButton(rect<s32>(0,0,1,1),parent, GUI_ID_CLOSE_WINDOW,L"");
    closeWindow->setRelativePositionProportional( rect<f32>(0.82, 0.145,0.88,0.252) );
    closeWindow->setUseAlphaChannel(true);
    closeWindow->setDrawBorder(false);
    closeWindow->setImage(driver->getTexture("2037689409.png") );

    return closeWindow;
}

void playtonMenu::hideCheckedPlayersButtons()
{
    for(int i = 0; i < 5; i++)
    {
        IGUIElement* element = playerGroup[i];
        if( element )
        {
            element->setVisible(false);
        }
    }
}

void playtonMenu::createLanguageWindow()
{
    menuLanguages = guienv->addWindow( rect<s32>(0,0,750, 418 ),true );
    menuLanguages->setDraggable( false );
    IGUIImage* menuLanguagesBackground = guienv->addImage( driver->getTexture("6260809552.png"), vector2di(0,0),true,menuLanguages,-1 );
    menuLanguagesBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );

    IGUIButton* spanish = guienv->addButton(rect<s32>(0,0,1,1),menuLanguages,GUI_ID,L"");
    spanish->setRelativePositionProportional( rect<f32>(0.27, 0.72,0.34,0.86) );
    spanish->setUseAlphaChannel(true);
    spanish->setText( L"" );
    spanish->setID( GUI_ID_ENGLISH );
    spanish->setDrawBorder(false);

    IGUIButton* french = guienv->addButton(rect<s32>(0,0,1,1),menuLanguages,GUI_ID,L"");
    french->setRelativePositionProportional( rect<f32>(0.46,0.72,0.535,0.86) );
    french->setUseAlphaChannel(true);
    french->setText( L"" );
    french->setID( GUI_ID_SPANISH );
    french->setDrawBorder(false);

    IGUIButton* english = guienv->addButton(rect<s32>(0,0,1,1),menuLanguages,GUI_ID,L"");
    english->setRelativePositionProportional( rect<f32>(0.63, 0.72,0.71,0.86) );
    english->setUseAlphaChannel(true);
    english->setText( L"" );
    english->setID( GUI_ID_FRENCH );
    english->setDrawBorder(false);

    windowList.push_back(instrutionsWindow );
    windowList.push_back( instrutionsWindow );

    windowList.push_back( setupWindow );
    windowList.push_back( playWindow );
    windowList.push_back( ilustrationWindow );
    windowList.push_back( creditsWindow );

    windowList.push_back( tournamentsWindow );
    windowList.push_back( simpleWindow );
    windowList.push_back( colorWindow );
    windowList.push_back( winnerColorWindow );

    windowList.push_back( menuMain );
    windowList.push_back( menuLanguages );
}

void playtonMenu::createWindows()
{

    IGUIButton* menu  = guienv->addButton(rect<s32>(0,0,1,1),0,GUI_ID,L"");
    menu->setRelativePositionProportional( rect<f32>(0.865, 0.0,0.98,0.1) );
    menu->setImage( driver->getTexture("7401152630.png") );
    menu->setUseAlphaChannel(true);
    menu->setDrawBorder(false);
    menu->setID(GUI_ID_MENU);

    //Menu Main
    menuMain = guienv->addWindow( rect<s32>(0,0,750, 418 ),true );
    menuMain->setVisible(false);
    menuMain->setDraggable( false );
    IGUIImage* menuMainBackground = guienv->addImage( driver->getTexture("7401152630.png") , vector2di(0,0),true,menuMain,-1 );
    menuMainBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );

    IGUIButton* instrutions = guienv->addButton(rect<s32>(0,0,1,1),menuMain,GUI_ID,L"");
    instrutions->setRelativePositionProportional( rect<f32>(0.145, 0.637,0.25,0.825) );
    instrutions->setID( GUI_ID_ILUSTRATIONS );
    instrutions->setDrawBorder(false);

    IGUIButton* Main4 = guienv->addButton(rect<s32>(0,0,1,1),menuMain,GUI_ID,L"");
    Main4->setRelativePositionProportional( rect<f32>(0.32, 0.63,0.425,0.825) );
    Main4->setDrawBorder(false);
    Main4->setID( GUI_ID_SETUP );

    IGUIButton* Main3 = guienv->addButton(rect<s32>(0,0,1,1),menuMain,GUI_ID,L"");
    Main3->setRelativePositionProportional( rect<f32>(0.45, 0.39,0.56,0.59) );
    Main3->setDrawBorder(false);
    Main3->setID( GUI_ID_PLAY  );

    IGUIButton* Main2 = guienv->addButton(rect<s32>(0,0,1,1),menuMain,GUI_ID,L"");
    Main2->setRelativePositionProportional( rect<f32>(0.585, 0.63,0.695,0.825) );
    Main2->setDrawBorder(false);
    Main2->setID( GUI_ID_ILUSTRATIONS );

    IGUIButton* Main1 = guienv->addButton(rect<s32>(0,0,1,1),menuMain,GUI_ID,L"");
    Main1->setRelativePositionProportional( rect<f32>(0.76, 0.63,0.87,0.825) );
    Main1->setUseAlphaChannel(true);
    Main1->setDrawBorder(false);
    Main1->setID( GUI_ID_CREDITS );

    IGUIButton* quit = guienv->addButton(rect<s32>(0,0,1,1),menuMain,GUI_ID,L"");
    quit->setRelativePositionProportional( rect<f32>(0.45, 0.85,0.56,0.95) );
    quit->setUseAlphaChannel(true);
    quit->setID( GUI_ID_QUIT );

    //Menu instrutions
    instrutionsWindow = guienv->addWindow( rect<s32>(20,20,730, 398 ),true );
    instrutionsWindow->setDrawTitlebar( false );
    instrutionsWindow->setDrawBackground(false);
    instrutionsWindow->getCloseButton()->setVisible(false);
    instrutionsWindow->setVisible(false);
    instrutionsWindow->setDraggable( false );
    menuMain->addChild( instrutionsWindow );
    instrutionsWindow->updateAbsolutePosition();
    IGUIImage* instrutionsBackground = guienv->addImage( driver->getTexture("2495400708.png"),
                                         vector2di(0,0),true,instrutionsWindow,-1 );
    instrutionsBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    instrutionsBackground->updateAbsolutePosition();
    instrutionsBackground->setID( GUI_ID_CLOSE_WINDOW );

    addCloseButton( instrutionsWindow );
    addReturnButton( instrutionsWindow );

//Menu setup
    setupWindow = guienv->addWindow( rect<s32>(20,20,730, 398 ),true );
    setupWindow->setVisible(false);
    setupWindow->setDraggable( false );
    setupWindow->setDrawTitlebar( false );
    setupWindow->setDrawBackground(false);
    menuMain->addChild( setupWindow );
    setupWindow->updateAbsolutePosition();
    setupWindow->getCloseButton()->setVisible(false);
    IGUIImage* setupBackground = guienv->addImage( driver->getTexture("8963994246.png"),
                                           vector2di(0,0),true,setupWindow,-1 );
    setupBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    setupBackground->updateAbsolutePosition();
    setupBackground->setID( GUI_ID_CLOSE_WINDOW );

    confMusic = guienv->addButton(rect<s32>(0,0,1,1),setupWindow,GUI_ID_CONTROL_MUSIC,L"");
    confMusic->setRelativePositionProportional( rect<f32>(0.48, 0.3,0.55,0.43) );
    confMusic->setUseAlphaChannel(true);
    confMusic->setImage( driver->getTexture("4393595198.png") );
    confMusic->setDrawBorder(false);

    confEffects = guienv->addButton(rect<s32>(0,0,1,1),setupWindow,GUI_ID_CONTROL_EFFECTS,L"");
    confEffects->setRelativePositionProportional( rect<f32>(0.48, 0.45,0.55,0.58) );
    confEffects->setUseAlphaChannel(true);
    confEffects->setImage( driver->getTexture("5768726791.png") );
    confEffects->setDrawBorder(false);

    confTexture = guienv->addButton(rect<s32>(0,0,1,1),setupWindow,GUI_ID_CONTROL_TEXTURES,L"");
    confTexture->setRelativePositionProportional( rect<f32>(0.48, 0.6,0.55,0.73) );
    confTexture->setUseAlphaChannel(true);
    confTexture->setImage( driver->getTexture("7571830545.png") );
    confTexture->setDrawBorder(false);

    addCloseButton( setupWindow );
    addReturnButton( setupWindow );

//Menu play
    playWindow = guienv->addWindow( rect<s32>(20,20,730, 398 ),true );
    playWindow->setVisible(false);
    playWindow->setDraggable( false );
    playWindow->setDrawTitlebar( false );
    playWindow->setDrawBackground(false);
    playWindow->getCloseButton()->setVisible(false);
    menuMain->addChild( playWindow );
    playWindow->updateAbsolutePosition();
    IGUIImage* playBackground = guienv->addImage( driver->getTexture("1609300588.png"),
                                 vector2di(0,0),true,playWindow,-1 );
    playBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    playBackground->updateAbsolutePosition();

    IGUIButton* tournament = guienv->addButton(rect<s32>(0,0,1,1),playWindow,GUI_ID_TOURNAMENT,L"");
    tournament->setRelativePositionProportional( rect<f32>(0.265, 0.26,0.455,0.62) );
    tournament->setUseAlphaChannel(true);
    tournament->setDrawBorder(false);

    IGUIButton* simple = guienv->addButton(rect<s32>(0,0,1,1),playWindow,GUI_ID_SIMPLE,L"");
    simple->setRelativePositionProportional( rect<f32>(0.55, 0.26,0.74,0.62) );
    simple->setUseAlphaChannel(true);
    simple->setDrawBorder(false);

    addCloseButton( playWindow );
    addReturnButton( playWindow );

//Menu ilustration
    ilustrationWindow = guienv->addWindow( rect<s32>(20,20,730, 398 ),true );
    ilustrationWindow->setVisible(false);
    ilustrationWindow->setDraggable( false );
    ilustrationWindow->setDrawTitlebar( false );
    ilustrationWindow->setDrawBackground(false);
    ilustrationWindow->getCloseButton()->setVisible(false);
    menuMain->addChild( ilustrationWindow );
    ilustrationWindow->updateAbsolutePosition();
    IGUIImage* ilustrationBackground = guienv->addImage( driver->getTexture("6143570360.png"),
                                       vector2di(0,0),true,ilustrationWindow,-1 );
    ilustrationBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    ilustrationBackground->updateAbsolutePosition();
    ilustrationBackground->setID( GUI_ID_CLOSE_WINDOW );

    addCloseButton( ilustrationWindow );
    addReturnButton( ilustrationWindow );

//Menu credits
    creditsWindow = guienv->addWindow( rect<s32>(20,20,730, 398 ),true );
    creditsWindow->setVisible(false);
    creditsWindow->setDraggable( false );
    creditsWindow->setDrawTitlebar( false );
    creditsWindow->setDrawBackground(false);
    creditsWindow->getCloseButton()->setVisible(false);
    menuMain->addChild( creditsWindow );
    creditsWindow->updateAbsolutePosition();
    IGUIImage* creditsBackground = guienv->addImage( driver->getTexture("8475858409.png"),
                                    vector2di(0,0),true,creditsWindow,-1 );
    creditsBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    creditsBackground->updateAbsolutePosition();
    creditsBackground->setID( GUI_ID_CLOSE_WINDOW );

    addCloseButton( creditsWindow );
    addReturnButton( creditsWindow );

//Menu Tournaments
    tournamentsWindow = guienv->addWindow( rect<s32>(0,0,1,1 ),true );
    tournamentsWindow->setDraggable( false );
    playWindow->addChild( tournamentsWindow );
    tournamentsWindow->setDrawTitlebar( false );
    tournamentsWindow->setDrawBackground(false);
    tournamentsWindow->getCloseButton()->setVisible(false);
    tournamentsWindow->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    tournamentsWindow->updateAbsolutePosition();
    tournamentsWindow->setVisible(false);

    IGUIImage* tournamentsBackground = guienv->addImage( driver->getTexture("3629191384.png"), vector2di(0,0),true,tournamentsWindow,-1 );
    tournamentsBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    tournamentsBackground->setScaleImage( true );

    addCloseButton( tournamentsWindow );
    addReturnButton( tournamentsWindow );

    IGUIButton* tournament1 = guienv->addButton(rect<s32>(0,0,1,1),tournamentsWindow,GUI_ID_CHECKED,L"");
    tournament1->setRelativePositionProportional( rect<f32>(0.35, 0.42,0.45,0.65) );
    tournament1->setImage( driver->getTexture("9892585150.png") );
    tournament1->setUseAlphaChannel(true);
    //tournament1->setImage( driver->getTexture( "tert" ) )
    tournament1->setText( L"" );
    tournament1->setDrawBorder(false);
    IGUIButton* checked = addCheckedButton( tournament1, tournament_TETRAtournament );
    checkedGroup.push_back( checked );

    IGUIButton* tournament2 = guienv->addButton(rect<s32>(0,0,1,1),tournamentsWindow,GUI_ID_CHECKED,L"");
    tournament2->setRelativePositionProportional( rect<f32>(0.55, 0.42,0.65,0.65) );
    tournament2->setImage( driver->getTexture("7909019489.png") );
    tournament2->setUseAlphaChannel(true);
    //tournament2->setDrawBorder(false);
    tournament2->setText( L"" );
    tournament2->setDrawBorder(false);
    checked = addCheckedButton( tournament2, tournament_HEXAtournament );
    checkedGroup.push_back( checked );

    IGUIButton* tournament3 = guienv->addButton(rect<s32>(0,0,1,1),tournamentsWindow,GUI_ID_CHECKED,L"");
    tournament3->setRelativePositionProportional( rect<f32>(0.75, 0.42,0.85,0.65) );
    tournament3->setImage( driver->getTexture("2239286400.png") );
    tournament3->setUseAlphaChannel(true);
    //tournament3->setDrawBorder(false);
    tournament3->setText( L"" );
    tournament3->setDrawBorder(false);
    checked = addCheckedButton( tournament3, tournament_OCTAtournament );
    checkedGroup.push_back( checked );

    IGUIButton* playNow = guienv->addButton(rect<s32>(0,0,1,1),tournamentsWindow,GUI_ID_SIMPLE,L"");
    playNow->setRelativePositionProportional( rect<f32>(0.86, 0.81,0.915,0.92) );
    playNow->setUseAlphaChannel(true);
    playNow->setImage( driver->getTexture( "9531477227.png" ) );
    playNow->setDrawBorder( false );

//Menu Simple
    simpleWindow = guienv->addWindow( rect<s32>(0,0,1,1 ),true );
    simpleWindow->setDraggable( false );
    simpleWindow->setDrawTitlebar( false );
    simpleWindow->setDrawBackground(false);
    playWindow->addChild( simpleWindow );
    simpleWindow->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    simpleWindow->updateAbsolutePosition();
    simpleWindow->setVisible(false);
    simpleWindow->getCloseButton()->setVisible(false);

    IGUIImage* simpleBackground = guienv->addImage( driver->getTexture("2820265428.png"), vector2di(0,0),true,simpleWindow,-1 );
    simpleBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );

    addCloseButton( simpleWindow );
    addReturnButton( simpleWindow );

    IGUIButton* player1 = guienv->addButton(rect<s32>(0,0,1,1),simpleWindow,GUI_ID_CHECKED_PLAYER,L"");
    player1->setRelativePositionProportional( rect<f32>(0.28, 0.22,0.4,0.45) );
    player1->setImage( driver->getTexture("9625687968.png") );
    player1->setUseAlphaChannel(true);
    player1->setDrawBorder(false);
    playerGroup[0] = addCheckedButton( player1, player_1 );

    IGUIButton* player2 = guienv->addButton(rect<s32>(0,0,1,1),simpleWindow,GUI_ID_CHECKED_PLAYER,L"");
    player2->setRelativePositionProportional( rect<f32>(0.675, 0.22,0.8,0.45) );
    player2->setImage( driver->getTexture("1988609046.png") );
    player2->setUseAlphaChannel(true);
    player2->setDrawBorder(false);

    playerGroup[1] = addCheckedButton( player2, player_2 );

    IGUIButton* player3 = guienv->addButton(rect<s32>(0,0,1,1),simpleWindow,GUI_ID_CHECKED_PLAYER,L"");
    player3->setRelativePositionProportional( rect<f32>(0.265, 0.52,0.39,0.745) );
    player3->setImage( driver->getTexture("3537101234.png") );
    player3->setUseAlphaChannel(true);
    player3->setDrawBorder(false);

    playerGroup[2] = addCheckedButton( player3, player_3 );

    IGUIButton* player4 = guienv->addButton(rect<s32>(0,0,1,1),simpleWindow,GUI_ID_CHECKED_PLAYER,L"");
    player4->setRelativePositionProportional( rect<f32>(0.69, 0.52,0.82,0.75) );
    player4->setImage( driver->getTexture("2152471419.png") );
    player4->setUseAlphaChannel(true);
    player4->setDrawBorder(false);

    playerGroup[3] = addCheckedButton( player4, player_4 );

    IGUIButton* player5 = guienv->addButton(rect<s32>(0,0,1,1),simpleWindow,GUI_ID_CHECKED_PLAYER,L"");
    player5->setRelativePositionProportional( rect<f32>(0.475, 0.6,0.595,0.83) );
    player5->setImage( driver->getTexture("1559727620.png") );
    player5->setUseAlphaChannel(true);
    player5->setDrawBorder(false);

    playerGroup[4] = addCheckedButton( player5, player_5 );

    IGUIButton* playNow2 = guienv->addButton(rect<s32>(0,0,1,1),simpleWindow,GUI_ID_WINDOW_COLOR,L"");
    playNow2->setRelativePositionProportional( rect<f32>(0.86, 0.81,0.915,0.92) );
    playNow2->setUseAlphaChannel(true);
    playNow2->setImage( driver->getTexture( "1975655917.png" ) );
    playNow2->setDrawBorder( false );

//Menu Color
    colorWindow = guienv->addWindow( rect<s32>(0,0,1,1 ),true );
    colorWindow->setDraggable( false );
    colorWindow->setDrawTitlebar( false );
    colorWindow->setDrawBackground(false);
    playWindow->addChild( colorWindow );
    colorWindow->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    colorWindow->updateAbsolutePosition();
    colorWindow->setVisible(false);
    colorWindow->getCloseButton()->setVisible(false);

    IGUIImage* colorBackground = guienv->addImage( driver->getTexture("6461973001.png"), vector2di(0,0),true,colorWindow,-1 );
    colorBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );

    addCloseButton( colorWindow );
    addReturnButton( colorWindow );

    IGUIButton* color1 = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_CHECKED_COLOR,L"");
    color1->setRelativePositionProportional( rect<f32>(0.2, 0.435,0.31,0.645) );
    color1->setUseAlphaChannel(true);
    //color1->setDrawBorder(false);
    color1->setDrawBorder( false );
    color1->setScaleImage( true );
    color1->setName( "red" );

    colorGroup.push_back( addCheckedButton( color1, RED ));

    IGUIButton* color2 = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_CHECKED_COLOR,L"");
    color2->setRelativePositionProportional( rect<f32>(0.325, 0.435,0.435,0.645) );
    color2->setUseAlphaChannel(true);
    color2->setDrawBorder( false );
    color2->setScaleImage( true );
    color2->setName( "green" );
    colorGroup.push_back( addCheckedButton( color2, GREEN ));

    IGUIButton* color3 = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_CHECKED_COLOR,L"");
    color3->setRelativePositionProportional( rect<f32>(0.452, 0.435,0.56,0.645) );
    color3->setUseAlphaChannel(true);
    color3->setDrawBorder( false );
    color3->setScaleImage( true );
    color3->setName( "yellow" );
    colorGroup.push_back( addCheckedButton( color3, YELLOW ));

    IGUIButton* color4 = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_CHECKED_COLOR,L"");
    color4->setRelativePositionProportional( rect<f32>(0.578, 0.435,0.688,0.645) );
    color4->setUseAlphaChannel(true);
    color4->setDrawBorder( false );
    color4->setScaleImage( true );
    color4->setName( "purple" );
    colorGroup.push_back( addCheckedButton( color4, PURPLE ));

    IGUIButton* color5 = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_CHECKED_COLOR,L"");
    color5->setRelativePositionProportional( rect<f32>(0.705, 0.435,0.815,0.645) );
    color5->setUseAlphaChannel(true);
    color5->setDrawBorder( false );
    color5->setScaleImage( true );
    color5->setName( "blue" );
    colorGroup.push_back( addCheckedButton( color5, BLUE ));

    IGUIButton* justPlay = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_PLAY_NOW,L"");
    justPlay->setRelativePositionProportional( rect<f32>(0.86, 0.81,0.915,0.92) );
    justPlay->setUseAlphaChannel(true);
    justPlay->setDrawBorder( false );
    justPlay->setImage( driver->getTexture( "6461973001.png" ) );


//Menu Score
    winnerColorWindow = guienv->addWindow( rect<s32>(0,0,1,1 ),true );
    winnerColorWindow->setDraggable( false );
    winnerColorWindow->setDrawTitlebar( false );
    winnerColorWindow->setDrawBackground(false);
    winnerColorWindow->setRelativePositionProportional( rect<f32>(0,0,1,1) );
    winnerColorWindow->updateAbsolutePosition();
    winnerColorWindow->setVisible(false);
    winnerColorWindow->getCloseButton()->setVisible(false);

    IGUIImage* winnerBackground = guienv->addImage( driver->getTexture("3002371387.png"), vector2di(0,0),true,winnerColorWindow,-1 );
    winnerBackground->setRelativePositionProportional( rect<f32>(0,0,1,1) );

    IGUIButton* winnerColor1 = guienv->addButton(rect<s32>(0,0,1,1),winnerColorWindow,GUI_ID_CHECKED_WINNER,L"");
    winnerColor1->setRelativePositionProportional( rect<f32>(0.2, 0.435,0.31,0.645) );
    winnerColor1->setUseAlphaChannel(true);
    winnerColor1->setImage(driver->getTexture( "4640065477.png" ));
    winnerColor1->setDrawBorder( false );
    winnerColor1->setName( "fire" );

    winnerColorGroup.push_back( addCheckedButton( winnerColor1, RED ));

    IGUIButton* winnerColor2 = guienv->addButton(rect<s32>(0,0,1,1),winnerColorWindow,GUI_ID_CHECKED_WINNER,L"");
    winnerColor2->setRelativePositionProportional( rect<f32>(0.325, 0.435,0.435,0.645) );
    winnerColor2->setUseAlphaChannel(true);
    winnerColor2->setImage(driver->getTexture( "4316875328.png" ));
    winnerColor2->setDrawBorder( false );
    winnerColor2->setName( "earth" );
    winnerColorGroup.push_back( addCheckedButton( winnerColor2, GREEN ));

    IGUIButton* winnerColor3 = guienv->addButton(rect<s32>(0,0,1,1),winnerColorWindow,GUI_ID_CHECKED_WINNER,L"");
    winnerColor3->setRelativePositionProportional( rect<f32>(0.452, 0.435,0.56,0.645) );
    winnerColor3->setUseAlphaChannel(true);
    winnerColor3->setImage( driver->getTexture("6349062596.png" ));
    winnerColor3->setDrawBorder( false );
    winnerColor3->setName( "air" );
    winnerColorGroup.push_back( addCheckedButton( winnerColor3, YELLOW ));

    IGUIButton* winnerColor4 = guienv->addButton(rect<s32>(0,0,1,1),winnerColorWindow,GUI_ID_CHECKED_WINNER,L"");
    winnerColor4->setRelativePositionProportional( rect<f32>(0.578, 0.435,0.688,0.645) );
    winnerColor4->setUseAlphaChannel(true);
    winnerColor4->setImage( driver->getTexture("1365147811.png" ));
    winnerColor4->setDrawBorder( false );
    winnerColor4->setName( "cosmos" );
    winnerColorGroup.push_back( addCheckedButton( winnerColor4, PURPLE ));

    IGUIButton* winnerColor5 = guienv->addButton(rect<s32>(0,0,1,1),winnerColorWindow,GUI_ID_CHECKED_WINNER,L"");
    winnerColor5->setRelativePositionProportional( rect<f32>(0.705, 0.435,0.815,0.645) );
    winnerColor5->setUseAlphaChannel(true);
    winnerColor5->setDrawBorder( false );
    winnerColor5->setImage(driver->getTexture( "3040520591.png" ));
    winnerColor5->setName( "water" );
    winnerColorGroup.push_back( addCheckedButton( winnerColor5, BLUE ));

    IGUIButton* acceptWinner = guienv->addButton(rect<s32>(0,0,1,1),colorWindow,GUI_ID_PLAY_NOW,L"");
    acceptWinner->setRelativePositionProportional( rect<f32>(0.86, 0.81,0.915,0.92) );
    acceptWinner->setUseAlphaChannel(true);
    acceptWinner->setImage( driver->getTexture( "ok.png" ) );
    acceptWinner->setDrawBorder( false );

//Play Button
    playton = guienv->addButton( recti(0,0,1,1)  );
    playton->setRelativePositionProportional( rectf(0.45,0.3,0.55,0.35) );
    playton->setText(L"Playton");
    playton->setID(  GUI_ID_PLAYTON );
    playton->setVisible(false);

    playAgain = guienv->addButton( recti(0,0,1,1)  );
    playAgain->setRelativePositionProportional( rectf(0.4,0.4,0.6,0.45) );
    playAgain->setText(L"Play Again");
    playAgain->setID(  GUI_ID_PLAY_AGAIN );
    playAgain->setVisible(false);
}

void playtonMenu::reset()
{
    playAgain->setVisible(false);
    playton->setVisible(false);
    hideCheckedButtons();
    hideCheckedPlayersButtons();
    hideCheckedColorButtons();
}

void playtonMenu::waitUserResult()
{
    playton->setVisible(true);
}

void playtonMenu::showPlayAgain()
{
    playAgain->setVisible(true);
}