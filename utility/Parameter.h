//
// Created by peter on 11/10/15.
//

#ifndef FUNCTION_UTILITIES_PARAMETER_H
#define FUNCTION_UTILITIES_PARAMETER_H

#include <limits>
#include <cmath>
#include <string.h>

namespace doc {
    namespace utility {


        template<class NumericType>
        class Parameter {
        private:
            NumericType min;
            NumericType max;
            bool includesMin;
            bool includesMax;
            std::string name;
            NumericType value;

        public:

            //constructors
            Parameter() : name("noname"), value(0), includesMax(true),
                          includesMin(true),
                          max(std::numeric_limits<NumericType>::max()),
                          min(std::numeric_limits<NumericType>::min()) { }

            Parameter(const std::string name, NumericType _val, const NumericType _min, const NumericType _max,
                      const bool includesMin, const bool includesMax) : min(std::min(_min,_max)), max(std::max(_min,_max)), includesMin(includesMin),
                                                                   includesMax(includesMax),
                                                                   name(name) {
                 setValue(_val);
            }

            Parameter(const std::string name, NumericType _val, const NumericType _min, const NumericType _max) :
                    min(std::min(_min,_max)), max(std::max(_min,_max)), includesMin(true),includesMax(true) {
                setValue(_val);
            }

            Parameter(const std::string name, NumericType value) : name(name), value(value), includesMax(false),
                                                                   includesMin(false),
                                                                   max(std::numeric_limits<NumericType>::max()),
                                                                   min(std::numeric_limits<NumericType>::min()) { }

            Parameter(const std::string name) : name(name), value(0), includesMax(false),
                                                includesMin(false),
                                                max(std::numeric_limits<NumericType>::max()),
                                                min(std::numeric_limits<NumericType>::min()) { }

            Parameter(const Parameter<NumericType> &p) : min(p.min), max(p.max), includesMax(p.includesMax),
                                                         includesMin(p.includesMin), name(p.name), value(p.value) { }

            ~Parameter(){

            }
            // operators

            operator NumericType() const { return value; }

            Parameter<NumericType> &operator=(NumericType val) {
                setValue(val);
                return *this;
            }

            Parameter<NumericType> &operator=(Parameter<NumericType> &parameter) {
                value = parameter.getValue();
                name = parameter.getName();
                includesMin = parameter.includesMin;
                includesMax = parameter.includesMax;
                max = parameter.max;
                min = parameter.min;
                return *this;
            }

            Parameter<NumericType>& operator=(Parameter<NumericType>&& parameter) {
                value = parameter.getValue();
                name = parameter.getName();
                includesMin = parameter.includesMin;
                includesMax = parameter.includesMax;
                max = parameter.max;
                min = parameter.min;
                return *this;
            }

            NumericType getValue() const {
                return value;
            }

            std::string getName() const { return name; }

            NumericType getMax() const { return max;}

            NumericType getMin( ) const {return min;}

            /* set to supplied value if in range, else to smallest or largest value in the range. */
            void setValue(NumericType _value) {
                if ((min < _value && _value < max) || (includesMin && min == _value) || (includesMax && max == _value)) {
                    Parameter::value = _value;
                }
                else if(_value < min){
                    if(includesMin){
                        value = min;
                    }
                    else{
                        if (!std::numeric_limits<NumericType>::is_integer) {
                            value = std::nextafter(min, max); /*closest to min */
                        }
                        else { /* is integer type */
                            value = min + 1;
                        }
                    }
                }
                else if(_value > max){
                    if(includesMax){
                        value = max;
                    }
                    else{
                        if (!std::numeric_limits<NumericType>::is_integer) {
                            value = std::nextafter<NumericType>(max, min); /*closest to max */
                        }
                        else { /* is integer type */
                            value = max - 1;
                        }
                    }
                }
                else if(_value == min) {
                    if (!std::numeric_limits<NumericType>::is_integer) {
                        value = std::nextafter<NumericType>(min,  max); /*closest to min */
                    }
                    else {
                        Parameter::value = min + 1;
                    }
                }
                else{ /*equals max and not includesMax */
                    if (!std::numeric_limits<NumericType>::is_integer) {
                        value = std::nextafter<NumericType>(max,  min); /*closest to min */
                    }
                    else {
                        Parameter::value = max - 1;
                    }
                }
            }

        };


    }
}

#endif //FUNCTION_UTILITIES_PARAMETER_H
