#include "RegroupService.hpp"


#include "Repos.hpp"
#include "ChangeStateTask.hpp"
#include "AsyncScaleTask.hpp"
#include "GridGroupTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "SelectTask.hpp"
#include "StopTask.hpp"
#include <cmath>


#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define MIN(A,B) ((A) < (B) ? (A) : (B))


namespace my{

    void RegroupService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        maxSquarCof = env.getMagicConsts().getMaxSquarCof();
        maxFightSquarCof = env.getMagicConsts().getMaxFightSquarCof();
    }

    int RegroupService::getRate(){
        return RATE;
    }

    void RegroupService::getAirBox(double & minX, double & maxX, double & minY, double & maxY){
        double nMinX, nMaxX, nMinY, nMaxY;

        Repos::getBox(vehicleManager->getmyFighters(), minX, minY, maxX, maxY);

        Repos::getBox(vehicleManager->getmyHelicopters(), nMinX, nMaxX, nMinY, nMaxY);
        minX = MIN(minX, nMinX);
        maxX = MAX(maxX, nMaxX);
        minY = MIN(minY, nMinY);
        maxY = MAX(maxY, nMaxY);
    }

    void RegroupService::getGroundBox(double & minX, double & maxX, double & minY, double & maxY){
        double nMinX, nMaxX, nMinY, nMaxY;

        Repos::getBox(vehicleManager->getmyIFVs(), minX, minY, maxX, maxY);

        Repos::getBox(vehicleManager->getmyArrvs(), nMinX, nMaxX, nMinY, nMaxY);
        minX = MIN(minX, nMinX);
        maxX = MAX(maxX, nMaxX);
        minY = MIN(minY, nMinY);
        maxY = MAX(maxY, nMaxY);

        Repos::getBox(vehicleManager->getmyTanks(), nMinX, nMaxX, nMinY, nMaxY);
        minX = MIN(minX, nMinX);
        maxX = MAX(maxX, nMaxX);
        minY = MIN(minY, nMinY);
        maxY = MAX(maxY, nMaxY);
    }

    bool RegroupService::action(){
        if (env->getState() != StateType::Idle && env->getState() != StateType::Attack && env->getState() != StateType::Figth)
            return false;

        /*double minX, maxX, minY, maxY;
        double aMinX, aMaxX, aMinY, aMaxY;

        size_t count = vehicleManager->getmyArrvs().size() + vehicleManager->getmyIFVs().size() + vehicleManager->getmyTanks().size();
        size_t aCount = vehicleManager->getmyHelicopters().size() + vehicleManager->getmyFighters().size();

        getGroundBox(minX, minY, maxX, maxY);
        getAirBox(aMinX, aMinY, aMaxX, aMaxY);

        double squar = (maxX - minX) * (maxY - minY);
        double aSquar = (aMaxX - aMinX) * (aMaxY - aMinY);

        if (env->getState() == StateType::Figth){
            if (squar <= count * maxFightSquarCof || aSquar <= aCount * maxFightSquarCof)
                return false;
        } else
            if (squar <= count * maxSquarCof || aSquar <= aCount * maxSquarCof)
                return false;*/

        double minX, maxX, minY, maxY;
        size_t count = vehicleManager->getMy().size();
        Repos::getBox(vehicleManager->getMy(), minX, minY, maxX, maxY);
        double squar = (maxX - minX) * (maxY - minY);
        if (env->getState() == StateType::Figth){
            if (squar <= sqrt(count) * maxFightSquarCof)
                return false;
        } else
            if (squar <= sqrt(count) * maxSquarCof)
                return false;


        taskManager->addTask(new ChangeStateTask(StateType::Group));
        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SpeedBarrierTask("Army", 0.1));
        taskManager->addTask(new ChangeStateTask(StateType::Idle));
        return true;
    }
}
