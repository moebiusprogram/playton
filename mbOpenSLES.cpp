#include "mbOpenSLES.h"

#ifdef MB_ANDROID

SLObjectItf mbOpenSLES::engineObject = NULL;
SLEngineItf mbOpenSLES::engineEngine = NULL;
SLObjectItf mbOpenSLES::outputMixObject = NULL;


mbOpenSLES::mbOpenSLES(android_app* app, AAssetManager* assetMgr)
{
    mgr         =   assetMgr;
    currentApp  =   app;

    createEngine();
}

mbOpenSLES::~mbOpenSLES()
{
    shutdown();
}

void mbOpenSLES::createEngine()
{

    SLresult result;
    // create engine
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the engine
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the engine interface, which is needed in order to create other objects
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // create output mix, with environmental reverb specified as a non-required interface
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the output mix
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
}

mbOutputPlayer* mbOpenSLES::createAssetAudioPlayer(const char * filename)
{
    mbOutputPlayer* output = new mbOutputPlayer();

    SLresult result;

    if(!mgr)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "Irrlicht", "Android sound asset not found\n");
        return 0;
    }

    AAsset* asset = AAssetManager_open(mgr, filename , AASSET_MODE_UNKNOWN);

    // the asset might not be found
    if (NULL == asset)
    {
        return 0;
    }

    // open asset as file descriptor
    off_t start, length;
    int fd = AAsset_openFileDescriptor(asset, &start, &length);

    if(fd < 0)
    {
        return 0;
    }

    AAsset_close(asset);

    // configure audio source
    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &(output->fdPlayerObject), &audioSrc, &audioSnk,
             3, ids, req);

    if(result != SL_RESULT_SUCCESS)
        return 0;

    // realize the player
    result = (*(output->fdPlayerObject))->Realize(output->fdPlayerObject, SL_BOOLEAN_FALSE);
    if(result != SL_RESULT_SUCCESS)
        return 0;

    // get the play interface
    result = (*(output->fdPlayerObject))->GetInterface(output->fdPlayerObject, SL_IID_PLAY, &output->fdPlayerPlay);
    if(result != SL_RESULT_SUCCESS)
        return 0;

    // get the seek interface
    result = (*(output->fdPlayerObject))->GetInterface(output->fdPlayerObject, SL_IID_SEEK, &output->fdPlayerSeek);
    if(result != SL_RESULT_SUCCESS)
        return 0;

    // get the mute/solo interface
    result = (*(output->fdPlayerObject))->GetInterface(output->fdPlayerObject, SL_IID_MUTESOLO, &output->fdPlayerMuteSolo);
     if(result != SL_RESULT_SUCCESS)
        return 0;

    // get the volume interface
    result = (*(output->fdPlayerObject))->GetInterface(output->fdPlayerObject, SL_IID_VOLUME, &output->fdPlayerVolume);
     if(result != SL_RESULT_SUCCESS)
        return 0;

    return output;
}

void mbOpenSLES::shutdown()
{
    if (outputMixObject != NULL)
    {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = NULL;
    }

    if (engineObject != NULL)
    {
        (*engineObject)->Destroy(engineObject);
        engineObject = NULL;
        engineEngine = NULL;
    }
}

void mbOpenSLES::destroyOutputPlayer(mbOutputPlayer* output)
{
    delete output;
}

mbOutputPlayer::mbOutputPlayer()
{

}

mbOutputPlayer::~mbOutputPlayer()
{
    if (fdPlayerObject != NULL)
    {
        (*fdPlayerObject)->Destroy(fdPlayerObject);
        fdPlayerObject = NULL;
        fdPlayerPlay = NULL;
        fdPlayerSeek = NULL;
        fdPlayerMuteSolo = NULL;
        fdPlayerVolume = NULL;
    }
}

void mbOutputPlayer::play()
{
    SLresult result;

    if (NULL != fdPlayerPlay)
    {
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay,SL_PLAYSTATE_STOPPED);
        if(result != SL_RESULT_SUCCESS)
            return;

        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay,SL_PLAYSTATE_PLAYING);
        if(result != SL_RESULT_SUCCESS)
            return;
    }

}

void mbOutputPlayer::stop()
{
    SLresult result;

    if (NULL != fdPlayerPlay)
    {
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay,SL_PLAYSTATE_STOPPED);
    }
    if(result != SL_RESULT_SUCCESS)
                return;
}

void mbOutputPlayer::pause()
{
    SLresult result;

    if (NULL != fdPlayerPlay)
    {
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay,SL_PLAYSTATE_PAUSED);
    }
    if(result != SL_RESULT_SUCCESS)
                return;
}

void mbOutputPlayer::resume()
{
    SLresult result;

    if (NULL != fdPlayerPlay)
    {
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay,SL_PLAYSTATE_PLAYING);
    }
    if(result != SL_RESULT_SUCCESS)
                return;
}

void mbOutputPlayer::setVolume(float volume)
{

    SLresult result;
    SLmillibel millibel = gain_to_attenuation( volume );

    if (NULL != fdPlayerVolume)
    {
        result = (*fdPlayerVolume)->SetVolumeLevel(fdPlayerVolume, millibel);
    }
    if(result != SL_RESULT_SUCCESS)
                return;
}

void mbOutputPlayer::setRepeat(bool loop)
{
    SLresult result;

    if (NULL != fdPlayerSeek)
    {
        result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, (SLboolean) loop, 0,
                SL_TIME_UNKNOWN);
    }
    if(result != SL_RESULT_SUCCESS)
                return;
}

float mbOutputPlayer::gain_to_attenuation( float gain)
{
    return gain < 0.01F ? -9600.0F : 2000 * log10( gain );
}

#endif
