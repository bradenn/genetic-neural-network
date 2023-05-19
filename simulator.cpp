//
// Created by Braden Nicholson on 5/16/23.
//

#include "simulator.h"
#include "genetic/random.h"
#include "genetic/world.h"

Simulator::Simulator() {
    gfx = new GFX();
    population = new Population(50);
    world = new World(population);
    statistics = new Statistics(world, population);
    frame = new Frame(12, 12, (int)gfx->width, (int)gfx->height, 10);
    frame->addPane(0, 0, 12, 1, new Pane("Metadata"));

    frame->addPane(10, 1, 2, 11, population);

    frame->addPane(2, 1, 8, 11, world);
    frame->addPane(0, 1, 2, 11, statistics);

}

void Simulator::render() {
    int ticks = 0;
    while (!glfwWindowShouldClose(gfx->window)) {
        // Drawing and input handling code will go here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glColor4d(1,1,1,1);

        glPushMatrix();
        glTranslated(-gfx->width/2, -gfx->height/2, 0);
        frame->render(gfx);
        glPopMatrix();
        GLenum err;
//        while((err = glGetError()) != GL_NO_ERROR)
//        {
//            const char *errStr[1000];
//            glfwGetError(errStr);
//            printf("%s - %s\n", gluErrorString(err), errStr);
//            // Process/log the error.
//        }
        glfwSwapBuffers(gfx->window);
        for (int i = 0; i < 50; ++i) {
            population->tick();
        }
        glfwPollEvents();
    }
}
