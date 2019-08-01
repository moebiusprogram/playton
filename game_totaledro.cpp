#include "playtonGame.h"

void playtonGame::getValuesFromDices()
{
    if(!rolling) return;

    bool inactives = pt_Physics->isInactive();

    if(!inactives)
    {
        rolling = false;
        pt_Physics->getValue( &numberCharts, &values );
        totaledrum->setMaterialTexture(0, driver->getTexture("7098644451.png") );
        filled  = true;
    }
}

void playtonGame::waitUserResult()
{
    totaledrum = smgr->addMeshSceneNode( smgr->getMesh( "3142320618.obj" ) );
    totaledrum->setRotation( vector3df(0,-90,0) );
    totaledrum->setMaterialTexture(0, driver->getTexture("3930222436.png") );
    totaledrum->setMaterialFlag( EMF_LIGHTING, false );
    vector3df equalPos = positions[active + 1];

    totaledrum->setPosition(vector3df( equalPos.X - 2, equalPos.Y, equalPos.Z ));
    totaledrum->setScale( vector3df(2.3,2.3,2.3) );
    cards.push_back( totaledrum );

    totaledrum->setID( GUI_ID_totaledrum );

    closedSelection = true;

    pt_Menu->waitUserResult();
}

void playtonGame::totaledrumEvent()
{

    list<s32>::Iterator itOp = operations.begin();
    list<f32>::Iterator Iterator = values.begin();

    f32 result      = 0;
    f32 value       = *Iterator;
    s32 opID        = *itOp;

    ++Iterator;
    f32 secondValue = *Iterator;

    result = executeOperation((f32)value, (f32)secondValue, opID);

    ++Iterator;
    ++itOp;

    if( Iterator != values.end() )
    {
        value   = *Iterator;
        opID    = *itOp;
        result  = executeOperation(result, value, opID);
    }

    if(active < 5)
    {
        displayResult( result );
        return;
    }

    ++Iterator;
    ++itOp;

    if( Iterator != values.end() )
    {
        value   = *Iterator;
        opID    = *itOp;
        result  = executeOperation(result, value, opID);
    }

    if(active < 7)
    {
        displayResult( result );
        return;
    }

    ++Iterator;
    ++itOp;

    if( Iterator != values.end() )
    {
        value   = *Iterator;
        opID    = *itOp;
        result  = executeOperation(result, value, opID);
    }

    if(active < 9)
    {
        displayResult( result );
        return;
    }

    ++Iterator;
    ++itOp;

    if( Iterator != values.end() )
    {
        value   = *Iterator;
        opID    = *itOp;
        result  = executeOperation(result, value, opID);
    }

    if(active < 11)
    {
        displayResult( result );
        return;
    }
}

void playtonGame::displayResult( f32 result )
{
    s32 resultInt = result;

    s32 decimalPart = pt_Util->getDecimalPart( result );
    stringw total(L"");
    total += resultInt;

    if( decimalPart > 0 )
    {
        total += L".";
        total += decimalPart;
    }

    totalText->setText( total.c_str()  );
    totalText->setOverrideColor( SColor(255,29,11,0) );

    pt_Menu->reset();
    pt_Menu->showPlayAgain();
}