#ifndef CODEWRITER_H_INCLUDED
#define CODEWRITER_H_INCLUDED

#include <fstream>


#include "Code.h"


using namespace std;

class CodeWriter{
    public:
        CodeWriter(ostream& out);
        void writeCode(Code);
        void flush();
    private:
        ostream &out;
        int value, size;
};
#endif // CODEWRITER_H_INCLUDED
