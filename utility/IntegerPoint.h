//
// IntegerPoint represents integral valued position - think pixel.
// Created by peter on 22/11/15.
//

#ifndef FUNCTION_UTILITIES_INTEGERPOINT_H
#define FUNCTION_UTILITIES_INTEGERPOINT_H

namespace emu {
    namespace utility {

        template<int D>  class IntegerPoint {
        public:
            int val[D]; //array of values for each dimension.

            IntegerPoint(){
                for (int i = 0; i < D; ++i) {
                    val[i] = 0;
                }
            }


            virtual bool operator()(const IntegerPoint &firstPoint, const IntegerPoint &otherPoint) const = 0;
        };
    };
};

class IntegerPoint {

};


#endif //FUNCTION_UTILITIES_INTEGERPOINT_H
