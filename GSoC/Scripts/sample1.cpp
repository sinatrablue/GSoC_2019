#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>

using namespace std;

ASTNode_t* ast = SBML_parseFormula("k * A");

double evalAST(ASTNode_t *ast){

    double result;
    int childnum = ASTNode_getNumChildren(ast);     // gets the number of children (in our case 2, k and A)
    ASTNode_t  **child = (ASTNode_t **) malloc(childnum * sizeof(ASTNode_t*));     // allocates as much ASTNode_t** as the node has children

    // get every child
    for(int i=0; i<childnum; i++){
        child[i] = ASTNode_getChild(ast, i);
    }

    // switch on the type of ast, the root node (in our case "*")
    switch(ASTNode_getType(ast)){
        case AST_INTEGER:
        int result = ASTNode_getInteger(ast);
        break;

        case AST_REAL:
        result = ASTNode_getReal(ast);
        break;

        case AST_NAME:
        char *l;
        double var;
        printf("Give the value of value : ");
        printf("%s=", ASTNode_getName(ast));    // prints variable that needs a value
        cin.getline(l, 20);     // reads value given by user
        sscanf(l, "%lf", &var);     // stores the float value read in var 
        delete(l);      // I read it as "free() in C ; delete() in C++" maybe it is not that trivial 
        printf("%s = %f\n", ASTNode_getName(ast), var);     // confirmation message
        result = var;
        break;

        case AST_CONSTANT_FALSE:
        result = 0.0;
        break;

        case AST_CONSTANT_TRUE:
        result = 1.0;
        break;

        case AST_PLUS:
        result = evalAST(child[0]) + evalAST(child[1]);
        break;

        case AST_MINUS:
        if(childnum==1)
        result = - (evalAST(child[0]));
        else
        result = evalAST(child[0]) - evalAST(child[1]);
        break;

        case AST_TIMES:     // which is going to be our case
        result = evalAST(child[0]) * evalAST(child[1]) ;
        break;

        case AST_DIVIDE:
        result = evalAST(child[0]) / evalAST(child[1]);
        break;

        case AST_POWER:
        result = pow(evalAST(child[0]),evalAST(child[1]));
        break;

        default :
        result = 0;
        break;

    }
    delete(child);

    return result;
}

void euler(double t, double y, double dt, double maxt){
    double tmp = 0;

    // Opening output file that will be plotted later (in main)
    ofstream outfile;
    outfile.open("sample1.txt",fstream::out | fstream::trunc);
    outfile.precision(4);

    while(t<maxt){
        tmp=y;
        y = y+dt * evalAST(ast);
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
