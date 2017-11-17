#pragma once
#ifndef _MY_NUCLEAR_ACTIVE_INTERRUPTION_HPP_
#define _MY_NUCLEAR_ACTIVE_INTERRUPTION_HPP_


#include "CommonInterruption.hpp"


namespace my{
    class NuclearActiveInterruption : public CommonInterruption{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            ActionManager* actionManager;
            GroupManager* groupManager;
        public:
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
            virtual void action();
    };
}


#endif


