#ifndef playtonMenu_H
#define playtonMenu_H

#include "common.h"
#include "mbSound.h"

class playtonMenu
{
    public:
        playtonMenu();
        virtual ~playtonMenu();
        void hideWindows();
        void hideCheckedButtons();
        IGUIButton* addCheckedButton( IGUIElement* parent, irr::s32 ID );
        IGUIButton* addReturnButton( IGUIElement* parent );
        IGUIButton* addCloseButton( IGUIElement* parent );
        void hideCheckedPlayersButtons();
        void hideCheckedColorButtons();
        void hideCheckedWinnerButtons();
        void createLanguageWindow();

        void createWindows();
        void instructionsEvent();
        void setupEvent();
        void playEvent();
        void ilustrationEvent();
        void creditsEvent();

        void tournamentEvent();
        void simpleEvent();

        void spanishEvent();
        void englishEvent();
        void frenchEvent();

        void musicEvent();
        void soundEvent();
        void textureEvent();

        void windowColorEvent();
        void scoreEvent();
        void checkedWinnerEvent();
        void restartEvent();

        void reset();
        void waitUserResult();
        void showPlayAgain();

        IGUIFont* getBigFont() {  return tt_font; }
    protected:

    private:

        IGUIEnvironment* guienv;
        IVideoDriver* driver;
        IGUIWindow* instrutionsWindow;
        IGUIWindow* setupWindow;
        IGUIWindow* playWindow;
        IGUIWindow* ilustrationWindow;
        IGUIWindow* creditsWindow;
        IGUIWindow* tournamentsWindow;
        IGUIWindow* simpleWindow;
        IGUIWindow* colorWindow;
        IGUIWindow* menuMain;
        IGUIWindow* menuLanguages;
        IGUIWindow* winnerColorWindow;
        IGUIWindow* activeWindow;
        IMeshSceneNode* plane;
        IGUIWindow* drag;
        IMeshSceneNode* btn1;
        IGUIFont* tt_font;
        IGUIFont* tt_font2;
        FontManager* fontMgr;
        std::vector<IGUIWindow*> windowList;
        IGUIImage* operators[ 5 ];
        list<IGUIButton*> checkedGroup;
        list<IGUIButton*> colorGroup;
        list<IGUIButton*> winnerColorGroup;
        IGUIButton* playerGroup[5];
        IGUIButton* playton;
        IGUIButton* playAgain;
        //setup
        IGUIButton* confMusic;
        IGUIButton* confEffects;
        IGUIButton* confTexture;
};

#endif // playtonMenu_H
