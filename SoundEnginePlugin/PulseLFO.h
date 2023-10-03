#include <cmath>

class PulseLFO {
public:
    PulseLFO();
    PulseLFO(float frequency, float amplitude, float dutyCycle);

    void setFrequency(float frequency);

    void setAmplitude(float amplitude);

    float getNextSample();

    void setDutyCycle(float dutyCycle);

private:
    float mFrequency;  
    float mAmplitude;   
    float mPhase;      
    float mDutyCycle;
    int mDirection;     
    float mSampleRate = 44100.0f; 
};