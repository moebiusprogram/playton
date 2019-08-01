#include "playtonGame.h"

void playtonGame::hideCiclingSolids()
{
    for(list<IMeshSceneNode*>::Iterator Iterator = ciclingSolids.begin(); Iterator != ciclingSolids.end(); ++Iterator)
    {
        IMeshSceneNode* node = *Iterator;
        node->remove();
    }

    ciclingSolids.clear();
    ciclingIDs.clear();
}

f32 playtonGame::executeOperation(f32 operand,f32 operand2, s32 opID )
{
    f32 result = 0;

    switch(opID)
    {
    case GUI_ID_MAS:
    {
        result = operand + operand2;
    }
    break;
    case GUI_ID_MENOS:
    {
        result = operand - operand2;
    }
    break;
    case GUI_ID_MULT:
    {
        result = operand * operand2;
    }
    break;
    case GUI_ID_DIV:
    {
        if(operand2 != 0)
            result = operand / operand2;
    }
    break;
    }
    return result;
}