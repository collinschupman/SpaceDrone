#include <cmath>|

#include "LFO.h"

TriangleLFO::TriangleLFO(float frequency, float amplitude)
        : mFrequency(frequency), mAmplitude(amplitude), mPhase(0.0f), mDirection(1) 
{
}

    void TriangleLFO::setFrequency(float frequency) {
        mFrequency = frequency;
    }

    void TriangleLFO::setAmplitude(float amplitude) {
        mAmplitude = amplitude;
    }

    float TriangleLFO::getNextSample() {
        float sample = (2.0f * mPhase - 1.0f) * mAmplitude;

        mPhase += mFrequency / mSampleRate * mDirection;

        if (mPhase >= 1.0f || mPhase <= 0.0f) {
            mDirection = -mDirection;
        }

        return sample;
    }
