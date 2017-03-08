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

            FrequencyData(int scale): scale(scale), maxHits(1), minHits(1), frequencyList(shared_ptr<FrequencyList2D>(new FrequencyList2D())) {

            }
            FrequencyData(): scale(200), maxHits(1), minHits(1), frequencyList(shared_ptr<FrequencyList2D>(new FrequencyList2D()))  {
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
std::ostream& operator<<(std::ostream &ostream1, const emu::utility::FrequencyData& pl) {
    using namespace std;
    using namespace emu::utility;

        ostream1 << pl.scale << " ";  /* scale */
        ostream1 << pl.maxHits<< " ";
        ostream1 << pl.minHits<< " ";
        shared_ptr<FrequencyList2D>  fd = pl.frequencyList;
        ostream1 << fd->size();
        ostream1 << " ";
        emu::utility::FrequencyList2DIter j = fd->begin();
        while (j != fd->end()) {
            ostream1 << j->first.val[0] << " "<< j->first.val[1] << " "<< j->second<< " ";
            j++;
        }
        ostream1 << " ";
        ostream1.flush();
    return ostream1;
}

std::istream& operator>>(std::istream &input, emu::utility::FrequencyData& pl) {
    using namespace emu::utility;
    using namespace std;
         input >> pl.scale;
        input >>  pl.maxHits >> pl.minHits;

        long freqDataSz;
        input >> freqDataSz;
        if(freqDataSz >0) {
            for (long j = 0; j < freqDataSz; j++) {
                long x, y;
                long freq;
                input >> x >> y >> freq;
                pl.frequencyList->insert(std::make_pair(emu::utility::IntegerPoint2D(x, y), freq));
            }
        }
    return input;
}


#endif //FUNCTION_UTILITIES_FREQUENCYDATA_H
