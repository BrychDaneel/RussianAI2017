#include "ServiceManager.hpp"


#include "ActiveType.hpp"


namespace my{

    ServiceManager::ServiceManager(Enviroment& enviroment) :
        enviroment(enviroment),
        actionManager(enviroment.getMoveHelper()),
        groupManager(actionManager, enviroment),
        taskManager(enviroment, actionManager, groupManager),
        actionLimitor(enviroment)
    {
    }

    ServiceManager::~ServiceManager(){
        for (Service * service : services)
            delete service;
    }

    void ServiceManager::addService(Service* service){
        services.push_back(service);
        lastCall[service] = -1;
    }

    void ServiceManager::runService(){
        int now = enviroment.getWorld()->getTickIndex();
        for (size_t i=0; i<services.size(); i++){
            Service * service = services[i];
            int rate = service->getRate();
            int& last = lastCall[service];
            if ( last == -1 || (rate!=0 && now - last >= rate)){
                last = now;
                if (service->action())
                    break;
            }
        }
    }

    void ServiceManager::action(){

        if (actionManager.action())
            return;

        if (taskManager.action()){
            actionManager.actionOrNope();
            return;
        }

        runService();

        if (actionManager.action())
            return;

        if (taskManager.action()){
            actionManager.sendNope();
            return;
        }


        actionManager.sendNope();
    }

    void ServiceManager::firstRun(){
        groupManager.setup();
        actionLimitor.setup();
        for (auto service : services)
            service->setup(enviroment, taskManager, actionManager, groupManager);
    }

    void ServiceManager::tick(){
        if (first){
            firstRun();
            first = false;
        }

        if (!actionLimitor.canAction()){
            actionManager.NopeOrNope();
            actionLimitor.tick(false);
            return;
        }

        int avgDelta = actionLimitor.getInterval() / actionLimitor.getLimit();
        int tickNumber = enviroment.getWorld()->getTickIndex();
        double lowActiveCof = enviroment.getMagicConsts().getLowActiveCof();

        switch (enviroment.getActive()){
            case ActiveType::Hight:
                action();
                break;
            case ActiveType::Normal:
                if (tickNumber == 0 || actionLimitor.getDelta() + 1 >= avgDelta)
                    action();
                else
                    actionManager.NopeOrNope();
                break;

            case ActiveType::Low:
                if (tickNumber == 0 || actionLimitor.getDelta() + 1 >= avgDelta * lowActiveCof)
                    action();
                else
                    actionManager.NopeOrNope();
                break;
        }

        actionLimitor.tick(!actionManager.lastIsNope());
    }

}
