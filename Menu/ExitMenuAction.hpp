//
// Created by lior on 14/06/19.
//

#ifndef DEVICESMANAGER_EXITMENUACTION_HPP
#define DEVICESMANAGER_EXITMENUACTION_HPP


#include <iostream>
#include "Action.hpp"

class ExitMenuAction final: public Action {
public:
    explicit ExitMenuAction(unsigned int lastIDReference) : Action(lastIDReference, "Exit from menu",
            []  {
                    std::cout << "Goodby..." << std::endl;
                    exit(0);
                    return true;
                }
    ){ _type = actionType::EXIT ; }

};


#endif //DEVICESMANAGER_EXITMENUACTION_HPP
