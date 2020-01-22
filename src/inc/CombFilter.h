#ifndef FilterAudio_hpp
#define FilterAudio_hpp

#include <stdio.h>


class FilterAudio {
public:
    FilterAudio(float fFIRCoeff, float fIIRCoeff, int iDelayInSamples, int iNumChannels); // Constructor
    ~FilterAudio();
    
    float **combFilterBlock(float **input, int blockSize, int numChannels);

    void clearDelayLines();
    
    int getDelayInSamples() const;
    float getFIRCoeff() const;
    float getIIRCoeff() const;

private:
    float fFIRCoeff;
    float fIIRCoeff;
    int iDelayInSamples;
    int iNumChannels;
    float **fFIRDelay;
    float **fIIRDelay;
};

#endif /* FilterAudio_h */
