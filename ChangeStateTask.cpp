#include "ChangeStateTask.hpp"


namespace my{
    ChangeStateTask::ChangeStateTask(StateType newState){
        this->newState = newState;
    }

    void ChangeStateTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
    }

    bool ChangeStateTask::action(){
        if (env->getState() != newState)
            env->setState(newState);
        return false;
    }
}

