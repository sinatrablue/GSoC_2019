#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>

using namespace std;

ASTNode_t* ast = SBML_parseFormula("k * A");

// Function defining the diff eq
double df(ASTNode_t *ast){
    ASTNode *ch1 = ASTNode_getLeftChild(ast);
    ASTNode *ch2 = ASTNode_getRightChild(ast);
    double x = ASTNode_getReal(ch1);
    double y = ASTNode_getReal(ch2);
    
    // Because I am not sure I can the operand "*" from ast let's start with :
    double z = y*x;
    return z;
}

void euler(double t, double y, double dt, double maxt){
    double tmp = 0;

    // Opening output file that will be plotted later (in main)
    ofstream outfile;
    outfile.open("sample1.txt",fstream::out | fstream::trunc);
    outfile.precision(4);

    while(t<maxt){
        tmp=y;
        y = y+dt * df(ast);
        t=t+dt;
        outfile<<fixed<<t<<"   "<<fixed<<y<<endl;

        // closing the ouput file, that now has all the coordinates in it
        outfile.close();
    }
}


int main(void){
    // Initializing the values
    double iAx = 0;
    double iAy = 1;
    double iBx = 0;
    double iBy = 0;
    double dt = 0.5;  // Worked well the last time

    double maxt;
    cout << "Maximum duration of simulation :" << endl;
    cin >> maxt;

    // Applying the function
    euler(iAx, iAy, dt, maxt);
    euler(iBx, iBy, dt, maxt);

    // Plotting the results
    // system("gnuplot -p -e \"plot 'sample1.txt'\"");

    return EXIT_SUCCESS;
}