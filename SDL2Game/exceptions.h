#ifndef _CC_EXCEPTIONS_H_
#define _CC_EXCEPTIONS_H_

#include <string>

namespace cc{
    class Exception{
    public:
        Exception(const char* error, const char* detail)
            :_error(error), _detail(detail){
            
        }
        ~Exception(){
            
        }
    public:
        std::string getError() const{
            return this->_error + this->_detail;
        }
    private:
        std::string _error;
        std::string _detail;
    };
};

#endif