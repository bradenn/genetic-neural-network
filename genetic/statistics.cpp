//
// Created by Braden Nicholson on 5/18/23.
//

#include <sstream>
#include "statistics.h"

Statistics::Statistics(World *world, Population *population) : Pane("Statistics"), world(world),
                                                               population(population) {

}

void Statistics::render(GFX *gfx, int width, int height) {
    int offsetY = 0;
    int lh = 20;

    int subheaderIndent = 16;
    int indent = 25;

    std::stringstream ss;

    gfx->text("Simulation", 32, subheaderIndent, offsetY += lh*2, 0);

    ss << "Generation: " << population->getRound();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    ss = std::stringstream();

    ss << "Tick: " << population->getTicks();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    ss = std::stringstream();

    ss << "Ticks/Generation: " << population->getGenerationTicks();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    gfx->text("Population", 32, subheaderIndent, offsetY += lh*2, 0);

    ss = std::stringstream();

    ss << "Genomes: " << population->getPopulation().size();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    ss = std::stringstream();

    ss << "Inputs: " << population->getInputs();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    ss = std::stringstream();

    ss << "Neurons: " << population->getNeurons();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    ss = std::stringstream();

    ss << "Outputs: " << population->getOutputs();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    ss = std::stringstream();

    ss << "Genes: " << population->getGenes();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

    gfx->text("Mutation", 32, subheaderIndent, offsetY += lh*2, 0);
    ss = std::stringstream();

    ss << "Rate: 1/" << population->getMutationRate();
    gfx->text(ss.str(), 28, indent, offsetY += lh, 0);

}
