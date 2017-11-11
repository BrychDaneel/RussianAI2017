#include "GotoAngleService.hpp"


#include "AsyncMoveTask.hpp"
#include "ChangeStateTask.hpp"


namespace my{
    bool GotoAngleService::action(){
        if (env->getState() != StateType::Idle)
            return false;

        int width = env->getGame()->getWorldWidth();
        int height = env->getGame()->getWorldHeight();

        taskManager->addTask(new ChangeStateTask(StateType::Attack));
        taskManager->addTask(new AsyncMoveTask("All", width, height, 0.4*0.6));
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

