//
// Created by peter on 11/10/15.
//

#ifndef FUNCTION_UTILITIES_PARAMETER_H
#define FUNCTION_UTILITIES_PARAMETER_H

#include <limits>
#include <cmath>
#include <string.h>
#include <type_traits>
#include <string>

namespace emu {
    namespace utility {


        template<class NumericType>
        class Parameter {
        private:
            NumericType _min;
            NumericType _max;
            bool includesMin;
            bool includesMax;
            std::string name;
            NumericType value;

        public:

            //constructors
            Parameter() : name("noname"), value(0), includesMax(true),
                          includesMin(true),
                          _max(std::numeric_limits<NumericType>::max()),
                          _min(std::numeric_limits<NumericType>::min()) { }

            Parameter(const std::string name, NumericType _val, const NumericType _min, const NumericType _max,
                      const bool includesMin, const bool includesMax) : _min(std::min(_min, _max)), _max(std::max(_min, _max)), includesMin(includesMin),
                                                                        includesMax(includesMax),
                                                                        name(name) {
                 setValue(_val);
            }

            Parameter(const std::string name, NumericType _val, const NumericType _min, const NumericType _max) :
                    _min(std::min(_min, _max)), _max(std::max(_min, _max)), includesMin(true), includesMax(true) {
                setValue(_val);
            }

            Parameter(const std::string name, NumericType value) : name(name), value(value), includesMax(false),
                                                                   includesMin(false),
                                                                   _max(std::numeric_limits<NumericType>::max()),
                                                                   _min(std::numeric_limits<NumericType>::min()) { }

            explicit Parameter(const std::string name) : name(name), value(0), includesMax(false),
                                                         includesMin(false),
                                                         _max(std::numeric_limits<NumericType>::max()),
                                                         _min(std::numeric_limits<NumericType>::min()) { }

            Parameter(const Parameter<NumericType> &p) : _min(p._min), _max(p._max), includesMax(p.includesMax),
                                                         includesMin(p.includesMin), name(p.name), value(p.value) { }

            ~Parameter(){

            }
            // operators

            explicit operator NumericType() const { return value; }

            Parameter<NumericType> &operator=(NumericType val) {
                setValue(val);
                return *this;
            }

            Parameter<NumericType> &operator=(Parameter<NumericType> const &parameter) {
                value = parameter.getValue();
                name = parameter.getName();
                includesMin = parameter.includesMin;
                includesMax = parameter.includesMax;
                _max = parameter._max;
                _min = parameter._min;
                return *this;
            }

            Parameter<NumericType>& operator=(Parameter<NumericType>&& parameter)  noexcept {
                value = parameter.getValue();
                name = parameter.getName();
                includesMin = parameter.includesMin;
                includesMax = parameter.includesMax;
                _max = parameter._max;
                _min = parameter._min;
                return *this;
            }

            NumericType getValue() const {
                return value;
            }

            std::string getName() const { return name; }

            NumericType getMax() const { return _max;}

            NumericType getMin( ) const {return _min;}

            /* set to supplied value if in range, else to smallest or largest value in the range. */
            void setValue(NumericType _value) {
                if ((_min < _value && _value < _max) || (includesMin && _min == _value) || (includesMax && _max == _value)) {
                    Parameter::value = _value;
                }
                else if(_value < _min){
                    if(includesMin){
                        value = _min;
                    }
                    else{
                        if (std::is_floating_point<NumericType>::value) {
                            //value = std::nextafter(_min, _max); /*closest to min */
                            value = _min + (_max -_min)/1000000.0;
                        }
                        else { /* is integer type */
                            value = _min + 1;
                        }
                    }
                }
                else if(_value > _max){
                    if(includesMax){
                        value = _max;
                    }
                    else{
                        if (std::is_floating_point<NumericType>::value) {
                            //value = std::nextafter<NumericType>(_max, _min); /*closest to max */
                            value = _max - (_max - _min)/1000000.0;
                        }
                        else { /* is integer type */
                            value = _max - 1;
                        }
                    }
                }
                else if(_value == _min) {
                    if (std::is_floating_point<NumericType>::value) {
                        //value = std::nextafter<NumericType>(_min, _max); /*closest to min */
                        value = _min + (_max -_min)/1000000.0;

                    }
                    else {
                        Parameter::value = _min + 1;
                    }
                }
                else{ /*equals max and not includesMax */
                    if (std::is_floating_point<NumericType>::value) {
                        //value = std::nextafter<NumericType>(_max, _min); /*closest to max */
                        value = _max - (_max - _min)/1000000.0;

                    }
                    else {
                        Parameter::value = _max - 1;
                    }
                }
            }

        };


    }
}

#endif //FUNCTION_UTILITIES_PARAMETER_H
