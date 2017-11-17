#pragma once
#ifndef _MY_DISMISS_TASK_HPP_
#define _MY_DISMISS_TASK_HPP_

#include "Task.hpp"


namespace my{
    class DismissTask : public Task{
        private:
            GroupManager * groupManager;
            std::string groupName;
            bool firstRun = true;
            ActionManager * actionManager;
        public:
            DismissTask(const char * groupName);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

