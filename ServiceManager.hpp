#pragma once
#ifndef _MY_SERVICE_MANAGER_HPP_
#define _MY_SERVICE_MANAGER_HPP_


#include "TaskManager.hpp"
#include "Service.hpp"
#include "Interruption.hpp"
#include "Enviroment.hpp"
#include "ActionLimitor.hpp"
#include <vector>


namespace my{
    class ServiceManager{
        private:
            Enviroment& enviroment;
            ActionManager actionManager;
            GroupManager groupManager;
            TaskManager taskManager;
            ActionLimitor actionLimitor;

            std::vector<Interruption*> interruptions;
            std::vector<Service*> services;
            std::map<Service*, int> lastCall;
            bool first = true;

            void firstRun();
            void action();
            void runService();

        public:
            ServiceManager(Enviroment& enviroment);
            virtual ~ServiceManager();
            void addService(Service* service);
            void addInterruption(Interruption* interruption);
            void tick();
    };
}

#endif

