#include "playtonGame.h"

void playtonGame::geometryDragging()
{

    if(dragged && dragging && dragged->getID() == ID_FLAG_IS_DRAGABLE && !closedSelection)
    {
        dragged->removeAnimators();
        vector2di pos = device->getCursorControl()->getPosition();

        line3df line = collMgr->getRayFromScreenCoordinates(pos);
        line3df ray;
        ray.start = line.start;
        ray.end = ray.start + (line.end - line.start).normalize() * 10000.0f;

        vector3df buttonPos  = dragged->getAbsolutePosition();
        vector3df closest = ray.getClosestPoint( buttonPos );

        if(closest.X < -14 )
        {
            closest.X = -14;
        }
        if(closest.X > 14 )
        {
            closest.X = 14;
        }

        dragged->setMaterialType( EMT_TRANSPARENT_ADD_COLOR );
        dragged->setPosition(vector3df( closest.X, closest.Y, closest.Z ));
        dragged->updateAbsolutePosition();
    }
}

void playtonGame::geometryReleased()
{
    if(closedSelection && filled )
    {
        if(dragged && dragging)
        {
            s32 id = dragged->getID();

            if( id == GUI_ID_totaledrum)
            {
                totaledrum_event();
            }
        }

        return;
    }

    if(dragged && dragging && !closedSelection)
    {
        s32 id = dragged->getID();

        vector3df pos1 = dragged->getPosition();
        ISceneNodeAnimator* animRot = smgr->createRotationAnimator( vector3df(0,2,0) );
        ISceneNodeAnimator* animRot2 = smgr->createRotationAnimator( vector3df(0,2,0) );

        dragging = false;

        if( id == ID_FLAG_IS_DRAGABLE )
        {
            dragged->remove();
        }

        if( selectingOperand )
        {

            if( active > 9 )
            {
                createCard(-1);
                return;
            }

            switch(id)
            {
            case GUI_ID_1:
            {
                ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(pos1, positionBoard[ board ],1000);
                IMeshSceneNode* solid = (IMeshSceneNode*)dice1->clone();
                solid->setVisible(true);
                ciclingSolids.push_back(solid);
                ciclingIDs.push_back(id);
                board++;

                solid->removeAnimators();
                solid->addAnimator(anim);
                solid->addAnimator(animRot);
                createCard( id );
                selectingOperand = false;
                anim->drop();
                animRot->drop();
                showNumberText();
            }
            break;
            case GUI_ID_2:
            {
                ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(pos1, positionBoard[ board ],1000);
                IMeshSceneNode* solid = (IMeshSceneNode*)dice2->clone();
                solid->setVisible(true);

                ciclingSolids.push_back(solid);
                ciclingIDs.push_back(id);
                board++;
                solid->removeAnimators();
                solid->addAnimator(anim);
                solid->addAnimator(animRot);

                createCard( id );
                selectingOperand = false;
                anim->drop();
                animRot->drop();
                showNumberText();
            }
            break;
            case GUI_ID_3:
            {
                ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(pos1, positionBoard[ board ],1000);
                IMeshSceneNode* solid = (IMeshSceneNode*)dice3->clone();
                solid->setVisible(true);
                ciclingSolids.push_back(solid);
                ciclingIDs.push_back(id);
                board++;
                solid->removeAnimators();
                solid->addAnimator(anim);
                solid->addAnimator(animRot);
                createCard( id );
                selectingOperand = false;
                anim->drop();
                animRot->drop();
                showNumberText();
            }
            break;
            case GUI_ID_4:
            {
                ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(pos1, positionBoard[ board ],1000);
                IMeshSceneNode* solid = (IMeshSceneNode*)dice4->clone();
                solid->setVisible(true);
                ciclingSolids.push_back(solid);
                ciclingIDs.push_back(id);
                board++;
                solid->removeAnimators();
                solid->addAnimator(anim);
                solid->addAnimator(animRot);
                createCard( id );
                selectingOperand = false;
                anim->drop();
                animRot->drop();
                showNumberText();
            }
            break;
            case GUI_ID_5:
            {
                ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(pos1, positionBoard[ board ],1000);
                IMeshSceneNode* solid = (IMeshSceneNode*)dice5->clone();
                solid->setVisible(true);
                ciclingSolids.push_back(solid);
                ciclingIDs.push_back(id);
                board++;
                solid->removeAnimators();
                solid->addAnimator(anim);
                solid->addAnimator(animRot);
                createCard( id );
                selectingOperand = false;
                anim->drop();
                animRot->drop();
                showNumberText();
            }
            break;
            default:
                break;
            }

            return;

        }

        if( !selectingOperand )
        {
            if( active > 9 ) return;

            createCilinder( id );
        }

        dragged = 0;

    }

}

void playtonGame::geometryClicked()
{
    vector2di pos = device->getCursorControl()->getPosition();
    ISceneNode* selected = collMgr->getSceneNodeFromScreenCoordinatesBB(pos);

    if(selected)
    {
        dragging = true;

        if( selected->getID() == ID_FLAG_IS_DRAGABLE && !closedSelection )
        {
            IMeshSceneNode* solid2 = (IMeshSceneNode*)selected->clone();
            dragged = solid2;
        } else {
            dragged = selected;
        }

    }
}