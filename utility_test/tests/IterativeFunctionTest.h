//
// cunit test fixture from template
//

#ifndef IterativeFunction_TEST_H
#define IterativeFunction_TEST_H

#include "../gtest/gtest-1.7.0/include/gtest/gtest.h"

#include "../../utility/IterativeFunction.h"

class IntHolder {
public:
    int val = 2;
};

class IterFuncA: public IterativeFunction<IntHolder>{

public:
   // IntHolder intHolder;
 //   IterFuncA(int i){ intHolder.val = i;}
    IterFuncA(){};

    IterFuncA(shared_ptr<IntHolder> ih){stored_inputs = make_tuple(shared_ptr<IntHolder>(ih));}

    IterFuncA(IterFuncA& iterFuncA):IterativeFunction<IntHolder>(iterFuncA){}

    IterFuncA& operator = (IterFuncA& iterFuncA1){
     //   this->intHolder = iterFuncA1.intHolder;
        return *this;
    }

   void  setValue(int i){ std::get<0>(stored_inputs)->val = i;}

    virtual void iterFunction(double *input, IntHolder ih){ (*input) = ih.val* (*input);}
};

class IFAccumulate: public IterativeFunction<IntHolder>{
public:
    IFAccumulate(){};
    IFAccumulate(shared_ptr<IntHolder> ih){stored_inputs = make_tuple(shared_ptr<IntHolder>(ih));}
    IFAccumulate(IFAccumulate& ifa):IterativeFunction<IntHolder>(ifa){}

    IFAccumulate&operator = (IFAccumulate& ifa){ return  *this;}

    void setValue(int i) { std::get<0>(stored_inputs)->val = i;}

    virtual void iterFunction(double *input, IntHolder ih){ (*input) = (*input) + ih.val* (*input);}
};

class DoubleHolderA: public Parameter<double> {
public:
    DoubleHolderA():Parameter<double >("delta",357.7){}
};

class IterFuncTriple: public IterativeFunction<IntHolder, DoubleHolderA>{

public:
   // IntHolderB intHolder;
    //   IterFuncA(int i){ intHolder.val = i;}
 //   IterFuncB(){};
    IterFuncTriple(shared_ptr<IntHolder> param, shared_ptr<DoubleHolderA> x){stored_inputs = make_tuple(shared_ptr<IntHolder>(param), shared_ptr<DoubleHolderA>(x));}

    IterFuncTriple(IterFuncTriple& iterFuncTriple):IterativeFunction<IntHolder, DoubleHolderA>(iterFuncTriple){}


    IterFuncTriple& operator = (IterFuncTriple& iterFuncTriple1){
        this->stored_inputs = iterFuncTriple1.stored_inputs;
        return *this;
    }
    virtual void iterFunction(double *in, IntHolder ih, DoubleHolderA delta) {
        (*in) = (ih.val +delta.getValue())* (*in);
    }
    virtual void setValue(int i, double x){ std::get<0>( stored_inputs)->val = i; std::get<1>( stored_inputs)->setValue(x);}
};

class IterativeFunctionTest : public ::testing::Test {

public:
    IterativeFunction<int> *objIterativeFunction;
    IterFuncA *ifunc;
    IterFuncTriple *if3;
    std::shared_ptr<IntHolder> alpha;
    shared_ptr<DoubleHolderA> dubbly;


    virtual void SetUp() {
        objIterativeFunction = new IterativeFunction<int>();
        alpha = std::shared_ptr<IntHolder>(new IntHolder());
        ifunc = new IterFuncA(alpha);

        dubbly = shared_ptr<DoubleHolderA>(new DoubleHolderA());
        if3 = new IterFuncTriple(alpha, dubbly);
    }

    virtual void TearDown() {
        delete objIterativeFunction;
        delete if3;
        delete ifunc;
    }
};

    TEST_F(IterativeFunctionTest, testConstructors) {
        double val = 0.1;
        double * in ;
        double *outval = (double*) malloc(sizeof(double)*2);
        outval[0]= 0.5; outval[1]= 77;
        double **out1 = &outval;
        in = &val;
        (*objIterativeFunction) (in);
        ASSERT_TRUE(**out1 ==0.5);

        (*ifunc)(in);
        ASSERT_TRUE(*in ==0.2);

        cout <<"in "<< *in <<endl;
 //       (*ifunc)(in,out1);

        //alpha->val = 3;
       ifunc->setValue(3);
        ifunc->operator()(in);
      //  cout << "out1 should be .3 "<< **out1 <<endl;
        ASSERT_TRUE(*in >= 0.6 &&(*in <0.7));

        if3->setValue(7, 1.5);
        if3->operator()(in);
       // cout << "out1 "<< **out1 <<endl;
        ASSERT_TRUE(*in > 5 && (*in < 5.2));
  //  ASSERT_TRUE(*in == 5.1);
        if3->setValue(0, .3);
        if3->operator()(in);
        cout << "out1 "<< *in <<endl;
        ASSERT_TRUE(*in < 2);

        free(outval);
    }

TEST_F(IterativeFunctionTest, testAccumulate){
    double in = 3.0;
   // double *outval = (double*) malloc(sizeof(double)*2);

    IFAccumulate ifa;
    ifa.setValue(1);

    ifa.operator()(&in);
    ASSERT_TRUE((int)(in) == 6);

    ifa.operator()(&in);
    ASSERT_TRUE((int)(in) == 12);

    ifa.operator()(&in);
    ASSERT_TRUE((int)(in) == 24);

    ifa.setValue(3);
    in=1;
    ifa.operator()(&in);
    ASSERT_TRUE((int)(in) == 4);

    ifa.operator()(&in);
    ASSERT_TRUE((int)(in) == 16);

}

#endif
