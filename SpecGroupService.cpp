#include "SpecGroupService.hpp"


#include "Repos.hpp"
#include "SleepTask.hpp"
#include "SelectTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "AsyncDeltaTask.hpp"
#include "BindTask.hpp"
#include "DismissTask.hpp"


namespace my{

    void SpecGroupService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        vehicleManager = env.getVehicleManager();
    }

    int SpecGroupService::getRate(){
        return RATE;
    }

    bool SpecGroupService::action(){
        double minX, minY, maxX, maxY;
        Repos::getBox(vehicleManager->getmyFighters(), minX, minY, maxX, maxY);
        taskManager->addTask(new SelectTask(maxX - 4, minY, maxX, maxY));
        taskManager->addTask(new AsyncDeltaTask(8, 0));
        taskManager->addTask(new SpeedBarrierTask("All", 0.1));
        taskManager->addTask(new AsyncDeltaTask(0, 16 + 74 * 3 - minY));
        taskManager->addTask(new SpeedBarrierTask("All", 0.1));
        taskManager->addTask(new DismissTask("Army"));

        taskManager->addTask(new SelectTask(maxX - 4 + 8, 74 * 4 - 5.8 * 2, maxX + 8, 74 * 4));
        taskManager->addTask(new BindTask("PascudaTop"));

        taskManager->addTask(new SelectTask(maxX - 4 + 8, 74 * 4 - 5.8 * 4, maxX + 8, 74 * 4 - 5.8 * 2));
        taskManager->addTask(new BindTask("PascudaRight"));

        taskManager->addTask(new SelectTask(maxX - 4 + 8, 74 * 4 - 5.8 * 10, maxX + 8, 74 * 4 - 5.8 * 4));
        taskManager->addTask(new BindTask("Guard"));

        return false;
    }
}



