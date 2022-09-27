#include <iostream>
#include <numeric>
#include <complex>
#include <vector>
#include <cmath>
using namespace std::complex_literals;

template<typename T>
std::ostream& operator << (std::ostream& os, std::vector<T> val)
{
    for(auto i : val)
        os << i << ' ';
    return os;
}

typedef std::complex<double> cmplx;
const cmplx two = 2j;
const cmplx one = 1;
const cmplx pi = std::acos(-1.0); 

std::vector<cmplx> 
FFT(std::vector<cmplx> a, cmplx omega)
{
    long len = a.size();
    if(len == 1) return a;

    long len_half = len >> 1;
    std::vector<cmplx> a_even(len_half, 0);
    std::vector<cmplx> a_odd(len_half, 0);
    for(int i = 0; i < len_half; ++i){
        a_even[i] = a[2*i];
        a_odd[i] = a[2*i+1];
    }
    std::vector<cmplx> y_even = FFT(a_even, omega*omega);
    std::vector<cmplx> y_odd = FFT(a_odd, omega*omega);

    std::vector<cmplx> y(len);
    cmplx x = 1;
    for(int i = 0; i < len_half; ++i){
        y[i] = y_even[i] + x*y_odd[i];
        y[i + len_half] = y_even[i] - x*y_odd[i];
        x *= omega;
    }
    return y;
}

std::vector<cmplx> 
poly_mult(std::vector<cmplx> a, std::vector<cmplx> b)
{
    long n = a.size();
    cmplx len = (cmplx) n;

    cmplx omega = std::exp(two*pi/len);
    std::vector<cmplx> p = FFT(a, omega);
    std::vector<cmplx> q = FFT(b, omega);

    std::vector<cmplx> c(n);
    for(int i = 0; i < n; ++i)
        c[i] = p[i]*q[i];
    std::vector<cmplx> mult = FFT(c, one/omega);
    std::vector<cmplx> m(mult.size());
    for(int i = 0; i < m.size(); ++i)
        m[i] = mult[i]/len;
    return m;
}

int 
main()
{
    std::vector<cmplx> a = {1,2,3,4,0,0,0,0};
    std::vector<cmplx> b = {-1,0,2,1,0,0,0,0};

    std::cout << poly_mult(a,b) << '\n';
}
