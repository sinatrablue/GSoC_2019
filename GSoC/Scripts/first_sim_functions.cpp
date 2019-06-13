#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>

using namespace std;

double evalAST(ASTNode_t *ast){

    double result;
    int childnum = ASTNode_getNumChildren(ast);     // gets the number of children
    ASTNode_t  **child = (ASTNode_t **) malloc(childnum * sizeof(ASTNode_t*));     // allocates as much ASTNode_t** as the node has children

    // get every child
    for(int i=0; i<childnum; i++){
        child[i] = ASTNode_getChild(ast, i);
    }

    // switch on the type of ast, the root node (in our case "*")
    switch(ASTNode_getType(ast)){
        case AST_INTEGER:
        result = ASTNode_getInteger(ast);
        break;

        case AST_REAL:
        result = ASTNode_getReal(ast);
        break;

        case AST_NAME:
        char *l;
        double var;
        printf("Give the (initial) value of variable : ");
        printf("%s=", ASTNode_getName(ast));    // prints variable that needs a value
        cin.getline(l, 20);     // reads value given by user
        sscanf(l, "%lf", &var);     // stores the float value read in var 
        delete(l);      // I read it as "free() in C ; delete() in C++" maybe it is not that trivial 
        printf("%s = %f\n", ASTNode_getName(ast), var);     // confirmation message
        result = var;
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

void euler(double t, double yA, double yB, double dt, double maxt, ofstream &outfile){
    map<double, pair<double, double> >result;

    while(t<maxt){
        pair<double, double> yy;
        yy = make_pair(yA,yB);
        pair<double, pair<double, double> > to_insert;
        to_insert = make_pair(t, yy);
        result.insert(to_insert);   // In the beginning of the loop to have the initial values as well
        yA = yA+dt * evalAST(ast);
        yB = 1-yA;  // Probably a bit a shame but I can't see any other relationship to be written between them
        t=t+dt;
    }
    // Writting all the results generated by the function in the output file
    for(map<double, pair<double, double> >::iterator it=result.begin(); it!=result.end(); it++){
        outfile << it->first << '\t' << it->second.first << '\t' << it->second.second << endl;
    }
}