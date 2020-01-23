
include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using std::cout;
using std::endl;

int Zero_Input();
int Diff_Block_Sizes();

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 // file paths
                            sOutputFilePath;

    clock_t                 time = 0;
    
    CombFilterIf *pCombFilter;
    
    float FIR_Coeff = 0.0;
    float IIR_Coeff = 0.0;
    float Delay = 0.0;
    int BlockSize = 2048; 
    int iFileOpenStatus;

    float                   **ppfAudioData = 0;

    CAudioFileIf            *phAudioFile = 0;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;

    showClInfo();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    if( argc == 7 || argc == 8) {
        //File path and name
        sInputFilePath = argv[1];
        sInputFileName = argv[2];

        //Gain
        FIR_Coeff = atof(argv[3]);
        IIR_Coeff = atof(argv[4]);

    fDelayInMSec = atof(argv[5]);
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    if (!phAudioFile->isOpen())
    {
        cout << "Wave file open error!";
        return -1;
    }
    phAudioFile->getFileSpec(stFileSpec);
        
    CombFilterIf::create(pCombFilter, BlockSize);

    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
    hOutputFile.open(sOutputFilePath.c_str(), std::ios::out);
    if (!hOutputFile.is_open())
    {
        cout << "Text file open error!";
        return -1;
    }

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    ppfAudioData = new float*[stFileSpec.Num_chans];
    for (int i = 0; i < stFileSpec.Num_chans; i++)
        ppfAudioData[i] = new float[kBlockSize];

    time = clock();
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output file
    while (!phAudioFile->isEof())
    {
        long long NumFrames = kBlockSize;
        phAudioFile->readData(ppfAudioData, NumFrames);

        cout << "\r" << "reading and writing";

        for (int i = 0; i < NumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.Num_chans; c++)
            {
                hOutputFile << ppfAudioData[c][i] << "\t";
            }
            hOutputFile << endl;
        }
    }

    cout << "\nreading/writing done in: \t" << (clock() - time)*1.F / CLOCKS_PER_SEC << " seconds." << endl;

float *sinwav(float freq, float amp, float len, int fs){

    float pi = 3.14;

    int lenSamp = ceil(len * fs);
    float* Sine = new float[lenSamp];


    for(int i = 0; i<lengthInSamples; i++){
        Sine[i] = amp* sin((2.f*pi*freq)/(fs) *i);
    }

    return Sine;
}  
        
 int Zero_Input() {
        CombFilter *pFilter;
        float FIR_Coeff = 1.0;
        float IIR_Coeff = 0.4;
        int SampleDelay = 10;
        int Num_chans = 1;
        int BlockSize = 1024;
        int NumBlocks = 30; 

        //Allocate memory
        float **ppfAudioData = new float *[Num_chans];
        for (int n = 0; n< Num_chans; n++) {
            ppfAudioData[n] = new float[BlockSize];
            for (int m = 0; m < BlockSize; m++) {
                ppfAudioData[n][m] = 0; //Initialize 
            }
        }
    
        pFilter = new CombFilter(FIR_Coeff, IIR_Coeff, SampleDelay, Num_chans);

        while (NumBlocks > 0) {

            //Get filtered data
            ppfAudioData = pFilter->combFilterBlock(ppfAudioData, BlockSize, Num_chans);

            for (int n = 0; n < Num_chans; n++) {
                for (int m = 0; m < iBlockSize; m++) {

                    
                    if (abs(ppfAudioData[n][m]) > 0) {
                        cout<<"\nZero Input Test failed\n";
                        return -1;
                    }
                }
            }
            NumBlocks--;
        }

    
        //Free memory
        delete pFilter;
        pFilter = 0;
        for (int n=0; n<Num_chans; n++) {
            delete [] ppfAudioData[n];
        }
        delete ppfAudioData;
    
    return 0;
}
        
int FIR_mag_test() {
    
    CombFilter *pComb;
    float FIR_Coeff = 1.0;
    float IIR_Coeff = 0.0;
    int Num_chans = 1;
    int BlockSize = 500;
   
    
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    CAudioFileIf::destroy(phAudioFile);
    hOutputFile.close();

    for (int i = 0; i < stFileSpec.Num_chans; i++)
        delete[] ppfAudioData[i];
    delete[] ppfAudioData;
    ppfAudioData = 0;

    return 0;

}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2020 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}


