//
// Created by Braden Nicholson on 12/26/22.
//

#ifndef FLUX_FONTRENDERER_H
#define FLUX_FONTRENDERER_H
#include <iostream>
#include "GLFW/glfw3.h"
#include <string>

using std::string;

#include <freetype/freetype.h>
#include FT_FREETYPE_H

class FontRenderer {
public:
    FontRenderer() = default;
    FontRenderer(const string &fontName);


    ~FontRenderer();
    void renderText(const string &text, double size, double x, double y, double z);

    double stringWidth(const string &text);

private:


    FT_Library ftLibrary{};
    FT_Face ftFace{};

    void renderChar(FT_Bitmap_ *bitmap, double x, double y, double z);


};


#endif //FLUX_FONTRENDERER_H
