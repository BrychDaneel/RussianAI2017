#pragma once
#ifndef _MY_CHANGE_STATE_TASK_HPP_
#define _MY_CHANGE_STATE_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include "StateType.hpp"


namespace my{
    class ChangeStateTask : public Task{
        private:
            Enviroment* env;
            StateType newState;
        public:
            ChangeStateTask(StateType newState);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
