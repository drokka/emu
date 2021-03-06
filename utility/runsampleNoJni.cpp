//#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include <ctime>
#include <fstream>
#include <assert.h>
#include "SymIconApp.h"
#include "ColourIcon.h"
#include "image/PaintIcon.h"
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

int runsample(int nparam, char** param, ostringstream &outData, unsigned char **pngBuf, int *len) {

    long iterations = 1000000;
    if(nparam >1){
        try {
            iterations = atol(param[1]);
        }catch (...){//do nothing
        }
    }

    //long res = callSym(iterations);
    //cout << "got max hits:" << res << endl;

    //testColourIcon();

    int sz = 999; /** use odd sz for even number either side of centre, otherwise last row and column not used. */
cout << "runsample sz= " << sz <<endl;
    QuiltIcon::QuiltType quiltType = QuiltIcon::QuiltType::SQUARE;
    if (nparam >= 3) {
        if ('H' == param[2][0]) { quiltType = QuiltIcon::QuiltType::HEX; }
        else if ('F' == param[2][0]) { quiltType = QuiltIcon::QuiltType::FRACTAL; }
    }
    if(nparam >=4)
    {
        sz = atoi(param[3]); /* WIDTH in pixels is passed in, but assuming height the same. */
    }
    double lambdaVal = 0.6;
    double alphaVal = 0.2;
    double betaVal = 0.3;
    double gammaVal = 0.4;
    double omegaVal = 0.2;
    double maVal = 2.0;
    if (nparam == 11) {
        try {
            lambdaVal = strtod(param[5], nullptr); /* HEIGHT is passed in but skipped/ignored. */
            alphaVal = strtod(param[6], nullptr);
            betaVal = strtod(param[7], nullptr);
            gammaVal = strtod(param[8], nullptr);
            omegaVal = strtod(param[9], nullptr);
            maVal = strtod(param[10], nullptr);
        } catch (...) {
            cout << "Error reading QuiltIcon parameters." << endl;
            //continue using default values
        }
    }
    /**
    cout << "got parameters " << endl;
    cout << "lambdaVal " << lambdaVal << endl;
    cout << "alphaVal " << alphaVal << endl;
    cout << "betaVal " << betaVal << endl;
    cout << "gammaVal " << gammaVal << endl;
    cout << "omegaVal " << omegaVal << endl;
    cout << "maVal " << maVal << endl;
     **************/


    double initX = 0.307;
    double initY = 0.079;
    std::string fnBase = "img_a_";

    double iconParams[] = {lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal};
    int numIconParams = 6;
    double bg[] ={0,0.2,.15,.5};
    double min[]= {0.0,.5,.3,.5};
    double max[] = {.3,.99,.99,1};

    ColourIcon::ColourFn colourFn = emu::utility::simpleColourFn;

    SymIconApp app(iterations, initX, initY, quiltType, fnBase, sz, iconParams, numIconParams, bg, min, max, colourFn);
    app.runGenerator();
    cout << "After runGenerator call max hits: " << app.maxhits << endl;

    app.save(outData);
     std::time_t result = std::time(nullptr);
     const std::string ddate = to_string(result).data();
     PaintIcon paintIcon;
    int res = paintIcon.paintPNG(app.colourIcon, "symi_" +ddate +".png",false);
    if(res == 0) {
        cout <<"save png image failed." << endl;
    }

    *pngBuf = paintIcon.paintPNGtoBuffer(app.colourIcon, false, len);
    if(*pngBuf == nullptr){
        cout <<"save png buffer failed." << endl;
    }
/********************************************
    res = PaintIcon::paintHDR(app.colourIcon, "symi_" +ddate +".hdr",false);
    if(res == 0) {
        cout <<"save hdr image failed." << endl;
    }
   ***************************************************************/
   cout<< "max hits is " << app.maxhits <<endl;
    return app.maxhits;

    }

