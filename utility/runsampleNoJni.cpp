#ifndef EMU_UTILITIES_RUNSAMPLE
#define EMU_UTILITIES_RUNSAMPLE

//#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include <ctime>
#include <fstream>
#include <assert.h>
#include "SymIconApp.h"
#include "ColourIcon.h"
using namespace std;
using namespace emu::utility;

#include <string.h>

#include <sstream>

/* native method
 * to return a new VM String. See the corresponding Kotlin source
 * file located at:
 *
 *   app/src/main/java/com/example/kotlin/KotlinJni.kt
 */

static void testColourIcon(){
    int xSz =1000, ySz=1000; //Dimensions
    double bgRGBA[4] = {2.0,0.0,1.1,5.5};
    double minRGBA[4] = {0.0,0.1, 0.3, 0.5};
    double maxRGBA[4] = {1.1, 1.2,1.3,1.4};
    PointList pointList = PointList();
    bool useAlpha = false;
    RgbaList2D colourArray = RgbaList2D ();

    ColourIcon clrI = ColourIcon(xSz,ySz,bgRGBA,minRGBA,maxRGBA,&pointList,colourArray);
    cout<<"testColourIcon: " << colourArray.size()<<endl;
   // cout<< "size " << colourArray.size() <<endl;
   // assert(colourArray.capacity() == 1000);
    double *colour = (double*)calloc(4, sizeof(double));
           colour[0] = .1;
    colour[1] =1.2;
    colour[2] =3.3;
    colour[3] =99.9;
    clrI.colourPoint(10,999,colour);
    cout<<"point 10,999 value " << colourArray.find(IntegerPoint2D(10,999))->second[0] <<endl;

   // assert(colourArray.at(999).size()==1000);
//   free(colour);  the pointer is added to the colour array. Freed on its deletion.
}
int reColour(stringstream& symIn, unsigned char **pngBuf, string fname, double* bg, double* min, double * max){
    SymIconApp* appy = new SymIconApp();
    symIn >> *appy;

    appy->setColour(bg,min,max);
    unsigned  char *buf = nullptr;

    appy->colourIcon.colourIn(appy->sz, false, &buf, 1, 0);
    int bufLen = 0;
    appy->createPNG(pngBuf, &bufLen, fname);
    delete appy;
    free(buf);
    return bufLen;
}
int reColourBuffer(stringstream& symIn, int sz, unsigned char **pngBuf, double* bg, double* min, double * max){
    SymIconApp* appy = new SymIconApp();
    symIn >> *appy;
//    std::time_t result = std::time(nullptr);
  //   const std::string ddate = to_string(result).data();
    //ofstream stream( "recolourBuffer"+ddate + ".txt", ios::out);
//    if(!stream){ cout << "failed create file stream" << endl;}
  //  else{
    ///    stream.write(symIn,);
 //   }

    appy->sz = sz;
    appy->colourIcon.xSz = sz;
    appy->colourIcon.ySz = sz;
    appy->setColour(bg,min,max);
 //   unsigned  char *buf = nullptr;
    int nperiod = (appy->type == QuiltIcon::QuiltType::HEX)? 2:1;

    appy->colourIcon.colourIn(sz, false, pngBuf, nperiod, 0);
    if(pngBuf == nullptr){
        appy->error = true;
        return 0;
    }
 //   int bufLen = 0;
 //   appy->createPngBuffer(pngBuf, &bufLen);
    delete appy;
  //  free(buf);
    return sz*sz*4;
}

int moreIterSample(long iterations, istringstream &inData, ostringstream &outData,
                   unsigned char **pngBuf, double *bgclr_c, double *minclr_c, double *maxclr_c, int sz=0) {
    SymIconApp* appy = new SymIconApp();
    inData >> *appy;
    appy->setIterations(iterations);
    appy->setInitPoint(appy->lastPoint);
    if(sz >0){ appy->sz = sz;}
    appy->runGenerator();
    appy->save(outData);
    //double bgc[4] = {0.99,0.99,0.99,0.0};
    //double minc[4] = {0.0,0.0,0.0,0.0};
    //double maxgc[4] = {0.4,0.0,0.0,0.0};

    //free(rgbaByteArray);
    stringstream strlog ; strlog << "colour double arrays " << *bgclr_c << " " << *(bgclr_c+1) << " " << *(bgclr_c+2) << " " << *(bgclr_c+3) << " " << *(bgclr_c+4) << " , "
                                 << *minclr_c << " " << *(minclr_c+1) << " " << *(minclr_c+2) << " " << *(minclr_c+3)<< " " << *(minclr_c+4) << " , "
                                 << *maxclr_c << " " << *(maxclr_c+1) << " " << *(maxclr_c+2) << " " << *(maxclr_c+3)  << " " << *(maxclr_c+4) << endl;

    if(bgclr_c != nullptr) {
        appy->setColour(bgclr_c, minclr_c, maxclr_c);
    }
   // unsigned  char *buf = nullptr;
    int nperiod = (appy->type == QuiltIcon::QuiltType::HEX)? 2:1;
     sz = appy->sz;

    int resy = sz*sz*4;

    appy->colourIcon.colourIn(appy->sz, false, pngBuf, nperiod, 0);
    if(pngBuf == nullptr){
        resy = 0;
    }
 //   int bufLen = 0;
//    appy->createPngBuffer(pngBuf, &bufLen, true);

    delete appy;
  //  free(buf);
    return sz*sz*4;
}

