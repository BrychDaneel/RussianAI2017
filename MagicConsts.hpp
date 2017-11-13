#pragma once
#ifndef _MY_ILLIGAL_STATE_EXCEPTION_HPP_
#define _MY_ILLIGAL_STATE_EXCEPTION_HPP_


#include <cstring>
#include "StateType.hpp"
#include "ActiveType.hpp"


namespace my{
    class MagicConsts{
        private:
            double lowActiveCof;
            size_t damageLogSize;
            ActiveType startActive;
            StateType startState;
            int minFightDamage;
            double defaultAttackSpeed;
            double minRotateAngle;
            double minRotateDistance;
            double fightMoveSpeed;
            double attackBorrier;
            double maxSquarCof;
            double maxFightSquarCof;
            double groupIntDistance;
            double perfectBreakPercent;
            int minRotateTime;
        public:
            MagicConsts();
            static MagicConsts getDefaulInstance();
            const double getLowActiveCof() const;
            const size_t getDamageLogSize() const;
            const ActiveType getStartActive() const;
            const StateType getStartState() const;
            const int getMinFightDamage() const;
            const double getDefaultAttackSpeed() const;
            const double getMinRotateAngle() const;
            const double getMinRotateDistance() const;
            const double getFightMoveSpeed() const;
            const double getAttackBorrier() const;
            const double getMaxSquarCof() const;
            const double getMaxFightSquarCof() const;
            const int getMinRotateTime() const;
            const int getGroupIntDistance() const;
            const double getPerfectBreakPercent() const;
    };
}


#endif
