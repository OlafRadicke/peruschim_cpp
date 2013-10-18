
#include <stdexcept>

#ifndef CORE_PERUSCHIMEXCEPTION_H
#define CORE_PERUSCHIMEXCEPTION_H

/**
 * A exception class. This exception is help full to give more information
 * in the Browser. Tntnet catch this exception and return the error message
 * in the browser.
 */
namespace Core {

    class PeruschimException : public std::runtime_error
    {
        public:

            /**
             * @err_message This message is show in the browser.
             */
            explicit PeruschimException( const std::string& err_message )
                : std::runtime_error( err_message ){}
    };

} // end namespace RouteReverse


#endif
