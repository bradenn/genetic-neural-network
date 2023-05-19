//
// Created by Braden Nicholson on 5/18/23.
//

#include "pane.h"

#include <utility>

void Pane::render(GFX *gfx, int width, int height) {
    gfx->drawRect(10, 10, 20, 20);
}

Pane::Pane(string title) : title(std::move(title)) {

}
