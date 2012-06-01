#ifndef HUFFMANCODER_H_INCLUDED
#define HUFFMANCODER_H_INCLUDED

#include <vector>
#include <map>
#include <utility>

using namespace std;

/**
    @author mgorvat
    Class, which associate values with their codes. Values after constructing class
    are immutable.
*/
template <class T>
class HuffmanCoder{
    public:
        /**
            Constructor. Makes the map.
            input:
                values — pointer to vector<T>, which containes  values, which are keys for codes
                codes — pointer to vector of codes. Code is a pair of two int values: length of code
                    and it's numeric value. i-th element in vector must be code of -th element in values
                    vector. Number of elements in values and codes must be equal.

        */
        HuffmanCoder(vector<T>* values, vector<pair<int, int> >* codes){
            for(int i = 0; i < (int)values->size(); i++){
                mp[(*values)[i]] = (*codes)[i];
            }
        }
        /**
            Reutrn code, associated with element.
            input:
                val — value, code of which need to be getted
            outpit:
                Code of velue as pair<int, int>, where first int is code length, and second is it's numeric value
        */
        pair<int, int> getCode(T* val){return mp[*val];}
    private:
        map<T, pair<int, int> > mp;//Here class store values
};
#endif // HUFFMANCODER_H_INCLUDED
