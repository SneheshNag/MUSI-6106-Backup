
include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 // file paths
                            sOutputFilePath;

    static const int        kBlockSize = 1024;

    clock_t                 time = 0;
    float FIR_Coeff = 0.0;
    float IIR_Coeff = 0.0;
    float Delay = 0.0;
    int BlockSize = 2048; //default blockSize
    bool bOutputResultToTextFile = false; //default
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
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.Num_channels; i++)
        ppfAudioData[i] = new float[kBlockSize];

    time = clock();
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output file
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile->readData(ppfAudioData, iNumFrames);

        cout << "\r" << "reading and writing";

        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioData[c][i] << "\t";
            }
            hOutputFile << endl;
        }
    }

    cout << "\nreading/writing done in: \t" << (clock() - time)*1.F / CLOCKS_PER_SEC << " seconds." << endl;

        
        
    int testZeroInput() {
        CombFilter *pFilter;
        float FIR_Coeff = 1.0;
        float IIR_Coeff = 0.5;
        int SampleDelay = 10;
        int Num_chans = 1;
        int BlockSize = 1024;
        int NumBlocks = 50; //Length of sample is 50 blocks

        //Allocate memory
        float **ppfAudioData = new float *[Num_chans];
        for (int n=0; n<Num_chans; n++) {
            ppfAudioData[n] = new float[BlockSize];
            for (int m=0; m<BlockSize; m++) {
                ppfAudioData[n][m] = 0; //Initialize all samples to zero
            }
        }
    
        pFilter = new CombFilter(FIR_Coeff, IIR_Coeff, SampleDelay, Num_chans);

        while (NumBlocks > 0) {

            //Get filtered data
            ppfAudioData = pFilter->combFilterBlock(ppfAudioData, BlockSize, Num_chans);

            for (int n=0; n<iNumChannels; n++) {
                for (int m=0; m<iBlockSize; m++) {

                    //Check if all the values are 0
                    if (abs(ppfAudioData[n][m]) > 0.001) {
                        cout<<"\nZero Input Test: failed!\n";
                        return -1;
                    }
                }
            }
            NumBlocks--;
        }

    cout<<"\nZero Input Test: Success!\n";
    
        //Free memory
        delete pFilter;
        pFilter = 0;
        for (int n=0; n<Num_chans; n++) {
            delete [] ppfAudioData[n];
        }
        delete ppfAudioData;
    
    return 0;
}
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


