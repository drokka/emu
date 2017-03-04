//
// Created by peter on 5/02/17.
//
#include "PointList.h"

#include <iostream>
#include <fstream>
#include <cairo.h>

using namespace std;
using namespace emu::utility;

int paint(emu::utility::PointList hl, char *imageName, char *imageExt);

int main(int nParam, char **param) {
    ifstream ifstream1;
    // char * imageFileName, *imageExt;
    if (nParam == 4) {
        try {
            string symFile(param[1]);
            cout << "File is " << symFile << endl;
            ifstream1.open(symFile.c_str(), std::ios::in);
            if (!ifstream1.is_open()) {
                throw;
            }

        } catch (...) {
            cout << "Error loading file." << endl;
            return 1;
        }
    } else {
        cout << "Please supply file name, image file name and extension." << endl;
        return 1;
    }

    FrequencyData fd1;
    fd1.frequencyList->insert(make_pair(IntegerPoint2D(1,2),17));

    FrequencyData fd2 = fd1;
cout<< fd2.frequencyList->size() << endl;

    emu::utility::PointList pl;
    cout << pl.freqTables.size() << "ft size after ctor" <<endl;
    ifstream1 >> pl;
    ifstream1.close();

    int res = paint(pl, param[2], param[3]);

    if (0 != res) {
        cout << " There was an error saving image." << endl;
    }
    return res;
};

int paint(emu::utility::PointList hl, char *imageName, char *imageExt) {
    PointList::ScaleDataIter i = hl.freqTables.begin();
    cout << "number of freqTables is " << hl.freqTables.size() << endl;
    while (i != hl.freqTables.end()) {
        cairo_surface_t *surface = 0;
        cairo_t *cr = 0;
        int sz = i.operator*().first;

        if (i->second.frequencyList->size() >0 ) {   // != nullptr) {
            surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, sz, sz);
            cr = cairo_create(surface);
            cairo_set_source_rgb(cr, 255, 255, 255);
            cairo_fill(cr);

            long maxhits = i.operator*().second.maxHits;
            cout << "maxHits for " << hl.COARSE << " is " << maxhits << endl;
            long fdiff = maxhits - 1; //maxx -minn;


            emu::utility::FrequencyList2DConstIter iter = i.operator*().second.frequencyList->begin();
            while (iter != i.operator*().second.frequencyList->end()) {
                int x = iter->first.val[0]; //(points+i)->x;
                int y = iter->first.val[1]; //((points+i)->y);
                long hits = iter->second;
//   cout << "looking for " << x <<" "<< y <<" " << hits <<endl;
/*****
PointFrequency::const_iterator pp = hl.hitPointList.find(*(points+i));
if(pp!= hl.hitPointList.cend())
{
 hits = pp->second;
//       cout<< "found!! " <<hits <<endl;
}
 ******************/
//  cout << "maxhits " <<maxhits <<endl;
                double opacity = (double) (hits - 1) / fdiff;
//   cout <<"opacity " << opacity <<endl;
//opacity=0.3*opacity;
//bound opacity between 0 and 1.
                opacity = (opacity <= 0) ? 1 : opacity;
                opacity = (opacity > 1) ? 1 : opacity;

                cairo_set_source_rgba(cr, 0.2, 0.95 * opacity, .9, opacity);
//    cairo_set_source_rgb (cr, 0.2, 0.95*opacity, .9);
                cairo_move_to(cr, x, y + 0.5);
                cairo_line_to(cr, x + 0.5, y + 0.5);
                cairo_stroke(cr);
                iter++;
            }

            std::cout << "After painting sz " << sz << " complete. " << '\n';

            string fname = string(imageName) + std::to_string(sz) + "." + imageExt;

            cairo_surface_write_to_png(surface, fname.c_str());
            cairo_destroy(cr);
            cairo_surface_destroy(surface);
        } else { cout << "No frequency table for scale " << sz << endl; }
        i++; //next freqTable / size
    }


    return 0;
};