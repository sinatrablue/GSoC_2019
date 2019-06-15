#ifndef first_sim_functions_hpp
#define first_sim_functions_hpp

#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>
#include<cmath>

double evalAST(ASTNode_t *ast, std::map<std::string, double> spec, ListOfParameters *loc);

std::map<std::string, double> euler(double t, std::map<std::string, double> spec, ASTNode_t *ast, ListOfSpeciesReferences *rList, ListOfSpeciesReferences *pList, ListOfParameters *loc);


#endif