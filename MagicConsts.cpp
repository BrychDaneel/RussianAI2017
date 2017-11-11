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
        instance.defaultAttackSpeed = 0.4 * 0.6;
        instance.minRotateAngle = PI / 4;
        instance.minRotateDistance = 200;
        instance.fightMoveSpeed = 0.1;
        instance.attackBorrier = 20;
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

}
