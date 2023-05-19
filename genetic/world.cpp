//
// Created by Braden Nicholson on 5/18/23.
//

#include "world.h"

World::World(Population *pPopulation) : Pane("World"), population(pPopulation){

}

void World::render(GFX *gfx, int width, int height) {
    glPushMatrix();
    glTranslated((double)width/2, (double)height/2, 0);
    for (int i = 0; i < population->getPopulation().size(); i++) {
        population->getPopulation()[i]->drawChar(gfx, population->min, population->max);
    }
    glColor4d(1,1,1,1);
    gfx->drawRect(population->px - 20, population->py - 20, 40, 40);
    glPopMatrix();
}
