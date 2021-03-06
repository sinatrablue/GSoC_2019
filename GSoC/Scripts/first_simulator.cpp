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
    // For every specie, add in the map its ID as key and initial amount
    for(auto v=0 ; v < spList->size() ; v++){
        pair<string, double> to_insert;
        to_insert = make_pair(spList->get(v)->getId(), spList->get(v)->getInitialAmount());
        spec.insert(to_insert); 
    }


    // Getting the list of reactions
    ListOfReactions *reacList = mod->getListOfReactions();

    double t=0;
    double dt = 0.05;
    double maxt;
    cout << "Maximum time of simulation ?" << endl;
    cin >> maxt;   // A bit stupid cause maxt won't be in seconds that way but we'll see later

    ofstream outfile;
    outfile.open("results.txt");
    // First line with names
    outfile << "t" << '\t';
    for(auto w = 0 ; w < spList->size() ; w++){
        outfile << spList->get(w)->getId() << '\t';
    }
    outfile << endl;
    // Initial values in output file
    outfile << t << '\t';
    for(auto itr = spec.begin() ; itr != spec.end(); itr++){
        outfile << itr->second << '\t';
    }
    outfile << endl;
    while(t<=maxt){
        // Initializing a second map for the dx/dt
        // Getting the ID of the species and initializing all the values at 0
        map<string, double> dxdt;
        for(auto v=0 ; v < spList->size() ; v++){
            pair<string, double> insert;
            insert = make_pair(spList->get(v)->getId(), 0);
            dxdt.insert(insert);
        }

        for(auto i = 0 ; i < reacList->size() ; i++){
            ListOfSpeciesReferences *rList = reacList->get(i)->getListOfReactants();
            ListOfSpeciesReferences *pList = reacList->get(i)->getListOfProducts();

            // Getting the formula of this reaction as an ASTNode_t*
            Reaction *reac = reacList->get(i);
            const ASTNode *ast = reac->getKineticLaw()->getMath();
            ListOfParameters* loc = reac->getKineticLaw()->getListOfParameters();
            // I can't do it on only one line because type 'Reaction' is apparently prevalent on type 'Reation_t' and so on

            dxdt = evalREACT(dt, spec, dxdt, ast, rList, pList, loc);
        }

        // After all reactions are evaluated, update the species' values :
        for(auto itr = spec.begin() ; itr != spec.end() ; itr++){
            cout << itr->first << endl;
            for(auto i = dxdt.begin() ; i != dxdt.end() ; i++){
                if(itr->first == i->first){
                    itr->second += i->second;
                }
            }
        }
        
        cout << "test" << endl;
        // Printing and pasting the new values in the output results file
        cout << "At time :  " << t << endl;
        outfile << t << '\t';
        for(auto itr = spec.begin() ; itr != spec.end() ; itr++){
            cout << "Specie :  " << itr->first << '\t' << "Amount :  " << itr->second << endl;
            cout << "==================================================================" << endl;
            outfile << itr->second << '\t';
        }
        outfile << endl;
        t += dt;
    }
    outfile.close();

    return EXIT_SUCCESS;
}