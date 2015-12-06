//
// Created by peter on 22/11/15.
//

#ifndef FUNCTION_UTILITIES_POINTLIST_H
#define FUNCTION_UTILITIES_POINTLIST_H

#include <set>
#include <map>

#include "Point2D.h"
#include "IntegerPoint2D.h"

namespace emu {
    namespace utility {


        class PointList {

        public:
            typedef std::multiset <Point2D, Point2D> PointList2D;
            typedef std::multiset <Point2D, Point2D>::const_iterator PointList2DIter;

            // Map of integral points to number of occurrences. Ordered by the points.
            typedef std::map <IntegerPoint2D, long> FrequencyList2D;
            typedef std::map <IntegerPoint2D, long>::const_iterator FrequencyList2DConstIter;
            typedef std::map <IntegerPoint2D, long>::iterator FrequencyList2DIter;

            typedef struct { int scale; long maxHits; long minHits; std::shared_ptr<FrequencyList2D> frequencyListPtr ; } FrequencyData;

            // map from scale value to corresponding data. For ease of access. Ordered by scale.
            typedef std::map<int, std::shared_ptr<FrequencyData> > ScaleData;
            typedef std::map<int, std::shared_ptr<FrequencyData> >::iterator ScaleDataIter;

            //Scale values
            const  int COARSE ;
            const  int MEDIUM ;
            const  int FINE;


            shared_ptr<PointList2D> rawList;
            ScaleData freqTables;


            PointList():COARSE(200),MEDIUM(800), FINE(1600) {
                rawList = shared_ptr<PointList2D>(new PointList2D());
                freqTables = ScaleData();
                //Add a coarse pixel image by default.
                freqTables.insert(make_pair(COARSE, shared_ptr<FrequencyData>(new FrequencyData())));
                freqTables[COARSE]->scale = COARSE;
                freqTables[COARSE]->maxHits = 1;
                freqTables[COARSE]->minHits = 1;
                freqTables[COARSE]->frequencyListPtr =  shared_ptr<FrequencyList2D> (new FrequencyList2D());
            }

            // add a raw point
            void addPoint(Point2D &pt){
                rawList->insert(pt);
                addIntegerPoint(COARSE, pt);
            }

            //Create an integral map
            int convert(int scale){
                ScaleDataIter i = freqTables.find(scale);
                if(i== freqTables.end()){
                    shared_ptr<FrequencyData> fdata = shared_ptr<FrequencyData>(new FrequencyData());
                    fdata->scale = scale;
                    // add integral points to the frequency list.
                  //  fdata->frequencyList.
                }
            }

        private:
            IntegerPoint2D addIntegerPoint(int scale, Point2D &pt){
                IntegerPoint2D ipp;
                ScaleDataIter i = freqTables.find(scale);
                if(i != freqTables.end()){
                   shared_ptr< FrequencyList2D> fd = i->second->frequencyListPtr;
                 //   assert(i->second->scale == scale);
                    int m = scale/2;
                    int a = m*(pt.val[0] +1); //normally generated pt values between -1, 1.
                    int b = m*( pt.val[1] +1); // integral values between 0 and scale
                    ipp = IntegerPoint2D(a,b);
                    FrequencyList2DIter j = fd->find(ipp);
                    if(j== fd->end()){
                        fd->insert(make_pair(ipp, 1));
                    }
                    else{
                        j->second+=1; //increment count
                        i->second->maxHits = max(i->second->maxHits, j->second);
                    }
                    cout<< fd->size() <<endl;
                }
                cout<< freqTables[COARSE]->frequencyListPtr->size() <<endl;
                return  ipp;
            }
        };

    };
};


#endif //FUNCTION_UTILITIES_POINTLIST_H
