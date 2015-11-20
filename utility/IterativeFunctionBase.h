//
// Created by peter on 14/10/15.
//

#ifndef FUNCTION_UTILITIES_ITERATIVEFUNCTIONBASE_H
#define FUNCTION_UTILITIES_ITERATIVEFUNCTIONBASE_H

namespace doc {
    namespace utility {


        class IterativeFunctionBase {
        public:
            IterativeFunctionBase() { }

            virtual void operator()(double *inout){ } //Identity

        };
    }}

#endif //FUNCTION_UTILITIES_ITERATIVEFUNCTIONBASE_H
