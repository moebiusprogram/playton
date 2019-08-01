#ifndef PLAYTON_UTILITY_H
#define PLAYTON_UTILITY_H

#include "common.h"

class playton_utility
{
    public:
        playton_utility();
        virtual ~playton_utility();
        s32 getDecimalPart( f32 value );
        f32 roundResult(f32 var);
        s32 calculateValues(s32 min, s32 max );
    protected:

    private:
        IRandomizer* randm;
};

#endif // PLAYTON_UTILITY_H
