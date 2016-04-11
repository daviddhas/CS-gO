#ifndef CSGO_H
#define CSGO_H

#include <algorithm>
#include <functional>
#include <vector>

typedef float Float;
template <class T>
class ReadTex{
public:
        ReadTex()
        {

        }

        ReadTex(std::vector<T> vec1)
        {
            vec=vec1;

        }

        /* Sums 2 vectors */

        ReadTex operator+ (const ReadTex& r)
        {
            assert(vec.size() == r.size());

            ReadTex result;
            result.reserve(r.vec.size());
            for(int i=0;i<result.size();i++)
            result.push_back(vec[i]+r[i]);

            /*    std::transform(r.begin(), r.end(), vec.begin(),
                   std::back_inserter(result), std::plus<Float>());
        */
            return result;
        }

        /* += Appdends to the vector */
        ReadTex operator+= (const ReadTex& r)
        {
         // vec.insert(vec.end(),r.begin(),r.end());
           return vec;
        }

        /* Returns the size of the ReadTex Vector*/
        size_t size()
        {
            return vec.size();

        }

        /* Reserves the size of the ReadTex Vector*/
        void  reserve(size_t size)
        {

            vec.reserve(size);

        }

        std::vector<Float>::iterator begin()
        {

            return vec.begin();

        }

        std::vector<Float>::iterator end()
        {

          return vec.end();

        }

private:

        std::vector <T> vec;

};


template <class T>
//class WriteTex : public ReadTex
class WriteTex
{
public:

        WriteTex operator= (const WriteTex& w)
        {
            vec = w;
        }



private:
        std::vector<T>vec;
};




#endif
