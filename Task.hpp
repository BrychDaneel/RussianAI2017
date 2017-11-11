#pragma once

#ifndef _MY_TASK_HPP_
#define _MY_TASK_HPP_


#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"


namespace my{
    class Task{
        public:
            virtual ~Task(){};
            virtual bool action() = 0;
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager) = 0;
    };
}
#endif
