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

    ScaleDataIter i=freqTables.begin();
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
    rl[rawIndex] =pt;
    rawIndex++;
    if(rawIndex == BUFFER_SIZE){
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
    // cout<< freqTables[COARSE]->frequencyList->size() <<endl;

    for(int p=0; p<rawIndex;p++){
        i->second.addIntegerPoint( rl[p]);
    }
    i->second.findMin();
}


std::ostream& operator<<(std::ostream &ostream1, const emu::utility::PointList& pl) {
    using namespace std;
    using namespace emu::utility;

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
    ostream1.flush();
    return ostream1;
}

std::istream& operator>>(std::istream &input, emu::utility::PointList& pl) {
    using emu::utility::PointList;
    using namespace std;
    long ftSize;
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
