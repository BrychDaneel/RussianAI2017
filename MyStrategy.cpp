#include "MyStrategy.h"

#include "MagicConsts.hpp"
#include "GroupingService.hpp"
#include "GotoAngleService.hpp"
#include "BaseBindService.hpp"
#include "FightDetectorService.hpp"
#include "EnemySearchService.hpp"
#include "AttackService.hpp"
#include "HealAngleDetectorService.hpp"
#include "RotateService.hpp"
#include "FrontDetectorService.hpp"
#include "FrontMoveService.hpp"
#include "CategoryBindService.hpp"
#include "RegroupService.hpp"
#include "CirculStartGroupService.hpp"
#include "SmartStartGroupService.hpp"
#include "TempService.hpp"
#include "AttackInterruption.hpp"
#include "PerfectBreakService.hpp"
#include "NuclearService.hpp"
#include "LoseDetectorService.hpp"
#include "RushDetectorService.hpp"
#include "SaveService.hpp"
#include "RushService.hpp"
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

    serviceManager.addService(new my::BaseBindService());

    serviceManager.addService(new my::SmartStartGroupService());
    serviceManager.addInterruption(new my::AttackInterruption());

    //serviceManager.addService(new my::TempService());

    serviceManager.addService(new my::FightDetectorService());

    serviceManager.addService(new my::FrontDetectorService());
    serviceManager.addService(new my::FrontMoveService());

    serviceManager.addService(new my::NuclearService());

    serviceManager.addService(new my::RegroupService());

    serviceManager.addService(new my::EnemySearchService());

    serviceManager.addService(new my::AttackService());

    serviceManager.addService(new my::HealAngleDetectorService());

    serviceManager.addService(new my::RotateService());

    serviceManager.addService(new my::PerfectBreakService());

    serviceManager.addService(new my::GotoAngleService());
    serviceManager.addService(new my::LoseDetectorService());
    serviceManager.addService(new my::RushDetectorService());

    serviceManager.addService(new my::SaveService());
    serviceManager.addService(new my::RushService());
}
