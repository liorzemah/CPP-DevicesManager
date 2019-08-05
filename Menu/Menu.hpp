//
// Created by lior on 09/06/19.
//

#ifndef DEVICESMANAGER_MENU_HPP
#define DEVICESMANAGER_MENU_HPP


#include <vector>
#include "Action.hpp"

class Menu {
private:
    std::vector<Action> _actions;
    bool _isAlive = false;
    bool _createExitAction;
    unsigned int _beginID, _endID;
    void display();

public:
    explicit Menu(unsigned int beginID, bool createsExitAction=true);
    void addAction(const std::string& description, const std::function<bool(std::string)>& method, const std::string& inputDescription);
    void addAction(const std::string& description, const std::function<bool()>& method);
    void addExitAction();
    void start();
    Action getAction(unsigned int id) { return _actions[id - _beginID]; }
    auto const getActionsCount() { return _actions.size(); };

};


#endif //DEVICESMANAGER_MENU_HPP
