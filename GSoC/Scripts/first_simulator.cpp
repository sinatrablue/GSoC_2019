#include<iostream>
#include<sbml/SBMLTypes.h>
#include<first_sim_functions.h>

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
            // Printing the time and initial species' amounts
            cout << "Time :  " << t << endl;
            ListOfSpeciesReferences *rList = reacList->get(i)->getListOfReactants();
            for(int j=0 ; j < rList->size() ; j++){
                cout << "Specie :  " << rList->get(j)->getId(); << "\t" << "Amount :  " << rList->get(j)->getInitialAmount(); << endl;
            }

            // Getting the formula of this reaction as an ASTNode_t*
            Reaction_t *reac = reacList->get(i);
            KineticLaw_t *kin = Reaction_getKineticLaw(reac);
            const char *form = KineticLaw_getFormula(kin);
            ASTNode_t *ast = SBML_parseFormula(form);
            // I can't do it on only one line because type 'Reaction' is apparently prevalent on type 'Reation_t' and so on


            /*Maintenant go juste appeler Euler en passant les réactants et produit + 'ast' non ? */
        }
    }

    string reactantID = reacList->get(1)->getListOfReactants()->getId();

    // Attention pour l'instant main ne retourne rien du tout
}