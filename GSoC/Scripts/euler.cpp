// Example on the Euler method
#include<iostream>
#include<cmath>

using namespace std;

// Function defining the diff eq
double df(double x, double y){      // Eq I chose : dy/dx=(1/x²)*y
    double z = (y/(x*x));           // because x¹ makes compile bug as always
    return z;
}

void euler(double x0, double y, double h, double x){
    double tmp = 0;

    while(x0<x){
        tmp=y;
        y = y+h * df(x0,y);
        cout << y << endl;
        x0=x0+h;
    }

    // Results
    cout << "At x = " << x << ", approximate solution is : " << y << endl;
}

int main(void){
    // Initializing the values
    double x0 = 0.5;
    double y0 = 1;
    double h = 0.05;  // Completely random for now

    // Value x at which we need approximation
    // We're gonna go from x0 to x adding 'h' everytime
    double x = 1;  // Random too

    // Applying the function
    euler(x0, y0, h, x);  // It will print the result

    return EXIT_SUCCESS;
}