//
// Created by peter on 4/03/17.
//

#ifndef FUNCTION_UTILITIES_FREQUENCYDATA_H
#define FUNCTION_UTILITIES_FREQUENCYDATA_H
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

        typedef std::map<IntegerPoint2D, long> FrequencyList2D;
        typedef std::map<IntegerPoint2D, long>::const_iterator FrequencyList2DConstIter;
        typedef std::map<IntegerPoint2D, long>::iterator FrequencyList2DIter;

        class FrequencyData {


        public:
            int minX=0;
            int maxX=0;
            int minY=0;
            int maxY=0;


            int scale;
            long maxHits;
            long minHits;
            shared_ptr<FrequencyList2D> frequencyList;

            FrequencyData(int scale, long maxHits, long minHits);

            FrequencyData(int scale);
            FrequencyData();

            ~FrequencyData();

            IntegerPoint2D addIntegerPoint( const Point2D &pt) ;
            long findMin();
        const    int rangeX();
         const   int rangeY();
            int getMinX(){return minX;}
            int getMaxX(){return maxX;}
            int getMinY(){ return minY;}
            int getMaxY(){return maxY;}
        };
    }
}

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::FrequencyData& pl);

std::istream& operator>>(std::istream &input, emu::utility::FrequencyData& pl);

#endif //FUNCTION_UTILITIES_FREQUENCYDATA_H
