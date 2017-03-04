//
// Created by peter on 18/01/17.
//

#ifndef FUNCTION_UTILITIES_POINTLISTTEST_H
#define FUNCTION_UTILITIES_POINTLISTTEST_H

#include <PointList.h>
#include <gtest/gtest.h>
#include <bits/ios_base.h>
#include <ios>
#include <fstream>

using namespace std;
//using namespace emu::utility;

class PointListTestSuite : public ::testing::Test {

public:
    PointListTestSuite() {}

};

TEST_F(PointListTestSuite, constructor){
    emu::utility::PointList pl;
    pl.addTable(pl.COARSE);
    pl.addTable(pl.MEDIUM);
    pl.addTable(pl.FINE);
    Point2D pt(1,1);
    pl.addPoint(pt);
   pl.addPoints();
   ASSERT_EQ(3, pl.freqTables.size() );
    ASSERT_EQ(1, pl.freqTables[pl.COARSE].frequencyList->size());

    emu::utility::PointList pl1 = pl;
    ASSERT_EQ(3, pl1.freqTables.size() );
    ASSERT_EQ(1, pl1.freqTables[pl.COARSE].frequencyList->size());

}

TEST_F(PointListTestSuite, addPoints){
    emu::utility::PointList pl = PointList();

    Point2D pt1= Point2D(0.1,1.1);
    pl.addPoint(pt1);
    ASSERT_EQ(1, pl.rawSize());
    pl.addPoint(pt1);
    ASSERT_EQ(2, pl.rawSize());

    for(int i=0; i<10;i++){
        Point2D pt(i+0.3,0.5);
        pl.addPoint(pt);
    }

    ASSERT_EQ(12, pl.rawSize());
    pl.convert(pl.COARSE);
    ASSERT_EQ(11, pl.coarseSize());

    FrequencyData  fd1 =  pl.freqTables[pl.COARSE];

    ASSERT_EQ(2,fd1.maxHits);
    ASSERT_EQ(1, fd1.minHits);

    for(int i=0; i<10;i++){
        Point2D pt(i+0.3,0.5);
        pl.addPoint(pt);
    }
    ASSERT_EQ(2,fd1.maxHits);
    cout<<fd1.frequencyList->size() << " " << endl;

    std::ofstream outy("/home/peter/out1", std::ofstream::out);

    outy <<pl;
    outy.flush(); outy.close();
    sleep(1);
    std::ifstream inStr(string("/home/peter/out1").c_str(), std::ios::in);
 //   std::istream_iterator<long>();
    PointList pl2;
if(inStr.bad()){
    cout<< "no good"<<endl;
}
    bool yeh = inStr.is_open();
    inStr >>pl2;

    inStr.close();

    ASSERT_EQ(0, pl2.freqTables[pl.COARSE].maxHits);
    /*
    PointList::FrequencyList2DConstIter ii = fd1->frequencyListPtr->begin();
    while(ii != fd1->frequencyListPtr->end()){

        cout << (ii->first).val[0] <<"," << (ii->first).val[1]<< "  " << ii->second <<endl;
        ii++;
    }
     */
//    ASSERT_EQ(2, fd1->minHits);
}

TEST_F(PointListTestSuite, addFrequencyList){
    emu::utility::PointList pl;

    int n=100;
    for(int i=0; i<n;i++){
        Point2D pt(i, 0.0);
        pl.addPoint(pt);
    }

    pl.convert(500);

  //  ASSERT_EQ(2, pl.freqTables.size());
 //   ASSERT_TRUE(pl.coarseSize() > n-1);

    ofstream outy("pltest.txt", ios_base::out);
    outy<<pl;
    outy.flush(); outy.close();

    ifstream iny("pltest.txt", ios_base::in);
    PointList pl2;
    iny>> pl2;
 //   ASSERT_EQ(2, pl2.freqTables.size());
//    ASSERT_TRUE(pl2.coarseSize() > n-1);

    ofstream outy2("pltest2.txt", ios_base::out);
    outy2<<pl2;
    outy2.flush(); outy2.close();

}

#endif //FUNCTION_UTILITIES_POINTLISTTEST_H
