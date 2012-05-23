#ifndef CODEWRITER_H_INCLUDED
#define CODEWRITER_H_INCLUDED

#include <fstream>
#include <iostream>


using namespace std;

class CodeWriter{
    public:
        CodeWriter(ostream& out);
        void writeCode(pair <int, int>);
        void flush();
    private:
        ostream &out;
        int value, size;
};
#endif // CODEWRITER_H_INCLUDED
