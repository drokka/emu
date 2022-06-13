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
            PointList *hl;

        public:
            Generator(IterativeFunctionBase *ff, long iters, PointList *hl);

            Point2D go(const Point2D& startPt) ;

            long iters = 10000;
        };
    }
}

#endif //FUNCTION_UTILITIES_GENERATOR_H
