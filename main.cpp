#include "common.h"
#include "mbSound.h"
#include "playton_game.h"
#include "playton_menu.h"


IrrlichtDevice *device;

ISceneManager* smgr;
IGUIEnvironment* guienv;
IVideoDriver* driver;

playton_game* pt_Game;
playton_menu* pt_Menu;

playton_translation* pt_Translation;

mbSound* pt_Sound;

IGUIInOutFader* fader;

class EventReceiverClass : public IEventReceiver {


public:

	virtual bool OnEvent(const SEvent &TEvent) {

/////////////////////////////////////////////////////
//                   GUI EVENTS                    //
/////////////////////////////////////////////////////

		if (TEvent.EventType == EET_GUIEVENT)
		{
		    s32 id = TEvent.GUIEvent.Caller->getID();


		    if( TEvent.GUIEvent.EventType == EGET_BUTTON_CLICKED ) {
                switch(id)
                    {
                        case GUI_ID_1:
                        {

                        }
                        return true;
                        case GUI_ID_2:
                        {

                        }
                        return true;
                        case GUI_ID_3:
                        {

                        }
                        return true;
                        case GUI_ID_4:
                        {

                        }
                        return true;
                        case GUI_ID_5:
                        {

                        }
                        return true;

                        //Operands
                        case GUI_ID_PLUS:
                        {
                            pt_Game->plusEvent();
                        }
                        return true;
                        case GUI_ID_MINUS:
                        {
                            pt_Game->minusEvent();
                        }
                        return true;
                        case GUI_ID_MULT:
                        {
                            pt_Game->multEvent();
                        }
                        return true;
                        case GUI_ID_DIV:
                        {
                            pt_Game->divEvent();
                        }
                        return true;
                        case GUI_ID_instrutions:
                        {
                            pt_Menu->instrutionsEvent();
                        }
                        return true;

                        case GUI_ID_setup:
                        {
                            pt_Menu->setupEvent();
                        }
                        return true;
                        case GUI_ID_play:
                        {
                            pt_Menu->playEvent();
                        }
                        return true;
                         case GUI_ID_ilustration:
                        {
                            pt_Menu->ilustrationEvent();
                        }
                        return true;
                        case GUI_ID_credits:
                        {
                            pt_Menu->creditsEvent();
                        }
                        return true;
                        case GUI_ID_PLAY_NOW:
                        {
                            pt_Game->playNowEvent();
                        }
                        return true;
                        case GUI_ID_WINDOW_COLOR:
                        {
                            pt_Menu->windowColorEvent();
                        }
                        return true;
                        case GUI_ID_PLAYTON:
                        {
                            pt_Game->playtonEvent();
                        }
                        return true;
                        case  GUI_ID_PLAY_AGAIN:
                        {
                            pt_Menu->scoreEvent();
                            pt_Game->resetEverything();
                        }
                        return true;
                        case GUI_ID_CLOSE_WINDOW:
                        {
                            TEvent.GUIEvent.Caller->getParent()->setVisible(false);
                        }
                        return true;
                        case GUI_ID_SALIR:
                        {
                            device->closeDevice();
                        }
                        return true;
                        case GUI_ID_tournament:
                        {
                            pt_Menu->tournamentEvent();
                        }
                        return true;
                        case GUI_ID_SIMPLE:
                        {
                           pt_Game->setSingle( true );
                           pt_Menu->simpleEvent();
                        }
                        return true;
                        case GUI_ID_SPANISH:
                        {
                            pt_Menu->spanishEvent();
                        }
                        return true;
                        case GUI_ID_FRENCH:
                        {

                            //pt_Menu->frenchEvent();
                        }
                        return true;
                        case GUI_IDENGLISH:
                        {
                            pt_Menu->englishEvent();
                        }
                        return true;
                        case GUI_ID_CHECKED:
                        {
                            pt_Game->checked_tournamentEvent(TEvent);
                        }
                        return true;
                        case GUI_ID_CHECKED_PLAYER:
                        {
                            pt_Game->checked_playerEvent(TEvent);
                        }
                        return true;
                        case GUI_ID_CHECKED_COLOR:
                        {
                            pt_Game->checked_colorEvent(TEvent);
                        }
                        return true;
                        case GUI_ID_CHECKED_WINNER:
                        {
                            pt_Game->checked_winnerEvent(TEvent);
                        }
                        return true;
                        case GUI_ID_MENU:
                        {
                            pt_Menu->restartEvent();
                            pt_Game->resetEverything();
                        }
                        return true;
                        case GUI_ID_CONTROL_MUSIC:
                        {
                            pt_Menu->musicEvent();
                        }
                        return true;
                        case GUI_ID_CONTROLEFFECTS:
                        {
                            pt_Sound->mute( !pt_Sound->isMuted() );
                        }
                        return true;
                        case GUI_ID_CONTROL_TEXTURES:
                        {

                        }
                        return true;

                        default:
                            return false;
                    }
		    }
		}
        if (TEvent.EventType == irr::EET_MOUSE_INPUTEVENT)
		{
			switch(TEvent.MouseInput.Event)
			{

            case EMIE_LMOUSE_PRESSED_DOWN:
                    pt_Game->geometryClicked();
                break;
			case EMIE_LMOUSE_LEFT_UP:
			    {
                    pt_Game->geometryReleased();
			    }
				break;
            case EMIE_RMOUSE_LEFT_UP:

                break;
			case EMIE_MOUSE_MOVED:
				break;

			default:
				break;
			}
		}

		return false;
	}

};

int main(int argc, char** argv)
{

    device = createDevice(EDT_OPENGL, dimension2d<u32>( RES_X, RES_Y ), 32,
            false, true, false, 0);

    device->setWindowCaption( PLAYTON_TITLE );
    device->setResizable(false);

    device->getSceneManager()->setAmbientLight( SColorf(255,255,255,255) );
    pt_Sound        = new mbSound();
    pt_Game         = new playton_game();
    pt_Menu         = new playton_menu();
    pt_Translation  = new playton_translation();

    pt_Game->setMenuHandler( pt_Menu );
    pt_Game->initGame();

    pt_Game->createScene();

    pt_Menu->createWindows();
    pt_Menu->createLanguageWindow();

    pt_Game->createNumberCharts();

    guienv = device->getGUIEnvironment();
    fader =  guienv->addInOutFader();
    fader->fadeIn( 1400 );

    EventReceiverClass receiver = EventReceiverClass();
    device->setEventReceiver(&receiver);

    pt_Sound->loadSound( "testing.ogg", PLAYTON_MAIN );
    pt_Sound->setLoopSound( true, PLAYTON_MAIN );

    irr::ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime();
    u32 DeltaTime = 0;

    while(device->run())
    {

        DeltaTime = irrTimer->getTime() - TimeStamp;
		TimeStamp = irrTimer->getTime();

		if(fader->isReady())
            fader->setVisible(false);

		pt_Game->update( DeltaTime );
    }

    device->drop();

    return 0;
}