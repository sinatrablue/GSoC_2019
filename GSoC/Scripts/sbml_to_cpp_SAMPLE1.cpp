#include<iostream>
#include<fstream>
#include<sbml/SBMLTypes.h>
#include<string>

using namespace std;

SBMLDocument *sample1(){
    SBMLDocument *doc = new SBMLDocument(3, 2);     // libsbml is currently lv 3 version 2

    // creating a model
    Model *mod = doc->createModel();
    mod->setId("BasicABecomesB");

    // defining the units
    UnitDefinition *defUnit;
    Unit *unit;

    defUnit = mod->createUnitDefinition();
    defUnit->setId("substance");
    unit = defUnit->createUnit();
    unit->setKind(UNIT_KIND_MOLE);

    defUnit = mod->createUnitDefinition();
    defUnit->setId("volume");
    unit = defUnit->createUnit();
    unit->setKind(UNIT_KIND_LITER);

    defUnit = mod->createUnitDefinition();
    defUnit->setId("area");
    unit = defUnit->createUnit();
    unit->setKind(UNIT_KIND_METER);
    unit->setExponent(2);

    defUnit = mod->createUnitDefinition();
    defUnit->setId("length");
    unit = defUnit->createUnit();
    unit->setKind(UNIT_KIND_METER);

    defUnit = mod->createUnitDefinition();
    defUnit->setId("time");
    unit = defUnit->createUnit();
    unit->setKind(UNIT_KIND_SECOND);

    // defining the compartment
    const string compName = "default";

    Compartment *comp = mod->createCompartment();
    comp->setId(compName);
    comp->setSize(1);

    // Species
    Species *sp;

    sp = mod->createSpecies();
    sp->setCompartment(compName);
    sp->setId("A");
    sp->setInitialAmount(1);

    sp = mod->createSpecies();
    sp->setCompartment(compName);
    sp->setId("B");
    sp->setInitialAmount(0);

    // The only reaction in our model
    Reaction *reac;
    SpeciesReference *spr;
    Parameter *parr;
    KineticLaw *kin;

    reac = mod->createReaction();
    reac->setId("A_to_B");

    spr = reac->createReactant();
    spr->setSpecies("A");

    spr = reac->createProduct();
    spr->setSpecies("B");

    kin = reac->createKineticLaw();
    ASTNode *astK = new ASTNode(AST_NAME);    astK->setName("kin");
    ASTNode *astA = new ASTNode(AST_NAME);  astA->setName("A");
    ASTNode *astB = new ASTNode(AST_NAME);  astB->setName("B");
    ASTNode *astTimes = new ASTNode(AST_TIMES);
    astTimes->addChild(astA);
    astTimes->addChild(astK);
    kin->setMath(astTimes);

    // Parameter
    parr = kin->createParameter();
    parr->setId("k");
    parr->setValue(0.5);
    parr->setUnits("substance");


    return doc;
}