
#include <stdio.h>


class CombFilter {
public:
    CombFilter(float FIR_Coeff, float IIR_Coeff, int SampleDelay, int Num_chans); // Constructor
    ~CombFilter();
    
    float **combFilterBlock(float **input, int blockSize, int Num_chans);

    void clearDelayLines();
    
    int getSampleDelay() const;
    float getFIRCoeff() const;
    float getIIRCoeff() const;

private:
    float FIRCoeff;
    float IIRCoeff;
    int SampleDelay;
    int Num_chans;
    float **FIR_Delay;
    float **IIR_Delay;
};

#endif /* CombFilter */
