#include "TaskManager.hpp"

namespace my{

    TaskManager::TaskManager(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager):
            env(env),
            actionManager(actionManager),
            groupManager(groupManager)
    {
    }

    TaskManager::~TaskManager(){
        while (!tasks.empty()){
            delete tasks.front();
            tasks.pop();
        }
    }

    void TaskManager::addTask(Task* task){
        tasks.push(task);
        task->setup(env, actionManager, groupManager);
    }

    bool TaskManager::action(){
        if (tasks.empty())
            return false;

        bool used = false;
        do{
            used = tasks.front()->action();
            if (!used){
                delete tasks.front();
                tasks.pop();
            }
        } while (!used && !tasks.empty());

        return used;
    }

    void TaskManager::clear(){
        while (!tasks.empty())
            tasks.pop();
    }

}
