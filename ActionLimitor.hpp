#pragma once
#ifndef _MY_ACTION_LIMITOR_HPP_
#define _MY_ACTION_LIMITOR_HPP_


#include "Enviroment.hpp"
#include <queue>


namespace my{
    class ActionLimitor{
        private:
            const Enviroment& env;
            int actionDetectionInterval;
            int baseActionCount;
            int additionalActionCountPerControlCenter;
            std::queue<bool> history;
            int count = 0;
            int delta = 0;

        public:
            ActionLimitor(const Enviroment & env);
            void setup();
            void tick(const bool action);
            const bool canAction() const;
            const int getLimit() const;
            const int getCount() const;
            const int getDelta() const;
            const int getInterval() const;
    };
}


#endif
