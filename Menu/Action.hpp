//
// Created by lior on 09/06/19.
//

#ifndef DEVICESMANAGER_ACTION_HPP
#define DEVICESMANAGER_ACTION_HPP

#include <functional>
#include <string>

enum actionType { BASE = 0, EXIT = 1}; /* You can add more types of action here,
                                       for any type you need implement subclass of Action */


class Action {
private:
    unsigned int _id;                                       /* ID of the action (unique number)*/
    const std::string _description;                         /* Description of the action method */
    bool _hasInput;
    std::string _input;                                     /* Input of the action method */
    const std::function<bool()> _methodWithoutArg;          /* Hold the action execute method */
    const std::function<bool(std::string)> _methodWithArg;  /* Hold the action execute method.
                                                             * The method itself is responsible for input verification */
    const std::string _inputDescription;                    /* Description of the input */

protected:
    actionType _type = actionType::BASE;

public:
    Action(unsigned int id, std::string description, std::function<bool(std::string)> methodWithArg, std::string  inputDescription)
    : _id(id), _description(std::move(description)), _hasInput(true), _methodWithoutArg(nullptr), _methodWithArg(std::move(methodWithArg)), _inputDescription(std::move(inputDescription)) {}
    Action(unsigned int id, std::string description, std::function<bool()> methodWithoutArg)
    : _id(id), _description(std::move(description)), _hasInput(false), _methodWithoutArg(std::move(methodWithoutArg)), _methodWithArg(nullptr) {}

    unsigned int getId() const;
    const std::string &getDescription() const;
    bool hasInput() const;
    const std::string &getInput() const;
    const std::function<bool()> &getMethodWithoutArg() const;
    const std::function<bool(std::string)> &getMethodWithArg() const;
    const std::string &getInputDescription() const;
    actionType getType() { return _type; };
    bool execute();
};


#endif //DEVICESMANAGER_ACTION_HPP
