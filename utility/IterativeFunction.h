//
// Created by peter on 14/10/15.
//

#ifndef FUNCTION_UTILITIES_ITERATIVEFUNCTION_H
#define FUNCTION_UTILITIES_ITERATIVEFUNCTION_H

#include <tuple>
#include <memory>
#include "Parameter.h"
#include "IterativeFunctionBase.h"
#include "index_sequence.h"

namespace doc {
    namespace  utility{
    using namespace std;

    template<typename... Parameter>
    class IterativeFunction : public IterativeFunctionBase {

    private:
        void execute_uf_wrapped(double *inout){
            return UnrolledFunction(inout, make_index_sequence<sizeof...(Parameter)>{});
        }


    protected:
        tuple<shared_ptr<Parameter>... > stored_inputs = make_tuple(shared_ptr<Parameter>(new Parameter)...);

        template<std::size_t... Is>
        void UnrolledFunction(double *inout, index_sequence<Is...>) {
            return iterFunction(inout,*std::get<Is>(stored_inputs)...); }

        template<std::size_t... Is>
                void unrolledSetValue(index_sequence<Is...>) {
            return setValue(*std::get<Is>(stored_inputs)...);
        }
    public:
        IterativeFunction(){ }
        IterativeFunction(Parameter...){
            stored_inputs = make_tuple(shared_ptr<Parameter>(new Parameter)...);
        }

        IterativeFunction(IterativeFunction& iterF2):stored_inputs(iterF2.stored_inputs){ }

        IterativeFunction& operator = (IterativeFunction& iF2){
            this->stored_inputs = iF2.stored_inputs;
            return *this;
        }

        IterativeFunction& operator = (IterativeFunction&& iF2){
            this->stored_inputs = iF2.stored_inputs;
            return *this;
        }

        virtual void setValue(Parameter...){ }

        virtual void iterFunction(double *inout, Parameter...){ }

        virtual void operator  ()(double *inout) { execute_uf_wrapped(inout); }

        //  unsigned list1(){ return  std::tuple_size<Params... >(parameters);}

    };
}}//namespace
#endif //FUNCTION_UTILITIES_ITERATIVEFUNCTION_H
