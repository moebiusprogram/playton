#include "playtonMenu.h"

void playtonMenu::instrutionsEvent()
{
    instrutionsWindow->setVisible(true);
    activeWindow = instrutionsWindow;
}

void playtonMenu::setupEvent()
{
    setupWindow->setVisible(true);
    activeWindow = setupWindow;
}

void playtonMenu::playEvent()
{
    playWindow->setVisible(true);
    activeWindow = playWindow;
}

void playtonMenu::ilustrationEvent()
{
    ilustrationWindow->setVisible(true);
    activeWindow = ilustrationWindow;
}

void playtonMenu::creditsEvent()
{
    creditsWindow->setVisible(true);
    activeWindow = creditsWindow;
}

void playtonMenu::tournamentEvent()
{
    IGUIElement* parent =  tournamentsWindow->getParent();
    parent->bringToFront( tournamentsWindow );
    tournamentsWindow->setVisible(true);
}

void playtonMenu::simpleEvent()
{
    IGUIElement* parent =  simpleWindow->getParent();
    parent->bringToFront( simpleWindow );
    simpleWindow->setVisible(true);
}

void playtonMenu::restartEvent()
{
    menuMain->setVisible(true);
}

void playtonMenu::window_colorEvent()
{
    IGUIElement* parent =  colorWindow->getParent();
    parent->bringToFront( colorWindow );
    colorWindow->setVisible(true);
}


void playtonMenu::spanishEvent()
{
    pt_Translation->setActiveLang( PLAYTON_SPANISH );
    menuLanguages->setVisible( false );
    menuMain->setVisible( true );
    pt_Translation->changeLanguage();
}

void playtonMenu::englishEvent()
{
    pt_Translation->setActiveLang(PLAYTON_ENGLISH);
    menuLanguages->setVisible( false );
    menuMain->setVisible( true );
    pt_Translation->changeLanguage();
}

void playtonMenu::frenchEvent()
{
    pt_Translation->setActiveLang(PLAYTON_FRENCH );
    menuLanguages->setVisible( false );
    menuMain->setVisible( true );
    pt_Translation->changeLanguage();
}

void playtonMenu::scoreEvent()
{
    winnerColorWindow->setVisible( true );
}

void playtonMenu::checkedWinnerEvent()
{
    winnerColorWindow->setVisible( false );
    hideCheckedWinnerButtons();
}

void playtonMenu::musicEvent()
{
    if( pt_Sound->isMuted() )
    {
        confMusic->setImage( driver->getTexture("8211875056.png") );
    } else {
        confMusic->setImage( driver->getTexture("8211875057.png") );
    }

    pt_Sound->mute( !pt_Sound->isMuted() );
}

void playtonMenu::soundEvent()
{

}

void playtonMenu::textureEvent()
{

}
