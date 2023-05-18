//
// Created by Braden Nicholson on 5/16/23.
//

#include <cmath>
#include "population.h"

Population::Population(int size) {
    for (int i = 0; i < size; ++i) {
        auto *g = new Genome(6, 10, 4, Genome::generateRandom(4000));
        map<uint8_t, uint16_t> inputs;
//        for (int d = 0; d < 10; ++d) {
//            time_t t;
//            time(&t);
//            srand(t);
//            uint8_t id = (rand() % 128) & 0xFFFF;
//            inputs[id] = rand() & 0xffff;
//        }
//        g->compute(inputs);
        genomes.push_back(g);
    }
}

double calcAngleAndMap(double x1, double y1, double x2, double y2, double p, double q) {
    // Calculate the angle in radians between the points
    double angle = atan2(y2 - y1, x2 - x1);

    // Normalize the angle to be between 0 and 2*pi
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    // Normalize the angle to be between 0 and 1
    double normalized_angle = angle / (2 * M_PI);

    // Map the angle to be between p and q
    double mapped_value = p + normalized_angle * (q - p);

    return mapped_value;
}

void Population::tick() {
    int minDist = 0;
    int minGenome = 0;
    int maxDist = 0;
    int maxGenome = 0;


    for (int i = 0; i < genomes.size(); i++) {


        map<uint8_t, uint16_t> inputs;
        auto a = std::chrono::steady_clock::now();
        auto value = (a.time_since_epoch().count()) % 1000;

        inputs[1] = (uint16_t) ((double) (1 << 16) + cos((2.0 * M_PI) * ((double) value / 1000.0/100.0)) * (2 ^ 16 /
                                                                                                                2));

        inputs[1] = (uint16_t) ((double) (1 << 16) + cos((2.0 * M_PI) * ((double) value / 1000.0/100.0)) * (2 ^ 16 /
                2));

        inputs[2] = (uint16_t) calcAngleAndMap(genomes[i]->posX, genomes[i]->posY, px, py, 0, 1 << 16);
        inputs[3] = (int) sqrt(pow(genomes[i]->posX - px, 2) + pow(genomes[i]->posY - py, 2));
        inputs[4] = (1 << 16)+(int)(px-genomes[i]->posX);
        inputs[5] = (1 << 16)+(int)(py-genomes[i]->posY);

        if (inputs[3] < minDist) {
            minDist = inputs[3];
            minGenome = i;
        }

        if (inputs[3] > maxDist) {
            maxDist = inputs[3];
            maxGenome = i;
        }

        auto out = genomes[i]->compute(inputs);
        genomes[i]->aX += out[0] * 1;
        genomes[i]->aY += out[1] * 1;
        genomes[i]->aX -= out[2] * 1;
        genomes[i]->aY -= out[3] * 1;

        if (genomes[i]->posX > 500 || genomes[i]->posX < -500 || genomes[i]->posY > 500 || genomes[i]->posY < -500) {
            genomes[i]->score = -1000;
        }


    }

    ticks++;

    if (ticks >= 1000) {
        round++;
        ticks = 0;
    }

    std::sort(genomes.begin(), genomes.end(), [this](Genome *lhs, Genome *rhs) {
        return sqrt(pow(lhs->posX - px, 2) + pow(lhs->posY - py, 2)) < sqrt(pow(rhs->posX - px,2) + pow(rhs->posY -
                                                                                                        py, 2));
    });
    int id = 0;
    for (const auto &item: genomes) {
        item->score += ((int)genomes.size()/2)-id;
//        printf("%d - %d\n", id, item->score);
        id++;
    }

    if (ticks == 0) {


        std::sort(genomes.begin(), genomes.end(), [this](Genome *lhs, Genome *rhs) {
            return lhs->score > rhs->score;
        });
        vector<Genome *> pool;


        int cnt = 0;
        vector<Genome *> nextGen;

        px = cos((rand() % 1000 / 250.0) * M_PI * 2) * 350;
        py = sin((rand() % 1000 / 250.0) * M_PI * 2) * 350;

        Genome *last = nullptr;
        for (auto &item: genomes) {
//            printf("%d - %d\n", cnt, item->score);

            if (cnt >= genomes.size() /4) {
                break;
            }
            if (last == nullptr) {
                last = item;
                continue;
            }

            nextGen.push_back(new Genome(item->numInputs, item->numNeurons, item->numOutputs, item->mingle(last)));
            nextGen.push_back(new Genome(item->numInputs, item->numNeurons, item->numOutputs, item->mingle(last)));
            nextGen.push_back(new Genome(item->numInputs, item->numNeurons, item->numOutputs, last->mingle(item)));
            nextGen.push_back(new Genome(item->numInputs, item->numNeurons, item->numOutputs, last->mingle(item)));
            last = nullptr;

            cnt++;
        }
        for (auto &item: genomes) {
            delete item;
        }
        genomes.clear();

//        std::sort(nextGen.begin(), nextGen.end(), [](Genome *lhs, Genome *rhs) {
//            auto a = std::chrono::steady_clock::now();
//            auto value = (a.time_since_epoch().count());
//            std::srand(value);
//            auto c = std::rand();
//            a = std::chrono::steady_clock::now();
//            value = (a.time_since_epoch().count());
//            std::srand(value);
//            auto b = std::rand();
//            return c > b;
//        });
        genomes = nextGen;

    }
}

void Population::render(GFX *g) {
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(g->width/2,0,0);
    glEnd();
    glPopMatrix();
    double xPadding = 10;
    double lw = (g->width - xPadding * 2) / (double) genomes.size();
    double lh = g->height / 8.0;


    glPushMatrix();
    glTranslated(-g->width / 2, -g->height / 2 + 10, 0);
    for (int i = 0; i < genomes.size(); i++) {
        glPushMatrix();
        glTranslated(lw * i + xPadding, 0, 0);
        genomes[i]->render(g, lw, lh);
        glPopMatrix();
    }

    glPopMatrix();

    glPushMatrix();
    glTranslated(0, g->height / 4 + 10, 0);
    for (int i = 0; i < genomes.size(); i++) {
        genomes[i]->drawChar(g);
    }

    g->drawRect(px - 20, py - 20, 40, 40);
    glPopMatrix();
}
