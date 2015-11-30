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
            IntegerPoint2D():IntegerPoint<2>(){}

            IntegerPoint2D(int a, int b){ val[0]=a; val[1] = b;}
//IntegerPoint2D(Point2D &point){}

            IntegerPoint2D(Point2D &point){
                (*this).val[0] = point.val[0];
                (*this).val[1] = point.val[1];
            }


            virtual bool operator()(const IntegerPoint &firstPoint, const IntegerPoint &otherPoint) const{
                if(firstPoint.val[0] < otherPoint.val[0]  ||
                   (firstPoint.val[0] == otherPoint.val[0]) && (firstPoint.val[1] < otherPoint.val[1]))
                    return true;
                else    return false;
            }

            bool operator< ( const IntegerPoint2D &otherPoint) const{
                if(this->val[0] < otherPoint.val[0]  ||
                   (this->val[0] == otherPoint.val[0]) && (this->val[1] < otherPoint.val[1]))
                    return true;
                else    return false;
            }
        };
    };
};


#endif //FUNCTION_UTILITIES_INTEGERPOINT2D_H
