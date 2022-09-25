//
// Created by peter on 10/05/15.
//

//#include <math.h>
//#include <iostream>
#include "QuiltIcon.h"
#include "GeneratorException.h"

using namespace emu::utility;

const double QuiltIcon::pi = acos(-1);
const double QuiltIcon::p2 = 2 * pi;

void QuiltIcon::generate1(double inputPoint[], double lambda, double alpha, double beta,
                          double gamma, double omega, double ma, double shift=0.5) {
    //shift either 0 or 0.5
    double  sx, sy;

    double xnew;
    double ynew;

    double x = inputPoint[0];
    double y = inputPoint[1];

    sx = sin(p2 * x);
    sy = sin(p2 * y);

    xnew = (lambda + alpha * cos(p2 * y)) * sx - omega * sy + beta * sin(2 * p2 * x) +
           gamma * sin(3 * p2 * x) * cos(2 * p2 * y) + ma * x + shift;
    ynew = (lambda + alpha * cos(p2 * x)) * sy + omega * sx + beta * sin(2 * p2 * y) +
           gamma * sin(3 * p2 * y) * cos(2 * p2 * x) + ma * y + shift;
/***
    if (xnew > 1) {
        xnew = xnew - (int) (xnew);
    }
    else {
        if (xnew < 0) xnew = xnew + (int) (-xnew) + 1;
    }
    if (ynew > 1) {
        ynew = ynew - (int) (ynew);
    }
    else {
        if (ynew < 0) ynew = ynew + (int) (-ynew) + 1;
    }
*********************/
    xnew = std::remainder(xnew, 1.0);
    ynew = std::remainder(ynew, 1.0);
    inputPoint[0] = xnew;
    inputPoint[1] = ynew;
}

/**************
void QuiltIcon::setParameters(double *const pDouble) {

    if (pDouble != nullptr) {
        lambda = *pDouble;
    }
    if (pDouble != nullptr) {
        alpha = *(pDouble + 1);
    }
    if (pDouble != nullptr) {
        beta = *(pDouble + 2);
    }
    if (pDouble != nullptr) {
        gamma = *(pDouble + 3);
    }
    if (pDouble != nullptr) {
        omega = *(pDouble + 4);
    }
    if (pDouble != nullptr) {
        ma = *(pDouble + 5);

    }

}
****************************/

/************
QuiltIcon::QuiltIcon() : Icon(6, 0) {
    pi = acos(-1); p2 = 2*pi;

    genFunc = &(QuiltIcon::generate1);
}

QuiltIcon::QuiltIcon(int numberParameters) : Icon(numberParameters, 0) {
    pi = acos(-1); p2 = 2*pi;

    genFunc = &(QuiltIcon::generate1);
}

QuiltIcon::QuiltIcon(const std::tuple<Params ...> &parameters) : IterativeFunctionBase(parameters) {

}
 ***********/
/*******
void QuiltIcon::operator()(double *input, double **output) {
    IterativeFunctionBase::operator()(input, output);
}

void QuiltIcon::UnrolledFunction(std::tuple &tuple, double *input, double **output) {
    generate1((std::get<0>(tuple)., )
}
*****************/

void QuiltIcon::iterFunction(double *input, Parameter<double> lambda, Parameter<double> alpha,
                             Parameter<double> beta,Parameter<double> gamma,Parameter<double> omega,Parameter<double> ma, Parameter<int> degSymPeriod) {

    switch (quiltType) {
        case QuiltType::SQUARE:
            generate1(input, lambda.getValue(), alpha.getValue(), beta.getValue(), gamma.getValue(),
                      omega.getValue(), ma.getValue());
            break;
        case QuiltType::HEX:
            generateHex(input, lambda.getValue(), alpha.getValue(), beta.getValue(), gamma.getValue(),
                        omega.getValue(), ma.getValue(), degSymPeriod.getValue());
            break;
        case QuiltType::FRACTAL:
            generateFractal(input, lambda.getValue(), alpha.getValue(), beta.getValue(), gamma.getValue(),
                            omega.getValue(), ma.getValue(), degSymPeriod.getValue());
    }
}

void QuiltIcon::setValue(double _lambda, double _alpha, double _beta, double _gamma, double _omega, double _ma) {
    std::get<0>(stored_inputs)->setValue(_lambda);

    std::get<1>(stored_inputs)->setValue(_alpha);
    std::get<2>(stored_inputs)->setValue(_beta);
    std::get<3>(stored_inputs)->setValue(_gamma);
    std::get<4>(stored_inputs)->setValue(_omega);

    std::get<5>(stored_inputs)->setValue(_ma);
}

