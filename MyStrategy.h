#pragma once

#ifndef _MY_STRATEGY_H_
#define _MY_STRATEGY_H_

#include "Strategy.h"
#include "ServiceManager.hpp"
#include "Enviroment.hpp"

class MyStrategy : public Strategy {
private:
    my::MagicConsts consts;
    my::Enviroment enviroment;
    my::ServiceManager serviceManager;

public:
    MyStrategy();

    void move(const model::Player& me, const model::World& world, const model::Game& game, model::Move& move) override;
};

#endif
