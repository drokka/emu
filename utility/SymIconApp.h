//
// Created by peter on 30/06/17.
//

#ifndef SYMICON_SYMICONAPP_H
#define SYMICON_SYMICONAPP_H


#include "QuiltIcon.h"

#include "Generator.h"
#include "ColourIcon.h"

using namespace emu::utility;

namespace emu {
    namespace utility {

        class SymIconApp {
        public:

            SymIconApp(long iterations, double initX, double initY, QuiltIcon::QuiltType type, string fnBase,
                       int sz, double *iconParams, int numIconParams, int degSym, double *bgColour, double *minColour,
                       double *maxColour, ColourIcon::ColourFn colourFn);
            SymIconApp(): SymIconApp(2, 0.1, 0.1, QuiltIcon::QuiltType::SQUARE, "sym", 9,
                                              const_cast<double *>(defaultParams), 6, 3,
                                              const_cast<double *>(defaultClr), const_cast<double *>(defaultClr),
                                              const_cast<double *>(defaultClr), nullptr){}
            virtual ~SymIconApp();


            long iterations = 100000;

            QuiltIcon::QuiltType type = QuiltIcon::QuiltType::SQUARE;
            double *iconParams;
            int numIconParams;
            double lambdaVal;
            double alphaVal;
            double betaVal;
            double gammaVal;
            double omegaVal;
            double maVal;
            int degSym;
            /*******  pp.aA=2; pp.bB=0; pp.gG=1; pp.oO=0.01;
             pp.degreeSym=4; pp.scale=1;
             pp.lL=-1.8; ****/

            //-1.830826997756958</lL><aA>2.8900375366210938</aA><bB>-2.312030076980591</bB>
            // <gG>2.231203079223633</gG><oO>0.06578969955444336</oO><degreeSym>3</degreeSym><scale>8</scale>
        private:

            Generator *gg;
            Point2D initPoint;

            RgbaList2D colourArray;

             double defaultParams[6] = {0.1,0.02,0.12,0.1,0.1,0.1};

             double defaultClr[4] = {0.1,0.1,0.1,0.1};
            //paintIcon.setUseAlpha(false);

            std::string fnBase = "img_a_";
            std::string errorMsg = "";

        protected:
        public:
            Point2D lastPoint;
            PointList hl;
            int sz = 1600;

            QuiltIcon *qi;
            bool error = false;

            ColourIcon colourIcon;
            void runGenerator();

            //void save();

            long fdiff;
            long maxhits;
            SymIconApp sizeSlice(const SymIconApp& symIconApp, const int size); // get data for one sized icon

            //           double bg[];
            //          double min[];
            //           double max[];
            void save(ostringstream &outy);

            void setColour(double *bgClr, double *minClr, double *maxClr);

            int createPNG(unsigned char **pngBuf, int *len, string fname);

            int createPngBuffer(unsigned char **pngBuf, int *len);
        };
    }
}

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::SymIconApp& symIconApp) ;
std::istream& operator>>(std::istream &input, emu::utility::SymIconApp& symIconApp);


#endif //SYMICON_SYMICONAPP_H
