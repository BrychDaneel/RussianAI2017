#include "GotoAngleService.hpp"


namespace my{
    bool GotoAngleService::action(){
        int width = env->getGame()->getWorldWidth();
        int height = env->getGame()->getWorldHeight();

        actionManager->select(0, 0, width, height);
        actionManager->move(width, height, 0.4 * 0.6);
        return true;
    }

    int GotoAngleService::getRate(){
        return RATE;
    }

    void GotoAngleService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }

    GotoAngleService::~GotoAngleService(){
    }
}

