#include "playtonGame.h"


void playtonGame::createCilinder( s32 id )
{
    if( selectingOperand ) return;

    irr::video::ITexture* cilinderTexture = 0;

    if(active == 9 && id != GUI_ID_EQUAL)
    {
        return;
    }

    if(id == GUI_ID_EQUAL && active > 1 )
    {
        cilinderTexture = driver->getTexture("8500204024.png");
        active++;
        IMeshSceneNode* cilinder = smgr->addMeshSceneNode( smgr->getMesh( "8500204024.obj" ) );
        cilinder->setPosition( positions[active]);
        cilinder->setScale( vector3df(2.3,2.3,2.3) );
        cilinders.push_back( cilinder );
        cilinder->setRotation( vector3df(95,-90,0 ));
        cilinder->setMaterialTexture( 0, cilinderTexture );
        cilinder->setVisible(true);
        selectingOperand = true;
        waitUserResult();

        return;
    }

    switch( id )
    {
        case GUI_ID_MAS:
            {
                cilinderTexture = driver->getTexture("7752620131.png");
                operations.push_back( id );
            }
            break;
        case GUI_ID_MENOS:
            {
                cilinderTexture = driver->getTexture("1668425297.png");
                operations.push_back( id );
            }
            break;
        case GUI_ID_MULT:
            {
                cilinderTexture = driver->getTexture("5715919029.png");
                operations.push_back( id );
            }
            break;
        case GUI_ID_DIV:
            {
                cilinderTexture = driver->getTexture("8632323895.png");
                operations.push_back( id );
            }
            break;
        default:
            break;
    }

    if( cilinderTexture )
    {
        active++;
        IMeshSceneNode* cilinder = smgr->addMeshSceneNode( smgr->getMesh( "9919129311.obj" ) );
        cilinder->setPosition( positions[active]);
        cilinder->setScale( vector3df(2.3,2.3,2.3) );
        cilinder->setRotation( vector3df(95,-90,0 ));
        cilinder->setMaterialTexture( 0, cilinderTexture );
        cilinders.push_back( cilinder );
        selectingOperand = true;
    }

}

void playtonGame::createCard( s32 id )
{
    if( active > 11 ) return;

    active++;

    IMeshSceneNode* card;

    if( active < 10 )
    {
        card = smgr->addMeshSceneNode( smgr->getMesh( "9550148953.obj" ) );
        card->setID( id );

        switch( id )
        {
        case GUI_ID_1:
            {
                card->setMaterialTexture(0, driver->getTexture("6388812062.png") );
            }
            break;
        case GUI_ID_2:
            {
                card->setMaterialTexture(0, driver->getTexture("8352478064.png") );
            }
            break;
        case GUI_ID_3:
            {
                card->setMaterialTexture(0, driver->getTexture("2802546539.png") );
            }
            break;
        case GUI_ID_4:
            {
                card->setMaterialTexture(0, driver->getTexture("4185336995.png") );
            }
            break;
        case GUI_ID_5:
            {
                card->setMaterialTexture(0, driver->getTexture("3599183683.png") );
            }
            break;
        default:
            break;
        }
    }

    card->setPosition( positions[active] );
    card->setScale( vector3df(2.3,2.3,2.3) );
    cards.push_back( card );
}

void playtonGame::createPositions()
{
    f32 height = -8.45;
    f32 deep = -11;

    positions[1] = vector3df(-18 + i,height,deep);
    positions[2] = vector3df(-14.65 + i,height,deep);
    positions[3] = vector3df(-11.5 + i,height,deep);
    positions[4] = vector3df(-8.2 + i,height,deep);
    positions[5] = vector3df(-4.99 + i,height,deep);
    positions[6] = vector3df( -1.75 + i,height,deep);
    positions[7] = vector3df( 1.5 + i,height,deep);
    positions[8] = vector3df( 4.8 + i,height,deep);
    positions[9] = vector3df( 8 + i,height,deep);
    positions[10] = vector3df( 11.33 + i,height,deep);
    positions[11] = vector3df( 14.33 + i,height,deep);

    positionBoard[0] = vector3df( -10.06, 1.52, 0 );
    positionBoard[1] = vector3df( -4.66,8.09,0 );
    positionBoard[2] = vector3df( 6.6,7.53,0);
    positionBoard[3] = vector3df( 11.53,0.25, 0);
    positionBoard[4] = vector3df( 0.53,-4.41,0);

    positionBoard[5] = vector3df( 12.33,-13,11);
    positionBoard[6] = vector3df( 12.33,-13,11);
    positionBoard[7] = vector3df( 12.33,-13,11);
    positionBoard[8] = vector3df( 12.33,-13,11);
    positionBoard[9] = vector3df( 12.33,-13,11);
    positionBoard[10] = vector3df( 12.33,-13,11);
    positionBoard[11] = vector3df( 12.33,-13,11);

}

void playtonGame::showNumberText()
{
    IGUIStaticText* numberText = 0;

    if( active == 0 )
    {
        numberText =  getNumberText( active );
    }
    else
    {
        numberText = getNumberText(  active / 2 );
    }

    if(numberText)
    {
        numberText->setVisible(true);
    }
}

IGUIStaticText* playtonGame::getNumberText( u32 index )
{
    return numbers[ index ];
}

void playtonGame::changeOperatorActive()
{
    if( operatorActive <  MAX_PLAYTON_OPERATIONS && !selectingOperator )
    {
        operatorActive++;
        selectingOperator = true;
        selectingOperand = false;
    }
}

void playtonGame::setHUDtournament()
{
    irr::core::stringw tournament(L"");
    tournament += actualPlay;
    tournament += "/";
    tournament += jugadasPosibles;

    HUDtournamentText->setText( tournament.c_str() );
}