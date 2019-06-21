#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>
#include<cmath>
#include "first_sim_functions.hpp"

using namespace std;

double evalAST(const ASTNode *ast, map<string, double> spec, ListOfParameters *loc){

    double result;
    int childnum = ASTNode_getNumChildren(ast);     // gets the number of children
    ASTNode_t  **child = (ASTNode_t **) malloc(childnum * sizeof(ASTNode_t*));     // allocates as much ASTNode_t** as the node has children

    // get every child
    for(int i=0; i<childnum; i++){
        child[i] = ASTNode_getChild(ast, i);
    }

    switch(ASTNode_getType(ast)){
        case AST_INTEGER:
        result = ASTNode_getInteger(ast);
        break;

        case AST_REAL:
        result = ASTNode_getReal(ast);
        break;

        case AST_NAME:
        // If I understaood well I have to put all this case between bracket because of a specificity when declaring things like strings in a switch
        {
            string name = ASTNode_getName(ast);
            cout << "AST_NAME :  " << name << endl;
            for(map<string, double>::iterator itr = spec.begin() ; itr != spec.end() ; itr++){  // Iterate in map
                if(name == itr->first){
                    result = itr->second;    // Update the value of reactants involved in the reaction which calls the euler function
                    //cout << "YES1" << endl;
                    //cout << "RESULT1 :  " << result << endl; 
                }
            }
            // If the variable was not in the species involved, check in the parameters
            for(int i=0 ; i < loc->size() ; i++){
                if(name == loc->get(i)->getId()){
                    result = loc->get(i)->getValue() ;
                    //cout << "YES2" << endl;
                    //cout << "RESULT2 :  " << result << endl;
                }
            }
        // If it is still undifined, there is a problem, maybe with the variable names
        // cout << "Problem with variable :  " << name << '\n' << "~>  Unable to find its value" << endl;
        // exit(1);
        }
        return result;
        break;

        case AST_PLUS:
        result = evalAST(child[0], spec, loc) + evalAST(child[1], spec, loc);
        break;

        case AST_MINUS:
        if(childnum==1)
        result = - (evalAST(child[0], spec, loc));
        else
        result = evalAST(child[0], spec, loc) - evalAST(child[1], spec, loc);
        break;

        case AST_TIMES:     // which is going to be our case
        result = evalAST(child[0], spec, loc) * evalAST(child[1], spec, loc) ;
        break;

        case AST_DIVIDE:
        result = evalAST(child[0], spec, loc) / evalAST(child[1], spec, loc);
        break;

        case AST_POWER:
        case AST_FUNCTION_POWER:
        result = pow(evalAST(child[0], spec, loc),evalAST(child[1], spec, loc));
        break;

        default :
        result = 0;
        break;

    }
    delete(child);

    return result;
}


map<string, double> euler(double dt, map<string, double> spec, const ASTNode *ast, ListOfSpeciesReferences *rList, ListOfSpeciesReferences *pList, ListOfParameters *loc){

    // Calculate from the equation of the reaction which calls the function
    double res = evalAST(ast, spec, loc);
    res += dt;
    // Et en vrai c'est à peu près tout pour cette fonction elle retourne ça et voilà merci

    //cout << "  Résultat evalAST :  " << res << endl;   test qui sert plus à rien


    // For the reactants :
    for(int i = 0 ; i < rList->size() ; i++){   // Iterate in reactant list
        map<string, double>::iterator itr = spec.find(rList->get(i)->getSpecies());
        if(itr != spec.end()){
            itr->second -= res+dt;    // Update the value of reactants involved in the reaction which calls the euler function
        } 
    }
    

    // For the products :
    // Nothing changes appart from "pList", we can use the same values' names for iterator and erase their content
    for(int i = 0 ; i < pList->size() ; i++){
    map<string, double>::iterator itr = spec.find(pList->get(i)->getSpecies());
        if(itr != spec.end()){
            itr->second += res+dt;
        } 
    }

    return spec;
}