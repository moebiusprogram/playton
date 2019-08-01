#ifndef MBOPENSLES_H
#define MBOPENSLES_H

#ifdef MB_ANDROID

#include <android_native_app_glue.h>
#include "jni.h"
#include <assert.h>
#include "android/log.h"
#include <cmath>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class mbOutputPlayer
{
    public:

    mbOutputPlayer();
    virtual ~mbOutputPlayer();

    void play();
    void stop();
    void pause();
    void resume();
    void setRepeat(bool loop);
    void setVolume(float volume);


    float gain_to_attenuation( float gain );

    SLObjectItf     fdPlayerObject;
    SLPlayItf       fdPlayerPlay;
    SLSeekItf       fdPlayerSeek;
    SLMuteSoloItf   fdPlayerMuteSolo;
    SLVolumeItf     fdPlayerVolume;
};

class mbOpenSLES
{
public:

    mbOpenSLES(android_app* app, AAssetManager* assetMgr);
    virtual ~mbOpenSLES();
    void createEngine();
    mbOutputPlayer* createAssetAudioPlayer(const char * filename);
    void shutdown();

    void destroyOutputPlayer(mbOutputPlayer* output);

protected:
private:

    AAssetManager* mgr;
    android_app* currentApp;

    static SLObjectItf engineObject;
    static SLEngineItf engineEngine;
    static SLObjectItf outputMixObject;

};

#endif
#endif // MBOPENSLES_H
