//
// Created by Braden Nicholson on 12/26/22.
//


#include "fontRenderer.h"
#include FT_FREETYPE_H

FontRenderer::FontRenderer(const string &fontName) {

    if (FT_Init_FreeType(&ftLibrary) != 0) {
        printf("Error ah no load\n");
        return;
    }

    if (FT_New_Face(ftLibrary, fontName.c_str(), 0, &ftFace)) {
        printf("Error ah no face\n");
        return;
    }

}

double FontRenderer::stringWidth(const string &text) {
    double width = 0.0;
    FT_GlyphSlot slot = ftFace->glyph;
    for (char c: text) {
        FT_Set_Pixel_Sizes(ftFace, 0, 24);
        FT_Load_Char(ftFace, c, FT_LOAD_RENDER);

//        renderChar(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top, z);
        width += (slot->advance.x >> 6);
    }
    return width;
}

void FontRenderer::renderChar(FT_Bitmap_ *bitmap, double x, double y, double z) {
    glPushMatrix();
    glScaled(0.5, 0.5, 0.5);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLuint texture;
    glGenTextures(1, &texture);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Upload the glyph bitmap data to the texture object
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->width, bitmap->rows, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE,
                 bitmap->buffer);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Draw a quad at the specified position
    glBegin(GL_QUADS);

    // Bind the texture to the quad
    glBindTexture(GL_TEXTURE_2D, texture);

    // Calculate the texture coordinates based on the aspect ratio of the glyph
    float s0 = 0.0f;
    float t0 = 0.0f;
    float s1 = 1.0f;
    float t1 = 1.0f;


    // Set the texture coordinates for the quad
    glTexCoord2f(s0, t0);
    glVertex2f(x, y);
    glTexCoord2f(s1, t0);
    glVertex2f(x + bitmap->width, y);
    glTexCoord2f(s1, t1);
    glVertex2f(x + bitmap->width, y + bitmap->rows);
    glTexCoord2f(s0, t1);
    glVertex2f(x, y + bitmap->rows);

    glEnd();

    // Disable texturing when you are finished rendering the glyph
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();
}

void FontRenderer::renderText(const string &text, double size, double x, double y, double z) {
    glPushMatrix();
    glScaled(1, -1, 1);
    FT_GlyphSlot slot = ftFace->glyph;
    double rx = 0, ry = 0, rz = 0;
    for (char c: text) {
        FT_Set_Pixel_Sizes(ftFace, 0, (int)size);
        FT_Load_Char(ftFace, c, FT_LOAD_RENDER);

        renderChar(&slot->bitmap, rx + slot->bitmap_left, ry - slot->bitmap_top, rz);

        rx += slot->advance.x >> 6;
        ry += slot->advance.y >> 6;
    }
    glPopMatrix();
}

FontRenderer::~FontRenderer() {
    FT_Done_Face(ftFace);
    FT_Done_FreeType(ftLibrary);
}
