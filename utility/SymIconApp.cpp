//
// Created by peter on 30/06/17.
//
#include <ctime>
#include <fstream>
#include <sstream>
#include "SymIconApp.h"

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

    qi = new QuiltIcon(lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal, degSym, type);
    gg = new Generator(qi, iterations, &hl);

    hl.addTable(sz); //add a fine scale
    hl.addPoints();


}

void SymIconApp::runGenerator() {
    try {
        gg->go(initPoint);
        hl.addPoints();
    } catch (std::exception &xx) {
        cout << "Error: " << xx.what() << endl;

    } catch (...) {
        cout << "error some other exception" << endl;
    }

    maxhits = hl.freqTables[sz].maxHits;
    cout << "maxHits for " << sz << " is " << maxhits << endl;
    fdiff = maxhits > 1 ? maxhits - 1 : 1; //maxx -minn;
}

void SymIconApp::save(ostringstream& outy) {
//colourIcon.setUseAlpha(false);
    colourIcon.colourIn();

    std::cout << "After colourIn complete. " << colourArray.size()<< '\n';


   // std::time_t result = std::time(nullptr);
   // const std::string ddate = to_string(result).data();

   // string dname = fnBase + ddate + ".sym";
    //std::ostringstream outy(dname, std::ios_base::out);
    outy << hl;
    outy.flush();
  //  outy.close();

   // cout << hl.rawSize() << " " << maxhits << endl;
   // cout << "Done!" << endl;
}

SymIconApp::~SymIconApp() {
    delete qi;
    delete gg;
}
