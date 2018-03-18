//
// Created by peter on 11/10/15.
//

#ifndef FUNCTION_UTILITIES_PARAMETERTEST_H
#define FUNCTION_UTILITIES_PARAMETERTEST_H

#include "../gtest/gtest-1.7.0/include/gtest/gtest.h"


#include "../../utility/Parameter.h"

using namespace emu::utility;

class ParameterTestSuite : public ::testing::Test {

public:
    typedef Parameter<int> PInt;
    typedef Parameter<double> PDouble;


    PInt *omega;
    PInt *delta;
    PInt *aa;
    PInt *bb;

    PDouble *alpha;
    PDouble *beta;


protected:
    virtual void SetUp() {

        omega = new PInt("omega", 7);
        delta = new PInt("delta", 7, 1, 10, false, false);

        alpha = new PDouble();

        aa = new PInt("aa", 17, -10, 10);
        bb = new PInt(*aa);

        beta = new PDouble("BETA");
    }


    virtual void TearDown() {
        delete omega;
        delete delta;
        delete alpha;
        delete aa;
        delete bb;
        delete beta;
    }
};
    TEST_F(ParameterTestSuite, testCtrs){
        ASSERT_TRUE(aa->getValue() == 10);
    ASSERT_TRUE(bb->getValue() == aa->getValue() && bb->getName() == aa->getName());
    ASSERT_TRUE(beta->getValue() == 0);
    }

TEST_F(ParameterTestSuite,  testSetValue){
        omega->setValue(77);
        ASSERT_TRUE(omega->getValue() == 77);
        omega->setValue(11);
        ASSERT_TRUE(omega->getValue() == 11);
        *delta = 0.5;
        ASSERT_TRUE(delta->getValue() == 2);

        ASSERT_TRUE(alpha->getValue() == 0);
    }

TEST_F(ParameterTestSuite,  testMaxMin) {
        delta->setValue(10);
        ASSERT_TRUE(delta->getValue() == 9); /* max is 10 and not includesMax */
        delta->setValue(111);
        ASSERT_TRUE(delta->getValue() == 9); /* max is 10 and not includesMax */
        delta->setValue(1);
        ASSERT_TRUE(delta->getValue() == 2); /* min is 1 and not includesMin */

  //      alpha->setValue(std::numeric_limits<double>::max());
  //      ASSERT_TRUE(alpha->getValue() < std::numeric_limits<double>::max());  /*  not includesMax so biggest less than max */

    }
TEST_F(ParameterTestSuite,  testName){
        ASSERT_TRUE(omega->getName().compare("omega") == 0);
        ASSERT_TRUE(alpha->getName() == "noname");
    }


#endif //FUNCTION_UTILITIES_PARAMETERTEST_H
