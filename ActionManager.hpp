#pragma once
#ifndef _MY_ACTIVE_MANAGER_HPP_
#define _MY_ACTIVE_MANAGER_HPP_


#include "model/Move.h"
#include "MoveHelper.hpp"
#include <queue>


namespace my{
    class ActionManager{
        private:
            std::queue<model::Move> actions;
            MoveHelper& moveHelper;
            bool isNope = false;
            bool isNuclear = false;
        public:
            ActionManager(MoveHelper& moveHelper);
            bool action();

            void sendNope();
            void actionOrNope();
            void NopeOrNope();

            bool empty();
            void clear();
            bool lastIsNope();

            bool lastIsNuclear();

            void nope();

            void select(const double left, const double top, const double right, const double bottom);
            void select(const double left, const double top, const double right, const double bottom, const model::VehicleType type);
            void select(const int groupId);

            void add(const double left, const double top, const double right, const double bottom);
            void add(const double left, const double top, const double right, const double bottom, const model::VehicleType type);
            void add(const int groupId);

            void deselect(const double left, const double top, const double right, const double bottom);
            void deselect(const double left, const double top, const double right, const double bottom, const model::VehicleType type);
            void deselect(const int groupId);

            void assign(const int groupId);
            void dismiss(const int groupId);
            void disband(const int groupId);

            void move(const double dx, const double dy);
            void move(const double dx, const double dy, const double maxSpeed);

            void scale(const double x, const double y, const double factor);
            void scale(const double x, const double y,  const double factor, const double maxSpeed);

            void rotate(const double x, const double y, const double angle);
            void rotate(const double x, const double y, const double angle, const double maxSpeed);
            void rotateAng(const double x, const double y, const double angle, const double maxAngularSpeed);

            void tactical_nuclear_strike(const long vehicleId, const double x, const double y);

            void product(long facilityId, model::VehicleType vehicleType);
            void stopProduct(long facilityId);
    };
}


#endif
