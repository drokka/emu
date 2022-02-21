//
// Created by peter on 10/05/15.
//

#ifndef QUILT_QUILTICON_H
#define QUILT_QUILTICON_H


//#include <math.h>
#include <tuple>
#include <functional>
#include "Parameter.h"
#include "IterativeFunction.h"
#include <ostream>
#include <istream>
#include <iostream>


using namespace emu::utility;

namespace emu {
    namespace utility {

        class QuiltIcon
                : public IterativeFunction<Parameter<double>, Parameter<double>, Parameter<double>, Parameter<double>,
                        Parameter<double>, Parameter<double> , Parameter<int>> {

            typedef Parameter<double> P_t;
            typedef Parameter<int> I_t;
            typedef std::tuple<Parameter<double>, Parameter<double>, Parameter<double>, Parameter<double>,
                    Parameter<double>, Parameter<double> , Parameter<int> > Pt_t;


        public:
            enum class QuiltType {
                SQUARE, HEX, FRACTAL
            };
            QuiltType quiltType = QuiltType::SQUARE;
            const static double pi;
            const static double p2;

            QuiltIcon(): QuiltIcon(0.1,0.1,0.1,0.1,0.1,0.1, 3, QuiltType::SQUARE){};

        public:
            QuiltIcon(const double _lambda, const double _alpha, const double _beta, const double _gamma,
                      const double _omega,
                      const double _ma, const int _degSym, QuiltType quiltType) :
                    lambda{new P_t("lambda", _lambda)}, alpha{new P_t("alpha", _alpha)},
                    beta{new P_t("beta", _beta)}, gamma{new P_t("gamma", _gamma)}, omega{new P_t("omega", _omega)},
                    ma{new P_t("ma", _ma)}, degSym{new I_t("degSym", _degSym)}, quiltType(quiltType) {

                stored_inputs = make_tuple(shared_ptr<P_t>(lambda), shared_ptr<P_t>(alpha), shared_ptr<P_t>(beta),
                                           shared_ptr<P_t>(gamma),
                                           shared_ptr<P_t>(omega), shared_ptr<P_t>(ma), shared_ptr<I_t>(degSym));
                //  parameters = std::make_tuple(lambda,alpha,beta,gamma,omega,ma);
                //   IterativeFunction(*())
           }

            QuiltIcon(QuiltIcon &qi) : IterativeFunction<P_t, P_t, P_t, P_t, P_t, P_t, I_t>(qi) { }

            QuiltIcon &operator=(QuiltIcon &qi) { return *this; }

      //  private:
// double _lambda, alpha, beta, gamma, omega, ma;
            shared_ptr<Parameter<double> > lambda, alpha, beta, gamma, omega, ma;
            shared_ptr<Parameter<int>> degSym;


        public:
            //       virtual void iterFunction(double *input, double **output, ) override;

            virtual void iterFunction(double *input, Parameter<double> lambda, Parameter<double> alpha,
                                      Parameter<double> beta, Parameter<double> gamma, Parameter<double> omega,
                                      Parameter<double> ma, Parameter<int> degSymPeriod);
//
//        virtual void setParameters(double *const pDouble);

            virtual void setValue(double _lambda, double _alpha, double _beta, double _gamma, double _omega,
                                  double _ma);

            static void generate1(double inputPoint[], double lambda, double alpha, double beta, double gamma,
                                  double omega, double ma);

            static void
            generateHex(double *inputPoint, double lambda, double alpha, double beta, double gamma, double omega,
                        double ma, int nperiod);

            void
            generateFractal(double *inputPoint, double lambda, double alpha, double beta, double gamma, double omega,
                            double ma, int degSym);
        };
    }
}


std::ostream& operator<<(std::ostream &ostream1, const emu::utility::QuiltIcon::QuiltType& quiltType) ;
std::istream& operator>>(std::istream &input, emu::utility::QuiltIcon::QuiltType& quiltType);

std::ostream& operator<<(std::ostream &ostream1, const emu::utility::QuiltIcon& quiltIcon) ;
std::istream& operator>>(std::istream &input, emu::utility::QuiltIcon& quiltIcon);



#endif //QUILT_QUILTICON_H
