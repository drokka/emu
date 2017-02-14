//
// Created by peter on 22/11/15.
//

#ifndef FUNCTION_UTILITIES_POINTLIST_H
#define FUNCTION_UTILITIES_POINTLIST_H

#include <set>
#include <map>
#include <memory>
#include <ostream>
#include <istream>
#include <iostream>

#include "Point2D.h"
#include "IntegerPoint2D.h"

namespace emu {
    namespace utility {
using namespace std;
//TODO   measure of change = stat distribution change...?

        class PointList {

        public:
            //typedef std::multiset<Point2D, Point2D> PointList2D;
            //typedef std::multiset<Point2D, Point2D>::const_iterator PointList2DIter;


            // Map of integral points to number of occurrences. Ordered by the points.
            typedef std::map<IntegerPoint2D, long> FrequencyList2D;
            typedef std::map<IntegerPoint2D, long>::const_iterator FrequencyList2DConstIter;
            typedef std::map<IntegerPoint2D, long>::iterator FrequencyList2DIter;

            typedef struct {
                int scale;
                long maxHits;
                long minHits;
                std::shared_ptr<FrequencyList2D> frequencyListPtr;
            } FrequencyData;

            // map from scale value to corresponding data. For ease of access. Ordered by scale.
            typedef std::map<int, std::shared_ptr<FrequencyData> > ScaleData;
            typedef std::map<int, std::shared_ptr<FrequencyData> >::iterator ScaleDataIter;
            typedef std::map<int, std::shared_ptr<FrequencyData> >::const_iterator ScaleDataConstIter;

            //Scale values
            const int COARSE = 200;
            const int MEDIUM = 800;
            const int FINE = 1600;
            const static long BUFFER_SIZE = 100000;


            //shared_ptr<PointList2D> rawList;
            long rawIndex;
            Point2D rl[BUFFER_SIZE];
            ScaleData freqTables;


            PointList() : COARSE(200), MEDIUM(800), FINE(1600), rawIndex(0), rawTotal(0) {
                // rawList = shared_ptr<PointList2D>(new PointList2D());
                freqTables = ScaleData();
                //Add a coarse pixel image by default.
                freqTables.insert(make_pair(COARSE, shared_ptr<FrequencyData>(new FrequencyData())));
                freqTables[COARSE]->scale = COARSE;
                freqTables[COARSE]->maxHits = 1;
                freqTables[COARSE]->minHits = 1;
                freqTables[COARSE]->frequencyListPtr = shared_ptr<FrequencyList2D>(new FrequencyList2D());
            }

       //     PointList(int COARSE);

            void addPoints() {
                ScaleDataIter i=freqTables.begin();
                while( i != freqTables.end() ){
                    convert(i->first);
                    cout<<"convert for scale "<< i->first <<endl;
                    i++;
                }
                rawTotal = rawTotal + rawIndex;
                rawIndex = 0;
            }

// add a raw point
            void addPoint(Point2D &pt) {
                //rawList->insert(pt);
                rl[rawIndex] =pt;
                rawIndex++;
                if(rawIndex == BUFFER_SIZE){
                    addPoints();
                }
                //addIntegerPoint(COARSE, pt);
            }

            //Create an integral mapinsert
            int convert(int scale) {
                ScaleDataIter i = freqTables.find(scale);
                if (i == freqTables.end()) {
                    std::shared_ptr<FrequencyData> fdata = std::shared_ptr<FrequencyData>(new FrequencyData());
                    fdata->scale = scale;
                    fdata->maxHits = 1;
                    fdata->minHits = 1;
                    fdata->frequencyListPtr = shared_ptr<FrequencyList2D>(new FrequencyList2D());
                    freqTables.insert(make_pair(scale, fdata));
                }
                // add integral points to the scale frequency list.
                //       shared_ptr<FrequencyData> scaleFD = freqTables.find(scale)->second;

                //PointList2DIter p = rawList.get()->begin();
                //while (p != rawList.get()->end()) {
                for(int p=0; p<rawIndex;p++){
                    addIntegerPoint(scale, rl[p]);
                }
            }

            long rawSize() {
                return rawTotal + rawIndex;
            }

            long coarseSize() {
                if (freqTables.size() > 0) {
                    return freqTables[COARSE]->frequencyListPtr->size();
                }
            }

//            friend std::ostream &operator<<(std::ostream &, const PointList &);

 //           friend std::istream &operator>>(std::istream &input, PointList &pl);

        private:
            IntegerPoint2D addIntegerPoint(int scale, const Point2D &pt) {
                IntegerPoint2D ipp;
                ScaleDataIter i = freqTables.find(scale);
                if (i != freqTables.end()) {
                    std::shared_ptr<FrequencyList2D> fd = i->second->frequencyListPtr;
                    //   assert(i->second->scale == scale);
                    int m = scale;
                    int a = m * (pt.val[0]); //normally generated pt values between -1, 1.
                    int b = m * (pt.val[1]); // integral values between 0 and scale
                    ipp = IntegerPoint2D(a, b);
                    FrequencyList2DIter j = fd->find(ipp);
                    if (j == fd->end()) {
                        fd->insert(std::make_pair(ipp, 1));
                    } else {
                        j->second += 1; //increment count
                        i->second->maxHits = std::max(i->second->maxHits, j->second);
                        //TODO: handle minHits
                    }
                    //  cout<< fd->size() <<endl;
                }
                // cout<< freqTables[COARSE]->frequencyListPtr->size() <<endl;
                return ipp;
            }

            long rawTotal;
        };
    };
};

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::PointList& pl) {

                ostream1 << pl.freqTables.size();
                ostream1<<" ";
                emu::utility::PointList::ScaleDataConstIter i = pl.freqTables.begin();
                while (i != pl.freqTables.end()) {
                    ostream1 << i->first << " ";  /* scale */
                    ostream1 << i->second->maxHits<< " ";
                    ostream1 << i->second->minHits<< " ";
                    std::shared_ptr<emu::utility::PointList::FrequencyList2D> fd = i->second->frequencyListPtr;
                    ostream1 << fd->size();
                    ostream1 << " ";
                    emu::utility::PointList::FrequencyList2DIter j = fd->begin();
                    while (j != fd->end()) {
                        ostream1 << j->first.val[0] << " "<< j->first.val[1] << " "<< j->second<< " ";
                        j++;
                    }
                    ostream1 << " ";
                    ostream1.flush();
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
                long scale;
                input >> scale;
                pl.freqTables.insert(
                        make_pair(scale, std::shared_ptr<emu::utility::PointList::FrequencyData>(new emu::utility::PointList::FrequencyData())));
                std::shared_ptr<emu::utility::PointList::FrequencyData> fdPtr = pl.freqTables[scale];
                fdPtr->scale = scale;
                input >>  fdPtr->maxHits >> fdPtr->minHits;
                long freqDataSz;
                input >> freqDataSz;
                //cout<< "Reading data got scale, maxhits, minhits and data length: " <<fdPtr->scale <<" "<< fdPtr->maxHits <<" "<< fdPtr->minHits <<" "<< freqDataSz << std::endl;
               // cout<<endl;
                if(freqDataSz >0) {
                    fdPtr->frequencyListPtr =  std::shared_ptr<emu::utility::PointList::FrequencyList2D>(new emu::utility::PointList::FrequencyList2D());
                    for (long j = 0; j < freqDataSz; j++) {
                        long x, y;
                        long freq;
                        input >> x >> y >> freq;
                        fdPtr->frequencyListPtr->insert(std::make_pair(emu::utility::IntegerPoint2D(x, y), freq));
                    }
                }
            }
            return input;
        }

//PointList::PointList(int COARSE) : COARSE(COARSE) {}

#endif //FUNCTION_UTILITIES_POINTLIST_H
