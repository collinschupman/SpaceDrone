#include "Geiger.h"

static AkInt16 PitchToFrequency(AkInt16 pitchValue)
{
    static AkInt16 baseFrequencyHz = 440.0f; 
    return baseFrequencyHz * pow(2, pitchValue / 12.0f);
}

Geiger::Geiger()
{
    
}

void Geiger::process(AkInt16 density, AkReal32 random, AkReal32 dynamic)
{
    // Density is added with [other signal?] and converted from logarithmic pitch values into linear frequency in HZ
    AkInt16 mysterySignal = 0;
    AkInt16 newDensity = density + mysterySignal;
    AkInt16 densityAsHz = PitchToFrequency(newDensity);

    // Linear frequency is fed as the frequency paramater of an LFO 
    mPulseLFO.setFrequency(densityAsHz);
    mPulseLFO.getNextSample();



    // LFO outputs a pulse wave which is used to to Trigger and A to E Trigger [?]
    // The events are fed to an order pathway:
    // Path 1: is used as the input of a randomizer
    // - The randomizer randomizes the input with RND deviation
    // - The output from the randomzier is further added with + (Dyn * -1) 
    // Path 2: is used to trigger a final value output (from path 1)

}
