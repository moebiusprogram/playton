#include "playton_game.h"
#include "physics.h"


playton_game::playton_game()
{
    this->rolling = false;
    this->dragging = false;
    this->singlePlay = false;
    this->totalText = 0;
    this->HUDtournamentText = 0;
    this->totalCard = 0;
    this->totaledrum = 0;
    this->actualPlay = 1;
}

playton_game::~playton_game()
{

}

void playton_game::initGame()
{
    driver  = device->getVideoDriver();
    smgr    = device->getSceneManager();
    guienv  = device->getGUIEnvironment();
    collMgr = smgr->getSceneCollisionManager();

    pt_Physics  = new playton_physics(device);
    pt_Util     = new playton_utility();

    createPositions();

    smgr->setAmbientLight( SColor(100,10,10,10) );
    selectingOperand = true;

    irr::core::CMatrix4<float> prjMat;
    s32 stage = 25;

    prjMat.buildProjectionMatrixOrthoLH( f32(stage*2),f32(stage*2*418/750),1,3000);

    orthogonalCamera = smgr->addCameraSceneNode();
    perspectiveCamera = smgr->addCameraSceneNode();

    pt_Physics->CreateStartScene();

    orthogonalCamera->setPosition( vector3df(0,30,-150) );
    perspectiveCamera->setPosition( vector3df(5.6,1997,-145));
    perspectiveCamera->setTarget(vector3df(0,415,-1375));
    orthogonalCamera->setTarget(vector3df(0,0,0));
    orthogonalCamera->setProjectionMatrix( prjMat,true );
}

