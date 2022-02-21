//
// Created by peter on 2/04/17.
// Wrapper for COLOURing generated data.
//

#ifndef UTILITY_ColourIcon_H
#define UTILITY_ColourIcon_H

#include "PointList.h"
#include "IntegerPoint2D.h"
#include <vector>

using namespace emu::utility;
using namespace std;

namespace emu {
    namespace utility {

       // typedef double RgbaInf[];
        typedef std::map<IntegerPoint2D, double*> RgbaList2D;
        typedef std::map<IntegerPoint2D, double*>::const_iterator RgbaList2DConstIter;
        typedef std::map<IntegerPoint2D, double*>::iterator RgbaList2DIter;

        void simpleColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                                   double *rgbaOut);
    class ColourIcon {
        PointList *pointList;
        bool useAlpha = false;


    public:
        double *minRGBA;
        double *maxRGBA;
        typedef void (*ColourFn)(double min[4], double max[4], long frequency, FrequencyData &pointList,
                                 double *rgbaOut); //calculate RGBA to colourise frequency

        ColourIcon(const int xSz, const int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList,
                 ColourFn colourFn , RgbaList2D &colourArray);

        ColourIcon(const int xSz, const int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList, RgbaList2D &colourArray);

        ColourFn colourFn = 0;
        void colourPoint( int x, int y, double *rgba) ;

        void colourIn();
        static ColourFn simpleColourFn;
        int xSz;
        int ySz;
        RgbaList2D &colourArray;
        //Dimensions
        double *bgRGBA;

        void setColour(double *bgRGBA, double *minRGBA, double *maxRGBA); //change the background, min and max colours.

        ~ColourIcon();

        void setColourFunction(ColourFn func);
    };

}
}
#endif //UTILITY_ColourIcon_H
