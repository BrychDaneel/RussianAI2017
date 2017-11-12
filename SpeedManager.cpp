#include "SpeedManager.hpp"


#define SQR(x) (x) * (x)
#include <cmath>


namespace my{
    SpeedManager::SpeedManager(){
    }

    void SpeedManager::update(const std::map<long long,model::Vehicle>& vehicles, int myId, const std::vector<model::VehicleUpdate>& updates){
        speed.clear();
        maxMySpeed = 0;
        maxEnemySpeed = 0;
        for (model::VehicleUpdate update : updates){
            const model::Vehicle& old = vehicles.find(update.getId())->second;
            if (update.getX() != old.getX() || update.getY() != old.getY()){
                double sp = SQR(update.getX() - old.getX()) + SQR(update.getY() - old.getY());
                speed[update.getId()] = sp;
                if (old.getPlayerId() == myId)
                    maxMySpeed = sp > maxMySpeed? sp : maxMySpeed;
                else
                    maxEnemySpeed = sp > maxEnemySpeed? sp : maxEnemySpeed;
            }
        }
    }

    double SpeedManager::getMaxMySpeed() const{
        return sqrt(maxMySpeed);
    }

    double SpeedManager::getMaxEnemySpeed() const{
        return sqrt(maxEnemySpeed);
    }

    double SpeedManager::getSpeed(long long id) const{
        if (speed.find(id) == speed.end())
            return 0;
        return sqrt(speed.find(id)->second);
    }

}
