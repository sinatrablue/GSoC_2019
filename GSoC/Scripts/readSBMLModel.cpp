#include<iostream>
#include<sbml/SBMLTypes.h>

using namespace std;

int main(int argc, char *argv[]){
    SBMLDocument *doc = readSBML(argv[1]);

    // First of all checking for errors
    int errors = doc->getNumErrors();
    cout << "In file : " << argv[1] << ", " << errors << "errors found." << endl;
    if(errors > 0){ doc->printErrors(); }

    // Getting the model out of the SBML document
    Model *mod = doc->getModel();
    // And now the components needed
    ListOfSpecies *sp = mod->getListOfSpecies();
    ListOfReactions *reac = mod->getListOfReactions();
    ListOfParameters *para = mod->getListOfParameters();
}