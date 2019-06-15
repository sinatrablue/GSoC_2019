#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>
#include<map>
#include<cmath>
#include "first_sim_functions.hpp"

using namespace std;

int main(int argc, char *argv[]){
    // Read SBML file
    SBMLDocument_t *doc = readSBML(argv[1]);

    // First of all checking for errors
    int errors = doc->getNumErrors();
    cout << "In file : " << argv[1] << ", " << errors << "errors found." << endl;
    if(errors > 0){ doc->printErrors(); }

    // Getting the model
    Model_t *mod = doc->getModel();

    // Initializing a map for the species
    map<string, double> spec;
    // Getting the list of species
    ListOfSpecies *spList = mod->getListOfSpecies();
    // For evry specie, add in the map its ID as key and initial amount
    for(int v=0 ; v < spList->size() ; v++){
        spec.insert(pair<string, double>(spList->get(v)->getId(), spList->get(v)->getInitialAmount())); 
    }
    
    // Getting the list of reactions
    ListOfReactions *reacList = mod->getListOfReactions();

    double t=0;
    double maxt;
    cout << "Maximum time of simulation ?" << endl;
    cin >> maxt;   // A bit stupid cause maxt won't be in seconds that way but we'll see later



    while(t<maxt){
        for(int i = 0 ; i < reacList->size() ; i++){
            ListOfSpeciesReferences *rList = reacList->get(i)->getListOfReactants();
            ListOfSpeciesReferences *pList = reacList->get(i)->getListOfProducts();

            // Getting the formula of this reaction as an ASTNode_t*
            Reaction_t *reac = reacList->get(i);
            KineticLaw_t *kin = Reaction_getKineticLaw(reac);
            const char *form = KineticLaw_getFormula(kin);
            ASTNode_t *ast = SBML_parseFormula(form);
            ListOfParameters *loc = KineticLaw_getListOfLocalParameters(kin);
            // I can't do it on only one line because type 'Reaction' is apparently prevalent on type 'Reation_t' and so on
            /* Il manque les local parameters qu'un AST_NAME peut demander aussi */
            spec = euler(t, spec, ast, rList, pList, loc);
        }
        
        // Printing and pasting the new values in the output results file
        ofstream outfile;
        outfile.open("results.txt");
        cout << "At time :  " << t << endl;
        for(map<string, double>::iterator itr = spec.begin() ; itr != spec.end() ; itr++){
            cout << "Specie :  " << itr->first << '\t' << "Amount :  " << itr->second << endl;  // Print the result
            outfile << itr->first << '\t' << t << '\t' << itr->second << endl;  // Paste the result in the output file
        }
        outfile.close();
    }

    return EXIT_SUCCESS;
}