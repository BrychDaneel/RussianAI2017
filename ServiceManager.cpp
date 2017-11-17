#include "ServiceManager.hpp"


#include "ActiveType.hpp"


namespace my{

    ServiceManager::ServiceManager(Enviroment& enviroment) :
        enviroment(enviroment),
        actionManager(enviroment.getMoveHelper()),
        groupManager(actionManager, enviroment),
        actionLimitor(enviroment)
    {
    }

    ServiceManager::~ServiceManager(){
        for (vector<Service*> services : threads)
            for (Service * service : services)
                delete service;

        for (vector<Interruption*>  interruptions : threads_int)
            for (Interruption * interruption : interruptions)
                delete interruption;
    }

    void ServiceManager::fill(size_t threadCount){
        while (threads.size() <= threadCount){
            vector<Service*> new_thread;
            vector<Interruption*> new_interruption;
            TaskManager newTaskManger(enviroment, actionManager, groupManager);

            threads.push_back(new_thread);
            threads_int.push_back(new_interruption);

            taskManagers.push_back(newTaskManger);
        }
    }

    void ServiceManager::addService(Service* service, size_t thread){
        fill(thread);
        threads[thread].push_back(service);
        lastCall[service] = -1;
    }

    void ServiceManager::addCommonInterruption(CommonInterruption* interruption){
        common_int.push_back(interruption);
    }

    void ServiceManager::addInterruption(Interruption* interruption, size_t thread){
        fill(thread);
        threads_int[thread].push_back(interruption);
    }

    void ServiceManager::changeThread(){
        cur = (cur + 1) % threads.size();
    }

    void ServiceManager::runService(){
        int now = enviroment.getWorld()->getTickIndex();
        for (size_t i=0; i<threads[cur].size(); i++){
            Service * service = threads[cur][i];
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


        size_t tr = 0;
        do{

            if (tr)
                for (Interruption * interruption : threads_int[cur])
                    interruption->action();

            if (taskManagers[cur].action()){
                actionManager.actionOrNope();
                if (taskManagers[cur].canInterrupt())
                    changeThread();
                return;
            }

            tr++;
            runService();

            if (actionManager.action())
                return;

            if (taskManagers[cur].action()){
                actionManager.actionOrNope();
                if (taskManagers[cur].canInterrupt())
                    changeThread();
                return;
            }

            changeThread();
        } while (tr < threads.size());

        actionManager.sendNope();
    }

    void ServiceManager::firstRun(){
        groupManager.setup();
        actionLimitor.setup();

        for (size_t i=0; i<threads.size(); i++)
            for (Service * service : threads[i])
                service->setup(enviroment, taskManagers[i], actionManager, groupManager);

        for (size_t i=0; i<threads.size(); i++)
            for (Interruption * interruption : threads_int[i])
                interruption->setup(enviroment, taskManagers[i], actionManager, groupManager);

        for (CommonInterruption * interruption : common_int)
            interruption->setup(enviroment, actionManager, groupManager);
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

        for (CommonInterruption * interruption : common_int)
            interruption->action();

        for (Interruption * interruption : threads_int[cur])
            interruption->action();

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
