#pragma once
#ifndef _MY_PASCUDA_SERVICE_HPP_
#define _MY_PASCUDA_SERVICE_HPP_


#include "Service.hpp"
#include <string>


namespace my{
    class PascudaService : public Service{
        private:
            Enviroment * env;
            TaskManager * taskManager;
            const VehicleManager * vehicleManager;
            GroupManager * groupManager;
            int RATE = 30;
            const char * pascudaName;
            bool topPascuda;
            bool first = true;

            double nuclearCancelRadius;
            double pascudaDelta;
            double maxPascudaNuclearDist;
            double minPascudaNuclearDist;
            double maxPascudaDist;


            void firsRun();
        public:
            PascudaService(const bool topPascuda=true);
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif


