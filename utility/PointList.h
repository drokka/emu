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
#include "FrequencyData.h"

namespace emu {
    namespace utility {
using namespace std;
//TODO   measure of change = stat distribution change...?

        class PointList {

        public:
            //typedef std::multiset<Point2D, Point2D> PointList2D;
            //typedef std::multiset<Point2D, Point2D>::const_iterator PointList2DIter;


            // Map of integral points to number of occurrences. Ordered by the points.

            // map from scale value to corresponding data. For ease of access. Ordered by scale.
            typedef std::map<int, FrequencyData > ScaleData;
            typedef std::map<int, FrequencyData>::iterator ScaleDataIter;
            typedef std::map<int, FrequencyData>::const_iterator ScaleDataConstIter;

            //Scale values
            const int COARSE = 200;
            const int MEDIUM = 800;
            const int FINE = 1600;
            const static long BUFFER_SIZE = 100000;


            //shared_ptr<PointList2D> rawList;
            ScaleData freqTables;

            PointList(const int COARSE, const int MEDIUM, const int FINE,  long rawTotal)
                    : COARSE(COARSE),
                      MEDIUM(MEDIUM),
                      FINE(FINE),
                      rawIndex(0), rawTotal(rawTotal) {
                
                //Add a coarse pixel image by default.
             //   freqTables.insert(make_pair(COARSE, shared_ptr<FrequencyData>(new FrequencyData())));
             //   freqTables[COARSE]->scale = COARSE;
             //   freqTables[COARSE]->maxHits = 1;
             //   freqTables[COARSE]->minHits = 1;
             //   freqTables[COARSE]->frequencyList = shared_ptr<FrequencyList2D>(new FrequencyList2D());
             //   addTable(COARSE);
              //  addTable(MEDIUM);
              //  addTable(FINE);  //Stored data only for the frequency tables. More accurate stored data requires adding a finer grained table.
            }


            PointList():rawIndex(0) { PointList(200, 800, 1600,  0);  }
            
            PointList(const PointList& pl){
                this->freqTables = pl.freqTables;

            }

            virtual ~PointList() {
             //   free(rl);
            }

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
            void convert(int scale) {
                addTable(scale);
                // add integral points to the scale frequency list.
                //       shared_ptr<FrequencyData> scaleFD = freqTables.find(scale)->second;

                //PointList2DIter p = rawList.get()->begin();
                //while (p != rawList.get()->end()) {
                for(int p=0; p<rawIndex;p++){
                    addIntegerPoint(scale, rl[p]);
                }
            }

            void addTable(int scale) {
                PointList::ScaleDataConstIter i = this->freqTables.find(scale);
                if (i == this->freqTables.end()) {
                    FrequencyData  fdata(scale) ;
                    //fdata.scale = scale;
                    fdata.maxHits = 1;
                    fdata.minHits = 1;
                    //fdata.frequencyList = new FrequencyList2D();
                    this->freqTables.insert(make_pair(scale, fdata));
                }
                cout<< "ft size: " <<this->freqTables.size() <<endl;
            }

            long rawSize() {
                return rawTotal + rawIndex;
            }

            long coarseSize() {

                    return freqTables[COARSE].frequencyList->size();
            }

//            friend std::ostream &operator<<(std::ostream &, const PointList &);

 //           friend std::istream &operator>>(std::istream &input, PointList &pl);

            long rawTotal=0;
        private:
            long rawIndex=0;
            Point2D rl[BUFFER_SIZE];

            IntegerPoint2D addIntegerPoint(int scale, const Point2D &pt) {
                IntegerPoint2D ipp;

                ScaleDataIter i = freqTables.find(scale);
                if (i != freqTables.end()) {
                        i->second.addIntegerPoint(pt);
                    //  cout<< fd->size() <<endl;
                }
                else {
                    FrequencyData fd(scale);
                    fd.addIntegerPoint(pt);
                    freqTables.insert(make_pair(scale, fd));
                }
                // cout<< freqTables[COARSE]->frequencyList->size() <<endl;
                return ipp;
            }

        };
    };
};

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::PointList& pl) {
    using namespace std;
    using namespace emu::utility;

                ostream1 << pl.freqTables.size();
                ostream1<<" ";
                emu::utility::PointList::ScaleDataConstIter i = pl.freqTables.begin();
                while (i != pl.freqTables.end()) {
                    ostream1 << i->first << " ";  /* scale */
                    ostream1 << i->second.maxHits<< " ";
                    ostream1 << i->second.minHits<< " ";
                    shared_ptr<FrequencyList2D>  fd = i->second.frequencyList;
                    ostream1 << fd->size();
                    ostream1 << " ";
                    emu::utility::FrequencyList2DIter j = fd->begin();
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
                        make_pair(scale,  emu::utility::FrequencyData(scale)));
                emu::utility::FrequencyData  fdPtr = (pl.freqTables)[scale];
                fdPtr.scale = scale;
                input >>  fdPtr.maxHits >> fdPtr.minHits;
                long freqDataSz;
                input >> freqDataSz;
                pl.rawTotal += freqDataSz;
                //cout<< "Reading data got scale, maxhits, minhits and data length: " <<fdPtr->scale <<" "<< fdPtr->maxHits <<" "<< fdPtr->minHits <<" "<< freqDataSz << std::endl;
               // cout<<endl;
                if(freqDataSz >0) {
                   // fdPtr.frequencyList =  new emu::utility::PointList::FrequencyList2D();
                    for (long j = 0; j < freqDataSz; j++) {
                        long x, y;
                        long freq;
                        input >> x >> y >> freq;
                        fdPtr.frequencyList->insert(std::make_pair(emu::utility::IntegerPoint2D(x, y), freq));
                    }
                }
            }
            return input;
        }

//PointList::PointList(int COARSE) : COARSE(COARSE) {}

#endif //FUNCTION_UTILITIES_POINTLIST_H
