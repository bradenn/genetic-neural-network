//
// Created by Braden Nicholson on 5/18/23.
//

#ifndef GENES_PANE_H
#define GENES_PANE_H

#include <string>
#include <utility>
#include "../gfx.h"


using std::string;

class Pane {

public:
    Pane(string title);
    virtual void render(GFX *gfx, int width, int height);

    string getTitle() {
        return title;
    };

private:
    string title;


};


#endif //GENES_PANE_H
