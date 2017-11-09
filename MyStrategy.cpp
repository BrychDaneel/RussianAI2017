#include "MyStrategy.h"

#include "MagicConsts.hpp"
#include "GroupingService.hpp"
#include "GotoAngleService.hpp"
#ifdef DEBUG
    #include <iostream>
#endif


using namespace model;


void MyStrategy::move(const Player& me, const World& world, const Game& game, Move& move) {
    #ifdef DEBUG
        std::cout << "Tick: " << world.getTickIndex() << std::endl;
    #endif
    enviroment.update(me, world, game, move);
    serviceManager.tick();
}

MyStrategy::MyStrategy() :
    consts(my::MagicConsts::getDefaulInstance()),
    enviroment(consts),
    serviceManager(enviroment)
{
    serviceManager.addService(new my::GroupingService());
    serviceManager.addService(new my::GotoAngleService());
}
