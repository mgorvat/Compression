#include "CodeWriter.h"



CodeWriter::CodeWriter(ostream& out): out(out), value(0), size(0){}
void CodeWriter::writeCode(Code code){
    if(code.length + size >= 8){
        int val = 0;
        for(int i = 0; i < code.length; i++){
            val = (val<<1) ^ (code.value & 0x01);
            code.value = code.value>>1;
        }
        while(code.length + size >= 8){
            for(int i = size; i < 8; i++){
                value = (value<<1) ^ (val & 0x01);
                val = val>>1;
                code.length--;
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
        code.value = 0;
        for(int i = 0; i < code.length; i++){
            code.value = (code.value<<1) ^ (val & 0x01);
            val = val>>1;
        }
    }
    value = (value<<code.length) ^ code.value;
    size += code.length;
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