void playton_game::createScene()
{
    ILightSceneNode* light = smgr->addLightSceneNode(0);
    light->setPosition(vector3df(0,8,-50));
    light->enableCastShadow(false);

    ILightSceneNode* light2 = smgr->addLightSceneNode(0);
    light2->setPosition(vector3df(2,2000,-145));
    light2->setRadius(20);
    light2->enableCastShadow(true);

    ILightSceneNode* light3 = smgr->addLightSceneNode(0);
    light3->setPosition(vector3df(12,2000,-155));
    light3->setRadius(10);
    light3->enableCastShadow( false );

    IMeshSceneNode* btn1 = smgr->addMeshSceneNode( smgr->getMesh( "2987769533.obj" ) );
    btn1->setPosition( vector3df(-22,8,10) );
    btn1->setMaterialFlag( EMF_LIGHTING, false );
    btn1->setMaterialTexture(0, driver->getTexture("2987769533.png") );
    btn1->setID( GUI_ID_1 );

    dice1 = (IMeshSceneNode*)btn1->clone();
    dice1->setVisible(false);
    dice1->setID(ID_FLAG_IS_DRAGABLE);

    IMeshSceneNode* btn2 = smgr->addMeshSceneNode( smgr->getMesh( "8882125518.obj" ) );
    btn2->setPosition( vector3df(-22,6,0) );
    btn2->setMaterialTexture(0, driver->getTexture("8882125518.png") );
    btn2->setID( GUI_ID_2 );

    dice2 = (IMeshSceneNode*)btn2->clone();
    dice2->setVisible(false);
    dice2->setID(ID_FLAG_IS_DRAGABLE);

    IMeshSceneNode* btn3 = smgr->addMeshSceneNode( smgr->getMesh( "9872173052.obj" ) );
    btn3->setPosition( vector3df(-22,2,0) );
    btn3->setMaterialTexture(0, driver->getTexture("9872173052.png") );
    btn3->setID( GUI_ID_3 );

    dice3 = (IMeshSceneNode*)btn3->clone();
    dice3->setVisible(false);
    dice3->setID(ID_FLAG_IS_DRAGABLE);

    IMeshSceneNode* btn4 = smgr->addMeshSceneNode( smgr->getMesh( "7025363126.obj" ) );
    btn4->setPosition( vector3df(-22,-2,0) );
    btn4->setMaterialTexture(0, driver->getTexture("7025363126.png") );
    btn4->setID( GUI_ID_4 );

    dice4 = (IMeshSceneNode*)btn4->clone();
    dice4->setVisible(false);
    dice4->setID(ID_FLAG_IS_DRAGABLE);

    IMeshSceneNode* btn5 = smgr->addMeshSceneNode( smgr->getMesh( "1703009609.obj" ) );
    btn5->setPosition( vector3df(-22,-6,0) );
    btn5->setMaterialTexture(0, driver->getTexture("1703009609.png") );
    btn5->setID( GUI_ID_5 );

    dice5 = (IMeshSceneNode*)btn5->clone();
    dice5->setVisible(false);
    dice5->setID( ID_FLAG_IS_DRAGABLE );

    ISceneNodeAnimator* anim = smgr->createRotationAnimator( vector3df(0,2,0) );
    ISceneNodeAnimator* anim2 = smgr->createRotationAnimator( vector3df(0,2,0) );
    ISceneNodeAnimator* anim3 = smgr->createRotationAnimator( vector3df(0,2,0) );
    ISceneNodeAnimator* anim4 = smgr->createRotationAnimator( vector3df(0,2,0) );
    ISceneNodeAnimator* anim5 = smgr->createRotationAnimator( vector3df(0,2,0) );

    btn1->addAnimator( anim );
    btn2->addAnimator( anim2 );
    btn3->addAnimator( anim3 );
    btn4->addAnimator( anim4 );
    btn5->addAnimator( anim5 );

//Cards
    f32 height = -8.45;
    f32 deep = -11;

    IMeshSceneNode* card1 = smgr->addMeshSceneNode( smgr->getMesh( "8785425749.obj" ) );
    card1->setPosition( vector3df(-22.9 + i,height,deep));
    card1->setScale( vector3df(2.3,2.3,2.3) );
    card1->setMaterialFlag( EMF_LIGHTING, false );
    card1->setMaterialTexture(0, driver->getTexture("8785425749.png") );
    card1->setRotation( vector3df(0,-90,0) );

    IMeshSceneNode* card2 = smgr->addMeshSceneNode( smgr->getMesh( "1949161899.obj" ) );
    card2->setPosition( vector3df(-21.25 + i,height,deep));
    card2->setScale( vector3df(2.3,2.3,2.3) );
    card2->setMaterialTexture(0, driver->getTexture("1949161899.png") );
    card2->setRotation( vector3df(0,-90,0) );

    vector3df scaledOperand = vector3df( 1.3,1.3,1.3 );

    IMeshSceneNode* operand1 = smgr->addMeshSceneNode( smgr->getMesh( "3730535182.obj" ) );
    operand1->setPosition( vector3df(21,8,3) );
    operand1->setScale( scaledOperand );
    operand1->setMaterialFlag( EMF_BACK_FACE_CULLING,false );
    operand1->setMaterialType(EMT_LIGHTMAP_ADD);
    operand1->setMaterialFlag( EMF_LIGHTING,false );
    operand1->setMaterialTexture(0, driver->getTexture("3730535182.png") );
    operand1->setRotation( vector3df(0,-90,0) );

    operand1->setID( GUI_ID_MAS );

    IMeshSceneNode* operand2 = smgr->addMeshSceneNode( smgr->getMesh( "8253825940.obj" ) );
    operand2->setPosition( vector3df(21,4.4,3) );
    operand2->setScale( scaledOperand );
    operand2->setMaterialTexture(0, driver->getTexture("8253825940.png") );
    operand2->setMaterialType(EMT_LIGHTMAP_ADD);
    operand2->setRotation( vector3df(0,-90,0) );
    operand2->setMaterialFlag( EMF_BACK_FACE_CULLING,false );
    operand2->setMaterialFlag( EMF_LIGHTING,false );
    operand2->setID( GUI_ID_MENOS );

    IMeshSceneNode* operand3 = smgr->addMeshSceneNode( smgr->getMesh( "5696506530.obj" ) );
    operand3->setPosition( vector3df(21,0.6,3) );
    operand3->setScale( scaledOperand );
    operand3->setMaterialTexture(0, driver->getTexture("5696506530.png") );
    operand3->setMaterialType(EMT_LIGHTMAP_ADD);
    operand3->setRotation( vector3df(0,-90,0) );
    operand3->setMaterialFlag( EMF_BACK_FACE_CULLING,false );
    operand3->setMaterialFlag( EMF_LIGHTING,false );
    operand3->setID( GUI_ID_MULT );

    IMeshSceneNode* operand4 = smgr->addMeshSceneNode( smgr->getMesh( "7891994630.obj" ) );
    operand4->setPosition( vector3df(21,-3.2,3) );
    operand4->setScale( scaledOperand );
    operand4->setMaterialTexture(0, driver->getTexture("7891994630.png") );
    operand4->setMaterialType(EMT_LIGHTMAP_ADD);
    operand4->setRotation( vector3df(0,-90,0) );
    operand4->setMaterialFlag( EMF_BACK_FACE_CULLING,false );
    operand4->setMaterialFlag( EMF_LIGHTING,false );
    operand4->setID( GUI_ID_DIV );

    IMeshSceneNode* operand5 = smgr->addMeshSceneNode( smgr->getMesh( "7767850029.obj" ) );
    operand5->setPosition( vector3df(21,-7,3) );
    operand5->setScale( vector3df( 0.48,0.48,0.48 ) );
    operand5->setMaterialType(EMT_LIGHTMAP_ADD);
    operand5->setMaterialFlag( EMF_LIGHTING,false );
    operand5->setMaterialTexture(0, driver->getTexture("7767850029.png") );
    operand5->setRotation( vector3df(0,180,0) );
    operand5->setID( GUI_ID_EQUAL );

    totalText = guienv->addStaticText(L"0.0", recti(0,0,1,1));
    totalText->setRelativePositionProportional( rectf(0.3,0.65,0.7,0.8) );
    totalText->setText(L"");
    totalText->setVisible(true);
    totalText->setOverrideFont( pt_Menu->getBigFont() );
    totalText->setOverrideColor( SColor(255,0,255,255) );
    totalText->setTextAlignment( EGUIA_CENTER,EGUIA_CENTER );

    HUDtournamentText = guienv->addStaticText(L"", recti(0,0,1,1));
    HUDtournamentText->setRelativePositionProportional( rectf(0.3,0.0,0.7,0.1) );
    HUDtournamentText->setText(L"null");
    HUDtournamentText->setVisible(true);
    HUDtournamentText->setOverrideFont( pt_Menu->getBigFont() );
    HUDtournamentText->setOverrideColor( SColor(255,0,0,0) );
    HUDtournamentText->setTextAlignment( EGUIA_CENTER,EGUIA_CENTER );
}

