//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENES_GFX_H
#define GENES_GFX_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "fontRenderer.h"

using std::vector;
using std::string;

class GFX {

public:
    GFX();
    ~GFX();

    void addCallback(void (*fn)());
    void run();

    GLFWwindow *window;

    double width = 0;
    double height = 0;

    void drawRect(double x, double y, double w, double h);

    void text(const string &text, double size, double x, double y, double z);

private:
    FontRenderer *fr;
    vector<void (*)()> funcs;

};


#endif //GENES_GFX_H
