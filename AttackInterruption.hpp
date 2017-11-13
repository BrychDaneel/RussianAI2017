#pragma once
#ifndef _MY_ATTACK_INTERRUPTION_HPP_
#define _MY_ATTACK_INTERRUPTION_HPP_


#include "Interruption.hpp"


namespace my{
    class AttackInterruption : public Interruption{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            ActionManager* actionManager;
            GroupManager* groupManager;
            int lastCall = 0;
            bool first = true;
        public:
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
            virtual void action();
    };
}


#endif
