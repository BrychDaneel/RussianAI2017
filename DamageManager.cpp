#include "DamageManager.hpp"



namespace my{
    DamageManager::DamageManager(size_t len){
        this->len = len;
    }

    void DamageManager::update(const std::map<long long,model::Vehicle>& vehicles, const std::vector<model::VehicleUpdate>& updates){
        if (log.size() >= len){
            log.pop_back();
            damageSum -= sumLog.back();
            sumLog.pop_back();
        }

        std::map<long long, int> damage;
        int delta = 0;
        for (model::VehicleUpdate update : updates){
            const model::Vehicle& old = vehicles.find(update.getId())->second;
            if (update.getDurability() < old.getDurability()){
                int d = old.getDurability() - update.getDurability();
                damage[old.getId()] = d;
                delta += d;
            }
        }
        damageSum += delta;
        log.push_front(damage);
        sumLog.push_front(delta);
    }

    int DamageManager::getSumDamage() const{
        return damageSum;
    }

    const deque<int>& DamageManager::getSumDamageLog() const{
        return sumLog;
    }

    const deque<std::map<long long, int> >& DamageManager::getDamageLog() const{
        return log;
    }
}
