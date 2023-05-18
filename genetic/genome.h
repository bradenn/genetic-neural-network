//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENES_GENOME_H
#define GENES_GENOME_H


#include <vector>
#include <map>
#include "stimulus.h"
#include "neuron.h"
#include "gene.h"
#include "../gfx.h"

using std::vector;
using std::map;


struct GenomeConfiguration {


};


class Genome {

public:

    Genome(uint8_t inputs, uint8_t neurons, uint8_t outputs, const vector<Gene> &genes);

    map<uint8_t, float> compute(const map<uint8_t, uint16_t> &stimuli);

    vector<Gene> mingle(Genome *mate);

    static vector<Gene> generateRandom(int numGenes);

    void render(GFX *g, double dx, double dy);


    double posX = 0;
    double posY = 0;
    double aX = 0;
    double aY = 0;

    void drawChar(GFX *pGfx);

    int score = 0;
    uint8_t numOutputs = 0;
    uint8_t numNeurons = 0;
    uint8_t numInputs = 0;
protected:

    double vX = 0;
    double vY = 0;
    double mass = 10;

    vector<Gene> core;
    vector<Gene> genes;

    map<uint8_t, float> inputs;
    map<uint8_t, float> neurons;
    map<uint8_t, int8_t> neuronCount;
    map<uint8_t, float> outputs;
    map<uint8_t, int8_t> outputCount;

    void cullGenes();

    bool geneIsValid(Gene gene);

    bool geneSourceExists(Gene gene);

    bool geneDestinationExists(Gene gene);

    void resetValues();
};


#endif //GENES_GENOME_H
