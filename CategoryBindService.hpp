#pragma once
#ifndef _MY_CATEGORY_BIND_SERVICE_HPP_
#define _MY_CATEGORY_BIND_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class CategoryBindService : public Service{
        private:
            ActionManager* actionManager;
            GroupManager* groupManager;
            const int RATE = 0;
            double width;
            double height;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

