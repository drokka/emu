//
// Created by peter on 21/11/15.
//

#ifndef FUNCTION_UTILITIES_POINT2DTEST_H
#define FUNCTION_UTILITIES_POINT2DTEST_H

#include <set>
#include <PointList.h>
#include "../../utility/Point2D.h"
#include "../../utility/IntegerPoint2D.h"
#include "../../utility/PointList.h"

#include "../gtest/gtest-1.7.0/include/gtest/gtest.h"

using namespace emu::utility;

class Point2DTestSuite:  public ::testing::Test {

public:
    Point2D p0, p1, p2, p3;
    Point2D q = Point2D(-99.9, 3.5);
    std::multiset<Point2D, Point2D> list;

    IntegerPoint2D ip0, ip1, ip2, ip3, ip4;
    IntegerPoint2D iq = IntegerPoint2D(-10,-23);

    std::multiset<IntegerPoint2D, IntegerPoint2D> iList;

protected:
    virtual void SetUp(){
        p2.val[0] =1.7;  p2.val[1] = 2.2;
        p3.val[0] = 1.7; p3.val[1] = 2.9;
        list.insert(p3);
        list.insert(p1);
        list.insert(p0);
        list.insert(p2);
    }
};


TEST_F(Point2DTestSuite, testPoint){
    ASSERT_TRUE(p0.val[0] ==0 && p0.val[1] ==0);
    ASSERT_TRUE(ip0.val[0] ==0 && ip0.val[1] ==0);
ASSERT_TRUE(q.val[1]== 3.5);
    ASSERT_TRUE(iq.val[0] == -10);
}

TEST_F(Point2DTestSuite, testPoint2DOrder){

    std::multiset<Point2D, Point2D>::const_iterator i = list.begin();

    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE( i->val[0] == 0); i++;
    ASSERT_TRUE( i->val[0] == 0); i++;
    ASSERT_TRUE( i->val[1] == 2.2); i++;
    ASSERT_TRUE( i->val[1] == 2.9); i++;
}

TEST_F(Point2DTestSuite, testPoint2IntegerPoint){
    Point2D point = p3;

    IntegerPoint2D ipt = IntegerPoint2D(point);
    ASSERT_TRUE(ipt.val[0] == 1);  //Is floor accurate enough?
    ASSERT_TRUE(ipt.val[1] == 2);

    PointList::FrequencyList2D  iList;


    iList.insert(make_pair(IntegerPoint2D(21,25), 11));

    iList.insert(make_pair(ipt, 13));

    ASSERT_TRUE(iList.begin()->second == 13);


}

TEST_F(Point2DTestSuite, testPointList1){
    PointList points1;
    points1.addPoint(p3);
    points1.addPoint(p3);

    ASSERT_TRUE(points1.freqTables.size() ==1);
    ASSERT_TRUE(points1.rawList->size() == 2);

    //Frequency table for COARSE scale added by default.
    ASSERT_TRUE(points1.freqTables[points1.COARSE]->scale == points1.COARSE);
    shared_ptr<PointList::FrequencyData> frequencyData = points1.freqTables[points1.COARSE];
    shared_ptr<PointList::FrequencyList2D> fl = frequencyData->frequencyListPtr;
    ASSERT_EQ(fl->size() , 1);
    ASSERT_EQ(fl->begin()->second,2);
    ASSERT_EQ(frequencyData->maxHits, 2);
}
#endif //FUNCTION_UTILITIES_POINT2DTEST_H
