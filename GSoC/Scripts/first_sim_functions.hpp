#ifndef first_sim_functions_hpp
#define first_sim_functions_hpp

#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>
#include<cmath>

double evalAST(ASTNode_t *ast, map<string, double> spec, ListOfParameters *loc);

map<string, double> euler(double t, map<string, double> spec, ASTNode_t *ast, ListOfSpeciesReferences *rList, ListOfSpeciesReferences *pList, ListOfParameters *loc);


#endif