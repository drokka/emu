//
// Created by peter on 2/04/17.
//

#include "ColourIcon.h"
#include <fstream>


emu::utility::ColourIcon::ColourIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList,
          ColourFn colourFn , RgbaList2D &clrArray) : xSz(xSz), ySz(ySz), bgRGBA(bgRGBA),
                                                              minRGBA(minRGBA), maxRGBA(maxRGBA),
                                                              pointList(pointList), colourFn(colourFn), colourArray(clrArray) {
}

emu::utility::ColourIcon::ColourIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA,
                                   double *maxRGBA, PointList *pointList, RgbaList2D &clrArray)
        : xSz(xSz), ySz(ySz), bgRGBA(bgRGBA), minRGBA(minRGBA), maxRGBA(maxRGBA), pointList(pointList),
          colourFn(emu::utility::simpleColourFn), colourArray(clrArray) {

}
void emu::utility::ColourIcon::colourIn() {

    FrequencyData &fd = pointList->freqTables[xSz];
    cout << "save max and range: " << fd.getMinX() << " " << fd.getMaxX() << " " << fd.getMinY() << " " << fd.getMaxY()
         << " "
         << fd.rangeX() << " " << fd.rangeY() << endl;
    double rescaleX = 1.0;
    double rescaleY = 1.0;
    int minX = fd.minX;
    int minY = fd.minY;
    if (fd.rangeX() > xSz) {
        rescaleX = (double) xSz / (double) fd.rangeX();
    }
    if (fd.rangeY() > ySz) { rescaleY = (double) ySz / (double) fd.rangeY(); }

    emu::utility::FrequencyList2DConstIter iter = pointList->freqTables[xSz].frequencyList->begin();

    while(iter != pointList->freqTables[xSz].frequencyList->end()){
        int x = (int) (rescaleX * (iter->first.val[0] - minX)); //(points+i)->x;
        int y = (int) (rescaleY * (iter->first.val[1] - minY)); //((points+i)->y);
        long hits = iter->second;
        //   cout << "looking for " << x <<" "<< y <<" " << hits <<endl;
        /*****
    PointFrequency::const_iterator pp = pointList->hitPointList.find(*(points+i));
    if(pp!= pointList->hitPointList.cend())
    {
         hits = pp->second;
  //       cout<< "found!! " <<hits <<endl;
    }
         ******************/
        double * rgba =(double*)(calloc(4, sizeof(double)));
        FrequencyData fd = pointList->freqTables[xSz];
        colourFn(minRGBA, maxRGBA, hits, fd, rgba);
       // cout << "colourFn gave rgba: "  << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3] <<endl;
        colourPoint( x, y, rgba);
        iter++;
    }
}

void emu::utility::ColourIcon::colourPoint(int x, int y, double *rgba)  {
    colourArray.emplace(IntegerPoint2D(x,y), rgba);
}

ColourIcon::~ColourIcon() {

    RgbaList2DConstIter iter = colourArray.begin();
    while(iter != colourArray.end()){
        free(iter->second);
        iter++;
    }
    colourArray.clear();

}

void emu::utility::simpleColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                                                    double *rgbaOut) {
    long maxhits = fd.maxHits;
    // cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
    long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;

    //  cout << "maxhits " <<maxhits <<endl;
    double opacity = (double)(hits - 1)/fdiff;
    //   cout <<"opacity " << opacity <<endl;std::max(
//opacity=0.3*opacity;
    //bound opacity between 0 and 1.
    opacity = (opacity <= 0)?0.05:opacity;
    opacity = (opacity >1)?1:opacity;
 rgbaOut[0]= 0.5 +0.5*opacity;
    rgbaOut[1]=  .9*opacity;
    rgbaOut[2]= 0.3 +0.7*opacity;
    rgbaOut[3]=opacity;
}

