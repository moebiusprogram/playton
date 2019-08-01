#include "mbSound.h"

#ifdef WITH_IRRKLANG
using namespace irrklang;
#endif

mbSound::mbSound():
    mainVolume( 0 ),
    effectVolume( 0 ),
    musicVolume( 0 ),
    paused( false ),
    muted( false )
{

#ifdef MB_ANDROID
    soundDevice = new mbOpenSLES(gData->app,gData->assetMgr);
#elif WITH_IRRKLANG
    soundDevice = new mbIrrklang();
#endif

    if (!soundDevice)
    {
        cerr << "device failed to open" << endl;
    }
}

mbSound::~mbSound()
{
    soundDevice->shutdown();
}

void mbSound::init()
{

}

void mbSound::loadSound(irr::core::stringc filename,s32 ID)
{

    if( getSoundFromID(ID) )
        return;

    mbOutputPlayer* sound = 0;
    sound = soundDevice->createAssetAudioPlayer(filename.c_str());

    if (!sound)
    {
        cerr << "File not found to load" << endl;
        return;
    }

    soundList.push_back(sound);
    soundMap.insert( ID, sound );
}

void mbSound::playSound(s32 ID)
{
    mbOutputPlayer* sound = getSoundFromID(ID);

    if(!sound)
    {
        cerr << "File not found to play" << endl;
        return;
    }

    sound->play();
}

void mbSound::playShortSound(irr::core::stringc filename)
{
#if defined(MB_ANDROID) || defined(WITH_IRRKLANG)
    mbOutputPlayer* sound = 0;
    sound = soundDevice->createAssetAudioPlayer(filename.c_str());
#else
    OutputStreamPtr sound = 0;
    sound = OpenSound(soundDevice, filename.c_str());
#endif

    if(sound)
    {
        sound->setVolume( effectVolume );
        sound->play();
    }
}

void mbSound::update()
{

}

#ifdef MB_ANDROID
void mbSound::shutDown()
{
    for(int ix = 0; ix < soundList.size();ix++ )
    {
       soundDevice->destroyOutputPlayer(soundList[ix]);
    }

    soundDevice->shutdown();
}
#endif

void mbSound::setLoopSound( bool loop, s32 ID )
{
    mbOutputPlayer* sound = getSoundFromID(ID);

    if(!sound)
    {
        cerr << "File not found to set loop" << endl;
        return;
    }

    sound->setRepeat(loop);
}

mbOutputPlayer* mbSound::getSoundFromID(s32 ID)
{
    soundMapping::Node* n = soundMap.find(ID);

    if(n)
    {
        return n->getValue();
    }

    return 0;
}

void mbSound::setVolume(f32 value,s32 ID)
{

    if(muted)
        return;

#if defined(MB_ANDROID) || defined(WITH_IRRKLANG)
    mbOutputPlayer* sound = 0;
#else
    OutputStreamPtr sound = 0;
#endif
}

void mbSound::stopSound (s32 ID )
{

}


void mbSound::pauseSound( s32 ID )
{
    mbOutputPlayer* sound = 0;
}

void mbSound::resumeSound( s32 ID )
{

}

void mbSound::mute( bool mute )
{

    for(s32 index = 0; index < soundList.size(); index++)
    {
        f32 volume = 0.0;
        if( !mute ) volume = 1;

        mbOutputPlayer* sound = soundList[index];
        sound->setVolume( volume );
    }

    muted = mute;
}

void mbSound::unmute()
{
    for(s32 index = 0; index < soundList.size(); index++)
    {
        mbOutputPlayer* sound = soundList[index];
        sound->setVolume( 1 );
    }

    muted = false;
}