# define M_PI           3.14159265358979323846  /* pi */

#include "PulseLFO.h"

static constexpr float kTwoPi = 2.0f * M_PI;
PulseLFO::PulseLFO()
{

 }

PulseLFO::PulseLFO(float frequency, float amplitude, float dutyCycle)
    : mFrequency(frequency), mAmplitude(amplitude), mDutyCycle(dutyCycle), mPhase(0.0f), mSampleRate(44100.0f) {
}

void PulseLFO::setFrequency(float frequency) {
    mFrequency = frequency;
}

void PulseLFO::setAmplitude(float amplitude) {
    mAmplitude = amplitude;
}

void PulseLFO::setDutyCycle(float dutyCycle) {
    mDutyCycle = dutyCycle;
}

float PulseLFO::getNextSample() {
    // Calculate the phase increment based on the desired frequency in Hz
    float phaseIncrement = (kTwoPi * mFrequency) / mSampleRate;

    float sample = (mPhase < mDutyCycle) ? mAmplitude : -mAmplitude;

    mPhase += phaseIncrement;

    if (mPhase >= 1.0f) {
        mPhase -= 1.0f;
    }

    return sample;
}