void QuiltIcon::generateHex(double *inputPoint, double lambda, double alpha, double beta, double gamma, double omega,
                            double ma, int nperiod) {

  //  double pi = cos(-1);
   // double p2 = 2 * pi;

   // int nperiod = 6;
    int HALFnperiod = nperiod / 2.0;
    double sx, sy, x, y;
    double xnew, ynew, sq3 = pow(3, .5);

    x = inputPoint[0];
    y = inputPoint[1];

    double k11 = 1.0, k12 = 0.0, k21 = .5, k22 = sq3 / 2,
            el11 = 1, el12 = -1 / sq3,
            el21 = 0, el22 = 2 / sq3,
            el31 = -(el11 + el21), el32 = -(el12 + el22),
            em11 = 2 * el11 + el21,
            em12 = 2 * el12 + el22,
            em21 = 2 * el21 + el31,
            em22 = 2 * el22 + el32,
            em31 = 2 * el31 + el11,
            em32 = 2 * el32 + el12,

            en11 = 3 * el11 + 2 * el21,
            en12 = 3 * el12 + 2 * el22,
            en21 = 3 * el21 + 2 * el31,
            en22 = 3 * el22 + 2 * el32,
            en31 = 3 * el31 + 2 * el11,
            en32 = 3 * el32 + 2 * el12,

            enh11 = 3 * el11 + el21,
            enh12 = 3 * el12 + el22,
            enh21 = 3 * el21 + el31,
            enh22 = 3 * el22 + el32,
            enh31 = 3 * el31 + el11,
            enh32 = 3 * el32 + el12,
            a11 = beta, a12 = gamma,
            a21 = (-a11 - sq3 * a12) / 2.0,
            a22 = (sq3 * a11 - a12) / 2.0,
            a31 = -a11 - a21,
            a32 = -a12 - a22,
            ah11 = a11, ah12 = -a12,
            ah21 = (-ah11 - sq3 * ah12) / 2.0,
            ah22 = (sq3 * ah11 - ah12) / 2.0,
            ah31 = -ah11 - ah21,
            ah32 = -ah12 - ah22;

    double s11, s12, s13, s21, s22, s23, s31, s32, s33, s3h1, s3h2, s3h3, by, bx;

    s11 = sin(p2 * (el11 * x + el12 * y));
    s12 = sin(p2 * (el21 * x + el22 * y));
    s13 = sin(p2 * (el31 * x + el32 * y));
    s21 = sin(p2 * (em11 * x + em12 * y));
    s22 = sin(p2 * (em21 * x + em22 * y));

    s23 = sin(p2 * (em31 * x + em32 * y));
    s31 = sin(p2 * (en11 * x + en12 * y));
    s32 = sin(p2 * (en21 * x + en22 * y));
    s33 = sin(p2 * (en31 * x + en32 * y));

    s3h1 = sin(p2 * (enh11 * x + enh12 * y));
    s3h2 = sin(p2 * (enh21 * x + enh22 * y));
    s3h3 = sin(p2 * (enh31 * x + enh32 * y));

    sx = el11 * s11 + el21 * s12 + el31 * s13;
    sy = el12 * s11 + el22 * s12 + el32 * s13;

    xnew = ma * x + lambda * sx - omega * sy;
    ynew = ma * y + lambda * sy + omega * sx;

    xnew = xnew + alpha * (em11 * s21 + em21 * s22 + em31 * s23);
    ynew = ynew + alpha * (em12 * s21 + em22 * s22 + em32 * s23);

    xnew = xnew + a11 * s31 + a21 * s32 + a31 * s33;
    ynew = ynew + a12 * s31 + a22 * s32 + a32 * s33;

    xnew = xnew + ah11 * s3h1 + ah21 * s3h2 + ah31 * s3h3;
    ynew = ynew + ah12 * s3h1 + ah22 * s3h2 + ah32 * s3h3;
    by = 2 * ynew / sq3;
    bx = xnew - by / 2.0;

    bx = std::remainder(bx, 1.0);
    by = std::remainder(by, 1.0);

    xnew = bx * k11 + by * k21;
    ynew = bx * k12 + by * k22;

//    for (int i = -HALFnperiod -1; i <  HALFnperiod +2 ; i++){
//	for (int j = 0 ; j < nperiod  +1  ; j++){
//		xx.xPix = XPixFuncQ(x + i * k11 + j * k21);          // (NumXPixel  * x / Info.degreeSym )

//			xx.yPix = YPixFuncQ(y + i * k12 + j * k22);
/*****			 AddPixelQ(x,y); *******/

    inputPoint[0] = xnew;
    inputPoint[1] = ynew;

}

