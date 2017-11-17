#pragma once
#ifndef _MY_COMMON_INTERRUPTION_HPP_
#define _MY_COMMON_INTERRUPTION_HPP_


#include "TaskManager.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"


namespace my{
    class CommonInterruption{
        public:
            virtual ~CommonInterruption(){};
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager) = 0;
            virtual void action() = 0;
    };
}


#endif

