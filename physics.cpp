#include "common.h"
#include "physics.h"


playtonPhysics::playtonPhysics(IrrlichtDevice* mainDevice)
{
    this->device = mainDevice;
    this->smgr = mainDevice->getSceneManager();
    this->driver = mainDevice->getVideoDriver();
    this->guienv = mainDevice->getGUIEnvironment();

	this->CollisionConfiguration = new btDefaultCollisionConfiguration();
	this->BroadPhase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
	this->Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	this->Solver = new btSequentialImpulseConstraintSolver();
	this->World = new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration);
}

playtonPhysics::~playtonPhysics()
{

}

void playtonPhysics::CreateStartScene()
{
	ClearObjects();

	CreateBox(btVector3(5.0f, 1990.0f, -150.0f), vector3df(25.0f, 0.5f, 25.0f), 0.0f, "8152247949.png");
	CreateBox(btVector3(5.0f, 1990.0f, -146.f), vector3df(15.0f, 15.0f,  0.5f), 0.0f, "1582769006.png",true);
	CreateBox(btVector3(5.0f, 1990.0f, -155.0f), vector3df(15.0f, 15.0f,  0.5f), 0.0f, "1582769006.png");
	CreateBox(btVector3(-1.5f, 1990.0f, -150.0f), vector3df(0.5f, 15.0f,  15.0f), 0.0f, "1582769006.png");
	CreateBox(btVector3(12.8f, 1990.0f, -150.0f), vector3df(0.5f, 15.0f,  15.0f), 0.0f, "1582769006.png");
}

void playtonPhysics::addTetraedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture)
{
    IAnimatedMesh* elementMesh = smgr->getMesh( "8211875055.x" );
    IMesh* elementMesh2 = smgr->getMesh( "8211875055.obj" );
	IAnimatedMeshSceneNode *Node = smgr->addAnimatedMeshSceneNode( elementMesh );
	IMeshSceneNode *Node2 = smgr->addMeshSceneNode( elementMesh2 );

	Node->setScale(TScale);
	Node2->setMaterialFlag(EMF_LIGHTING, true);
	Node2->setMaterialTexture(0, driver->getTexture( texture.c_str() ) );
    Node2->setName( "tetraedro" );
    ITriangleSelector* selector = smgr->createTriangleSelector( elementMesh2, Node2 );
    Node2->setTriangleSelector(selector);
    Node2->addShadowVolumeSceneNode( elementMesh );
    Node2->setID( TETRAEDRO );

	for( int i = 0; i < Node->getJointCount(); i++ )
    {
        IBoneSceneNode* bone = Node->getJointNode(i);
        const c8* bone_name = bone->getName();

        s32 bone_value = atoi(bone_name + 1);

        if( bone_value > 0 )
        {
            vector3df pos = bone->getAbsolutePosition();
            ISceneNode* cube = smgr->addEmptySceneNode();
            cube->setPosition(vector3df(-(pos.X), (pos.Y),pos.Z));
            cube->setName( bone_name );
            cube->updateAbsolutePosition();
            cube->setParent( Node2 );
        }
    }
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);

	btConvexHullShape *Shape = new btConvexHullShape();
    Shape->addPoint(btVector3(0.756964,-0.309030,0.437034));
    Shape->addPoint(btVector3(-0.756964,-0.309030,0.437034));
    Shape->addPoint(btVector3(0.000000,-0.309029,-0.874068));
    Shape->addPoint(btVector3(0.000000,0.927088,0.000000));
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);
	RigidBody->setRestitution(0.7f);
	RigidBody->applyTorque( btVector3(200,200,200) );
	RigidBody->setUserPointer((void *)(Node2));
    Node->remove();

	World->addRigidBody(RigidBody);

    dice.push_back(RigidBody);
}

