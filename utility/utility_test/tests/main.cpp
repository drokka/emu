//
// Created by peter on 28/10/15.
//

#include <sstream>
#include "../utility/Parameter.h"
#include "ParameterTest.h"
#include "IterativeFunction.h"
#include "IterativeFunctionTest.h"
#include "Point2DTest.h"
#include "PointListTest.h"
#include "ColourIcon.h"
#include "QuiltIcon.h"
#include "SymIconApp.h"
#include "colourIcon.cpp"

using namespace std;


using namespace emu::utility;

void myClrFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                                  double *rgbaOut) {
    long maxhits = fd.maxHits;
    // cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
    long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;

    //  cout << "maxhits " <<maxhits <<endl;
    double opacity = (double)(hits - 1)/fdiff;
    //   cout <<"opacity " << opacity <<endl;std::max(
//opacity=0.3*opacity;
    //bound opacity between 0 and 1.
    opacity = (opacity <= 0)?0.05:opacity;
    opacity = (opacity >1)?1:opacity;
    rgbaOut[0]= 0.5 +0.5*opacity;
    rgbaOut[1]=  .9*opacity;
    rgbaOut[2]= 0.3 +0.7*opacity;
    rgbaOut[3]=opacity;
}



TEST(parameterA,basictest ) {
    const std::string name ="omega";
    emu::utility::Parameter < int > omega (name, 7);
    omega.setValue(7);

    ASSERT_TRUE(omega.getName() == "omega");
    ASSERT_TRUE(omega.getValue() == 7);

    omega.setValue(77);
    ASSERT_TRUE(omega.getValue() == 77);


    Parameter<int> delta("delta", 7, 1, 10, false, false);
    ASSERT_TRUE(delta.getValue() == 7);
    ASSERT_TRUE(delta.getMin() == 1);
    ASSERT_TRUE(delta.getMax() == 10);

    delta.setValue(11);

    ASSERT_TRUE(delta.getValue() == 9);

    delta.setValue(0);
    ASSERT_TRUE(delta.getValue() == 2);

}

TEST(symi, streaming){
    //"100000","F", "121", "cannot count",
    //                        "0.2", "0.13", "0.7","0.39","0.22","0.073","4"


    PointList pointList, pl2;
    Point2D points[20];
    for(int k=0; k<20; k++){
        points[k] = Point2D(k,1);
    }
    for(int i=0;i<20;i++) {
        pointList.addPoint(points[i]);
    }
    pointList.addPoints();

    stringstream ss;
    ss << pointList;
  //  istringstream iss(ss.str());

  cout << "pointList compare pl2" << endl;
  cout << pointList << endl;
    ss>> pl2;
    cout << pl2 << endl;

    ASSERT_EQ(pl2.freqTables.size(), pointList.freqTables.size());

    emu::utility::QuiltIcon::QuiltType qt1, qt2;

    qt1 = emu::utility::QuiltIcon::QuiltType::SQUARE;
    qt2 = emu::utility::QuiltIcon::QuiltType::HEX;

    stringstream ss3;
    ss3<<qt1;
    cout << ss3.str() <<endl;
  //  iss.str(ss3.str());
    ss3 >> qt2;
    ASSERT_EQ(qt1, qt2);
    QuiltIcon quiltIcon(0.2,0.2,0.1,0.3,0.1,0.5, 3,
                        emu::utility::QuiltIcon::QuiltType::HEX);
    QuiltIcon qi2;
    stringstream ss4;
    ss4 << quiltIcon;
    cout << ss4.str() <<endl;
 //   iss.clear();
  //  iss.str(ss4.str());
   // cout << "iss: " << iss.str() <<endl;
    ss4>> qi2;
    ASSERT_EQ(qi2.lambda->getValue(), quiltIcon.lambda->getValue());
    ASSERT_EQ(qi2.quiltType, quiltIcon.quiltType);
    int sz = 11, degSym = 3;
    double maxColour[] = {0.9,0.9,0.9,0.1};
    double bgColour[] = {0.1,0.2,0.2,0.1};
    double minColour[] = {0.3,0.3,0.3,0.1};
    double params[] = {0.01, 0.01, 0.1, 0.01, 0.3, 0.2};
    double params2[] = {.02, .02, .6, .01, .9, .9};

    ColourIcon::ColourFn colourFn = myClrFn;

    SymIconApp *app1 = new SymIconApp(100, 0.3, 0.1, emu::utility::QuiltIcon::QuiltType::SQUARE,
                    "symitest", sz, params ,
                    6, degSym,  bgColour, minColour,
    maxColour, colourFn);
    app1->runGenerator();
    stringstream ss5;

    ss5 << *(app1);
    cout<<"app1:" <<endl;
    cout <<*(app1) <<endl;
    cout<<"ss5 string:" <<endl;
    cout << ss5.str() <<endl;
    delete app1;
    SymIconApp app2(10, 0.1,0.7,emu::utility::QuiltIcon::QuiltType::FRACTAL,
                    "ss", sz, params2,
                    6, 5, bgColour, minColour, maxColour, colourFn);

    ss5 >> app2;
    cout << "app2 after load: " <<endl
    << app2 <<endl;

    ASSERT_EQ(app2.degSym, 3);
    ASSERT_EQ(app2.omegaVal, 0.3);
    ASSERT_EQ(0.3, app2.qi->omega->getValue());
}
