#include<iostream>
#include<sbml/SBMLTypes.h>

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

    /*De là, on initialisera t=0 et toute la fin va se jouer dans la boucle while(t>maxt)
    Il faut récupérer les formules des réactions et les convertir en ASTNode_t* avec SBMLParseFormula.
    Pour chaque réaction, on récupère la formula, on la converti, on l'évalue avec la fonction qu'il faut.
    Ensuite on récupère les réactants et les produits de la réaction qu'on teste et on calcule les
    valeurs actuelles d'amount avec Euler. On print ça et on remplace dans la map + ça va en ofstream.*/

    double t=0;
    double maxt;
    cout << "Maximum time of simulation ?" << endl;
    cin >> maxt;   // A bit stupid cause maxt won't be in seconds that way but we'll see later

    while(t<maxt){
        for(int i = 0 ; i < reacList->size() ; i++){
            // Getting the formula of this reaction as an ASTNode_t*
            Reaction_t *reac = reacList->get(i);
            KineticLaw_t *kin = Reaction_getKineticLaw(reac);
            const char *form = KineticLaw_getFormula(kin);
            ASTNode_t *ast = SBML_parseFormula(form);
            // I can't do it on only one line because type 'Reaction' is apparently prevalent on type 'Reation_t' and so on
        }
    }

    string reactantID = reacList->get(1)->getListOfReactants()->getId();
    SBMLDocument_t
    // Attention pour l'instant main ne retourne rien du tout
}