//
// Created by peter on 30/06/17.
//
#include <ctime>
#include <fstream>
#include <sstream>
#include "SymIconApp.h"
//#include "image/PaintIcon.h"   //JNI
#include "GeneratorException.h"

using namespace emu::utility;

SymIconApp::SymIconApp(long iterations, double initX, double initY, QuiltIcon::QuiltType type, string fnBase,
                       int sz, double *iconParams, int numIconParams, int degSym, double *bgColour, double *minColour,
                       double *maxColour, ColourIcon::ColourFn colourFn)
        : iterations(iterations), initPoint(Point2D(initX, initY)),
          type(type), fnBase(fnBase), sz(sz), iconParams(iconParams),
          numIconParams(numIconParams),degSym(degSym), hl(PointList()), colourArray(),
          colourIcon(ColourIcon( sz, sz, bgColour, minColour, maxColour, &hl, colourFn, colourArray)) {

    if (numIconParams > 5) {
        lambdaVal = iconParams[0];
        alphaVal = iconParams[1];
        betaVal = iconParams[2];
        gammaVal = iconParams[3];
        omegaVal = iconParams[4];
        maVal = iconParams[5];
    }

    switch (type) {
        case QuiltIcon::QuiltType::SQUARE: hl.notTiled = true;
            maVal = floor(maVal*10);     // tiled patterns have integral values... or sixth root of 1.
            break;  //notTiled used to add buffer to scaling for non-repeating patterns.
        case QuiltIcon::QuiltType::SQUARE_ICON: hl.notTiled = true;
           // maVal = floor(maVal*10);
            break;
        case QuiltIcon::QuiltType::FRACTAL: hl.notTiled = true; break;
        case QuiltIcon::QuiltType::HEX: hl.notTiled = false;
            maVal = floor(maVal*10);

    }

    qi = new QuiltIcon(lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal, degSym, type);
    gg = new Generator(qi, iterations, &hl);

    hl.addTable(sz); //add a fine scale
    hl.addPoints();


}

void SymIconApp::setIterations(long iter){
    iterations = iter;
    gg->iters = iter;
}

void SymIconApp::runGenerator() {
    try {
       lastPoint = gg->go(initPoint);
        hl.addPoints();
    } catch (std::exception &xx) {
        cout << "Error: " << xx.what() << endl;
        errorMsg.append("Error.").append(xx.what());
        error = true;
        maxhits = 0;
        return;
    }catch(GeneratorException &xx) {
        errorMsg.append("Error.").append(xx.message);
       // error = true;
      //  maxhits = 0;
        cout<< errorMsg <<endl;
      //  return;   // see what we got.
    }
    catch (...) {
        cout << "error some other exception" << endl;
        errorMsg.append("Error. runGenerator: error some other exception occured.");
        error = true;
        maxhits = 0;
        return;
    }

    maxhits = hl.freqTables[sz].maxHits;
    cout << "maxHits for " << sz << " is " << maxhits << endl;
    fdiff = maxhits > 1 ? maxhits - 1 : 1; //maxx -minn;
}

int SymIconApp::createPNG(unsigned char ** pngBuf, int *len, string fname){

   // unsigned char* rgbaArray = nullptr;
    int nperiod = (qi->quiltType == QuiltIcon::QuiltType::HEX)?2:1;
    colourIcon.colourIn(sz, true, pngBuf, nperiod, 0);
    if (pngBuf == nullptr){
        error = true;
        errorMsg = "colourIn returned empty buffer, no useful data.";
        *len = 0;
        return  0;
    }
    cout<< "createPNG pngBuf first and last pixel: " << endl;
    cout << (*pngBuf)[0] <<","<< (*pngBuf)[1] <<","<<(*pngBuf)[2] <<","<< (*pngBuf)[3] <<","<<endl;
    cout << (*pngBuf)[(sz*sz-1)*4 +0] <<","<< (*pngBuf)[(sz*sz-1)*4 +1] <<","<<(*pngBuf)[(sz*sz-1)*4 +2] <<","<< (*pngBuf)[(sz*sz-1)*4 +3] <<","<<endl;
//  PaintIcon::savePNG(fname, sz,sz,rgbaArray);   //NOT for JNI version!

  /*  PaintIcon paintIcon;
    int res = paintIcon.paintPNG(colourIcon, fname, true);
    if (res == 0) {
        cout << "save png image failed." << endl;
    }

    paintIcon.paintPNGtoBuffer(colourIcon, true, len,false, pngBuf);
    if (*pngBuf == nullptr) {
        cout << "save png buffer failed." << endl;
        */

/********************************************
    res = PaintIcon::paintHDR(app.colourIcon, "symi_" +ddate +".hdr",false);
    if(res == 0) {
        cout <<"save hdr image failed." << endl;
    }
   ***************************************************************/
  //  }

  *len = sz*sz*4;
    return  *len;
}
/*
int SymIconApp::createPngBuffer(unsigned char ** pngBuf, int *len, bool switchRGBAtoARGB){
    PaintIcon paintIcon;
     paintIcon.paintPNGtoBuffer(colourIcon, true, len,  switchRGBAtoARGB, pngBuf);
    if (*pngBuf == nullptr) {
        cout << "save png buffer failed." << endl;
*/
/********************************************
    res = PaintIcon::paintHDR(app.colourIcon, "symi_" +ddate +".hdr",false);
    if(res == 0) {
        cout <<"save hdr image failed." << endl;
    }
   ***************************************************************/
 /*   }
    return  *len;
}
  */
