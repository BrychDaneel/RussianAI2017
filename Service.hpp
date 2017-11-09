#pragma once
#ifndef _MY_SERVICE_HPP_
#define _MY_SERVICE_HPP_


#include "TaskManager.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"


namespace my{
    class Service{
        public:
            virtual bool action() = 0;
            virtual int getRate() = 0;
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager) = 0;
            virtual ~Service(){};
    };
}
#endif


