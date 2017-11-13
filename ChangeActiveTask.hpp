#pragma once
#ifndef _MY_CHANGE_ACTIVE_TASK_HPP_
#define _MY_CHANGE_ACTIVE_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include "ActiveType.hpp"


namespace my{
    class ChangeActiveTask : public Task{
        private:
            Enviroment* env;
            ActiveType newActive;
        public:
            ChangeActiveTask(ActiveType newActive);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

