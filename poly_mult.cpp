#include <iostream>
#include <numeric>
#include <complex>
#include <functional>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std::complex_literals;
/*
 * Polynomial multiplication done the naive way is a O(n^2) time procedure.
 * However, by introducing the FFT which is a divide and conqure algorithm
 * we can change this into a O(nlog n) time algorithm. This is achived by
 * using the DFT with primitive nth roots of unity. By doing so we change
 * the DFT from O(n^2) to O(nlog n), thus giving the FFT.
 *
 * The inputs of the PolyMult function are two 2n degree padded polynomials.
 * They need to be padded, due to the fact that multiplying two polynomials
 * of degree n-1 will result in one polynomial of degree 2n-2. Further more
 * the padding is there to ensure that 2n is a power of 2. Thus, n is also a
 * power of 2.
 * 
 * In the particular implementation bellow, we use the complex roots of unity.
 * These are used for two properties:
 *     1. Reduction Property
 *     2. Reflection Property
 * These two properties allow us to take advantage of the divide and conqure
 * nature of the FFT.
 */
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
    // Handling the reduction property
    std::vector<cmplx> y_even = FFT(a_even, omega*omega);
    std::vector<cmplx> y_odd = FFT(a_odd, omega*omega);

    std::vector<cmplx> y(len);
    cmplx x = 1;
    for(int i = 0; i < len_half; ++i){
        y[i] = y_even[i] + x*y_odd[i];
        y[i + len_half] = y_even[i] - x*y_odd[i]; // The reflection property
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
    std::transform(p.begin(), // c[i] = p[i]*q[i]
                   p.end(),
                   q.begin(),
                   c.begin(),
                   std::multiplies<cmplx>());
    std::vector<cmplx> mult = FFT(c, one/omega);
    std::transform(mult.begin(), // mult[i] = mult[i]/len
                   mult.end(),
                   mult.begin(),
                   [len](cmplx m){return m/len;});
    return mult;
}

int 
main()
{
    std::vector<cmplx> a = {1,2,3,4,0,0,0,0};
    std::vector<cmplx> b = {-1,0,2,1,0,0,0,0};

    std::cout << poly_mult(a,b) << '\n';
}
