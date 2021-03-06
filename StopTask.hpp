#pragma once
#ifndef _MY_STOP_TASK_HPP_
#define _MY_STOP_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include <string>


namespace my{
    class StopTask : public Task{
        private:
            bool firstRun = true;
            ActionManager* actionManager;
        public:
            StopTask();
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

