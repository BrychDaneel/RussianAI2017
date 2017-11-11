#include "SleepTask.hpp"


namespace my{
    SleepTask::SleepTask(int time){
        this->time = time;
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

