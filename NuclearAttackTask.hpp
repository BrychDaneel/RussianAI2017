#pragma once
#ifndef _MY_NUCLEAR_ATTACK_TASK_HPP_
#define _MY_NUCLEAR_ATTACK_TASK_HPP_


#include "Task.hpp"


namespace my{
    class NuclearAttackTask : public Task{
        private:
            bool firstRun = true;
            ActionManager * actionManager;
            long unitId;
            double x, y;
        public:
            NuclearAttackTask(long unitId, double x, double y);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
