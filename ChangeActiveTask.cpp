#include "ChangeActiveTask.hpp"


namespace my{
    ChangeActiveTask::ChangeActiveTask(ActiveType newActive){
        this->newActive = newActive;
    }

    void ChangeActiveTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
    }

    bool ChangeActiveTask::action(){
        if (env->getActive() != newActive)
            env->setActive(newActive);
        return false;
    }
}


