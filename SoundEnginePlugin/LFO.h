#include <cmath>

class TriangleLFO {
public:
    TriangleLFO(float frequency, float amplitude);

    void setFrequency(float frequency);

    void setAmplitude(float amplitude);

    float getNextSample();

private:
    float mFrequency;  
    float mAmplitude;   
    float mPhase;      
    int mDirection;     
    static constexpr float mSampleRate = 44100.0f; 
};