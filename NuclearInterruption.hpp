#pragma once
#ifndef _MY_NUCLEAR_INTERRUPTION_HPP_
#define _MY_NUCLEAR_INTERRUPTION_HPP_


#include "Interruption.hpp"


namespace my{
    class NuclearInterruption : public Interruption{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            ActionManager* actionManager;
            GroupManager* groupManager;
            const char * groupName;
            bool recall;
            bool checkStartGroup;
            int last_call;
        public:
            NuclearInterruption(const char * groupName = "Army", bool recall=true, bool checkStartGroup=false);
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
            virtual void action();
    };
}


#endif

