//
// Created by peter on 5/02/17.
//
#include "PointList.h"

#include <fstream>


using namespace std;
using namespace emu::utility;

//int paint(emu::utility::PointList hl, char *imageName, char *imageExt);

void testColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                  double *rgbaOut);


int main(int nParam, char **param) {
    using namespace emu::utility;

    ifstream ifstream1;
    // char * imageFileName, *imageExt;
    double bg[] = {1,1,1, 1};
    double mmin[] = {0, .9, .9, 0.5};
    double mmax[] = {0, .3, .2, 1};

    if (nParam >1) {
        try {
            string symFile(param[1]);
            cout << "File is " << symFile << endl;
            ifstream1.open(symFile.c_str(), std::ios::in);
            if (!ifstream1.is_open()) {
                cout<< "Could not open " << symFile <<endl;
                throw;
            }

        } catch (...) {
            cout << "Error loading file." << endl;
            return 1;
        }
    } else {
        cout << "Please supply file name, image file name and extension." << endl;
        return 1;
    }

    if(nParam == 14){
        try {
            bg[0] = atof(param[2]);
            bg[1] = atof(param[3]);
            bg[2] = atof(param[4]);
            bg[3] = atof(param[5]);

            mmin[0] = atof(param[6]);
            mmin[1] = atof(param[7]);
            mmin[2] = atof(param[8]);
            mmax[3] = atof(param[9]);

            mmax[0] = atof(param[10]);
            mmax[1] = atof(param[11]);
            mmax[2] = atof(param[12]);
            mmax[3] = atof(param[13]);

        }catch (...)
        {cout<< "Could not set colour values using defaults";}

    }
     emu::utility::PointList pl;
   // cout << pl.freqTables.size() << "ft size after ctor" <<endl;
    ifstream1 >> pl;
    ifstream1.close();

    unsigned long numTables = pl.freqTables.size();
    cout<< "number of frequency tables is " << numTables <<endl;
    PointList::ScaleDataConstIter ii = pl.freqTables.begin();


    while(ii != pl.freqTables.end()) {
        int sz = ii->first;
        long maxhits = pl.freqTables[sz].maxHits;
        long minhits = pl.freqTables[sz].findMin();
        cout << "maxHits for " << sz << " is " << maxhits << endl;
        cout << "minHits for " << sz << " is " << minhits << endl;
        //  PaintIcon paintIcon(sz,sz,bg,mmin,mmax,&hl);
       // emu::symicon::PaintIcon paintIcon(sz, sz, bg, mmin, mmax, &pl, &testColourFn);
       // paintIcon.setUseAlpha(true);
       // paintIcon.paint();
        ii++;
    }
     return 0;
};

void testColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd, double *rgbaOut) {
    long maxhits = fd.maxHits;
    // cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
    long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;

    //  cout << "maxhits " <<maxhits <<endl;
    double opacity = ((double )hits/(double)maxhits);
    //   cout <<"opacity " << opacity <<endl;std::max(
//opacity=0.3*opacity;
    //bound opacity between 0 and 1.
    //opacity = (opacity <= .5)?0.5:opacity;
    // opacity = (opacity >1)?1:opacity;
    double span1= maxRGBA[0] - minRGBA[0];
    double span2= maxRGBA[1] - minRGBA[1];
    double span3= maxRGBA[2] - minRGBA[2];

    rgbaOut[0]= minRGBA[0] +span1*opacity;
    rgbaOut[1]= minRGBA[1] +span2*opacity;
    rgbaOut[2]= minRGBA[2] +span3*opacity;
    rgbaOut[3]=opacity;
   // rgbaOut[3] = 1.0;
}
