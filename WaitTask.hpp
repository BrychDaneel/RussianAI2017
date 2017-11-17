#pragma once
#ifndef _MY_WAIT_TASK_HPP_
#define _MY_WAIT_TASK_HPP_


#include "Task.hpp"


namespace my{
    class WaitTask : public Task{
        private:
            Enviroment * env;
            int time;
            bool interrupt;
        public:
            WaitTask(int time, bool interrupt=true);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
            virtual bool canInterrupt();
    };
}
#endif




