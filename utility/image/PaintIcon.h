//
// Created by peter on 27/01/2021.
//
/******
 * Using stb C image library defined in header files
 */

#ifndef FUNCTION_UTILITIES_PAINTICON_H
#define FUNCTION_UTILITIES_PAINTICON_H

#include <ColourIcon.h>


using namespace emu::utility;
using namespace std;

namespace emu {
    namespace utility {
        class PaintIcon {
            void getCharArray(ColourIcon &colourIcon, bool withAlpha);
             void getFloatArray(ColourIcon &colourIcon, bool withAlpha);

            unsigned char *charBuffer = nullptr;
            float  *floatBuffer = nullptr;
            unsigned  char *pngBuffer = nullptr;

        public:
             int paintPNG(ColourIcon &colourIcon, string fileName, bool withAlpha);

            int paintHDR(ColourIcon &colourIcon, string fileName, bool withAlpha);
             unsigned char * paintPNGtoBuffer(ColourIcon &colourIcon, bool withAlpha, int *len);

            virtual ~PaintIcon();
        };
    }
}

#endif //FUNCTION_UTILITIES_PAINTICON_H
