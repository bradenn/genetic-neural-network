//
// Created by Braden Nicholson on 5/18/23.
//

#ifndef GENES_NODE_H
#define GENES_NODE_H

#include <cstdint>
#include <string>
#include <utility>
#include <ios>
#include <sstream>

using std::string;

class Node {

public:
    Node(string name, string description, uint8_t type, uint8_t id, uint16_t bias)
            : name(std::move(name)), description(std::move(description)), type(type), id(id), bias(bias) {
    }

    string getName() {
        return name;
    }

    string getDescription() {
        return name;
    }

    string getHexAddress() const {
        std::stringstream stream;
        stream << std::hex << id;
        return stream.str();
    }

private:

    uint8_t type: 1;
    uint8_t id: 7;

    uint16_t bias;

    string name;
    string description;


};

#endif //GENES_NODE_H
