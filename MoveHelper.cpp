#include "MoveHelper.hpp"
#include "IlligalStateException.hpp"


namespace my{
    MoveHelper::MoveHelper(model::Move* move)
    {
        this->move = move;
    }

    MoveHelper::MoveHelper(){
    }

    void MoveHelper::reset(model::Move* move){
        this->move = move;
    }

    bool MoveHelper::isSet(){
        return set;
    }

    void MoveHelper::trySet(){
        if (set){
            IlligalStateException exc;
            throw exc;
        }

        set = true;
    }

    void MoveHelper::assign(const model::Move& move){
        this->move->setAction(move.getAction());
        this->move->setAngle(move.getAngle());
        this->move->setBottom(move.getBottom());
        this->move->setFacilityId(move.getFacilityId());
        this->move->setGroup(move.getGroup());
        this->move->setLeft(move.getLeft());
        this->move->setMaxAngularSpeed(move.getMaxAngularSpeed());
        this->move->setMaxSpeed(move.getMaxSpeed());
        this->move->setRight(move.getRight());
        this->move->setTop(move.getTop());
        this->move->setVehicleType(move.getVehicleType());
        this->move->setX(move.getX());
        this->move->setY(move.getY());
        this->move->setFactor(move.getFactor());
        this->move->setVehicleId(move.getVehicleId());
    }
}
