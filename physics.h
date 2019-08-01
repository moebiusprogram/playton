#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "common.h"
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class playton_physics
{

public:

    IrrlichtDevice* device;
    ISceneManager* smgr;
    IGUIEnvironment* guienv;
    irr::video::IVideoDriver* driver;

    playton_physics(IrrlichtDevice* device);
    virtual ~playton_physics();

    list<btRigidBody *> Objects;
    list<btRigidBody *> dice;

    void CreateStartScene();
    void CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass,std::string texture = "3948248684.png",bool hidden = false);
    void getValue(const list<IGUIStaticText*>* numberCharts, list<f32>* val );
    void addTetraedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture = "3948248684.png");
    void addHexaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass,std::string texture = "3948248684.png");
    void addOctaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass,std::string texture = "3948248684.png");
    void addDodecaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass,std::string texture = "3948248684.png");
    void addIcosaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass,std::string texture = "3948248684.png");
    void CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass);
    void UpdatePhysics(u32 TDeltaTime);
    void UpdateRender(btRigidBody *TObject);
    void runPhysics( list<s32> solidIDs );
    void applySomeTorque();
    void ClearDice();
    void ClearObjects();
    bool isInactive();
    s32 getValueFromBones( ISceneNode* Node );
    btDiscreteDynamicsWorld *World;
    btDefaultCollisionConfiguration *CollisionConfiguration;
    btBroadphaseInterface *BroadPhase;
    btCollisionDispatcher *Dispatcher;
    btSequentialImpulseConstraintSolver *Solver;
};

#endif // PHYSICS_H_INCLUDED