void playtonPhysics::addHexaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture)
{
    IAnimatedMesh* elementMesh = smgr->getMesh( "8211875056.x" );
    IMesh* elementMesh2 = smgr->getMesh( "8211875056.obj" );
	IAnimatedMeshSceneNode *Node = smgr->addAnimatedMeshSceneNode( elementMesh );
	IMeshSceneNode *Node2 = smgr->addMeshSceneNode( elementMesh2 );
	Node->setScale(TScale);
	Node2->setMaterialFlag(EMF_LIGHTING, true);
	Node2->setMaterialTexture(0, driver->getTexture(texture.c_str()));
    Node2->setID( HEXAEDRO );

	for( int i = 0; i < Node->getJointCount(); i++ )
    {
        IBoneSceneNode* bone = Node->getJointNode(i);
        const c8* bone_name = bone->getName();
        s32 bone_value = atoi(bone_name + 1);

        if( bone_value > 0 )
        {
            vector3df pos = bone->getAbsolutePosition();
            ISceneNode* cube = smgr->addEmptySceneNode();
            cube->setPosition(vector3df(-(pos.X), (pos.Y),pos.Z));
            cube->setName( bone_name );
            cube->updateAbsolutePosition();
            cube->setParent( Node2 );
        }
    }

    ITriangleSelector* selector = smgr->createTriangleSelector( elementMesh2, Node2 );
    Node2->setTriangleSelector(selector);
    Node2->addShadowVolumeSceneNode( elementMesh2 );

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);

	btConvexHullShape *Shape = new btConvexHullShape();
    Shape->addPoint(btVector3(0.592540,0.592540,0.592540));
    Shape->addPoint(btVector3(0.592540,-0.592540,-0.592541));
    Shape->addPoint(btVector3(0.592540,0.592541,-0.592540));
    Shape->addPoint(btVector3(-0.592540,-0.592541,0.592541));
    Shape->addPoint(btVector3(0.592540,-0.592541,0.592541));
    Shape->addPoint(btVector3(-0.592540,0.592540,0.592540));
    Shape->addPoint(btVector3(-0.592540,-0.592540,-0.592541));
    Shape->addPoint(btVector3(-0.592540,0.592541,-0.592540));

	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);
	RigidBody->setRestitution(0.7f);
	RigidBody->applyTorque( btVector3(200,200,200) );
	RigidBody->setUserPointer((void *)(Node2));

    Node->remove();

	World->addRigidBody(RigidBody);

	dice.push_back(RigidBody);
}

void playtonPhysics::addOctaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture)
{
    IAnimatedMesh* elementMesh = smgr->getMesh( "8211875057.x" );
    IMesh* elementMesh2 = smgr->getMesh( "8211875057.obj" );

	IAnimatedMeshSceneNode *Node = smgr->addAnimatedMeshSceneNode( elementMesh );
	IMeshSceneNode *Node2 = smgr->addMeshSceneNode( elementMesh2 );
	Node->setScale(TScale);
	Node2->setMaterialFlag(EMF_LIGHTING, true);
	Node2->setMaterialTexture(0, driver->getTexture(texture.c_str() ));
    Node2->setID( OCTAEDRO );

	for( int i = 0; i < Node->getJointCount(); i++ )
    {
        IBoneSceneNode* bone = Node->getJointNode(i);
        const c8* bone_name = bone->getName();

        s32 bone_value = atoi(bone_name + 1);

        if( bone_value > 0 )
        {
            vector3df pos = bone->getAbsolutePosition();
            ISceneNode* cube = smgr->addEmptySceneNode();
            cube->setPosition(vector3df(-(pos.X), (pos.Y),pos.Z));
            cube->setName( bone_name );
            cube->updateAbsolutePosition();
            cube->setParent( Node2 );
        }
    }
    ITriangleSelector* selector = smgr->createTriangleSelector( elementMesh2, Node2 );
    Node2->setTriangleSelector(selector);
    Node2->addShadowVolumeSceneNode( elementMesh2 );

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);

	btConvexHullShape *Shape = new btConvexHullShape();
    Shape->addPoint(btVector3(0.000000,0.000000,-1.008364));
    Shape->addPoint(btVector3(-1.008364,0.000000,0.000000));
    Shape->addPoint(btVector3(0.000000,1.008364,0.000000));
    Shape->addPoint(btVector3(0.000000,-0.000000,1.008364));
    Shape->addPoint(btVector3(0.000000,-1.008364,-0.000001));
    Shape->addPoint(btVector3(1.008364,0.000000,0.000000));
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);
	RigidBody->setRestitution(0.7f);
	RigidBody->applyTorque( btVector3(200,100,200) );
	RigidBody->setUserPointer((void *)(Node2));

    Node->remove();

	World->addRigidBody(RigidBody);
	dice.push_back(RigidBody);
}

