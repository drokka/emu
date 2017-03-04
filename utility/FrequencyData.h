//
// Created by peter on 4/03/17.
//

#ifndef FUNCTION_UTILITIES_FREQUENCYDATA_H
#define FUNCTION_UTILITIES_FREQUENCYDATA_H
#include <map>
#include <memory>
#include <ostream>
#include <istream>
#include <iostream>

#include "Point2D.h"
#include "IntegerPoint2D.h"

namespace emu {
    namespace utility {
        using namespace std;

        typedef std::map<IntegerPoint2D, long> FrequencyList2D;
        typedef std::map<IntegerPoint2D, long>::const_iterator FrequencyList2DConstIter;
        typedef std::map<IntegerPoint2D, long>::iterator FrequencyList2DIter;

        class FrequencyData {

        public:


            int scale;
            long maxHits;
            long minHits;
            shared_ptr<FrequencyList2D> frequencyList;

            FrequencyData(int scale, long maxHits, long minHits)
                    : scale(scale), maxHits(maxHits), minHits(minHits), frequencyList(shared_ptr<FrequencyList2D>(new FrequencyList2D())) {
            }

            FrequencyData(int scale): scale(scale), maxHits(0), minHits(0), frequencyList(shared_ptr<FrequencyList2D>(new FrequencyList2D())) {

            }
            FrequencyData(): scale(200), maxHits(0), minHits(0), frequencyList(shared_ptr<FrequencyList2D>(new FrequencyList2D()))  {
            }

            IntegerPoint2D addIntegerPoint( const Point2D &pt) {
                IntegerPoint2D ipp;
                int m = this->scale;
                int a = m * (pt.val[0]); //normally generated pt values between -1, 1.
                int b = m * (pt.val[1]); // integral values between 0 and scale
                ipp = IntegerPoint2D(a, b);
                FrequencyList2DIter j = frequencyList->find(ipp);
                if (j == frequencyList->end()) {
                    frequencyList->insert(std::make_pair(ipp, 1));
                } else {
                    j->second += 1; //increment count
                    maxHits = std::max(maxHits, j->second);
                    //TODO: handle minHits
                }
            }

        };
    }
}

#endif //FUNCTION_UTILITIES_FREQUENCYDATA_H