void QuiltIcon::generateFractal(double *inputPoint, double lambda, double alpha, double beta, double gamma,
                                double omega, double ma, int  degSym) {
    //first get needed trig constants:
    double PI = acos(-1);
    int n = degSym;// Info.degreeSym;
    int m;

    double a11, a12, a22, a21, b1, b2;
    a11 = lambda;
    a12 = alpha;
    a21 = beta;
    a22 = gamma;
    b1 = omega;
    b2 = ma;

    // Need to be a contraction affine map. NOT any of:
    //a11^2 + a21^2 > 1
    //a21^2 + a22^2 >1
    // a11^2 + a21^2 +   a21^2 + a22^2 > 1 + (a11*a22 - a21*a12)^2
    double a1 = a11*a11 + a21*a21;
    double a2 = a21*a21 + a22*a22;
    if(a1 >1 || a2 >1 || (a1+a2 ) > 1 + ((a11*a22 - a21*a12)*(a11*a22 - a21*a12))){
        cout <<"error not a contraction" <<endl;
        throw GeneratorException("Generate fractal parameters not a contraction");
    }

    double x = inputPoint[0];
    double y = inputPoint[1];

    if (n >=128 ) n=127;
    double c[128]; //= new double[128];   //degree sym assumed < 128
    double s[128]; //= new double[128];
    for (int i = 0; i < n; i++) {
        double angle = 2 * PI * i / n;
        c[i] = cos(angle);
        s[i] = sin(angle);
    }
    double xnew, ynew, x1, y1;
//Info.numberSteps +=1;
    xnew = a11 * x + a12 * y + b1;
    ynew = a21 * x + a22 * y + b2;
    m =  (rand()%n);
    if (m < 0) { m = 0 - m; }
    x1 = xnew;
    y1 = ynew;
    xnew = c[m] * x1 - s[m] * y1;
    ynew = s[m] * x1 + c[m] * y1;

    //  if (Info.CONJ == true) {
    //
    if (rand()%2 == 0) ynew = -ynew; //FIXIT pass in CONJ!!!!!!!!!!!!!
    // }
    double xnewMod = (xnew );
    double ynewMod = (ynew );

    inputPoint[0] = xnewMod; //<1?xnewMod:1.0; //(xnew + .5)*0.96;  //hack scale down to avoid out of range... hopefully
    inputPoint[1] = ynewMod; // <1? ynewMod: 1.0; // (ynew + .5)*0.96;


  //  if(inputPoint[0] >=1 || inputPoint[1] >=1){
  //      cout << "exploding " << inputPoint[0] << " " << inputPoint[1] <<endl;
      //  throw ( MATH_ERREXCEPT) ;
   // }
//    cout << "x: " << inputPoint[0] <<" y: " << inputPoint[1] <<endl;
}

//public static void  getIconDefault(Parameters pp) {
/***
	 Info.ICON = 1;
    Info.L = -1.8;	 Info.A = 2; Info.B = 0; Info.G  = 1; Info.O = 0;
						Info.b2 = 0; Info.degreeSym  = 3; Info.scale  = 1;
						startX  = .01; startY  = .003;
						x  = startX; y  = startY;
Info.numberSteps  = 0;  Info.MaxHits  = 1;

   currentHP.xPix  = 0; 	currentHP.yPix  = 0;  currentHP.Hits  = 0;

    pp.aA=2; pp.bB=0; pp.gG=1; pp.oO=0.01;
    pp.degreeSym=4; pp.scale=1;
    pp.lL=-1.8;

}******/


std::ostream& operator<<(std::ostream &ostream1, const emu::utility::QuiltIcon::QuiltType& quiltType) {
    using namespace std;
    using namespace emu::utility;
    switch (quiltType) {
        case emu::utility::QuiltIcon::QuiltType::SQUARE:
            ostream1 << 0;
            break;
        case QuiltIcon::QuiltType::HEX:
            ostream1 << 1;
            break;
        case QuiltIcon::QuiltType::FRACTAL:
            ostream1 << 2;
            break;
    }
    return ostream1;
}
std::istream& operator>>(std::istream &input, emu::utility::QuiltIcon::QuiltType& quiltType){
    int readValue;
    input >> readValue;
    switch (readValue) {
        case 0: quiltType = emu::utility::QuiltIcon::QuiltType::SQUARE; break;
        case 1: quiltType = emu::utility::QuiltIcon::QuiltType::HEX; break;
        case 2: quiltType = emu::utility::QuiltIcon::QuiltType::FRACTAL; break;
        default: quiltType = emu::utility::QuiltIcon::QuiltType::SQUARE;
    }
   return input ;
}

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::QuiltIcon& quiltIcon) {
    using namespace std;
    using namespace emu::utility;
    ostream1<< quiltIcon.quiltType <<" "
     << quiltIcon.lambda->getValue()<<" " << quiltIcon.alpha->getValue()<<" " << quiltIcon.beta->getValue()<<" "
            << quiltIcon.gamma->getValue()<<" " << quiltIcon.omega->getValue()<<" " << quiltIcon.ma->getValue()<<" "
            <<quiltIcon.degSym->getValue()<<" ";

    return ostream1;
}

std::istream& operator>>(std::istream &input, emu::utility::QuiltIcon& quiltIcon){
    using namespace std;
    using namespace emu::utility;
    input >> quiltIcon.quiltType;
    double readVal;
    input >> readVal;
    quiltIcon.lambda->setValue(readVal);
    input >> readVal;
    quiltIcon.alpha->setValue(readVal);
    input >> readVal;
    quiltIcon.beta->setValue(readVal);
    input >> readVal;
    quiltIcon.gamma->setValue(readVal);
    input >> readVal;
    quiltIcon.omega->setValue(readVal);
    input >> readVal;
    quiltIcon.ma->setValue(readVal);

    int degSym;
    input >> degSym;
    quiltIcon.degSym->setValue(degSym);

    return input;
}

