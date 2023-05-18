//
// Created by Braden Nicholson on 5/16/23.
//

#include <cmath>
#include "genome.h"
#include "random.h"

Genome::Genome(uint8_t inputs, uint8_t neurons, uint8_t outputs, const vector<Gene> &genes) {


    this->genes = genes;
    this->core = genes;
    auto a = std::chrono::high_resolution_clock::now();
    std::srand(a.time_since_epoch().count());
    posX = 250 - std::rand() % 500;
    posY = 250 - std::rand() % 500;
    numInputs = inputs;
    numNeurons = neurons;
    numOutputs = outputs;
    resetValues();
    cullGenes();

}

vector<Gene> Genome::generateRandom(int numGenes) {
    auto genes = vector<Gene>();
    auto a = std::chrono::high_resolution_clock::now();
    std::srand(a.time_since_epoch().count());

    for (int i = 0; i < numGenes; ++i) {
        auto g = Gene{};
        g.sourceType = std::rand();
        g.sourceId = (uint16_t) (std::rand() % 128) & 0x7fff;
        g.destinationType = std::rand();
        g.destinationId = (uint16_t) (std::rand() % 128) & 0x7fff;
        g.weight = Gene::randomWeight();
        genes.push_back(g);
    }
    return genes;
}

bool Genome::geneSourceExists(Gene gene) {
    switch (gene.sourceType) {
        case INPUT:
            if (inputs.find(gene.sourceId) != inputs.end()) {
                return true;
            }
            break;
        case NEURON:
            if (neurons.find(gene.sourceId) != neurons.end()) {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool Genome::geneDestinationExists(Gene gene) {
    switch (gene.destinationType) {
        case NEURON:
            if (neurons.find(gene.destinationId) != neurons.end()) {
                return true;
            }
            break;
        case OUTPUT:
            if (outputs.find(gene.destinationId) != outputs.end()) {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}


bool Genome::geneIsValid(Gene gene) {
    return geneSourceExists(gene) && geneDestinationExists(gene);
}

void Genome::cullGenes() {
    vector<Gene> replacement;
    for (const auto &item: genes) {
        if (geneIsValid(item)) {
            replacement.push_back(item);
        }
    }
    genes = replacement;
}

void Genome::resetValues() {
    for (int i = 0; i < numInputs; ++i) {
        this->inputs[i] = 0;
//        printf("I 0x%x\n", (i & 0x7fff));
    }

    for (int i = 0; i < numNeurons; ++i) {
        this->neurons[i] = 0;
        neuronCount[i] = 0;
//        printf("N 0x%x\n", (i & 0x7fff));
    }

    for (int i = 0; i < numOutputs; ++i) {
        this->outputs[i] = 0;
        outputCount[i] = 0;
//        printf("O 0x%x\n", (i & 0x7fff));
    }

}
float sigmoid(float x) {
    float result;
    result = 1 / (1 + exp(-x));
    return result;
}
map<uint8_t, float> Genome::compute(const map<uint8_t, uint16_t> &stimuli) {

    vX = vX + aX * 0.01;
    vY = vY + aY * 0.01;

    posX = posX +vX * 0.01;
    posY = posY + vY * 0.01;

    if (genes.empty()) {
        score = -INT_MAX;
        return map<uint8_t, float>{};
    }
//    printf("%zu working genes\n", genes.size());
    resetValues();


    for (const auto &item: stimuli) {
        if (inputs.find(item.first) != inputs.end()) {
            inputs[item.first] = (float) item.second / ((1 << 16) / 4.0f);
        }
    }
    // Handle input-neuron & input-output action
    for (const auto &item: genes) {
        if (item.sourceType == NEURON) continue;
        if (inputs.find(item.sourceId) != inputs.end()) {
            auto weight = inputs[item.sourceId] * item.normalizeWeight();
            if (item.destinationType == NEURON) {
                neurons[item.destinationId] += weight;
                neuronCount[item.destinationId]++;
            } else if (item.destinationType == OUTPUT) {
                outputs[item.destinationId] += weight;
                outputCount[item.destinationId]++;
            }
        }
    }
    // Handle neuron-neuron action
    for (const auto &item: genes) {
        if (item.sourceType != NEURON) continue;
        if (item.destinationType != NEURON) continue;

        if (neurons.find(item.sourceId) != neurons.end()) {
            auto weight = neurons[item.sourceId] * item.normalizeWeight();
            neurons[item.destinationId] += weight;
            neuronCount[item.destinationId]++;
        }
    }
    // Handle neuron activation
    for (auto &item: neurons) {
        item.second = tanh(item.second);
    }
    // Handle neuron-output action
    for (const auto &item: genes) {
        if (item.sourceType != NEURON) continue;
        if (item.destinationType != OUTPUT) continue;

        if (neurons.find(item.sourceId) != neurons.end()) {
            auto weight = neurons[item.sourceId] * item.normalizeWeight();
            outputs[item.destinationId] += weight;
            outputCount[item.destinationId]++;
        }
    }
    // Handle output activation
    for (auto &item: outputs) {
        item.second = tanh(item.second);
    }

    auto out = outputs;


    return out;
}
void setColor(double value) {
    if (value < 0.0 || value > 1.0) {
        // Invalid value, handle error here.
        return;
    }

    double r, g, b;
    if (value < 0.5) {
        // Fade from blue to green
        r = 0.0;
        g = value * 2.0;
        b = 1.0 - value * 2.0;
    } else {
        // Fade from green to red
        value -= 0.5;  // Adjust value to be in range [0, 0.5]
        r = value * 2.0;
        g = 1.0 - value * 2.0;
        b = 0.0;
    }

    glColor4d(r, g, b, 1.0);
}
void Genome::render(GFX *g, double dx, double dy) {

    glPushMatrix();
    glColor4d(1, 1, 1, 0.3);
    g->drawRect(0, 0, dx, dy);

    double xGap = 5;
    double yGap = 10;
    double inputY = (dy - yGap * 1) / (double) inputs.size();

    double gutter = xGap;
    double layerX = ((dx - xGap * 4) / 3);

    glTranslated(xGap, yGap, 0);

    int idx = 0;
    for (const auto &item: inputs) {
        setColor(item.second);
        g->drawRect(0, inputY * idx, layerX, inputY - yGap);
        idx++;
    }

    double neuronY = (dy - yGap * 1) / (double) neurons.size();
    idx = 0;
    for (const auto &item: neurons) {
        setColor(item.second);
        g->drawRect(layerX + gutter, neuronY * idx, layerX, neuronY - yGap);
        idx++;
    }

    double outputY = (dy - yGap * 1) / (double) outputs.size();
    idx = 0;
    for (const auto &item: outputs) {
        setColor(item.second);
        g->drawRect(layerX * 2 + gutter * 2, outputY * idx, layerX, outputY - yGap);
        idx++;
    }
    glColor4d(1, 1, 1, 0.3);
    double nSep = 0;
    double nSepCnt = 0;
    for (const auto &item: genes) {
        if (item.sourceType == item.destinationType && item.sourceType == NEURON) nSepCnt++;
    }
    double nSepDx = layerX / nSepCnt;

    for (const auto &item: genes) {
        setColor(item.normalizeWeight());
        glLineWidth(item.normalizeWeight() * 4);
        glBegin(GL_LINES);
//        if(item.sourceType != INPUT || item.destinationType != NEURON) continue;
        int si = 0;
        int sf = -1;
        switch (item.sourceType) {
            case INPUT:
                for (const auto &input: inputs) {
                    if (item.sourceId == (uint16_t) input.first) {
                        sf = si;
                        break;
                    }
                    si++;
                }
                if (sf == -1) break;
                glVertex3d(layerX / 2, inputY * sf + inputY / 2 - yGap / 2, 0);
                break;
            case NEURON:
                for (const auto &input: neurons) {
                    if (item.sourceId == (uint16_t) input.first) {
                        sf = si;
                        break;
                    }
                    si++;
                }
                if (sf == -1) break;
                if (item.destinationType == NEURON) {
                    glVertex3d(layerX + gutter + (nSepDx * nSep),
                               neuronY * sf + neuronY
                                              / 2 - yGap
                                                    / 2,
                               0);
                } else {
                    glVertex3d(layerX * 2 + gutter, neuronY * sf + neuronY / 2 - yGap / 2, 0);
                }
                break;
            default:
                break;
        }

        int ni = 0;
        int nf = -1;
        switch (item.destinationType) {
            case NEURON:
                for (const auto &neuron: neurons) {
                    if (item.destinationId == (uint16_t) neuron.first) {
                        nf = ni;
                        break;
                    }
                    ni++;
                }
                if (nf == -1) break;
                if (item.sourceType == NEURON) {
                    glVertex3d(layerX + gutter + (nSepDx * nSep), neuronY * nf +
                                                                  neuronY / 2 -
                                                                  yGap / 2, 0);
                    nSep++;
                } else {
                    glVertex3d(layerX * 1 + gutter, neuronY * nf + neuronY / 2 - yGap / 2, 0);
                }
            case OUTPUT:
                for (const auto &neuron: outputs) {
                    if (item.destinationId == (uint16_t) neuron.first) {
                        nf = ni;
                        break;
                    }
                    ni++;
                }
                if (nf == -1) break;
                glVertex3d(layerX * 2.5 + gutter * 2, outputY * nf + outputY / 2 - yGap / 2, 0);
            default:
                break;
        }
        glEnd();
        glLineWidth(1);


    }

    glPopMatrix();

}

void Genome::drawChar(GFX *g) {
    glPushMatrix();
    glColor4d(1, 1, 1, 0.3);
    g->drawRect(posX, posY, 10, 10);
    glPopMatrix();

}

vector<Gene> Genome::mingle(Genome *mate) {

    vector<Gene> set;
    auto a = std::chrono::high_resolution_clock::now();
    std::srand(a.time_since_epoch().count() / 1000 / 10);
    for (int i = 0; i < core.size(); ++i) {
        if (i <= core.size() / 2) {
            if (std::rand() % 2000 == 1) {
                flipRandomBit(core[i]);
                set.push_back(core[i]);
            } else {
                set.push_back(core[i]);

            }

        } else {
            if (std::rand() % 2000 == 1) {
                flipRandomBit(mate->core[i]);
                set.push_back(mate->core[i]);
            } else {
                set.push_back(mate->core[i]);
            }
        }
    }

    return set;
}

