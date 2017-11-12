#include "SmartStartGroupService.hpp"


#include "model/Vehicle.h"
#include <map>
#include "Repos.hpp"

#include "SelectTask.hpp"
#include "AsyncMoveTask.hpp"
#include "AsyncDeltaTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "ChangeStateTask.hpp"
#include "GridGroupTask.hpp"
#include "SleepTask.hpp"
#include "AsyncRotateTask.hpp"
#include "StopTask.hpp"

namespace my{

    void SmartStartGroupService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
    }

    int SmartStartGroupService::getRate(){
        return RATE;
    }

    model::VehicleType SmartStartGroupService::convert(int a){
        switch (a){
            case 2:
                return model::VehicleType::IFV;
            case 3:
                return model::VehicleType::TANK;
            case 4:
                return model::VehicleType::FIGHTER;
            case 5:
                return model::VehicleType::HELICOPTER;
            default:
                return model::VehicleType::ARRV;
        }
    }

    bool SmartStartGroupService::action(){
        taskManager->addTask(new ChangeStateTask(StateType::Group));

        int ground[3][3];
        int air[3][3];
        for (int i=0; i<3; i++)
            for (int ii=0; ii<3; ii++)
                ground[i][ii] = air[i][ii] = 0;

        double cx, cy;
        int arrvsY, IFVsY, tanksY, fighterY, helicopterY;

        Repos::getCenter(vehicleManager->getmyArrvs(), cx, cy);
        arrvsY = ((int)cy) / 74;
        ground[((int)cx) / 74][((int)cy) / 74] = 1;

        Repos::getCenter(vehicleManager->getmyIFVs(), cx, cy);
        IFVsY = ((int)cy) / 74;
        ground[((int)cx) / 74][((int)cy) / 74] = 2;

        Repos::getCenter(vehicleManager->getmyTanks(), cx, cy);
        tanksY = ((int)cy) / 74;
        ground[((int)cx) / 74][((int)cy) / 74] = 3;

        Repos::getCenter(vehicleManager->getmyFighters(), cx, cy);
        fighterY = ((int)cy) / 74;
        air[((int)cx) / 74][((int)cy) / 74] = 4;

        Repos::getCenter(vehicleManager->getmyHelicopters(), cx, cy);
        helicopterY = ((int)cy) / 74;
        air[((int)cx) / 74][((int)cy) / 74] = 5;

        int count = 0;
        for (int ii=0; ii<3; ii++)
            for (int i=0; i<3; i++)
                if (ground[i][ii]){
                    int d = count - i;
                    if (d){
                        taskManager->addTask(new SelectTask(convert(ground[i][ii])));
                        taskManager->addTask(new AsyncDeltaTask(d*74, 0));
                    }
                    count ++;
                }

        count = 0;
        for (int ii=0; ii<3; ii++)
            for (int i=0; i<3; i++)
                if (air[i][ii]){
                    int d = count - i;
                    if (d){
                        taskManager->addTask(new SelectTask(convert(air[i][ii])));
                        taskManager->addTask(new AsyncDeltaTask(d*74, 0));
                    }
                    count ++;
                }

        taskManager->addTask(new SpeedBarrierTask(0.1));

        taskManager->addTask(new SelectTask(model::VehicleType::ARRV));

        taskManager->addTask(new AsyncDeltaTask(0, (0 - arrvsY - 2.5)*74));

        taskManager->addTask(new SelectTask(model::VehicleType::IFV));
        if (IFVsY != 0)
            taskManager->addTask(new AsyncDeltaTask(0, (0 - IFVsY)*74));


        taskManager->addTask(new ChangeStateTask(StateType::Idle));
        return true;
    }

}

