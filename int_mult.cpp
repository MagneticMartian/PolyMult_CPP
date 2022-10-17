#include "poly_mult.h"

template<typename T>
bool is_pow2(T a)
{
    T n = a;
    while(n != 1){
        if(n % 2 != 0) return false;
        n >>= 1;
    }
    return true;
}
template<typename T>
std::vector<T> int_vect(T a)
{
    std::vector<T> vec;
    T m = a;
    T num_dig = (T)log10(a);
    T res;
    for(T i = 0; i <= num_dig; ++i){
        res = m % 10;
        vec.push_back(res);
        m /= 10;
    }
    return vec;
}
template<typename T>
std::vector<cmplx> coeff_preproc(T a)
{
    std::vector<T> coeff_a = int_vect(a);
    T len_a = coeff_a.size();
    T m_a;
    if(is_pow2(len_a)) m_a = (T) std::log2(len_a);
    else m_a = std::log2(len_a) + 1;

    T new_len_a = (T) std::pow(2,m_a);
    T n_zero_a = new_len_a * 2 - len_a;
    std::vector<cmplx> pad_coeff_a;
    for(auto val : coeff_a) pad_coeff_a.push_back(val);
    for(T i = 0; i < n_zero_a; ++i)
        pad_coeff_a.push_back(0);
    return pad_coeff_a;
}
template<typename T>
T int_mult(T a, T b)
{
    std::vector<cmplx> pad_coeff_a = coeff_preproc(a);
    std::vector<cmplx> pad_coeff_b = coeff_preproc(b);
    if(pad_coeff_a.size() < pad_coeff_b.size()){
        T diff = pad_coeff_b.size() - pad_coeff_a.size();
        for(T i = 0; i < diff; ++i) pad_coeff_a.push_back(0);
    }
    if(pad_coeff_a.size() > pad_coeff_b.size()){
        T diff = pad_coeff_a.size() - pad_coeff_b.size();
        for(T i = 0; i < diff; ++i) pad_coeff_b.push_back(0);
    }
    std::vector<cmplx> res0 = poly_mult(pad_coeff_a,pad_coeff_b);
    T n = res0.size();
    std::vector<T> res1(n);
    std::transform(res0.begin(),res0.end(),res1.begin(),[](cmplx a){
            return (T)std::round(std::abs(a));
            });
    for(T i = 0; i < res1.size(); ++i)
        res1[i] = res1[i]*(T)pow(10,i);
    //return std::accumulate(res1.begin(),res1.end(),0);
    T tot = 0;
    for(auto i : res1) tot += i;
    return tot;
}
int main()
{
    int a = 15, b = 15;
    std::cout << int_mult(a,b) << '\n';
}
