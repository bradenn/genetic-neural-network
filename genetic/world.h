//
// Created by Braden Nicholson on 5/18/23.
//

#ifndef GENES_WORLD_H
#define GENES_WORLD_H


#include "../window/pane.h"
#include "population.h"

class World : public Pane {

public:
    explicit World(Population *pPopulation);

    void render(GFX *gfx, int width, int height) override;

private:

    Population *population;

};


#endif //GENES_WORLD_H
