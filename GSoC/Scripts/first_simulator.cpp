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
    SBMLDocument *doc = readSBML(argv[1]);

    // First of all checking for errors
    int errors = doc->getNumErrors();
    cout << "In file : " << argv[1] << ", " << errors << " errors found." << endl;
    if(errors > 0){ doc->printErrors(); }

    // Getting the model
    Model *mod = doc->getModel();

    // Initializing a map for the species
    map<string, double> spec;
    // Getting the list of species
    ListOfSpecies *spList = mod->getListOfSpecies();
    // For evry specie, add in the map its ID as key and initial amount
    for(int v=0 ; v < spList->size() ; v++){
        pair<string, double> to_insert;
        to_insert = make_pair(spList->get(v)->getId(), spList->get(v)->getInitialAmount());
        spec.insert(to_insert); 
    } // ici correction
    
    // Getting the list of reactions
    ListOfReactions *reacList = mod->getListOfReactions();

    double t=0;
    double dt = 0.05;
    double maxt;
    double diff = 0;
    cout << "Maximum time of simulation ?" << endl;
    cin >> maxt;   // A bit stupid cause maxt won't be in seconds that way but we'll see later

    ofstream outfile;
    outfile.open("results.txt");
    // Initial values in output file
    for(map<string, double>::iterator itr = spec.begin() ; itr != spec.end() ; itr++){
        outfile << itr->first << '\t' << t << '\t' << itr->second << endl;
    }
    while(t<=maxt){
        for(int i = 0 ; i < reacList->size() ; i++){
            ListOfSpeciesReferences *rList = reacList->get(i)->getListOfReactants();
            ListOfSpeciesReferences *pList = reacList->get(i)->getListOfProducts();

            // Getting the formula of this reaction as an ASTNode_t*
            Reaction *reac = reacList->get(i);
            const ASTNode *ast = reac->getKineticLaw()->getMath();
            ListOfParameters* loc = reac->getKineticLaw()->getListOfParameters();
            // I can't do it on only one line because type 'Reaction' is apparently prevalent on type 'Reation_t' and so on

            spec = euler(dt, spec, ast, rList, pList, loc);
        }
        
        // Printing and pasting the new values in the output results file
        cout << "At time :  " << t << endl;
        for(map<string, double>::iterator itr = spec.begin() ; itr != spec.end() ; itr++){
            cout << "Specie :  " << itr->first << '\t' << "Amount :  " << itr->second << endl;  // Print the result
            cout << "==================================================================" << endl;
            outfile << itr->first << '\t' << t << '\t' << itr->second << endl;  // Paste the result in the output file
        } // ici aussi correction pour le fichier de sortie
        t += dt;
    }
    outfile.close();

    return EXIT_SUCCESS;
}