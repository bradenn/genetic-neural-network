//
// Created by Braden Nicholson on 5/18/23.
//

#include "frame.h"

Frame::Frame(int cols, int rows, int width, int height, int gap)
        : cols(cols), rows(rows), width(cols), height(rows), gap(gap) {


}

void Frame::addPane(int col, int row, int spanX, int spanY) {

}

int Frame::spanHeight(int spanCols) const {
    int gutterHeight = spanCols-1;
    return (cellHeight * spanCols) + (gap * gutterHeight);
}

int Frame::spanWidth(int spanRows) const {
    int gutterWidth = spanRows-1;
    return (cellWidth * spanRows) + (gap * gutterWidth);
}

void Frame::recalculateSize() {
    guttersX = 2 + cols - 1;
    cellWidth = (int) ((width - (guttersX * gap)) / cols);
    guttersY = 2 + rows - 1;
    cellHeight = (int) ((height - (guttersY * gap)) / rows);
}

void Frame::render(GFX *gfx) {



}
