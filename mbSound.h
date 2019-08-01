#ifndef MBSOUND_H
#define MBSOUND_H

#include "common.h"
#include <string>

#ifdef MB_ANDROID
    #include "mbOpenSLES.h"
#elif WITH_IRRKLANG
    #include "mbIrrklang.h"
#endif

class mbSound
{
public:

    mbSound();

    virtual ~mbSound();

    void init();
    void loadSound(irr::core::stringc filename, s32 ID);
    void playSound(s32 ID);
    void stopSound(s32 ID);
    void playShortSound(irr::core::stringc filename);
    void pauseSound(s32 ID);
    void resumeSound(s32 ID);
    void shutDown();
    void mute( bool mute );
    void unmute();
    void setLoopSound(bool loop , s32 ID);
    void update();
    bool isPlaying();
    bool isPaused();
    bool isMuted(){ return muted;}
    s32 getSoundIndex();
    void setVolume(f32 value, s32 ID);
    f32 mainVolume;
    f32 musicVolume;
    f32 effectVolume;

private:

    typedef irr::core::map<s32,mbOutputPlayer*> soundMapping;

    soundMapping soundMap;

    irr::core::array<mbOutputPlayer*> soundList;
    irr::core::array<mbOutputPlayer*> effectList;

    mbOutputPlayer* activeSound;
    mbOutputPlayer* mainTheme;

#ifdef MB_ANDROID
    mbOpenSLES*     soundDevice;
#elif WITH_IRRKLANG
    mbIrrklang*     soundDevice;
#endif

    bool paused;
    bool muted;
    mbOutputPlayer* getSoundFromID(s32 ID );
};

#endif // MBSOUND_H