void playtonPhysics::addIcosaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture)
{
    IAnimatedMesh* elementMesh = smgr->getMesh( "8211875058.x" );
    IMesh* elementMesh2 = smgr->getMesh( "8211875058.obj" );

	IAnimatedMeshSceneNode *Node = smgr->addAnimatedMeshSceneNode( elementMesh );
	IMeshSceneNode *Node2 = smgr->addMeshSceneNode( elementMesh2 );
	Node->setScale(TScale);
	Node2->setMaterialFlag(EMF_LIGHTING, true);
	Node2->setMaterialTexture(0, driver->getTexture(texture.c_str() ));
    Node2->setID( ICOSAEDRO );

	for( int i = 0; i < Node->getJointCount(); i++ )
    {
        IBoneSceneNode* bone = Node->getJointNode(i);
        const c8* bone_name = bone->getName();

        s32 bone_value = atoi(bone_name + 1);

        if( bone_value > 0 )
        {
            vector3df pos = bone->getAbsolutePosition();
            ISceneNode* cube = smgr->addEmptySceneNode();
            cube->setPosition(vector3df(-(pos.X), (pos.Y),pos.Z));
            cube->setName( bone_name );
            cube->updateAbsolutePosition();
            cube->setParent( Node2 );
        }
    }
    ITriangleSelector* selector = smgr->createTriangleSelector( elementMesh2, Node2 );
    Node2->setTriangleSelector(selector);
    Node2->addShadowVolumeSceneNode( elementMesh2 );

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);

	btConvexHullShape *Shape = new btConvexHullShape();
    Shape->addPoint(btVector3(-0.000000,0.399989,-0.647214));
    Shape->addPoint(btVector3(0.647212,0.000021,-0.399998));
    Shape->addPoint(btVector3(-0.000000,-0.399979,-0.647215));
    Shape->addPoint(btVector3(-0.000000,0.399989,0.647213));
    Shape->addPoint(btVector3(-0.400000,0.647205,0.000000));
    Shape->addPoint(btVector3(-0.647214,0.000021,0.400000));
    Shape->addPoint(btVector3(0.400004,0.647205,0.000000));
    Shape->addPoint(btVector3(0.647212,0.000021,0.400000));
    Shape->addPoint(btVector3(-0.000000,-0.399979,0.647213));
    Shape->addPoint(btVector3(-0.400000,-0.647259,-0.000000));
    Shape->addPoint(btVector3(0.400004,-0.647259,-0.000000));
    Shape->addPoint(btVector3(-0.647214,0.000021,-0.399998));

	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);
	RigidBody->setRestitution(0.7f);
	RigidBody->applyTorque( btVector3(200,200,200) );
	RigidBody->setUserPointer((void *)(Node2));

    Node->remove();

	World->addRigidBody(RigidBody);
	dice.push_back(RigidBody);
}

