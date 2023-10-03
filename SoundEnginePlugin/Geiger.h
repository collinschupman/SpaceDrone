#pragma once

#include <AK/SoundEngine/Common/AkNumeralTypes.h>
#include "PulseLFO.h"

class Geiger
{
public: 
    Geiger();
    void process(AkInt16 density, AkReal32 random, AkReal32 dynamic);

private:
    PulseLFO mPulseLFO;
};
