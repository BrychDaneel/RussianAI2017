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
#include "AsyncScaleTask.hpp"
#include "ChangeActiveTask.hpp"
#include "BindTask.hpp"

#include "pi.hpp"

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
        int arrvsX, IFVsX, tanksX, fighterX, helicopterX;

        Repos::getCenter(vehicleManager->getmyArrvs(), cx, cy);
        arrvsY = ((int)cy) / 74;
        arrvsX = ((int)cx) / 74;
        ground[arrvsX][arrvsY] = 1;

        Repos::getCenter(vehicleManager->getmyIFVs(), cx, cy);
        IFVsY = ((int)cy) / 74;
        IFVsX = ((int)cx) / 74;
        ground[IFVsX][IFVsY] = 2;

        Repos::getCenter(vehicleManager->getmyTanks(), cx, cy);
        tanksY = ((int)cy) / 74;
        tanksX = ((int)cx) / 74;
        ground[tanksX][tanksY] = 3;

        Repos::getCenter(vehicleManager->getmyFighters(), cx, cy);
        fighterY = ((int)cy) / 74;
        fighterX = ((int)cx) / 74;
        air[fighterX][fighterY] = 4;

        Repos::getCenter(vehicleManager->getmyHelicopters(), cx, cy);
        helicopterY = ((int)cy) / 74;
        helicopterX = ((int)cx) / 74;
        air[helicopterX][helicopterY] = 5;

        int xs[6];

        taskManager->addTask(new ChangeActiveTask(ActiveType::Hight));

        int count = 0;
        for (int ii=0; ii<3; ii++)
            for (int i=0; i<3; i++)
                if (ground[i][ii]){
                    xs[ground[i][ii]] = count;
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
                    xs[air[i][ii]] = count;
                    int d = count - i;
                    if (d){
                        taskManager->addTask(new SelectTask(convert(air[i][ii])));
                        taskManager->addTask(new AsyncDeltaTask(d*74, 0));
                    }
                    count ++;
                }

        taskManager->addTask(new SpeedBarrierTask(0.1));

        taskManager->addTask(new SelectTask(model::VehicleType::ARRV));
        taskManager->addTask(new AsyncDeltaTask(0, (0 - arrvsY)*74));

        taskManager->addTask(new SelectTask(model::VehicleType::IFV));
        if (IFVsY != 0)
            taskManager->addTask(new AsyncDeltaTask(0, (0 - IFVsY)*74));

        taskManager->addTask(new SelectTask(model::VehicleType::TANK));
        if (tanksY != 2)
            taskManager->addTask(new AsyncDeltaTask(0, (2 - tanksY)*74));

        taskManager->addTask(new SelectTask(model::VehicleType::HELICOPTER));
        if (helicopterY != 0)
            taskManager->addTask(new AsyncDeltaTask(0, (0 - helicopterY)*74));

        taskManager->addTask(new SelectTask(model::VehicleType::FIGHTER));
        if (fighterY != 2)
            taskManager->addTask(new AsyncDeltaTask(0, (2 - fighterY)*74));

        taskManager->addTask(new SpeedBarrierTask(0.1));



        taskManager->addTask(new ChangeActiveTask(ActiveType::Normal));


        for (int i=0; i<10; i++){
            double left = 0;
            double top = 16 + 5.8 * (9-i);
            double right = 3*74;
            double bottom = 16 + 5.8 * (10-i);
            taskManager->addTask(new SelectTask(left, top, right, bottom));
            taskManager->addTask(new AsyncDeltaTask(0, 5.8 * (9-i)));
        }
        taskManager->addTask(new SpeedBarrierTask(0.1));


        taskManager->addTask(new SelectTask(model::VehicleType::ARRV));
        taskManager->addTask(new AsyncDeltaTask(0, 5.8));
        taskManager->addTask(new SpeedBarrierTask(0.1));

        for (int it = 1; it<=5; it++){

            for (int i=0; i<3; i++){
                double left = 0;
                double right = 3*74;

                double top = 16 + 116/3*i;
                double bottom = 16 + 116/3*(i+1);
                if (it==4 || it==3){
                    top = 74*2 + 16 + 58/3*i;
                    bottom = 74*2 + 16 + 58/3*(i+1);
                }
                if (it==1)
                    top += 5.8;
                    bottom += 5.8;

                taskManager->addTask(new SelectTask(left, top, right, bottom, convert(it)));
                taskManager->addTask(new AsyncDeltaTask( (i - xs[it])*74 ,0));
            }
        }
        taskManager->addTask(new SpeedBarrierTask(0.1));

        for (int i=0; i<2; i++){
            double left = i*74;
            double top = 16;
            double right = (i+1)*74;
            double bottom = 74*2;
            taskManager->addTask(new SelectTask(left, top, right, bottom));
            taskManager->addTask(new AsyncDeltaTask(0, (2-i)*116/3));

            left = i*74;
            top = 74*2 + 16;
            right = (i+1)*74;
            bottom = 74*3;
            taskManager->addTask(new SelectTask(left, top, right, bottom));
            taskManager->addTask(new AsyncDeltaTask(0, (2-i)*58/3));
        }

        taskManager->addTask(new SpeedBarrierTask(0.1));

        taskManager->addTask(new SelectTask(0, 0, 3 * 74, 2 * 74));
        taskManager->addTask(new AsyncDeltaTask(0, 74, 0.6*0.4));

        taskManager->addTask(new SelectTask(0, 16 + 2 * 74, 3 * 74, 3 * 74));
        taskManager->addTask(new AsyncDeltaTask(0, -74, 0.6*0.4));

        taskManager->addTask(new SpeedBarrierTask(0.1));


        taskManager->addTask(new SelectTask(0, 0, 1.5 * 74, 3 * 74));
        taskManager->addTask(new AsyncDeltaTask(74, 0, 0.6*0.4));


        taskManager->addTask(new SelectTask(1.5 * 74, 0, 3 * 74, 3*74));
        taskManager->addTask(new AsyncDeltaTask(-74, 0, 0.6*0.4));

        taskManager->addTask(new SpeedBarrierTask(0.1));

        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SpeedBarrierTask(0.1));

        taskManager->addTask(new ChangeStateTask(StateType::Idle));

        pAngle = PI / 2;
        env->putData("PAngle", &pAngle);
        return true;
    }

}

