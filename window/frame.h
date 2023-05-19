//
// Created by Braden Nicholson on 5/18/23.
//

#ifndef GENES_FRAME_H
#define GENES_FRAME_H


#include "../gfx.h"
#include <map>
#include "pane.h"

using std::map;
using std::pair;

struct PaneBounds {
    int col;
    int row;
    int spanX;
    int spanY;
};

class Frame {

public:

    Frame(int cols, int rows, int width, int height, int gap);

    void addPane(int col, int row, int spanX, int spanY, Pane *pane);

    void render(GFX *gfx);

private:

    vector<pair<PaneBounds, Pane*>> panes;

    bool showGrid = false;

    void recalculateSize();

    int cols = 12;
    int rows = 12;

    int width = 0;
    int height = 0;

    int gap = 0;

    int cellWidth = 0;
    int cellHeight = 0;

    int guttersX = 0;
    int guttersY = 0;

    int spanHeight(int spanCols) const;
    int spanWidth(int spanRows) const;

    int paneOffsetX(int col) const;
    int paneOffsetY(int row) const;


};


#endif //GENES_FRAME_H
