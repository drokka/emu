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
#include "runsampleNoJni.cpp"

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

TEST(FD, symi_streaming_Test){
    FrequencyData fd(10);
    for (int i=0;i<10;i++){
        for(int j=0;j<10;j++) {

            fd.addIntegerPoint(Point2D(i*0.1, j*0.1));

        }}

    cout << fd <<endl;

    ASSERT_EQ( fd.minX,0);
    ASSERT_EQ( fd.minY,0);
    ASSERT_EQ( fd.maxX,9);
    ASSERT_EQ( fd.maxY,9);

    ASSERT_EQ(fd.maxHits, 1);

    fd.addIntegerPoint(Point2D(0.3,0.3));
    ASSERT_EQ(fd.maxHits, 2);

    cout << fd <<endl;
    stringstream ss;  ss<<fd;

    FrequencyData fd2;
    ss>> fd2;

    ASSERT_EQ( fd2.minX,0);
    ASSERT_EQ( fd2.minY,0);
    ASSERT_EQ( fd2.maxX,9);
    ASSERT_EQ( fd2.maxY,9);

    ASSERT_EQ(fd2.maxHits, 2);

    cout<< fd2 <<endl;
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
    int sz = 301, degSym = 3;
    double maxColour[] = {0.9,0.9,0.9,0.1};
    double bgColour[] = {0.9,0.9,0.0,0.1};
    double minColour[] = {0.3,0.3,0.3,0.1};
    double params[] = {0.1, 0.1, 0.1, 0.4, 0.3, 0.2};
    double params2[] = {.02, .02, .6, .01, .9, .9};

    ColourIcon::ColourFn colourFn = myClrFn;

    SymIconApp *app1 = new SymIconApp(1000, 0.3, 0.1, emu::utility::QuiltIcon::QuiltType::SQUARE,
                    "symitest", sz, params ,
                    6, degSym,  bgColour, minColour,
    maxColour, colourFn);
    app1->runGenerator();
    stringstream ss5;
    cout << "app1 hl: "<<endl;
    cout << app1->hl <<endl;
    ss5 << *(app1);
    cout<<"app1:" <<endl;
    cout <<*(app1) <<endl;
    cout<<"ss5 string:" <<endl;
    cout << ss5.str() <<endl;

    SymIconApp app2(10, 0.1,0.7,emu::utility::QuiltIcon::QuiltType::FRACTAL,
                    "ss", sz, params2,
                    6, 5, bgColour, minColour, maxColour, colourFn);

    ss5 >> app2;
    cout << "app2 after load: " <<endl
    << app2 <<endl;

    ASSERT_EQ(app2.degSym, 3);
    ASSERT_EQ(app2.omegaVal, 0.3);
    ASSERT_EQ(0.3, app2.qi->omega->getValue());

    ASSERT_EQ(app2.hl.freqTables.size(), app1->hl.freqTables.size());
    ASSERT_EQ(app2.hl.freqTables[0].maxX, app1->hl.freqTables[0].maxX);
    ASSERT_EQ(app2.hl.freqTables[0].maxY, app1->hl.freqTables[0].maxY);
    ASSERT_EQ(app2.hl.freqTables[0].maxHits, app1->hl.freqTables[0].maxHits);

    double mClr[4] = {.1,.0,.6,0.2};
    double maxClr[4] = {.9,0.333,0.01,1.0};
    double bgClr[4] = {.01,0.99,0.0,.9};
    unsigned char *pngBuf = nullptr;

    stringstream ss6;
    ss6 << *app1;
cout<<" ss6" <<endl;
cout << ss6.str()<<endl;

std::time_t result = std::time(nullptr);
     const std::string ddate = to_string(result).data();
     string ff = "testIco" + ddate + ".png";
int bufLen =    reColour(ss6,&pngBuf,ff , bgClr,mClr, maxClr);

    unsigned char *pngBuf2 = nullptr;
    stringstream ss7;
    ss7 << *app1;

    int bufLen2 =    reColourBuffer(ss7,301,&pngBuf2 , bgClr,mClr, maxClr);
cout <<"png buffer length is: " <<bufLen << " bufLen2 is: " << bufLen2 <<endl;
cout <<"streaming test done"<<endl;
cout << "ss7 is:______________________________________________________________________" <<endl;
cout << ss7.str() << endl;
    cout<<"reiter test"<<endl;
    cout << "rawtotal " << app1->hl.rawTotal << "  max hits " << app1->hl.freqTables.at(201).maxHits <<endl;
    ostringstream osIter("yep");
    istringstream inPutSym(ss7.str());
    unsigned char *pngBuf3 = nullptr;
    int reiterResult = moreIterSample(10000,inPutSym , osIter, &pngBuf3, bgClr, mClr,maxClr);
    cout <<"moreIter result " << reiterResult << " output data is " << endl;
    istringstream inny(osIter.str());
    inny >> *app1;
    cout << "rawtotal " << app1->hl.rawTotal << "  max hits " << app1->hl.freqTables.at(201).maxHits <<endl;

    cout << osIter.str() <<endl;
    stringstream iter1Stream(osIter.str());

      reColour(iter1Stream,&pngBuf,"iter1.png" , bgClr,mClr, maxClr);
 /*    iter1Stream >> *app1;
     unsigned  char *bb = nullptr;
     int ii = 0;

     app1->createPNG(&bb, &ii, "iter_1.png"); */
//    result = stbi_write_png("iter_1.png", 201,201, 3, pngBuf3,  201 * 3);
    cout<<"reiter test TWO"<<endl;

    ostringstream osIter1("yep");
    istringstream inPutSym1(osIter.str());
    int reiterResult1 = moreIterSample(100000,inPutSym1, osIter1, &pngBuf2, bgClr,mClr, maxClr);
    istringstream inny2(osIter1.str());
    inny2 >> *app1;
    cout << "rawtotal " << app1->hl.rawTotal << "  max hits " << app1->hl.freqTables.at(201).maxHits <<endl;

    cout <<"moreIter result " << reiterResult1 << " output data is " << endl;
    cout << osIter1.str() <<endl;
    stringstream iter12Stream(osIter1.str());
    reColour(iter12Stream,&pngBuf,"iter2.png" , bgClr,mClr, maxClr);
/*
    iter12Stream >> *app1;
    unsigned  char *bb1 = nullptr;
    int ii1 = 0;
    app1->createPNG(&bb1, &ii1, "iter_2.png"); */
}