void playton_game::newGame()
{
    actualPlay = 1;
}

void playton_game::resetEverything()
{
    active          = 0;
    operatorActive  = 0;
    board           = 0;

    rolling = false;
    filled  = false;
    singlePlay = false;
    selectingOperand = true;

    activeTournament = 0;

    for(list<IMeshSceneNode*>::Iterator Iterator = cilinders.begin(); Iterator != cilinders.end(); ++Iterator)
    {
        IMeshSceneNode* Object = *Iterator;
        Object->remove();
    }

    int testing = 0;

    for(list<IMeshSceneNode*>::Iterator Iterator = cards.begin(); Iterator != cards.end(); ++Iterator )
    {
        IMeshSceneNode* Object = *Iterator;
        Object->remove();
    }

    for(list<IGUIStaticText*>::Iterator Iterator = numberCharts.begin(); Iterator != numberCharts.end(); ++Iterator)
    {
        IGUIStaticText* text = *Iterator;

        text->setVisible(false);
        text->setText(L"0");
    }

    if( totalText )
    {
        totalText->setText(L"" );
    }


    cards.clear();
    cilinders.clear();
    values.clear();
    operations.clear();
    closedSelection = false;

    if( totalCard )
    {
        totalCard->setVisible(false);
    }

    hideCiclingSolids();
    pt_Physics->ClearDice();
    selectedColors.clear();
    pt_Menu->reset();
}

void playton_game::update( u32 DeltaTime )
{
    getValuesFromDices();
    pt_Physics->UpdatePhysics( DeltaTime );

    driver->beginScene(true, true, SColor(0,200,200,200));

    smgr->setActiveCamera( perspectiveCamera );
    driver->setViewPort(rect<s32>(0,0,RES_X,RES_Y));
    smgr->drawAll();

    smgr->setActiveCamera( orthogonalCamera );
    driver->setViewPort(rect<s32>(0,0,RES_X,RES_Y));
    geometryDragging();
    smgr->drawAll();

    guienv->drawAll();
    smgr->setActiveCamera( orthogonalCamera );
    driver->endScene();
}