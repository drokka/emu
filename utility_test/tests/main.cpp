//
// Created by peter on 28/10/15.
//

#include <iostream>

#include "../../utility/Parameter.h"
#include "ParameterTest.h"
#include "IterativeFunction.h"
#include "IterativeFunctionTest.h"
#include "Point2DTest.h"
#include "PointListTest.h"

using namespace std;


using namespace emu::utility;




TEST(parameterA,basictest ) {

    Parameter<int> omega("omega", 7);
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

    delta=0.5;
    ASSERT_TRUE(delta.getValue() == 2);

}
