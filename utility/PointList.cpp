//
// Created by peter on 9/04/17.
//

#include "PointList.h"


emu::utility::PointList::PointList(const int COARSE, const int MEDIUM, const int FINE,  long rawTotal)
        : COARSE(COARSE),  MEDIUM(MEDIUM),  FINE(FINE),
          rawIndex(0), rawTotal(rawTotal),freqTables(ScaleData()) {
    addTable(COARSE);
}


emu::utility::PointList::PointList(): rawIndex(0), rawTotal(0),freqTables(ScaleData()){
    addTable(COARSE);
}

emu::utility::PointList::PointList(const PointList& pl){
    this->freqTables = pl.freqTables;
}

void emu::utility::PointList::addPoints() {
  //  cout<< "addPoints   range fixed " << rawMinX <<", " << rawMinY << "     " << rawMaxX << ", " <<rawMaxY << endl;
    auto i=freqTables.begin();
    while( i != freqTables.end() ){
        convert(i->first);
        i++;
    }
    rawTotal = rawTotal + rawIndex;
    rawIndex = 0;
}

// add a raw point
void emu::utility::PointList::addPoint(Point2D &pt) {
    //rawList->insert(pt);
    if(!rangeFixed) {
        if (pt.val[0] < rawMinX) rawMinX = pt.val[0];
        if (pt.val[0] > rawMaxX) rawMaxX = pt.val[0];
        if (pt.val[1] < rawMinY) rawMinY = pt.val[1];
        if (pt.val[1] > rawMaxY) rawMaxY = pt.val[1];
    }

    rl[rawIndex] =pt;
    rawIndex++;
    if(rawIndex == BUFFER_SIZE){
        rangeFixed = true;

        addPoints();
        //  memset((void*)(rl),BUFFER_SIZE, sizeof(Point2D));
    }
    //addIntegerPoint(COARSE, pt);
}


void emu::utility::PointList::addTable(int scale) {
    PointList::ScaleDataConstIter i = this->freqTables.find(scale);
    if (i == this->freqTables.end()) {
        FrequencyData  fdata(scale) ;
        this->freqTables.insert(make_pair(scale, fdata));
    }
}

long emu::utility::PointList::rawSize() {
    return rawTotal + rawIndex;
}

long emu::utility::PointList::coarseSize() {
    if(freqTables.find(COARSE)!= freqTables.end()) {
        return freqTables[COARSE].frequencyList->size();
    }
    else return 0;
}

void emu::utility::PointList::convert(int scale) {
    // add integral points to the scale frequency list.
    addTable(scale);

    ScaleDataIter i = freqTables.find(scale);

    // SCALE the points hit  to 2x2 square. Fractal needs buffer as low frequency outliers happen on more iterations. OR Not.
    double expand = 1.0;
   // if(notTiled) expand = 1.2;
    double range = std::max(rawMaxX - rawMinX, rawMaxY - rawMinY)*expand;
   // cout << "convert, range is set to " << range << " , expand is " << expand << endl;
    double sq3Half = pow(3.0, 0.5)*0.5;
    for(int p=0; p<rawIndex;p++){
        double x =   (rl[p].val[0])*2.0/range; //convert to -1 to 1 square. Assuming centre (0,0) and size 2.
        double y =  (rl[p].val[1])*2.0/range;

        if(notTiled) {
            i->second.addIntegerPoint(Point2D(x, y));
        }
        else { //assume HEX and period      (int)(NumXPixel  * x / Info.degreeSym )          (NumYPixel - NumYPixel * y / Info.degreeSym)
            double nperiod = 1.0;
          //  double baseWidth =  1.0;     // 4.0/3.0; // 2/3 of the width, is the symmetric triangle base size pattern comes off.

            x = x/nperiod; y = y/nperiod;  //scale down by period.
            for (int k =  -(nperiod*0.5) - 1 ; k <  nperiod*0.5 + 2 ; k++) {
                for (int j = -2; j < nperiod + 1; j++) {
                    double xx = x + (k/nperiod);  //   k11, k12 (1,0)    k21,k22 (0.5, sq3/2) // (NumXPixel  * x / Info.degreeSym )

                    double yy =  y - (1.0/nperiod)*j*sq3Half;                          //2.0 - (2.0 / nperiod) * (y + j * sq3Half);
                    if (xx < -1 || xx >= 1 || yy < -1 || yy >= 1) {
                        //   cout << "outside of boundary x = " << x << " , y = " << y << endl;
                        continue; // ignore values outside of range - what happened to scaling?
                    }
                    i->second.addIntegerPoint(Point2D(xx, yy));
                }
            }
        }

    }

    //    for (int i = -HALFnperiod -1; i <  HALFnperiod +2 ; i++){
//	for (int j = 0 ; j < nperiod  +1  ; j++){
//		xx.xPix = XPixFuncQ(x + i * k11 + j * k21);          // (NumXPixel  * x / Info.degreeSym )

//			xx.yPix = YPixFuncQ(y + i * k12 + j * k22);

    i->second.findMin();
}
emu::utility::PointList::~PointList() {
    auto tableIter  = freqTables.begin();
    while(tableIter != freqTables.end()){
        tableIter->second.frequencyList->clear();

        tableIter++;
    }
    freqTables.clear();
}
std::ostream& operator<<(std::ostream &ostream1, const emu::utility::PointList& pl) {
    using namespace std;
    using namespace emu::utility;
    ostream1 << " rawTotal " << pl.rawTotal << " ";
    ostream1 << pl.rawMaxX << " " << pl.rawMaxY << " "<< pl.rawMinX << " "<< pl.rawMinY << " " ;
    ostream1 << pl.notTiled << " " ;
    ostream1 << pl.freqTables.size();
    ostream1<<" ";
    auto i = pl.freqTables.begin();
    while (i != pl.freqTables.end()) {
        //   ostream1 << i->second;
        ostream1 <<endl << "freqTable BEGIN "  <<endl;
     //   ostream1<< i->first;
        ::operator<<(ostream1, i->second);
        ostream1 << " ";
        i++;
    }
    ostream1 << endl;
    ostream1.flush();
    return ostream1;
}

std::istream& operator>>(std::istream &input, emu::utility::PointList& pl) {
    using emu::utility::PointList;
    using namespace std;
    long ftSize;
    string discard;
    input >> discard;
    input >> pl.rawTotal ;
    input >> pl.rawMaxX >> pl.rawMaxY >> pl.rawMinX >> pl.rawMinY >> pl.notTiled;
    input >> ftSize;

    for (int i = 0; i < ftSize; i++) {
        input.ignore(100, '\n');
        input.ignore(100, '\n');

        int scale;
        //  fdPtr.scale = scale;
        std::streampos p_orig = input.tellg();
        input >> scale;
        pl.addTable(scale);
        input.seekg(p_orig); /* Go back so scale can be read again by >>FrequencyData */
        //   input >> pl.freqTables.find(scale)->second;
        ::operator>>(input, pl.freqTables.find(scale)->second);
    }

    return input;
}
