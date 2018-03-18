//
// Created by peter on 21/11/15.
//

#ifndef FUNCTION_UTILITIES_POINT2D_H
#define FUNCTION_UTILITIES_POINT2D_H

#include "Point.h"

namespace emu {
    namespace utility {

        class Point2D:public Point<2> {
        public:
            Point2D():Point<2>(){}

            Point2D(double x, double y){ val[0] = x; val[1] = y;}

            virtual bool operator()(const Point &firstPoint, const Point &otherPoint) const{
                if(firstPoint.val[0] < otherPoint.val[0]  ||
                   (firstPoint.val[0] == otherPoint.val[0]) && (firstPoint.val[1] < otherPoint.val[1]))
                    return true;
                else    return false;
            }

            bool operator< ( const Point2D &otherPoint) const{
                if(this->val[0] < otherPoint.val[0]  ||
                   (this->val[0] == otherPoint.val[0]) && (this->val[1] < otherPoint.val[1]))
                    return true;
                else    return false;
            }
        };

    };
    };

#endif //FUNCTION_UTILITIES_POINT2D_H
