// Example on the Euler method
#include<iostream>
#include<cmath>

using namespace std;

// Function defining the diff eq
double df(double x, double y){      // Eq I chose : dy/dx=(1/x²)*y
    double z = (1/x²)*y;
    return z;
}

