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
            Generator(IterativeFunctionBase *ff, long iters, PointList *hl);

            void go(Point2D startPt) ;
        };
    }
}

#endif //FUNCTION_UTILITIES_GENERATOR_H
