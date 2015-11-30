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
            typedef std::map <IntegerPoint2D, long>::const_iterator FrequencyList2DIter;

            typedef struct { int scale; FrequencyList2D frequencyList ; } FrequencyData;

            // map from scale value to corresponding data. For ease of access. Ordered by scale.
            typedef map<int, shared_ptr<FrequencyData> > ScaleData;
            typedef map<int, shared_ptr<FrequencyData> >::iterator ScaleDataIter;

            shared_ptr<PointList2D> rawList;
            ScaleData freqTables;


            PointList() {rawList = shared_ptr<PointList2D>(new PointList2D()); freqTables = ScaleData();}

            // add a raw point
            void addPoint(Point2D &pt){rawList->insert(pt);}

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

        };
    };
};

#endif //FUNCTION_UTILITIES_POINTLIST_H