void playtonPhysics::addDodecaedro(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture)
{
    IAnimatedMesh* elementMesh = smgr->getMesh( "8211875059.x" );
    IMesh* elementMesh2 = smgr->getMesh( "8211875059.obj" );

	IAnimatedMeshSceneNode *Node = smgr->addAnimatedMeshSceneNode( elementMesh );
	IMeshSceneNode *Node2 = smgr->addMeshSceneNode( elementMesh2 );
	Node->setScale(TScale);
	Node2->setMaterialFlag(EMF_LIGHTING, true);
	Node2->setMaterialTexture(0, driver->getTexture(texture.c_str()));
    Node2->setID( DODECAEDRO );

	for( int i = 0; i < Node->getJointCount(); i++ )
    {
        IBoneSceneNode* bone = Node->getJointNode(i);
        const c8* bone_name = bone->getName();

        s32 bone_value = atoi(bone_name + 1);

        if( bone_value > 0 )
        {
            vector3df pos = bone->getAbsolutePosition();
            ISceneNode* cube = smgr->addEmptySceneNode();
            cube->setPosition(vector3df(-(pos.X), (pos.Y),pos.Z));
            cube->setName( bone_name );
            cube->updateAbsolutePosition();
            cube->setParent( Node2 );
        }
    }
    ITriangleSelector* selector = smgr->createTriangleSelector( elementMesh2, Node2 );
    Node2->setTriangleSelector(selector);
    Node2->addShadowVolumeSceneNode( elementMesh2 );

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);

	btConvexHullShape *Shape = new btConvexHullShape();
    Shape->addPoint(btVector3(-0.634921,0.127675,-0.209246));
    Shape->addPoint(btVector3(-0.241447,-0.540838,-0.335272));
    Shape->addPoint(btVector3(-0.393473,-0.540838,0.126025));
    Shape->addPoint(btVector3(0.241447,0.540838,0.335272));
    Shape->addPoint(btVector3(-0.244251,0.540838,0.333235));
    Shape->addPoint(btVector3(-0.395206,0.127674,0.539185));
    Shape->addPoint(btVector3(0.393473,0.540838,-0.126025));
    Shape->addPoint(btVector3(-0.392402,0.540838,-0.129321));
    Shape->addPoint(btVector3(0.636654,0.127675,-0.203913));
    Shape->addPoint(btVector3(0.395207,-0.127675,-0.539185));
    Shape->addPoint(btVector3(0.392402,-0.540838,0.129321));
    Shape->addPoint(btVector3(-0.636654,-0.127675,0.203913));
    Shape->addPoint(btVector3(-0.001733,-0.540838,0.413160));
    Shape->addPoint(btVector3(0.002804,0.127675,-0.668506));
    Shape->addPoint(btVector3(0.244251,-0.540838,-0.333235));
    Shape->addPoint(btVector3(0.634921,-0.127675,0.209246));
    Shape->addPoint(btVector3(0.390670,0.127674,0.542482));
    Shape->addPoint(btVector3(-0.002804,-0.127675,0.668507));
    Shape->addPoint(btVector3(0.001733,0.540838,-0.413160));
    Shape->addPoint(btVector3(-0.390670,-0.127675,-0.542482));

	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);
	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);
	RigidBody->setRestitution(0.7f);
	RigidBody->applyTorque( btVector3(200,100,200) );

	RigidBody->setUserPointer((void *)(Node2));
    Node->remove();

	World->addRigidBody(RigidBody);
	dice.push_back(RigidBody);
}

void playtonPhysics::CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass, std::string texture, bool hidden)
{
	IMeshSceneNode *Node = smgr->addCubeSceneNode(1.0f);
	Node->setScale(TScale);

	Node->setMaterialFlag(EMF_LIGHTING, false);
	Node->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL_REF );
	Node->setMaterialTexture(0, driver->getTexture(texture.c_str()));

    ITriangleSelector* selector = smgr->createTriangleSelector( Node->getMesh(), Node );
    Node->setTriangleSelector(selector);

    if(hidden)
    {
        Node->setVisible(false);
    }

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);
	btCollisionShape *Shape = new btBoxShape(HalfExtents);
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);
	RigidBody->setRestitution(0.7f);
	RigidBody->applyTorque( btVector3(50,50,50) );
	RigidBody->setUserPointer((void *)(Node));

	World->addRigidBody(RigidBody);
	Objects.push_back(RigidBody);
}

void playtonPhysics::applySomeTorque()
{
    for(list<btRigidBody *>::Iterator Iterator = dice.begin(); Iterator != dice.end(); ++Iterator) {

		btRigidBody* body =  *Iterator;
		body->applyTorqueImpulse( btVector3(1.2,1.1,1.3) );
	}
}