/*
int SymIconApp::createByteBuffer(unsigned char **buf, int *len, bool switchRGBAtoARGB) {
    PaintIcon paintIcon;
     paintIcon.getCharArray(colourIcon, true,   switchRGBAtoARGB);
    if (paintIcon.charBuffer == nullptr) {
        cout << "save char buffer failed." << endl;
    }
    *buf = paintIcon.charBuffer;
    *len = sz*sz*4; //with alpha

    return  *len;
}
 */

void SymIconApp::save(ostringstream& outy) {
//colourIcon.setUseAlpha(false);
    if(error){
        outy << errorMsg;
    }
    else {
      //  unsigned  char *buf = nullptr;
      //  int nperiod = (type == QuiltIcon::QuiltType::HEX)? 2:1;

      //  colourIcon.colourIn(sz, false, &buf,nperiod);

      //  std::cout << "After colourIn complete. " << colourArray.size() << '\n';


        // std::time_t result = std::time(nullptr);
        // const std::string ddate = to_string(result).data();

        // string dname = fnBase + ddate + ".sym";
        //std::ostringstream outy(dname, std::ios_base::out);
        outy << *this ;
      //  free(buf);
    }
    outy.flush();
  //  outy.close();

   // cout << hl.rawSize() << " " << maxhits << endl;
   // cout << "Done!" << endl;
}

SymIconApp::~SymIconApp() {
    delete qi;
    delete gg;
  }

void SymIconApp::setColour(double *bgClr, double *minClr, double *maxClr) {
    colourIcon.setColour(bgClr,minClr,maxClr);
}

void SymIconApp::setInitPoint(Point2D point2D) {
    initPoint = std::move(point2D);
}

/*
emu::utility::SymIconApp SymIconApp::sizeSlice(const emu::utility::SymIconApp &symIconApp, const int sz) {
    SymIconApp appy;

    appy.sz = sz;
    appy.colourIcon.xSz = appy.colourIcon.ySz = sz;

     appy.lambdaVal =  symIconApp.lambdaVal;
     appy.alphaVal =  symIconApp.alphaVal;
     appy.betaVal = symIconApp.betaVal;
     appy.gammaVal =  symIconApp.gammaVal;
     appy.omegaVal =  symIconApp.omegaVal;
     appy. maVal =  symIconApp.maVal;
     appy.degSym = symIconApp.degSym;


     if(!symIconApp.hl.freqTables.empty() && !symIconApp.hl.freqTables.at(sz).frequencyList->empty()) {

         appy.hl.freqTables.emplace(sz,symIconApp.hl.freqTables.at(sz).frequencyList );
         appy.hl.rawTotal = symIconApp.hl.rawTotal;

     }
    return appy;
}
*/
std::ostream& operator<<(std::ostream &ostream1, const emu::utility::SymIconApp& symIconApp) {
    ostream1 << symIconApp.sz<< " "
    << symIconApp.lambdaVal <<" "
    << symIconApp.alphaVal << " "
    << symIconApp.betaVal << " "
    << symIconApp.gammaVal << " "
            << symIconApp.omegaVal << " "
            << symIconApp.maVal << " "
            << symIconApp.degSym << " "
            << *(symIconApp.qi) <<" " << symIconApp.hl <<" "
            << symIconApp.lastPoint.val[0] <<" "  << symIconApp.lastPoint.val[1] << " " ;


    //<< symIconApp.colourIcon.colourArray <<" ";
    return ostream1;
}
std::istream& operator>>(std::istream &input, emu::utility::SymIconApp& symIconApp){
  //  QuiltIcon quiltIconIn;
 //   PointList pointListIn;
    input >> symIconApp.sz;
    input >> symIconApp.lambdaVal
     >> symIconApp.alphaVal
                         >> symIconApp.betaVal
                         >> symIconApp.gammaVal
                         >> symIconApp.omegaVal
                         >> symIconApp.maVal
                         >> symIconApp.degSym;
    input >> *(symIconApp.qi); symIconApp.type = symIconApp.qi->quiltType;   //Data should only live in one place!!
    input >>  symIconApp.hl ;
    double x, y;
    input >> x >> y;
    symIconApp.lastPoint = Point2D(x,y);

    symIconApp.colourIcon.xSz = symIconApp.sz;
    symIconApp.colourIcon.ySz = symIconApp.sz;

 //   symIconApp.hl.addTable(symIconApp.sz);
 //   symIconApp.hl.addPoints(); //time consuming.

    return input;
}
