#pragma once
#ifndef _MY_SERVICE_MANAGER_HPP_
#define _MY_SERVICE_MANAGER_HPP_


#include "TaskManager.hpp"
#include "Service.hpp"
#include "Interruption.hpp"
#include "CommonInterruption.hpp"
#include "Enviroment.hpp"
#include "ActionLimitor.hpp"
#include <vector>


namespace my{
    class ServiceManager{
        private:
            Enviroment& enviroment;
            ActionManager actionManager;
            GroupManager groupManager;
            ActionLimitor actionLimitor;


            size_t cur = 0;
            std::vector<TaskManager> taskManagers;
            std::vector<std::vector<Interruption*> > threads_int;
            std::vector<CommonInterruption*> common_int;
            std::vector<std::vector<Service*> > threads;
            std::map<Service*, int> lastCall;
            bool first = true;

            void firstRun();
            void action();
            void runService();
            void changeThread();
            void fill(size_t threadCount);

        public:
            ServiceManager(Enviroment& enviroment);
            virtual ~ServiceManager();
            void addService(Service* service, size_t thread=0);
            void addInterruption(Interruption* interruption, size_t thread=0);
            void addCommonInterruption(CommonInterruption* interruption);
            void tick();
    };
}

#endif

