//
// Created by peter on 2/04/17.
//

#include "ColourIcon.h"
#include "GeneratorException.h"
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
void emu::utility::ColourIcon::colourIn(int sz , bool argb, unsigned char **rgbaByteArray, int nperiod = 1) {

    if(colourFn == nullptr){
        colourFn = emu::utility::simpleColourFn;
    }

    FrequencyData *fd = nullptr;
    int iconSize = xSz;
    // byte array background colour
    int byteArrayLen = iconSize*iconSize*4; //ASSUMING alpha
    int pixelLen = iconSize*iconSize;

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

if(frequLen < 1) { // No interesting image
//    throw emu::utility::GeneratorException("ColourIn: frequencyList size too small.");  //Throwing through static C not good??
    return; // Use null rgbaByteArray to signal error
}

    *rgbaByteArray = static_cast<unsigned char *>(malloc(byteArrayLen));
    //  if(nperiod == 1) {  //Not HEX, for HEX want transparent background....
    for (int k = 0; k < pixelLen; k++) {
        for (int j = 0; j < 4; j++) {
            (*rgbaByteArray)[4 * k + j] = (unsigned char) (bgRGBA[j] * 255.0);
        }
    }
    // }

    double tan30 = 0.57735027;
    double sin60 = 0.8660254;
    double gradient = -sin60*2.0 , k1 = -gradient*sz/3, k2 = (7.0/8.0-gradient)*sz*2.0/3.0;
    cout << "gradient and consts " << gradient << ", " << k1 << ", " << k2 << endl;

    double rescale = min(rescaleX, rescaleY);
        for (;iter != pointList->freqTables[iconSize].frequencyList->end(); iter++) {
            int x = (int) (rescale * (iter->first.val[0] - minX)); //(points+i)->x;
            int y = (int) (rescale * (iter->first.val[1] - minY)); //((points+i)->y);
            long hits = iter->second;

            // rescaleX is 2/3 rescaleY is 1.
          //  cout << "rescale values are rescaleX " <<rescaleX << " rescaleY " << rescaleY << "ratio " << rescaleY/rescaleX << endl;
            //   cout << "looking for " << x <<" "<< y <<" " << hits <<endl;
         //   if(x >= xSz || y >= ySz){
        //        continue;
         //   }
            /*****
        PointFrequency::const_iterator pp = pointList->hitPointList.find(*(points+i));
        if(pp!= pointList->hitPointList.cend())
        {
             hits = pp->second;
      //       cout<< "found!! " <<hits <<endl;
        }
             ******************/
             auto szDD = (double) sz;
             double widthHEX = szDD * 2.0 / 3.0;
             double heightHex = sz*  0.578246393  - 4;       // 7.0/12.0 -6;   //Hack!!!!!!!11
            double sq3 =  pow(3, 0.5);
            auto *rgba = (double *) (calloc(4, sizeof(double)));
            colourFn(minRGBA, maxRGBA, hits, pointList->freqTables[iconSize], rgba);
          //  cout << "colourFn gave rgba: " << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3] << endl;

     //       if(argb){ //switch for Android bitmap ARGB format
       //         double clr[4] = {rgba[3], rgba[0], rgba[1], rgba[2]};
         //       colourPoint(x,y,clr);
           // }else {
          //  double bottomOffset = widthHEX*tan30/2; //bottom left corner x position
            double midX = sz/2.0; // middle of parallelogram
            double midY = sz*2/7; // trial and error!!!
             //  if(pow(x-midX,2) + pow(y-midY,2) > pow(sz/2,2)) continue; //exclude those extra triangles, nearly


            colourPoint(x, y, rgba);
                if(nperiod == 1) {
                    if(x < 0 || x >= sz || y < 0 || y >= ySz) continue;

                    for (int i = 0; i < 4; i++) {
                        (*rgbaByteArray)[4 * (y * iconSize + x) + i] = (unsigned char) (rgba[i] *255.0);
                    }
                }else {
                    // a hex quilt. just use nperiod as flag not doing the full tiling.
                        // Hmm generating a parallelogram containing the full hex shape but extended top left
                        // and bottom right corners beyond the hex border. Need to exclude these triangle regions
                        // before the diagonal hex stacking.
                    if(x*gradient + k1 > y || x*gradient + k2 < y) continue;

                    for(int i = -1; i<= 3 ; i++){
                        int xx = (x+ 0.75*widthHEX*i);
                        if(xx < 0 || xx >= sz) continue;
                        for(int j= -1; j <= 3 ; j++){

                            int yy = (y + heightHex*((-(i%2)*0.5) + j));
                            if(yy < 0 || yy >= ySz) continue;
                            for (int ii = 0; ii < 4; ii++) {   //pixel depth is 4 rgba
                                int index = int(4 * (yy * sz + xx) + ii);
                                if(index >= sz*sz*4 ) {cout << "index too big: " << index <<endl;
                                    continue;
                                }
                                (*rgbaByteArray)[index] = (unsigned char) (rgba[ii] *255.0);
                            }
                        }
                    }
                  }
  /*         for(int l=-3;l<3;l++) {
                for (int ll = -3; ll < 3; ll++) {
                    for (int ii = 0; ii < 4; ii++) {
                        (*rgbaByteArray)[4 * (int) ((10+ll) * iconSize + 10+l) + ii] = (unsigned char) (0);

                         (*rgbaByteArray)[4 * (int) ((midY+ll) * widthHEX + midX+l) + ii] = (unsigned char) (0);
                         cout <<"mid square index" << 4 * (int) ((midY+ll) * widthHEX + midX+l) + ii <<endl;
                    }
                }
            }*/
           // }
          //  cout <<"colourPoint done" <<endl;
          free(rgba);
        }
 /*   for(int l=-3;l<3;l++) {
        for (int ll = -3; ll < 3; ll++) {
            for (int ii = 0; ii < 4; ii++) {
                (*rgbaByteArray)[4 * (int) ((10+ll) * iconSize + 10+l) + ii] = (unsigned char) (0);

                int index = 4 *((sz*7/12 +ll) * sz + (sz*2/3)+l) + ii;
                (*rgbaByteArray)[index] = (unsigned char) (0);
                cout <<"mid square index " << index <<endl;

            }
        }
    } */

    cout<< "loop done" << endl;
}

void emu::utility::ColourIcon::colourPoint(int x, int y, double *rgba)  {
    colourArray.emplace(IntegerPoint2D(x,y), rgba);
}

ColourIcon::~ColourIcon() = default;

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

