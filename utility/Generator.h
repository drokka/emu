//
// Created by peter on 12/12/15.
//

#ifndef FUNCTION_UTILITIES_GENERATOR_H
#define FUNCTION_UTILITIES_GENERATOR_H

#include "IterativeFunctionBase.h"
#include "PointList.h"

namespace emu {
    namespace utility {

        class Generator {

            IterativeFunctionBase *iterativeFunctionPtr;
            long iters = 10000;
            PointList *hl;

        public:
            Generator(IterativeFunctionBase *ff, long iters, PointList *hl):
                    iterativeFunctionPtr(ff), iters(iters), hl(hl) { }

            void go(Point2D startPt) {

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
            }
        };
    }
}

#endif //FUNCTION_UTILITIES_GENERATOR_H
