//
// 2D position with integer values.
// Created by peter on 22/11/15.
//

#ifndef FUNCTION_UTILITIES_INTEGERPOINT2D_H
#define FUNCTION_UTILITIES_INTEGERPOINT2D_H

#include "IntegerPoint.h"
#include "Point2D.h"

namespace emu {
    namespace utility {

        class IntegerPoint2D:public IntegerPoint<2> {
        public:
            IntegerPoint2D();
            IntegerPoint2D(int a, int b);
//IntegerPoint2D(Point2D &point){}

            IntegerPoint2D(Point2D &point);

            virtual bool operator()(const IntegerPoint &firstPoint, const IntegerPoint &otherPoint) const;

            bool operator< ( const IntegerPoint2D &otherPoint) const;
        };
    };
};


#endif //FUNCTION_UTILITIES_INTEGERPOINT2D_H
