#include "NuclearInterruption.hpp"


#include "AsyncScaleTask.hpp"
#include "SleepTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "SelectTask.hpp"
#include "ChangeActiveTask.hpp"
#include "ChangeStateTask.hpp"
#include "WaitTask.hpp"


namespace my{

    NuclearInterruption::NuclearInterruption(const char * groupName, bool recall, bool checkStartGroup){
        this->groupName = groupName;
        this->recall = recall;
        this->checkStartGroup = checkStartGroup;
    }

    void NuclearInterruption::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
        last_call = - env.getGame()->getBaseTacticalNuclearStrikeCooldown();
    }

    void NuclearInterruption::action(){
        if (env->getWorld()->getOpponentPlayer().getNextNuclearStrikeVehicleId() == -1)
            return;

        if (checkStartGroup && env->getState() == StateType::StartGroup)
            return;

        int tick = env->getWorld()->getTickIndex();

        if (tick - last_call <= env->getGame()->getTacticalNuclearStrikeDelay())
            return;

        last_call = tick;

        int nucleX = env->getWorld()->getOpponentPlayer().getNextNuclearStrikeX();
        int nucleY = env->getWorld()->getOpponentPlayer().getNextNuclearStrikeY();

        bool far = true;
        for (model::Vehicle vehicle : groupManager->getVehicles(groupName))
            if (vehicle.getDistanceTo(nucleX, nucleY) < env->getGame()->getTacticalNuclearStrikeRadius()){
                far = false;
                break;
            }

        if (far)
            return;

        int time = env->getWorld()->getOpponentPlayer().getNextNuclearStrikeTickIndex();
        int sleep =  time - env->getWorld()->getTickIndex();

        taskManager->clear();
        taskManager->addTask(new ChangeStateTask(StateType::Idle));
        taskManager->addTask(new ChangeActiveTask(ActiveType::Hight));
        taskManager->addTask(new SelectTask(groupName, false));
        taskManager->addTask(new AsyncScaleTask(nucleX, nucleY, 10));
        taskManager->addTask(new WaitTask(time));


        taskManager->addTask(new ChangeActiveTask(ActiveType::Hight));

        if (recall){
            taskManager->addTask(new SelectTask(groupName));
            taskManager->addTask(new AsyncScaleTask(nucleX, nucleY, 0.1));
            taskManager->addTask(new SleepTask(sleep));
        }
    }
}

