#pragma once
#ifndef _MY_GOTO_ANGLE_SERVICE_HPP_
#define _MY_GOTO_ANGLE_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class GotoAngleService : public Service{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            ActionManager* actionManager;
            GroupManager* groupManager;
            const int RATE = 0;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
            virtual ~GotoAngleService();
    };
}
#endif

