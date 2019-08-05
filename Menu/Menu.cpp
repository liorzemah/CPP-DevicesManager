#include <iostream>
#include "Menu.hpp"
#include "ExitMenuAction.hpp"

void Menu::addAction(const std::string &description, const std::function<bool(std::string)> &method, const std::string& inputDescription) {
    _endID = _actions.size() + _beginID;
    _actions.emplace_back(_endID , description, method, inputDescription);
}

void Menu::addAction(const std::string &description, const std::function<bool()> &method) {
    _endID = _actions.size() + _beginID;
    _actions.emplace_back(_actions.size() + _beginID, description, method);
}

void Menu::addExitAction() {
    _createExitAction = true;
}

Menu::Menu(unsigned int beginID, bool createExitAction) : _beginID(beginID), _endID(beginID), _createExitAction(createExitAction){

}

void Menu::start()
{
    if (_createExitAction) {
        if (_actions[getActionsCount() - 1].getType() != actionType::EXIT)
            _actions.push_back(ExitMenuAction(_actions.size() + _beginID));
    } else{
        if (_actions[getActionsCount() - 1].getType() == actionType::EXIT)
            _actions.pop_back();
    }
    _isAlive = true;
    while (_isAlive)
        display();
}

void Menu::display() {
    bool hasException;
    int actionID = 0;
    do {
        hasException = false;
        std::cout << "Devices monitor menu: " << std::endl;
        for (auto const &action : _actions) {
            std::cout << action.getId() << ". " << action.getDescription() << std::endl;

        }
        std::cout << "Please enter a number of action (" << _beginID << "-" << (_beginID + _actions.size() - 1) << "): "
                  << std::endl;

        try {
            std::string input;
            std::cin >> input;
            actionID = std::stoi(input);
        }catch (std::invalid_argument &e)
        {
            std::cerr << "Invalid input, please try again " << std::endl;
            hasException = true;
        }

    } while(hasException || actionID < _beginID || actionID > (_beginID + _actions.size() - 1));
    getAction(actionID).execute();
}





