#ifndef MBIRRKLANG_H
#define MBIRRKLANG_H
#include "common.h"
#include <irrKlang.h>

using namespace irrklang;

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
    stringc path;
    ISound* source;

    ISoundEngine* engine;
};

class mbIrrklang
{
public:

    mbIrrklang();
    virtual ~mbIrrklang();
    void createEngine();
    mbOutputPlayer* createAssetAudioPlayer(const char * filename);
    void shutdown();
private:

    ISoundEngine* engine;

};

#endif // MBIRRKLANG_H
