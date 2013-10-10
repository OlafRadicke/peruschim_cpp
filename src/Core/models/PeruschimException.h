#include <iostream>
#include <exception>

#ifndef CORE_PERUSCHIMEXCEPTION_H
#define CORE_PERUSCHIMEXCEPTION_H

namespace Core {

    class PeruschimException : public std::exception
    {
        public:
            PeruschimException( const char* err_message ):errMessage( err_message ){}
//             PeruschimException( const std::string err_message ):errMessage( err_message ){}

            const char* what() const throw() { return errMessage; }

        private:
            const char* errMessage;
//             const std::string errMessage;
    };

} // end namespace RouteReverse


#endif
