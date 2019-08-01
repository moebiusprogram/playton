#include "playtonGame.h"


void playtonGame::plusEvent()
{
    if ( active == 0 )
    {
        return;
    }
    changeOperatorActive();
    activeOperator->setImage( driver->getTexture("3345133631.png") );
}

void playtonGame::minusEvent()
{
    if ( active == 0 )
    {
        return;
    }
    changeOperatorActive();
    activeOperator->setImage( driver->getTexture("2600034676.png") );
}

void playtonGame::multEvent()
{
    if ( active == 0 )
    {
        return;
    }
    changeOperatorActive();
    activeOperator->setImage( driver->getTexture("6619176782.png") );
}

void playtonGame::divEvent()
{
    if ( active == 0 )
    {
        return;
    }
    changeOperatorActive();
    activeOperator->setImage( driver->getTexture("4618267118.png") );
}

void playtonGame::playNowEvent()
{
    if( activeTournament > 0 || singlePlay )
    {
        newGame();
        setHUDtournament();
        pt_Menu->hideWindows();
        fader->setVisible(true);
        fader->fadeIn(1000);
    }
}

void playtonGame::checkedTournamentEvent( SEvent TEvent )
{
    pt_Menu->hideCheckedButtons();
    core::list<IGUIElement*>::ConstIterator child = TEvent.GUIEvent.Caller->getChildren().begin();
    activeTournament = (*child)->getID();

    if( activeTournament == tournament_TETRAtournament )
    {
        posiblePlay = 4;
    } else if( activeTournament == tournament_HEXAtournament )
    {
        posiblePlay = 6;
    } else if( activeTournament == tournament_OCTAtournament )
    {
        posiblePlay = 8;
    }

    (*child)->setVisible(true);
}

void playtonGame::checkedPlayerEvent( SEvent TEvent )
{
    pt_Menu->hideCheckedPlayersButtons();
    pt_Menu->hideCheckedColorButtons();

    selectedColors.clear();
    core::list<IGUIElement*>::ConstIterator child = TEvent.GUIEvent.Caller->getChildren().begin();
    numeroJugadores = (*child)->getID();
    numeroJugadores = numeroJugadores - 4999999;

    (*child)->setVisible(true);
}

void playtonGame::checkedColorEvent( SEvent TEvent )
{
    IGUIButton* button = (IGUIButton*)TEvent.GUIEvent.Caller;
    core::list<IGUIElement*>::ConstIterator child = button->getChildren().begin();
    s32 id = (*child)->getID();
    selectedColors.push_back( id );

    button->setImage( driver->getTexture("8657369634.png") );
    button->setEnabled( false );
}

void playtonGame::checkedWinnerEvent( SEvent TEvent )
{
    IGUIButton* button = (IGUIButton*)TEvent.GUIEvent.Caller;
    core::list<IGUIElement*>::ConstIterator child = button->getChildren().begin();
    s32 id = (*child)->getID();
    const c8* winner = button->getName();

    actualPlay++;

    irr::core::stringw tournament(L"");
    tournament += actualPlay;
    tournament += "/";
    tournament += posiblePlay;

    HUDtournamentText->setText( tournament.c_str() );

    pt_Menu->checkedWinnerEvent();
    button->setEnabled( false );
}

void playtonGame::playtonEvent()
{
    pt_Physics->runPhysics( ciclingIDs );
    pt_Menu->reset();

    hideCiclingSolids();
    setRolling(true);
}