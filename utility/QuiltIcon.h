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

using namespace emu::utility;

namespace emu {
    namespace utility {

        class QuiltIcon
                : public IterativeFunction<Parameter<double>, Parameter<double>, Parameter<double>, Parameter<double>,
                        Parameter<double>, Parameter<double> > {

            typedef Parameter<double> P_t;
            typedef std::tuple<Parameter<double>, Parameter<double>, Parameter<double>, Parameter<double>,
                    Parameter<double>, Parameter<double> > Pt_t;


        public:
            enum class QuiltType {
                SQUARE, HEX, FRACTAL
            };
            QuiltType quiltType = QuiltType::SQUARE;
            const static double pi;
            const static double p2;

        public:
            QuiltIcon(const double _lambda, const double _alpha, const double _beta, const double _gamma,
                      const double _omega,
                      const double _ma, QuiltType quiltType) :
                    lambda{new P_t("lambda", _lambda)}, alpha{new P_t("alpha", _alpha)},
                    beta{new P_t("beta", _beta)}, gamma{new P_t("gamma", _gamma)}, omega{new P_t("omega", _omega)},
                    ma{new P_t("ma", _ma)}, quiltType(quiltType) {

                stored_inputs = make_tuple(shared_ptr<P_t>(lambda), shared_ptr<P_t>(alpha), shared_ptr<P_t>(beta),
                                           shared_ptr<P_t>(gamma),
                                           shared_ptr<P_t>(omega), shared_ptr<P_t>(ma));
                //  parameters = std::make_tuple(lambda,alpha,beta,gamma,omega,ma);
                //   IterativeFunction(*())
           }

            QuiltIcon(QuiltIcon &qi) : IterativeFunction<P_t, P_t, P_t, P_t, P_t, P_t>(qi) { }

            QuiltIcon &operator=(QuiltIcon &qi) { return *this; }

        private:
// double _lambda, alpha, beta, gamma, omega, ma;
            shared_ptr<Parameter<double> > lambda, alpha, beta, gamma, omega, ma;


        public:
            //       virtual void iterFunction(double *input, double **output, ) override;

            virtual void iterFunction(double *input, Parameter<double> lambda, Parameter<double> alpha,
                                      Parameter<double> beta, Parameter<double> gamma, Parameter<double> omega,
                                      Parameter<double> ma);
//
//        virtual void setParameters(double *const pDouble);

            virtual void setValue(double _lambda, double _alpha, double _beta, double _gamma, double _omega,
                                  double _ma);

            static void generate1(double inputPoint[], double lambda, double alpha, double beta, double gamma,
                                  double omega, double ma);

            static void
            generateHex(double *inputPoint, double lambda, double alpha, double beta, double gamma, double omega,
                        double ma);

            void
            generateFractal(double *inputPoint, double lambda, double alpha, double beta, double gamma, double omega,
                            double ma);
        };
    }
}

#endif //QUILT_QUILTICON_H
