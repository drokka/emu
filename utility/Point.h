//
// Point base class representsing a point in space.
// Created by peter on 21/11/15.
//

#ifndef FUNCTION_UTILITIES_POINT_H
#define FUNCTION_UTILITIES_POINT_H

namespace emu {
    namespace utility {

        template<int D>  class Point {
        public:
            double val[D]; //array of values for each dimension.

            Point(){
                for (int i = 0; i < D;) {
                    val[i] = 0;
                    i++;
                }
            }
            virtual bool operator()(const Point &firstPoint, const Point &otherPoint) const = 0;
        };
    };
};

#endif //FUNCTION_UTILITIES_POINT_H
