//
// Created by peter on 2/04/17.
//

#include "ColourIcon.h"
#include <fstream>


emu::utility::ColourIcon::ColourIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList,
          ColourFn colourFn , RgbaList2D &clrArray) : xSz(xSz), ySz(ySz), bgRGBA(bgRGBA),
                                                              minRGBA(minRGBA), maxRGBA(maxRGBA),
                                                              pointList(pointList), colourFn(colourFn), colourArray(clrArray) ,rgbaByteArray(nullptr){
}

emu::utility::ColourIcon::ColourIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA,
                                   double *maxRGBA, PointList *pointList, RgbaList2D &clrArray)
        : xSz(xSz), ySz(ySz), bgRGBA(bgRGBA), minRGBA(minRGBA), maxRGBA(maxRGBA), pointList(pointList),
          colourFn(emu::utility::simpleColourFn), colourArray(clrArray),rgbaByteArray(nullptr) {

}
void emu::utility::ColourIcon::colourIn(int sz , bool argb) {

    if(colourFn == nullptr){
        colourFn = emu::utility::simpleColourFn;
    }

    FrequencyData *fd = nullptr;
    int iconSize = xSz;
    // byte array background colour
    int byteArrayLen = iconSize*iconSize*4; //ASSUMING alpha
    int pixelLen = iconSize*iconSize;
    rgbaByteArray = static_cast<unsigned char *>(malloc(byteArrayLen));
    for(int k =0 ; k< pixelLen; k++){
        for(int j=0; j<4; j++){
            rgbaByteArray[4*k+j] = (unsigned char) (bgRGBA[j]*255.0);
        }
    }
    //----------------------------------------
    if( sz==0) {
        fd = &(pointList->freqTables[xSz]);
    }else if(pointList->freqTables.find(sz) != pointList->freqTables.end()) {
        fd = &(pointList->freqTables[sz]);
        iconSize = sz;
    }else{
        cout<<"error sz " <<sz <<"  xsz " << xSz <<endl;
        return;
    }
    cout << "save max and range: " << fd->getMinX() << " " << fd->getMaxX() << " " << fd->getMinY() << " " << fd->getMaxY()
         << " "
         << fd->rangeX() << " " << fd->rangeY() << endl;
    double rescaleX = 1.0;
    double rescaleY = 1.0;
    int minX = fd->minX;
    int minY = fd->minY;
    if (fd->rangeX() > iconSize) {
        rescaleX = (double) iconSize / (double) fd->rangeX();
    }
    if (fd->rangeY() > iconSize) { rescaleY = (double) iconSize / (double) fd->rangeY(); }

    emu::utility::FrequencyList2DConstIter iter = pointList->freqTables[iconSize].frequencyList->begin();
int frequLen = pointList->freqTables[iconSize].frequencyList->size();
cout << "frequ Len " << frequLen <<endl;

        for (;iter != pointList->freqTables[iconSize].frequencyList->end(); iter++) {
            int x = (int) (rescaleX * (iter->first.val[0] - minX)); //(points+i)->x;
            int y = (int) (rescaleY * (iter->first.val[1] - minY)); //((points+i)->y);
            long hits = iter->second;
            //   cout << "looking for " << x <<" "<< y <<" " << hits <<endl;
            if(x >= xSz || y >= ySz){
                continue;
            }
            /*****
        PointFrequency::const_iterator pp = pointList->hitPointList.find(*(points+i));
        if(pp!= pointList->hitPointList.cend())
        {
             hits = pp->second;
      //       cout<< "found!! " <<hits <<endl;
        }
             ******************/
            double *rgba = (double *) (calloc(4, sizeof(double)));
            colourFn(minRGBA, maxRGBA, hits, pointList->freqTables[iconSize], rgba);
            cout << "colourFn gave rgba: " << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3] << endl;

     //       if(argb){ //switch for Android bitmap ARGB format
       //         double clr[4] = {rgba[3], rgba[0], rgba[1], rgba[2]};
         //       colourPoint(x,y,clr);
           // }else {
                colourPoint(x, y, rgba);
                for(int i=0; i<4;i++){
                    rgbaByteArray[4*(y*iconSize +x) +i] = (unsigned char)(rgba[i]*255.0);
                }
           // }
          //  cout <<"colourPoint done" <<endl;
         // free(rgba);
        }
        cout<< "loop done" << endl;
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
    free(rgbaByteArray);
}

void ColourIcon::setColour(double *bgRGBAin, double *minRGBAin, double *maxRGBAin) {

    bgRGBA = bgRGBAin; minRGBA = minRGBAin; maxRGBA = maxRGBAin;
}

void ColourIcon::setColourFunction(ColourIcon::ColourFn func){
    colourFn = func;
}

void emu::utility::simpleColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                                                    double *rgbaOut) {
    long maxhits = fd.maxHits;
    // cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
    long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;

    //  cout << "maxhits " <<maxhits <<endl;
    double ratio = (double)(hits - 1)/fdiff;
    //   cout <<"opacity " << opacity <<endl;std::max(
//opacity=0.3*opacity;
    //bound opacity between 0 and 1.
  //  opacity = (opacity <= 0)?0.05:opacity;
  //  opacity = (opacity >1)?1:opacity;
  for(int i=0;i<4;i++){
      rgbaOut[i] = minRGBA[i] + ratio*(maxRGBA[i] - minRGBA[i]);
  }
   // rgbaOut[3] = 1.0;
}

