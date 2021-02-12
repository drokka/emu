//
// Created by peter on 22/04/17.
//

#include "IntegerPoint2D.h"

emu::utility::IntegerPoint2D::IntegerPoint2D():IntegerPoint<2>(){}

emu::utility::IntegerPoint2D::IntegerPoint2D(int a, int b){ val[0]=a; val[1] = b;}
//IntegerPoint2D(Point2D &point){}


emu::utility::IntegerPoint2D::IntegerPoint2D(Point2D &point){
(*this).val[0] = point.val[0];
(*this).val[1] = point.val[1];
}


bool emu::utility::IntegerPoint2D::operator()(const IntegerPoint &firstPoint, const IntegerPoint &otherPoint) const{
    if(firstPoint.val[0] < otherPoint.val[0]  ||
            ((firstPoint.val[0] == otherPoint.val[0]) && (firstPoint.val[1] < otherPoint.val[1])))
        return true;
    else    return false;
}

bool emu::utility::IntegerPoint2D::operator< ( const IntegerPoint2D &otherPoint) const{
    if(this->val[0] < otherPoint.val[0]  ||
            ((this->val[0] == otherPoint.val[0]) && (this->val[1] < otherPoint.val[1])))
        return true;
    else    return false;
}
