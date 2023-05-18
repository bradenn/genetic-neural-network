//
// Created by Braden Nicholson on 5/16/23.
//

#include <iostream>
#include "gfx.h"

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

}


void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // When left mouse button is pressed, store the current cursor position
//        glfwGetCursorPos(window, &prevMouseX, &prevMouseY);
    }
}

void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS) {
//        // Calculate the change in cursor position
//        double dx = xpos - prevMouseX;
//        double dy = ypos - prevMouseY;
//
//        camera.rx = fmod(camera.rx + dy, 360);
//        camera.ry = fmod(camera.ry + dx, 360);
//        // Perform any desired action with the mouse drag event
//        // (e.g., rotating the camera, moving objects, etc.)
//
//        // Update the previous mouse position
//        prevMouseX = xpos;
//        prevMouseY = ypos;
    }
}

GFX::GFX() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

//#ifdef __APPLE__
//    /* We need to explicitly ask for a 3.2 context on OS X */
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#endif

    window = glfwCreateWindow(800, 600, "Genetic Physics Simulator", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    GLFWmonitor *mon = glfwGetPrimaryMonitor();
    int xp, yp, w, h;
    glfwGetMonitorWorkarea(mon, &xp, &yp, &w, &h);

    width = (int) ((double) w / 1.5);
    height = (int) ((double) h / 1.5);

    glfwSetWindowSize(window, (int) width, (int) height);
    glfwSetWindowPos(window, w / 2 - (int) width / 2, h / 2 - (int) height / 2);

//    glfwSetWindowSizeCallback(window, resize);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, scrollCallback);


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND_DST_ALPHA);
    fr = new FontRenderer("./IBMPlexSans-Regular.ttf");
    // Main loop
    glfwWindowHint(GLFW_SAMPLES, 2);
    glEnable(GL_MULTISAMPLE);

//    glViewport(0, (int)height, (int)width, (int)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluPerspective(60.0, 4.0 / 3.0, 0, 100.0);
    glOrtho(-width/2, width/2, -height/2, height/2, 0, 100);
//    glFrustum(-width/2, width/2, -height/2, height/2, 0, 1000);
    glMatrixMode(GL_MODELVIEW);

}
void GFX::text(const string& text, double size, double x, double y, double z) {
    glPushMatrix();
//    glTranslated(x, y, z);

    glColor4d(1,1,1,1);
    fr->renderText(text, 64, x, y, z);
    glPopMatrix();
}

void GFX::drawRect(double x, double y, double w, double h) {
    glPushMatrix();
    glTranslated(x, y, 0);
    glBegin(GL_LINES);
    // Top
    glVertex3d(0, 0, 0);
    glVertex3d(w, 0, 0);
    // Right
    glVertex3d(w, 0, 0);
    glVertex3d(w, h, 0);
    // Bottom
    glVertex3d(w, h, 0);
    glVertex3d(0, h, 0);
    // Left
    glVertex3d(0, h, 0);
    glVertex3d(0, 0, 0);
    glEnd();
    glPopMatrix();
}

void GFX::run() {

}

GFX::~GFX() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GFX::addCallback(void (*fn)()) {
    funcs.push_back(fn);
}
