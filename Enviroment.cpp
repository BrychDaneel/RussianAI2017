#include "Enviroment.hpp"
#include <vector>


namespace my{

    void Enviroment::update(const model::Player& me, const model::World& world, const model::Game& game, model::Move& move)
    {
        this->me = &me;
        this->world = &world;
        this->game = &game;
        this->moveHelper.reset(&move);
        if (first){
            firstRun();
            first = false;
        }

        std::vector<model::VehicleUpdate> updates = world.getVehicleUpdates();
        std::vector<model::Vehicle> newVehicles = world.getNewVehicles();

        speedManager.update(vehicleManager->getAll(), me.getId(), updates);
        damageManager.update(vehicleManager->getAll(), updates);

        for (size_t i=0; i<newVehicles.size(); i++)
            vehicleManager->add(newVehicles[i]);

        for (size_t i=0; i<updates.size(); i++)
            vehicleManager->update(updates[i]);
    }

    Enviroment::Enviroment(const MagicConsts& magicConsts):
        magicConsts(magicConsts),
        damageManager(magicConsts.getDamageLogSize()),
        state(magicConsts.getStartState()),
        active(magicConsts.getStartActive())
    {
    }

    Enviroment::~Enviroment(){
        delete vehicleManager;
    }

    void Enviroment::firstRun(){
        terrain = world->getTerrainByCellXY();
        weather = world->getWeatherByCellXY();
        facilitys = world->getFacilities();
        vehicleManager = new VehicleManager(world->getMyPlayer().getId());
    }

    model::TerrainType Enviroment::getTerrain(const int x, const int y){
        return terrain[x][y];
    }

    model::WeatherType Enviroment::getWeather(const int x, const int y){
        return weather[x][y];
    }

    const VehicleManager* Enviroment::getVehicleManager(){
        return vehicleManager;
    }

    const MagicConsts& Enviroment::getMagicConsts(){
        return magicConsts;
    }

    const DamageManager& Enviroment::getDamageManager(){
        return damageManager;
    }

    const SpeedManager& Enviroment::getSpeedManager(){
        return speedManager;
    }

    MoveHelper& Enviroment::getMoveHelper(){
        return moveHelper;
    }

    const vector<model::Facility>& Enviroment::getFacilitys(){
        return facilitys;
    }

    const model::Player* Enviroment::getMe() const{
        return me;
    }

    const model::World* Enviroment::getWorld() const{
        return world;
    }

    const model::Game* Enviroment::getGame() const{
        return game;
    }

    const ActiveType Enviroment::getActive() const{
        return active;
    }

    void Enviroment::setActive(const ActiveType active){
        this->active = active;
    }

    const StateType Enviroment::getState() const{
        return state;
    }

    void Enviroment::setState(const StateType state){
        this->state = state;
    }

    void Enviroment::putData(const string name, void * value){
        data.put(name, value);
    }

    void* Enviroment::getData(const string name){
        return data.get(name);
    }

    void Enviroment::removeData(const string name){
        data.remove(name);
    }
}

