//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENES_POPULATION_H
#define GENES_POPULATION_H


#include "genome.h"
#include "../window/pane.h"

class Population : public Pane{

public:
    Population(int size);

    void render(GFX *g);

    void render(GFX *g, int width, int height);

    void tick();

    double px = 0;
    double py = 0;

    vector<Genome*> getPopulation() {
        return genomes;
    }

    int getRound(){
        return round;
    }

    int getTicks() {
        return ticks;
    }

    int getGenerationTicks() {
        return ticksPerGeneration;
    }

    int getInputs() {
        return inputs;
    }

    int getNeurons() {
        return neurons;
    }

    int getOutputs() {
        return outputs;
    }

    int getGenes() {
        return genes;
    }

    int getMutationRate() {
        return mutationRate;
    }

    double max = 0;
    double min = 0;
private:

    vector<Genome*> genomes;

    int inputs = 0;
    int outputs = 0;
    int neurons = 0;
    int genes = 0;
    int mutationRate = 0;


    int ticksPerGeneration = 5000;
    int round = 0;
    int ticks = 0;


};


#endif //GENES_POPULATION_H
