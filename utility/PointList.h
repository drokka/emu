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

            typedef std::map<Point2D, long> RawData;
            typedef std::map<Point2D, long>::iterator RawDataIter;
            typedef std::map<Point2D, long>::const_iterator RawDataConstIter;

            //Scale values
             int COARSE = 201;
              int MEDIUM = 941;
             int FINE = 1601;
            const static long BUFFER_SIZE = 10000;


            //shared_ptr<PointList2D> rawList;
            ScaleData freqTables;
           // RawData rawData;
            PointList(const int COARSE, const int MEDIUM, const int FINE,  long rawTotal);


            PointList();

            PointList(const PointList& pl);
            virtual ~PointList() ;

            void addPoints() ;

// add a raw point
            void addPoint(Point2D &pt) ;


            void addTable(int scale) ;

            long rawSize() ;

            long coarseSize() ;

//            friend std::ostream &operator<<(std::ostream &, const PointList &);

 //           friend std::istream &operator>>(std::istream &input, PointList &pl);

            long rawTotal=0;
            double rawMinX = -1.0;
            double rawMaxX = 1.0;
            double rawMinY = -1.0;
            double rawMaxY = 1.0;
            bool rangeFixed = false;  // will estimate a range hence scale factor after first pass
            bool notTiled = true;
        private:
            long rawIndex=0;
            Point2D rl[BUFFER_SIZE];
            //Create an integral mapinsert

            void convert(int scale) ;

        };
    };
};

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::PointList& pl);

std::istream& operator>>(std::istream &input, emu::utility::PointList& pl);

//PointList::PointList(int COARSE) : COARSE(COARSE) {}

#endif //FUNCTION_UTILITIES_POINTLIST_H
