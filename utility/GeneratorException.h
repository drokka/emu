//
// Created by peter on 18/09/2022.
//

#ifndef FUNCTION_UTILITIES_GENERATOREXCEPTION_H
#define FUNCTION_UTILITIES_GENERATOREXCEPTION_H
#include <string>
namespace emu {
    namespace utility {

        class GeneratorException: std::exception {
        public:
            GeneratorException(std::string basicString) {
                message = basicString;
            }

            std::string message;
        };

    } // emu
} // utility

#endif //FUNCTION_UTILITIES_GENERATOREXCEPTION_H