int runsample(int nparam, char** param, ostringstream &outData, double** lastPoint,unsigned char **pngBuf, int *len,
              ostringstream &iconDefUsed, const char* clrFun, double clrFunExp) {

    long iterations = 10000;
    if(nparam >1){
        try {
            iterations = atol(param[1]);
        }catch (...){//do nothing
        }
    }

    cout<<"runsample nparam and parameters: " << nparam;
    for(int i=0; i<nparam;i++){ cout<< " " <<param[i];}
    cout<<endl;
    //long res = callSym(iterations);
    //cout << "got max hits:" << res << endl;

    //testColourIcon();

    int sz = 12; /** use odd sz for even number either side of centre, otherwise last row and column not used. */
int degSym = 4;
    QuiltIcon::QuiltType quiltType = QuiltIcon::QuiltType::SQUARE;
    if (nparam >= 3) {
        if ('H' == param[2][0]) { quiltType = QuiltIcon::QuiltType::HEX; }
        else if ('F' == param[2][0]) { quiltType = QuiltIcon::QuiltType::FRACTAL; }
        else if ('I' == param[2][0]) { quiltType = QuiltIcon::QuiltType::SQUARE_ICON;}
    }
    if(nparam >=5)
    {
        sz = atoi(param[3]); /* WIDTH in pixels is passed in, but assuming height the same. */
        degSym = atoi(param[5]);
    }
    cout << "runsample sz= " << sz <<endl;

    double lambdaVal = 0.6;
    double alphaVal = 0.2;
    double betaVal = 0.3;
    double gammaVal = 0.4;
    double omegaVal = 0.2;
    double maVal = 0.5;


    if (nparam >= 12) {
        try {
            lambdaVal = strtod(param[6], nullptr); // HEIGHT is passed in but skipped/ignored.
            alphaVal = strtod(param[7], nullptr);
            betaVal = strtod(param[8], nullptr);
            gammaVal = strtod(param[9], nullptr);
            omegaVal = strtod(param[10], nullptr);
            maVal = strtod(param[11], nullptr);
        } catch (...) {
            cout << "Error reading QuiltIcon parameters." << endl;
            //continue using default values
        }
    }
    iconDefUsed.clear();
    iconDefUsed << " lambdaVal = "+to_string(lambdaVal)
            << " alphaVal = "+to_string(alphaVal)
            << " betaVal = "+to_string(betaVal)
            << " gammaVal = "+to_string(gammaVal)
            << " omegaVal = "+to_string(omegaVal)
            << " maVal = "+to_string(maVal)
            << " degSym = "+to_string(degSym)
            << " quiltType = " << int(quiltType)
            << " width = " << sz
            << " iterations = " << iterations
            << endl;
/*******************************************
    if (nparam == 12) {
        try {
            lambdaVal = strtod(param[5], nullptr); // HEIGHT is passed in but skipped/ignored.
            alphaVal = strtod(param[6], nullptr);
            betaVal = strtod(param[7], nullptr);
            gammaVal = strtod(param[8], nullptr);
            omegaVal = strtod(param[9], nullptr);
            maVal = strtod(param[10], nullptr);
            degSym = atoi(param[11]);
        } catch (...) {
            cout << "Error reading QuiltIcon parameters." << endl;
            //continue using default values
        }
    }  */

    cout << "got parameters " << endl;
    cout << "lambdaVal " << lambdaVal << endl;
    cout << "alphaVal " << alphaVal << endl;
    cout << "betaVal " << betaVal << endl;
    cout << "gammaVal " << gammaVal << endl;
    cout << "omegaVal " << omegaVal << endl;
    cout << "maVal " << maVal << endl;



    double initX = 0.307;
    double initY = 0.079;
    if(*lastPoint != nullptr && (*lastPoint)[0] != 0.0) initX = (*lastPoint)[0];
    if(*lastPoint != nullptr && (*lastPoint)[1] != 0.0) initY = (*lastPoint)[1];

    std::string fnBase = "img_a_";

    double iconParams[] = {lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal};
    int numIconParams = 6;
    double bgClr[] ={0, 0.2, .15, 1.0};
    double minClr[]= {0.0,.5,.3,1.0};
    double maxClr[] = {.3,.99,.99,1.0};

    if(nparam == 24) { //colours provided
        bgClr[0] = strtod(param[12], nullptr);
        bgClr[1] = strtod(param[13], nullptr);
        bgClr[2] = strtod(param[14], nullptr);
        bgClr[3] = strtod(param[15], nullptr);

        minClr[0] = strtod(param[16], nullptr);
        minClr[1] = strtod(param[17], nullptr);
        minClr[2] = strtod(param[18], nullptr);
        minClr[3] = strtod(param[19], nullptr);
        maxClr[0] = strtod(param[20], nullptr);
        maxClr[1] = strtod(param[21], nullptr);
        maxClr[2] = strtod(param[22], nullptr);
        maxClr[3] = strtod(param[23], nullptr);
    }

    ColourIcon::ColourFn colourFn = emu::utility::simpleColourFn;
 // cout << "colour double arrays " << *bgClr << " " << *(bgClr+1) << " " << *(bgClr+2) << " " << *(bgClr+3) << " " << *(bgClr+4) << " , "
   //                             << *minClr << " " << *(minClr+1) << " " << *(minClr+2) << " " << *(minClr+3)<< " " << *(minClr+4) << " , "
     //                            << *maxClr << " " << *(maxClr+1) << " " << *(maxClr+2) << " " << *(maxClr+3)  << " " << *(maxClr+4) << endl;

    SymIconApp app(iterations, initX, initY, quiltType, fnBase, sz, iconParams, numIconParams, degSym, bgClr, minClr, maxClr, colourFn);
    app.runGenerator();
    cout << "After runGenerator call max hits: " << app.maxhits << endl;
    app.save(outData);
    *lastPoint =(double *) malloc(sizeof(double ) *2);
    (*lastPoint)[0] = app.lastPoint.val[0];
    (*lastPoint)[1] = app.lastPoint.val[1];
     //std::time_t result = std::time(nullptr);
    // const std::string ddate = to_string(result).data();
   // int res = PaintIcon::paintPNG(app.colourIcon, "symi_" +ddate +".png",false);
  //  if(res == 0) {
  //  unsigned  char *buf = nullptr;
    int nperiod = (app.type == QuiltIcon::QuiltType::HEX)? 2:1;
    app.colourIcon.colourIn(sz, false, pngBuf, nperiod, clrFunExp);
    if(pngBuf == nullptr){
        app.error = true;
    return 0;
}
 /*
    if(!app.error) {

        app.createPNG(pngBuf, len,"symi_" + ddate + ".png");
        cout << "runsample app.createPNG() call  buffer length returned is " << *len << endl;

        cout<< "runsample createPNG pngBuf first and last pixel: " << endl;
        cout << (*pngBuf)[0] <<","<< (*pngBuf)[1] <<","<<(*pngBuf)[2] <<","<< (*pngBuf)[3] <<","<<endl;
        cout << (*pngBuf)[(sz*sz-1)*4 +0] <<","<< (*pngBuf)[(sz*sz-1)*4 +1] <<","<<(*pngBuf)[(sz*sz-1)*4 +2] <<","<< (*pngBuf)[(sz*sz-1)*4 +3] <<","<<endl;

        /********************************************

        PaintIcon paintIcon;
        int res = paintIcon.paintPNG(app.colourIcon, "symi_" + ddate + ".png", false);
        if (res == 0) {
            cout << "save png image failed." << endl;
        }

        *pngBuf = paintIcon.paintPNGtoBuffer(app.colourIcon, false, len);
        if (*pngBuf == nullptr) {
            cout << "save png buffer failed." << endl;

    res = PaintIcon::paintHDR(app.colourIcon, "symi_" +ddate +".hdr",false);
    if(res == 0) {
        cout <<"save hdr image failed." << endl;
    }
   ***************************************************************/


cout<< "max hits is " << app.maxhits <<endl;
   int resy = app.maxhits;

    return resy;

    }

/*    extern "C"
 int runsamplewrapimp(int nparam, char** param, unsigned char **pngBuf, int *len) {

    ostringstream outdata("outy string");
    ostringstream defdata("defn string");
    int resy = runsample(nparam, param, len reinterpret_cast<ostringstream &>(outdata), pngBuf, len,
                         reinterpret_cast<ostringstream &>(defdata));

    return resy;
} */


#endif
