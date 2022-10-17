# PolyMult_CPP
## poly_mult.h
This is a C++ reimplementation of my older PolyMult Class that I wrote in Python.
## int_mult.cpp
This is a C++ reimplementation of my older IntMult Class that I wrote in Python.
# restating what has been said before.
Recursive FFT polynomial multiplication.

This is an implementation of the method laid out in Ando Emerencia's paper on Huge integer multiplication: http://www.cs.rug.nl/~ando/pdfs/Ando_Emerencia_multiplying_huge_integers_using_fourier_transforms_paper.pdf
## Usage
The functions multiplies two polynomials together using the Fast Fourier Transform. To achive this it calculates the complex roots of unity.

The polynomials fed to the FFT function must be in list form:
```
a_0 + a_1*x + ... + a_(n-1)*x^(n-1)
is
a = [a_0, a_1, ..., a_(n-1)]
```
Further the way that this method works is that there needs to be 2 polynomials, of differing (or the same) degrees, that are padded with zeros such that both lists have their number of elements being the same power of two.
```
a = [a_0, a_1, ..., a_(n-1), 0, 0, ..., 0]
b = [b_0, b_1, ..., b_(m-1), 0, 0, ..., 0]
```
### Conversion to integer multiplication
The func int_mult takes two integers of arbitrary size (for all practical purposes) and turns them into polynomials and then multiplies them using the poly_mult function.

In other words this is doing integer multiplication with the Fast Fourier Transform.
# gcc options
Example compilation:
```
g++ --std=c++20 -fext-numeric-literals poly_mult.cpp
```
