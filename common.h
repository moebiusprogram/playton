#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <irrlicht.h>
#include <iostream>
#include <string>
#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "font_manager.h"
#include "playton_translation.h"

#define PLAYTON_TITLE L"Playton"
#define RES_X 750
#define RES_Y 418
#define WITH_IRRKLANG 1


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

#include "enumerations.h"

class mbSound;

extern mbSound* pt_Sound;
extern IrrlichtDevice *device;
extern playton_translation* pt_Translation;
extern IGUIInOutFader* fader;

#endif // COMMON_H_INCLUDED
