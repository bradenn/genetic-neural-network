//
// Created by Braden Nicholson on 5/16/23.
//

#include "simulator.h"
#include "genetic/genome.h"
#include "genetic/random.h"

Simulator::Simulator() {
    gfx = new GFX();
    population = new Population(50);

}

void Simulator::render() {
    int ticks = 0;
    while (!glfwWindowShouldClose(gfx->window)) {
        // Drawing and input handling code will go here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glColor3f(1,0,0);

        glColor4d(1,1,1,1);

        glPushMatrix();
        population->render(gfx);
        gfx->text("Test test", 1, 100, 1, 1);
        glPopMatrix();

        glfwSwapBuffers(gfx->window);
        glfwPollEvents();
        for (int i = 0; i < 50; ++i) {
            population->tick();
            ticks++;
        }

    }
}
