#include "playton_utility.h"

playton_utility::playton_utility()
{
    this->randm   = device->getRandomizer();
}

playton_utility::~playton_utility()
{

}

s32 playton_utility::getDecimalPart( f32 value )
{
    f32 fractpart,intpart;

    fractpart = modff (value , &intpart);
    fractpart *= 100;

    return (s32)fractpart;
}

f32 playton_utility::roundResult(f32 var)
{
    f32 value = (s32)(var * 100 + .5);
    return (f32)value / 100;
}

s32 playton_utility::calculateValues(s32 min, s32 max )
{
    max = max - min;
    s32 result = randm->rand()%( max );

   return result + min;
}
