#pragma once
#ifndef _MY_INTERRUPTION_HPP_
#define _MY_INTERRUPTION_HPP_


#include "TaskManager.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"


namespace my{
    class Interruption{
        public:
            virtual ~Interruption(){};
            virtual void setup(Enviroment& env, TaskManager& taskManager,
                            ActionManager& actionManager, GroupManager& groupManager) = 0;
            virtual void action() = 0;
    };
}


#endif

