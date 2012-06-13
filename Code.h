#ifndef CODE_H_INCLUDED
#define CODE_H_INCLUDED

class Code{
    public:
        Code(): length(0), value(0){}
        Code(int length, int val): length(length), value(val){}
        int length;
        int value;
};


#endif // CODE_H_INCLUDED
