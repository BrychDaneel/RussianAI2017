#include "ActionLimitor.hpp"


namespace my{
    ActionLimitor::ActionLimitor(const Enviroment& env) :
        env(env)
    {
    }

    void ActionLimitor::setup(){
        actionDetectionInterval = env.getGame()->getActionDetectionInterval();
        baseActionCount = env.getGame()->getBaseActionCount();
        additionalActionCountPerControlCenter = env.getGame()->getAdditionalActionCountPerControlCenter();

        for (int i=0; i<actionDetectionInterval; i++)
            history.push(false);
    }

    void ActionLimitor::tick(const bool action){
        if (history.front())
            count--;
        history.pop();

        if (action){
            count++;
            delta = 0;
        } else
            delta ++;
        history.push(action);
    }

    const bool ActionLimitor::canAction() const{
        return count < getLimit();
    }

    const int ActionLimitor::getLimit() const{
        return baseActionCount;
    }

    const int ActionLimitor::getCount() const{
        return count;
    }

    const int ActionLimitor::getDelta() const{
        return delta;
    }

    const int ActionLimitor::getInterval() const{
        return actionDetectionInterval;
    }
}
