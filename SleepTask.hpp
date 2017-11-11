#pragma once
#ifndef _MY_SLEEP_TASK_HPP_
#define _MY_SLEEP_TASK_HPP_


#include "Task.hpp"


namespace my{
    class SleepTask : public Task{
        private:
            Enviroment * env;
            bool firstRun = true;
            int startTime;
            int time;
        public:
            SleepTask(int time);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif



