#pragma once
#ifndef _MY_DAMAGE_MANAGER_HPP_
#define _MY_DAMAGE_MANAGER_HPP_


#include "model/VehicleUpdate.h"
#include "model/Vehicle.h"
#include <deque>
#include <map>


using std::deque;


namespace my{
    class DamageManager{
        private:
            deque<std::map<long long, int> > log;
            deque<int> sumLog;
            size_t len;
            int damageSum = 0;
        public:
            DamageManager(size_t len);
            void update(const std::map<long long,model::Vehicle>& vehicles, const std::vector<model::VehicleUpdate>& updates);
            int getSumDamage() const;
            const deque<int>& getSumDamageLog() const;
            const deque<std::map<long long, int> >& getDamageLog() const;
    };
}


#endif

