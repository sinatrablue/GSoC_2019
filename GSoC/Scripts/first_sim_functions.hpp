#ifndef first_sim_functions_hpp
#define first_sim_functions_hpp

#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>
#include<cmath>

LIBSBML_CPP_NAMESPACE_USE

double evalAST(const ASTNode *ast, std::map<std::string, double> spec, ListOfParameters *loc);

std::map<std::string, double> evalREACT(double &dt, std::map<std::string, double> &spec, std::map<std::string, double> &dxdt, const ASTNode *ast, ListOfSpeciesReferences *rList, ListOfSpeciesReferences *pList, ListOfParameters *loc);


#endif