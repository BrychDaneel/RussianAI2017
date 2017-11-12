#pragma once
#ifndef _MY_GRID_GROUPUP_TASK_HPP_
#define _MY_GRID_GROUPUP_TASK_HPP_


#include "Task.hpp"


namespace my{
    class GridGroupTask : public Task{
        private:
            Enviroment * env;
            bool fRun = true;
            int vSplits, hSplits;
            ActionManager * actionManager;
            const VehicleManager * vehicleManager;
            double width, height;
            int i = 0, ii = 0;
            bool selected = false;
            double minX, maxX, minY, maxY;
            double cx, cy, dx, dy;
        public:
            GridGroupTask(int vSplits, int hSplits);
            virtual bool action();
            void firstRun();
            bool loop();
            void go();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
