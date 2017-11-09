#pragma once
#ifndef _MY_ENVIROMENT_HPP_
#define _MY_ENVIROMENT_HPP_


#include "MoveHelper.hpp"
#include "model/TerrainType.h"
#include "model/WeatherType.h"
#include "model/Player.h"
#include "model/World.h"
#include "model/Game.h"
#include "model/Move.h"
#include "model/Facility.h"
#include <vector>
#include "Data.hpp"
#include "MagicConsts.hpp"
#include "VehicleManager.hpp"
#include "StateType.hpp"
#include "ActiveType.hpp"


using std::vector;
using std::map;
using std::string;


namespace my{
    class Enviroment{
        private:
            vector<vector<model::TerrainType> > terrain;
            vector<vector<model::WeatherType> > weather;
            vector<model::Facility> facilitys;
            const model::Player * me;
            const model::World * world;
            const model::Game * game;
            const MagicConsts& magicConsts;
            MoveHelper moveHelper;
            VehicleManager* vehicleManager = nullptr;
            Data data;
            bool first = true;

            StateType state = StateType::Unknown;
            ActiveType active = ActiveType::Normal;

            void firstRun();

        public:
            Enviroment(const MagicConsts& magicConsts);
            ~Enviroment();

            void update(const model::Player& me, const model::World& world, const model::Game& game, model::Move& move);

            model::TerrainType getTerrain(const int x, const int y);
            model::WeatherType getWeather(const int x, const int y);

            const VehicleManager* getVehicleManager();
            const MagicConsts& getMagicConsts();

            MoveHelper& getMoveHelper();
            const vector<model::Facility>& getFacilitys();
            const model::Player* getMe() const;
            const model::World* getWorld() const;
            const model::Game* getGame() const;

            const ActiveType getActive() const;
            void setActive(const ActiveType active);

            const StateType getState() const;
            void setState(const StateType state);

            void putData(const string name, void * value);
            void* getData(const string name);
    };
}

#endif
