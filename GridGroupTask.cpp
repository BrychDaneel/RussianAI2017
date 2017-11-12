#include "GridGroupTask.hpp"
#include "Repos.hpp"


namespace my{
    GridGroupTask::GridGroupTask(int vSplits, int hSplits){
        this->vSplits = vSplits;
        this->hSplits = hSplits;
    }

    void GridGroupTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->actionManager = &actionManager;
        this->vehicleManager = env.getVehicleManager();
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
    }

    void GridGroupTask::firstRun(){

            Repos::getBox(vehicleManager->getMy(), minX, minY, maxX, maxY);

            cx = (maxX + minX) / 2;
            cy = (maxY + minY) / 2;

            dx = (maxX - minX) / (vSplits + 1);
            dy = (maxY - minY) / (hSplits + 1);
    }

    bool GridGroupTask::loop(){
        if (ii>hSplits){
            ii=0;
            i++;
        }
        if (i>vSplits)
            return false;

        double left = minX + dx * i;
        double top = minY + dy * ii;
        double right = minX + dx * (i+1);
        double bottom = minY + dy * (ii+1);


        actionManager->select(left, top, right, bottom);

        ii++;
        return true;
    }

    void GridGroupTask::go(){
        std::vector<model::Vehicle> selected;
        for (auto pair : vehicleManager->getMy()){
            const model::Vehicle vehicle = pair.second;
            if (vehicle.isSelected())
                    selected.push_back(vehicle);
        }
        double scx, scy;
        Repos::getCenter(selected, scx, scy);
        actionManager->move(cx - scx, cy - scy);
    }

    bool GridGroupTask::action(){
        if (fRun){
            firstRun();
            fRun = false;
        }

        if (!selected){
            selected = true;
            return loop();
        }

        go();
        selected = false;
        return true;
    }
}


