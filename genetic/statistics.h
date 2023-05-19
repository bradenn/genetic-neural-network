//
// Created by Braden Nicholson on 5/18/23.
//

#ifndef GENES_STATISTICS_H
#define GENES_STATISTICS_H


#include "../window/pane.h"
#include "world.h"

class Statistics : public Pane {

public:
    Statistics(World *world, Population *population);

    void render(GFX *gfx, int width, int height) override;

private:
    World *world;

    Population *population;
};


#endif //GENES_STATISTICS_H
