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
                    : COARSE(COARSE),  MEDIUM(MEDIUM),  FINE(FINE),
                      rawIndex(0), rawTotal(rawTotal),freqTables(ScaleData()) {
            }


            PointList():COARSE(200),  MEDIUM(800), FINE(1600),
                        rawIndex(0), rawTotal(0),freqTables(ScaleData()){
            }
            
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
                    this->freqTables.insert(make_pair(scale, fdata));
                }
                cout<< "ft size: " <<this->freqTables.size() <<endl;
            }

            long rawSize() {
                return rawTotal + rawIndex;
            }

            long coarseSize() {
                if(freqTables.find(COARSE)!= freqTables.end()) {
                    return freqTables[COARSE].frequencyList->size();
                }
                else return 0;
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
                    ostream1 << i->second;
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
                long scale;
              //  fdPtr.scale = scale;
                std::streampos p_orig = input.tellg();
                input >> scale;
                pl.addTable(scale);
                input.seekg(p_orig); /* Go back so scale can be read again by >>FrequencyData */
                input >> pl.freqTables[scale];

            }
            return input;
        }

//PointList::PointList(int COARSE) : COARSE(COARSE) {}

#endif //FUNCTION_UTILITIES_POINTLIST_H
