#pragma once
#ifndef _MY_BIND_TASK_HPP_
#define _MY_BIND_TASK_HPP_

#include "Task.hpp"


namespace my{
    class BindTask : public Task{
        private:
            GroupManager * groupManager;
            std::string groupName;
            bool firstRun;
        public:
            BindTask(const std::string& groupName);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif


