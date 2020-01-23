#include "CombFilter.h"
#include <iostream>

CombFilter::CombFilter(float FIR_Coeff, float IIR_Coeff, int SampleDelay, int Num_chans) {
    // Initialize coefficients
    this->FIR_Coeff = FIR_Coeff;
    this->IIR_Coeff = IIR_Coeff;
    this->SampleDelay = SampleDelay;
    this->Num_chans = Num_chans;
    
    FIR_Delay = new float *[Num_chans];
    IIR_Delay = new float *[Num_chans];
    
    for(int n = 0; n < Num_chans; n++){
        FIR_Delay[n] = new float[SampleDelay];
        IIR_Delay[n] = new float[SampleDelay];
    }
    
    clearDelayLines();
}


CombFilter::~CombFilter()     // Destructor for filterAudio //
{   
    // Free all memory
    for (int k=0; k < Num_chans; k++) {
        delete [] FIR_Delay[k];
        delete [] IIR_Delay[k];
    }
    delete [] FIR_Delay;
    delete [] IIR_Delay;

}

// FIR and IIR implementation //
float ** CombFilter::combFilterBlock(float **fInput, int BlockSize, int Num_chans){
    
    // Allocate memory for output
    float **fOutput = new float *[Num_chans];
    
    for (int i = 0; i < Num_chans ; i ++)
    {
        fOutput[i] = new float[BlockSize];
    }
    
    
    for(int i = 0; i<Num_chans; i++){    // Filter each channel
        
        
        for(int j = 0; j < BlockSize; j++){
            fOutput[i][j] = fInput[i][j] + FIR_Coeff*FIR_Delay[i][SampleDelay-1] + IIR_Coeff*IIR_Delay[i][SampleDelay-1];
            
            for(int k = SampleDelay-1; k>0; k--){
                FIR_Delay[i][k] = FIR_Delay[i][k-1];
                IIR_Delay[i][k] = IIR_Delay[i][k-1];
            }
            FIR_Delay[i][0] = fInput[i][j];
            IIR_Delay[i][0] = fOutput[i][j];
        }
        
    }
    
    return fOutput;
}


void CombFilter::clearDelayLines(){     //clear the multichannel delay lines
    // Initialize delay lines
    for(int n = 0; n < Num_chans; n++){
        for(int k = 0; k < SampleDelay; k++){
            FIR_Delay[n][k] = 0.0;
            IIR_Delay[n][k] = 0.0;
        }
    }
}

int CombFilter::getSampleDelay() const{  //return the number of samples in the delay line
    return SampleDelay;
}

float CombFilter::getFIRCoeff() const{     // Return FIR gain coefficient
    return FIR_Coeff;
}

float CombFilter::getIIRCoeff() const{     // Return IIR gain coefficient
    return IIR_Coeff;
}
