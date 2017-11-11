#pragma once
#ifndef _MY_SELECT_TASK_HPP_
#define _MY_SELECT_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include <string>


namespace my{
    class SelectTask : public Task{
        private:
            ActionManager* actionManager;
            GroupManager* groupManager;
            int gid;
            std::string name;
            double width;
            double height;
            double left, top, right, bottom;
            bool firstRun = true;

            enum class SelectType{All, GID, Name, Rect} selectType;
        public:
            SelectTask();
            SelectTask(int groupId);
            SelectTask(const std::string & groupName);
            SelectTask(double left, double top, double right, double bottom);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif


