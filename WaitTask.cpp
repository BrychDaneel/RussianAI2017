#include "WaitTask.hpp"


namespace my{
    WaitTask::WaitTask(int time, bool interrupt){
        this->time = time;
        this->interrupt = interrupt;
    }

    bool WaitTask::canInterrupt(){
        return interrupt;
    }

    void WaitTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
    }

    bool WaitTask::action(){

        if (env->getWorld()->getTickIndex() >= time)
            return false;

        return true;
    }
}


