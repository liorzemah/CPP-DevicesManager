//
// Created by lior on 09/06/19.
//

#include <iostream>
#include "Action.hpp"


unsigned int Action::getId() const {
    return _id;
}

const std::string &Action::getDescription() const {
    return _description;
}

bool Action::hasInput() const {
    return _hasInput;
}

const std::string &Action::getInput() const {
    return _input;
}

const std::function<bool()> &Action::getMethodWithoutArg() const {
    return _methodWithoutArg;
}

const std::function<bool(std::string)> &Action::getMethodWithArg() const {
    return _methodWithArg;
}

const std::string &Action::getInputDescription() const {
    return _inputDescription;
}


bool Action::execute() {
    if (_hasInput){
        do {
            std::cout << _inputDescription << ":";
            std::cin >> _input;
        }
        while(_input.empty());
        return _methodWithArg(_input);
    }
    else
        return _methodWithoutArg();
}