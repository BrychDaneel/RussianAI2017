#include "MagicConsts.hpp"


#include "pi.hpp"


namespace my{
    MagicConsts::MagicConsts(){
    }

    MagicConsts MagicConsts::getDefaulInstance(){
        MagicConsts instance;
        instance.lowActiveCof = 2.0;
        instance.damageLogSize = 60;
        instance.startActive = ActiveType::Normal;
        instance.startState = StateType::Idle;
        instance.minFightDamage = 300;
        instance.defaultAttackSpeed = 0.7 * 0.4 * 0.6;
        instance.minRotateAngle = PI / 6;
        instance.minRotateDistance = 100;
        instance.minRotateTime = 240;
        instance.fightMoveSpeed = 0.1;
        instance.attackBorrier = 20;
        instance.maxSquarCof = 700;
        instance.maxFightSquarCof = 900;
        instance.groupIntDistance = 200;
        instance.perfectBreakPercent = 0.5;
        instance.nuclearDist = 50;
        instance.maxNuclearDist = 100;
        instance.minNuclearDistPercent = 0.7;
        instance.maxNuclearDistPercent = 0.85;
        instance.minVisionCof = 0.6;
        instance.loseCof = 0.5;
        instance.rushCof = 3;
        instance.minRushTick = 15000;
        instance.nuclearCancelRadius = 30;
        instance.pascudaDelta = 20;
        instance.maxPascudaNuclearDist = 96;
        instance.minPascudaNuclearDist = 56;
        instance.maxPascudaDist = 12;
        instance.guardInteresCount = 5;
        instance.guardInteresRadius = 32;
        instance.guardMinArmyDist = 30;
        instance.guardMaxDist = 25;
        instance.guardZoneRadius = 800;
        instance.farNuclearCount = 100;
        instance.minFarRange = 40;
        //instance.addRange = ;
        return instance;
    }

    const double MagicConsts::getLowActiveCof() const{
        return lowActiveCof;
    }

    const size_t MagicConsts::getDamageLogSize() const{
        return damageLogSize;
    }

    const ActiveType MagicConsts::getStartActive() const{
        return startActive;
    }

    const StateType MagicConsts::getStartState() const{

        return startState;
    }

    const int MagicConsts::getMinFightDamage() const{
        return minFightDamage;
    }

    const double MagicConsts::getDefaultAttackSpeed() const{
        return defaultAttackSpeed;
    }

    const double MagicConsts::getMinRotateAngle() const{
        return minRotateAngle;
    }

    const double MagicConsts::getMinRotateDistance() const{
        return minRotateDistance;
    }

    const double MagicConsts::getFightMoveSpeed() const{
        return fightMoveSpeed;
    }

    const double MagicConsts::getAttackBorrier() const{
        return attackBorrier;
    }

    const double MagicConsts::getMaxSquarCof() const{
        return maxSquarCof;
    }

    const double MagicConsts::getMaxFightSquarCof() const{
        return maxFightSquarCof;
    }

    const int MagicConsts::getMinRotateTime() const{
        return minRotateTime;
    }

    const int MagicConsts::getGroupIntDistance() const{
        return groupIntDistance;
    }

    const double MagicConsts::getPerfectBreakPercent() const{
        return perfectBreakPercent;
    }

    const double MagicConsts::getNuclearDist() const{
        return nuclearDist;
    }

    const double MagicConsts::getMinNuclearDistPercent() const{
        return minNuclearDistPercent;
    }

    const double MagicConsts::getMaxNuclearDistPercent() const{
        return maxNuclearDistPercent;
    }

    const double MagicConsts::getMinVisionCof() const{
        return minVisionCof;
    }

    const double MagicConsts::getLoseCof() const{
        return loseCof;
    }


    const double MagicConsts::getRushCof() const{
        return rushCof;
    }

    const double MagicConsts::getMinRushTick() const{
        return minRushTick;
    }

    const double MagicConsts::getNuclearCancelRadius() const{
        return nuclearCancelRadius;
    }

    const double MagicConsts::getMaxNuclearDist() const{
        return maxNuclearDist;
    }

    const double MagicConsts::getMaxPascudaNuclearDist() const{
        return maxPascudaNuclearDist;
    }

    const double MagicConsts::getMinPascudaNuclearDist() const{
        return minPascudaNuclearDist;
    }

    const double MagicConsts::getPascudaDelta() const{
        return pascudaDelta;
    }

    const double MagicConsts::getMaxPascudaDist() const{
        return maxPascudaDist;
    }

    const int MagicConsts::getGuardInteresCount() const{
      return guardInteresCount;
    }

    const double MagicConsts::getGuardInteresRadius() const{
        return guardInteresRadius;
    }

    const double MagicConsts::getGuardMinArmyDist() const{
        return guardMinArmyDist;
    }

    const double MagicConsts::getGuardMaxDist() const{
        return guardMaxDist;
    }

    const double MagicConsts::getGuardZoneRadius() const{
        return guardZoneRadius;
    }

    const double MagicConsts::getFarNuclearCount() const{
        return farNuclearCount;
    }

    const double MagicConsts::getMinFarRange() const{
        return minFarRange;
    }

    const double MagicConsts::getAddRange() const{
        return addRange;
    }

}
