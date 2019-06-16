#ifndef first_sim_functions_hpp
#define first_sim_functions_hpp

#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>
#include<cmath>

double evalAST(const ASTNode *ast, std::map<std::string, double> spec, ListOfParameters *loc);

std::map<std::string, double> euler(std::map<std::string, double> spec, const ASTNode *ast, ListOfSpeciesReferences *rList, ListOfSpeciesReferences *pList, ListOfParameters *loc);


#endif