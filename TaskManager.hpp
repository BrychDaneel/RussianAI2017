#pragma once
#ifndef _MY_TASK_MANAGER_HPP_
#define _MY_TASK_MANAGER_HPP_


#include "Task.hpp"
#include "ActionManager.hpp"
#include <queue>


namespace my{
    class TaskManager{
        private:
            std::queue<Task *> tasks;
            Enviroment& env;
            ActionManager& actionManager;
            GroupManager& groupManager;

        public:
            TaskManager(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
            virtual ~TaskManager();
            void addTask(Task* task);
            void clear();
            bool canInterrupt();
            bool action();
    };
}


#endif
