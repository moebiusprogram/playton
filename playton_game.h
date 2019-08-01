#ifndef PLAYTONGAME_H
#define PLAYTONGAME_H

#include "common.h"
#include "physics.h"
#include "playton_translation.h"
#include "playtonMenu.h"
#include "playton_utility.h"
#include "gui_freetype_font.h"

class playtonGame
{
    public:
        playtonGame();
        virtual ~playtonGame();
        void getValuesFromDices();
        void createCilinder( s32 id );
        void createCard( s32 id );
        void hideCiclingSolids();
        void waitUserResult();
        void geometryDragging();
        void geometryReleased();
        void geometryClicked();
        void createScene();
        void changeOperatorActive();
        void displayResult( f32 result );
        void totaledrum_event();
        void createNumberCharts();
        void resetEverything();
        void newGame();
        void initGame();

        void showNumberText();
        void setRolling( bool rolling ) { this->rolling = rolling; }
        void setDragging( bool dragging ) { this->dragging = dragging; }
        void setSingle( bool single ) { this->singlePlay = single; }
        void setMenuHandler( playtonMenu* pt_Menu ) { this->pt_Menu = pt_Menu; }
        void setHUDtournament();
        bool isRolling() { return this->rolling; }
        bool isDragging() { return this->dragging; }
        void update( u32 DeltaTime );

        //eventos
        void plusEvent();
        void minusEvent();
        void multEvent();
        void divEvent();

        void playNowEvent();
        void checkedTournamentEvent( SEvent TEvent );
        void checkedPlayerEvent( SEvent TEvent );
        void checkedColorEvent( SEvent TEvent );
        void checkedWinnerEvent( SEvent TEvent );

        void playton_event();

        IGUIStaticText* getNumberText( u32 index );
        void createPositions();

        f32 executeOperation(f32 operand,f32 operand2, s32 opID );
    protected:

    private:

        playtonPhysics*        pt_Physics;
        playtonMenu*           pt_Menu;
        playton_utility*        pt_Util;

        bool rolling;
        bool dragging;
        bool singlePlay;

        s32 actualPlay;
        s32 posiblePlay;

        IGUIImage* activeOperator;
        IVideoDriver* driver;
        ISceneManager* smgr;
        IGUIEnvironment* guienv;

        ISceneCollisionManager* collMgr;

        vector3df positions[16];
        vector3df positionBoard[16];

        void fillNumberCharts();

        ISceneNode* dragged;

        ICameraSceneNode* orthogonalCamera;
        ICameraSceneNode* perspectiveCamera;

        list<IMeshSceneNode*> cilinders;
        list<IMeshSceneNode*> cards;
        list<IMeshSceneNode*> ciclingSolids;
        list<IGUIStaticText*> numberCharts;
        list<f32> values;
        list<s32> operations;
        list<s32> selectedColors;
        list<s32> ciclingIDs;

        IGUIStaticText* totalText;
        IGUIStaticText* HUDtournamentText;

        IMeshSceneNode* totaledrum;

        IMeshSceneNode* dice1;
        IMeshSceneNode* dice2;
        IMeshSceneNode* dice3;
        IMeshSceneNode* dice4;
        IMeshSceneNode* dice5;
        IMeshSceneNode* ghost1;
        IMeshSceneNode* ghost2;
        IMeshSceneNode* ghost3;
        IMeshSceneNode* ghost4;
        IMeshSceneNode* ghost5;
        IMeshSceneNode* totalCard;
        IGUIStaticText* number1;
        IGUIStaticText* number2;
        IGUIStaticText* number3;
        IGUIStaticText* number4;
        IGUIStaticText* number5;
        IGUIStaticText* numbers[6];
};

#endif // PLAYTONGAME_H
