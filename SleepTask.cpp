#include "SleepTask.hpp"


namespace my{
    SleepTask::SleepTask(int time, bool interrupt){
        this->time = time;
        this->interrupt = interrupt;
    }

    bool SleepTask::canInterrupt(){
        if (firstRun)
            return false;
        return interrupt;
    }

    void SleepTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
    }

    bool SleepTask::action(){
        if (firstRun)
            startTime = env->getWorld()->getTickIndex();
        firstRun = false;

        if (env->getWorld()->getTickIndex() - startTime >= time)
            return false;

        return true;
    }
}

