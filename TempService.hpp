#pragma once
#ifndef _MY_TEMP_SERVICE_HPP_
#define _MY_TEMP_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class TempService : public Service{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            ActionManager* actionManager;
            GroupManager* groupManager;
            const int RATE = 60;
            int sg = 1;
            bool firstRun = true;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif
