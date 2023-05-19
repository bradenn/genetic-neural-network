//
// Created by Braden Nicholson on 5/18/23.
//

#include "frame.h"

Frame::Frame(int cols, int rows, int width, int height, int gap)
        : cols(cols), rows(rows), width(width), height(height), gap(gap) {

    recalculateSize();
}

void Frame::addPane(int col, int row, int spanX, int spanY, Pane *pane) {

    auto pb = PaneBounds{
            .col = col,
            .row = row,
            .spanX = spanX,
            .spanY = spanY
    };

    panes.emplace_back(pb, pane);
}

int Frame::paneOffsetX(int col) const {
    int gutters = col + 1;
    int gutterWidth = gutters * gap;
    int colsOffset = (col) * cellWidth;
    return colsOffset + gutterWidth;
}

int Frame::paneOffsetY(int row) const {
    int gutters = row + 1;
    int gutterHeight = gutters * gap;
    int rowsOffset = (row) * cellHeight;
    return rowsOffset + gutterHeight;
}


int Frame::spanHeight(int spanCols) const {
    int gutterHeight = spanCols - 1;
    return (cellHeight * spanCols) + (gap * gutterHeight);
}

int Frame::spanWidth(int spanRows) const {
    int gutterWidth = spanRows - 1;
    return (cellWidth * spanRows) + (gap * gutterWidth);
}

void Frame::recalculateSize() {

    guttersX = cols - 1;
    cellWidth = (int) (((width - gap * 2) - (guttersX * gap)) / cols);
    guttersY = rows - 1;
    cellHeight = (int) (((height - gap * 2) - (guttersY * gap)) / rows);
}

void Frame::render(GFX *gfx) {


    if (showGrid) {
        glPushMatrix();
        glColor4f(1, 0.5, 0.05, 0.32);
//    gfx->drawRect(gap, gap, width - gap * 2, height - gap * 2);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                gfx->drawRect(paneOffsetX(i), paneOffsetY(j), spanWidth(1), spanHeight(1));
            }
        }
        glPopMatrix();
    }

    glPushMatrix();
    for (const auto &item: panes) {
        glColor4f(1, 1, 1, 0.32);
        auto bounds = item.first;
        auto pane = item.second;


        auto paneX = paneOffsetX(bounds.col);
        auto paneY = paneOffsetY(bounds.row);
        auto paneWidth = spanWidth(bounds.spanX);
        auto paneHeight = spanHeight(bounds.spanY);

//        glViewport(paneX, paneY, paneWidth, paneHeight);
//        printf("%d %d - %d %d\n", paneX, paneY, paneWidth, paneHeight);
        glPushMatrix();
        glTranslated(paneX, paneY, 0);
        gfx->text(pane->getTitle(), 32, 8, 16, 0);
        gfx->drawRect(0, 0, paneWidth, paneHeight);
        glTranslated(0, 24, 0);
        pane->render(gfx, paneWidth, paneHeight-32);
//        glEnable(GL_SCISSOR_TEST);
//        glScissor(0, 0, paneWidth, paneHeight);
//        glDisable(GL_SCISSOR_TEST);
        glPopMatrix();


    }
    glPopMatrix();
}