void playtonPhysics::UpdatePhysics(u32 TDeltaTime)
{

	World->stepSimulation(TDeltaTime * 0.001f, 60);

	for(list<btRigidBody *>::Iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {

		UpdateRender(*Iterator);
	}

	for(list<btRigidBody *>::Iterator Iterator = dice.begin(); Iterator != dice.end(); ++Iterator) {

		UpdateRender(*Iterator);
	}
}

void playtonPhysics::runPhysics( list<s32> solidIDs )
{
    for(list<s32>::Iterator Iterator = solidIDs.begin(); Iterator != solidIDs.end(); ++Iterator) {

		s32 id = *Iterator;

		 switch(id)
        {
        case GUI_ID_1:
            {
                addTetraedro(btVector3(5.0f, 1995.0f, -150.0f), vector3df(1,1,1), 1.0f,"8211875040.png");
            }
            break;
        case GUI_ID_2:
            {
                addHexaedro(btVector3(5.9f, 1995.0f, -148.0f), vector3df(1,1,1), 1.0f,"8211875041.png");
            }
            break;
        case GUI_ID_3:
            {
                addOctaedro(btVector3(6.1f, 1995.0f, -148.0f), vector3df(1,1,1), 1.0f,"8211875042.png");
            }
            break;
        case GUI_ID_4:
            {
                addDodecaedro(btVector3(5.2f, 1995.0f, -151.0f), vector3df(1,1,1), 1.0f,"8211875043.png");
            }
            break;
        case GUI_ID_5:
            {
                addIcosaedro(btVector3(4.8f, 1995.0f, -151.0f), vector3df(1,1,1), 1.0f,"8211875044.png");
            }
            break;
        default:
            break;
        }
	}

    applySomeTorque();
}

void playtonPhysics::UpdateRender(btRigidBody *TObject)
{
	ISceneNode *Node = static_cast<ISceneNode *>(TObject->getUserPointer());

	// Set position
	btVector3 Point = TObject->getCenterOfMassPosition();
	Node->setPosition(vector3df((f32)Point[0], (f32)Point[1], (f32)Point[2]));

	// Set rotation
	vector3df Euler;
	const btQuaternion& TQuat = TObject->getOrientation();
	quaternion q(TQuat.getX(), TQuat.getY(), TQuat.getZ(), TQuat.getW());
	q.toEuler(Euler);
	Euler *= RADTODEG;
	Node->setRotation(Euler);
}

void playtonPhysics::ClearObjects()
{

	for(list<btRigidBody *>::Iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {
		btRigidBody *Object = *Iterator;

		ISceneNode *Node = static_cast<ISceneNode *>(Object->getUserPointer());
		Node->remove();

		World->removeRigidBody(Object);

		delete Object->getMotionState();
		delete Object->getCollisionShape();
		delete Object;
	}

	Objects.clear();
}

void playtonPhysics::ClearDice()
{
	for(list<btRigidBody *>::Iterator Iterator = dice.begin(); Iterator != dice.end(); ++Iterator) {
		btRigidBody *Object = *Iterator;

		ISceneNode *Node = static_cast<ISceneNode *>(Object->getUserPointer());
		Node->remove();

		World->removeRigidBody(Object);

		delete Object->getMotionState();
		delete Object->getCollisionShape();
		delete Object;
	}

	dice.clear();
}

bool playtonPhysics::isInactive()
{
    bool inactives = false;

    for(list<btRigidBody *>::Iterator Iterator = dice.begin(); Iterator != dice.end(); ++Iterator) {

		btRigidBody* body = *Iterator;

		if( body->isActive() )
        {
            inactives = true;
        }
	}

	return inactives;
}

void playtonPhysics::getValue(const list<IGUIStaticText*>* numberCharts, list<f32>* values )
{

    list<IGUIStaticText*>::ConstIterator chartIt = numberCharts->begin();

     for(list<btRigidBody *>::Iterator Iterator = dice.begin(); Iterator != dice.end(); ++Iterator) {

		btRigidBody* body = *Iterator;
        ISceneNode *Node = static_cast<ISceneNode *>(body->getUserPointer());

        IGUIStaticText* text = *chartIt;

        s32 val = getValueFromBones( Node );
        text->setText( stringw(val).c_str() );
        values->push_back( val );
        ++chartIt;
	}

}

s32 playtonPhysics::getValueFromBones(ISceneNode* Node )
{
    list<ISceneNode*> bones = Node->getChildren();

    for(list<ISceneNode*>::Iterator Iterator = bones.begin(); Iterator != bones.end(); ++Iterator)
    {
        vector3df pos = (*Iterator)->getAbsolutePosition();

        if( Node->getID() == ICOSAEDRO )
        {
            if( pos.Y > 1991.42)
            {
                const c8* bone_name = (*Iterator)->getName();
                s32 bone_value = atoi(bone_name + 1);
                return bone_value;
            }
        }
        else if(pos.Y > 1991.3 )
        {
            const c8* bone_name = (*Iterator)->getName();
            s32 bone_value = atoi(bone_name + 1);
            return bone_value;
        }
    }

    return 0;
}