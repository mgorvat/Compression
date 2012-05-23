#include "CodeWriter.h"


void displayCode(pair<int, int> code){
    int buf = 0;
    int val = code.second;
    for(int i = 0; i < code.first; i++){
        buf = (buf<<1) ^ (val & 0x01);
        val = val>>1;
    }
    for(int i = 0; i < code.first; i++){
        cout<<(buf&0x01);
        buf = buf>>1;
    }
    cout<<" ";
}

CodeWriter::CodeWriter(ostream& out): out(out), value(0), size(0){}
void CodeWriter::writeCode(pair<int, int> code){
    if(code.first + size >= 8){
        int buf = 0;
        int val = 0;
        int to = code.first;
        for(int i = 0; i < code.first; i++){
            val = (val<<1) ^ (code.second & 0x01);
            code.second = code.second>>1;
        }
        while(code.first + size >= 8){
            for(int i = size; i < 8; i++){
                value = (value<<1) ^ (val & 0x01);
                val = val>>1;
                code.first--;
            }

            out.write((char*)&value, 1);
//            displayCode(pair<int, int>(8, value));
            if(value == 0xff){
                value = 0;
                out.write((char*)&value, 1);
//                displayCode(pair<int, int>(8, value));
            }
            value = 0; size = 0;
        }
        code.second = 0;
        for(int i = 0; i < code.first; i++){
            code.second= (code.second<<1) ^ (val & 0x01);
            val = val>>1;
        }
    }
    value = (value<<code.first) ^ code.second;
    size += code.first;
}

void CodeWriter::flush(){
    if(size != 0){

        while(size < 8){
            value= (value<<1) ^ 1;
            size++;
        }
        char c = (char)value;
//        displayCode(pair<int, int>(size, value));
        out.write(&c, 1);
    }
    size = 0;
    value = 0;
}
