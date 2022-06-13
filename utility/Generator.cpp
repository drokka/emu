//
// Created by peter on 22/04/17.
//

#include "Generator.h"

emu::utility::Generator::Generator(IterativeFunctionBase *ff, long iters, PointList *hl):
iterativeFunctionPtr(ff), iters(iters), hl(hl) { }

emu::utility::Point2D  emu::utility::Generator::go(const Point2D& startPt) {

    emu::utility::Point2D point;
    point.val[0] = startPt.val[0];
    point.val[1] = startPt.val[1];
    hl->addPoint(point);

    for (int i = 0; i < iters; i++) {
        double inPt[2] = {(double) (point.val[0]), (double) point.val[1]};

        (*iterativeFunctionPtr)(inPt);
        point.val[0] = inPt[0];
        point.val[1] = inPt[1];
        hl->addPoint(point);
    }
    return point;
}
