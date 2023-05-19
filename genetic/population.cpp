//
// Created by Braden Nicholson on 5/16/23.
//

#include <cmath>
#include "population.h"
#include "random.h"
#include "deque"

using std::deque;

Population::Population(int size) : Pane("Population") {
    inputs = 8;
    neurons = 8;
    outputs = 4;
    genes = 1000;
    ticksPerGeneration = 1000;
    mutationRate = 10;
    for (int i = 0; i < size; ++i) {
        auto *g = new Genome(inputs, neurons, outputs, Genome::generateRandom(genes));
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
    double minDist = 0;
    double maxDist = 0;

    for (auto &genome: genomes) {
        map<uint8_t, uint16_t> in{};

        in[0] = (uint16_t) ((double) (1 << 16) +
                            sin(((2.0 * M_PI) / ticksPerGeneration * 4) * (ticks)) * ((1 << 16) / 2.0));

        in[1] = (uint16_t) ((double) (1 << 16) +
                            cos(((2.0 * M_PI) / ticksPerGeneration * 4) * (ticks)) * ((1 << 16) / 2.0));

        in[2] = (uint16_t) calcAngleAndMap(genome->posX, genome->posY, px, py, 0, 1 << 16);


        double dst = sqrt(pow(genome->posX - px, 2) + pow(genome->posY - py, 2));
        in[3] = ((1 << 16) / 2) - (int) (dst * 100.0);

        in[4] = genome->posX<px?(1<<16)/2:0; // +x
        in[5] = genome->posX>px?(1<<16)/2:0; // -x

        in[6] = genome->posY<py?(1<<16)/2:0; // +y
        in[7] = genome->posY>py?(1<<16)/2:0; // -y


        genome->distance = (double) dst;

        auto out = genome->compute(in);

        genome->posX += out[0] * 2;
        genome->posX -= out[1] * 2;
        genome->posY += out[2] * 2;
        genome->posY -= out[3] * 2;

        if (genome->posX > 600 || genome->posX < -600 || genome->posY > 600 || genome->posY < -600) {
            genome->score -= 1000;
        } else {
            if (dst < minDist) {
                minDist = dst;
            }

            if (dst > maxDist) {
                maxDist = dst;
            }
        }
    }

    min = minDist;
    max = maxDist;

    ticks = (ticks + 1) % ticksPerGeneration;

    std::sort(genomes.begin(), genomes.end(), [this](Genome *lhs, Genome *rhs) {
        auto lhsDistance = sqrt(pow(lhs->posX - px, 2) + pow(lhs->posY - py, 2));
        auto rhsDistance = sqrt(pow(rhs->posX - px, 2) + pow(rhs->posY - py, 2));
        return lhsDistance < rhsDistance;
    });

    int id = 0;

    for (const auto &item: genomes) {
        item->score += (int) genomes.size() / 2 - id;
        id++;
    }

    if (ticks == 0) {
        round++;


        px = cos((randomUInt() % 1000 / 250.0) * M_PI * 2) * 200;
        py = sin((randomUInt() % 1000 / 250.0) * M_PI * 2) * 200;

        std::sort(genomes.begin(), genomes.end(), [this](Genome *lhs, Genome *rhs) {
            return lhs->score > rhs->score;
        });


        vector<Genome *> pool;
        for (auto &item: genomes) {

            if (item->score < 0 && pool.size() >= genomes.size() / 2) {
                break;
            }

            pool.push_back(item);
        }

//
        vector<Genome *> nextGen;
        for (int i = 0; i < genomes.size() - 4; i += 2) {

            auto item = pool[(i) % pool.size()];
            auto mate = pool[(i + 1) % pool.size()];
            nextGen.push_back(
                    new Genome(item->numInputs, item->numNeurons, item->numOutputs, item->mingle(mate, mutationRate)));
            nextGen.push_back(
                    new Genome(mate->numInputs, mate->numNeurons, mate->numOutputs, mate->mingle(item, mutationRate)));
        }
        for (int i = 0; i < 4; ++i) {
            nextGen.push_back(new Genome(inputs, neurons, outputs, Genome::generateRandom(genes)));
        }


        for (auto &item: genomes) {
            delete item;
        }

        genomes.clear();
        pool.clear();


        std::sort(nextGen.begin(), nextGen.end(), [](Genome *lhs, Genome *rhs) {
            return randomUInt() > randomUInt();
        });

        genomes = nextGen;

        nextGen.clear();

    }
}

void Population::render(GFX *g, int width, int height) {

    int rows = 9;
    int cols = 6;

    int gap = 4;
    double lw = (double) (width) / cols;
    double lh = (double) (height) / rows;
    double lwG = (double) (width - (gap * (2 + cols - 1))) / cols;
    double lhG = (double) (height - (gap * (2 + rows - 1))) / rows;

    glPushMatrix();
//    glTranslated(-g->width / 2, -g->height / 2 + 10, 0);
    for (int i = 0; i < genomes.size(); i++) {
        glPushMatrix();
        glTranslated(gap / 2.0 + lw * (i % cols), gap / 2.0 + floor(i / cols) * lh, 0);
        genomes[i]->render(g, lwG, lhG, min, max);
        glPopMatrix();
    }

    glPopMatrix();

}
