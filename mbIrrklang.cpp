#include "mbIrrklang.h"

using namespace irrklang;

mbIrrklang::mbIrrklang():
    engine( NULL )
{
   createEngine();
}

mbIrrklang::~mbIrrklang()
{
    //dtor
}

void mbIrrklang::createEngine()
{
    engine = createIrrKlangDevice();

    if(!engine)
    {
        cout << "irrklang not created" << endl;
        return;
    }
}

void mbIrrklang::shutdown()
{
    engine->drop();
}

mbOutputPlayer* mbIrrklang::createAssetAudioPlayer(const char* path)
{
    if(!engine)
    {
        cout << "Error creating asset for no engine" << endl;
        return NULL;
    }

    mbOutputPlayer* output = new mbOutputPlayer();

    if(!output)
    {
        cout << "Error creating mbOutputPlayer" << endl;
         return NULL;
    }

    output->source = engine->play2D(path, false,true,true);

    if(!output)
    {
        cout << "Error loading ISound" << endl;
        return NULL;
    }

    output->path = path;
    cout << output->path.c_str() << endl;
    output->engine = engine;

    return output;
}

mbOutputPlayer::mbOutputPlayer():
    source( NULL )
{

}

mbOutputPlayer::~mbOutputPlayer()
{

}

void mbOutputPlayer::play()
{
    if(source->isFinished())
        source = engine->play2D(path.c_str(),false,true,true);
    source->setIsPaused(false);
}

void mbOutputPlayer::stop()
{
    source->stop();
}

void mbOutputPlayer::pause()
{
    source->setIsPaused(true);
}

void mbOutputPlayer::resume()
{
    source->setIsPaused(false);
}

void mbOutputPlayer::setRepeat(bool repeat)
{
    source->setIsLooped(repeat);
}

void mbOutputPlayer::setVolume(float volume)
{
    source->setVolume(volume);
}
