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
             void getFloatArray(ColourIcon &colourIcon, bool withAlpha);

            float  *floatBuffer = nullptr;
            unsigned  char *pngBuffer = nullptr;

        public:
            void getCharArray(ColourIcon &colourIcon, bool withAlpha, bool switchRGBAtoARGB = false);

            int paintPNG(ColourIcon &colourIcon, string fileName, bool withAlpha);

            int paintHDR(ColourIcon &colourIcon, string fileName, bool withAlpha);
             unsigned char * paintPNGtoBuffer(ColourIcon &colourIcon, bool withAlpha, int *len, bool switchRGBAtoARGB = false);

            virtual ~PaintIcon();

            unsigned char *charBuffer = nullptr;
        };
    }
}

#endif //FUNCTION_UTILITIES_PAINTICON_H
