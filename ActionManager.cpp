#include "ActionManager.hpp"

#ifdef DEBUG
    #include "InvalidAngleException.hpp"
#endif // DEBUG
#include "pi.hpp"

#ifdef DEBUG
    #include <iostream>
    void print(model::ActionType type){
        switch (type){
            case model::ActionType::NONE:
                std::cout<<"NONE";
                break;
            case model::ActionType::CLEAR_AND_SELECT:
                std::cout<<"CLEAR_AND_SELECT";
                break;
            case model::ActionType::ADD_TO_SELECTION:
                std::cout<<"ADD_TO_SELECTION";
                break;
            case model::ActionType::DESELECT:
                std::cout<<"DESELECT";
                break;
            case model::ActionType::ASSIGN :
                std::cout<<"ASSIGN";
                break;
            case model::ActionType::DISMISS:
                std::cout<<"DISMISS";
                break;
            case model::ActionType::DISBAND:
                std::cout<<"DISBAND";
                break;
            case model::ActionType::MOVE:
                std::cout<<"MOVE";
                break;
            case model::ActionType::ROTATE:
                std::cout<<"ROTATE";
                break;
            case model::ActionType::SETUP_VEHICLE_PRODUCTION:
                std::cout<<"SETUP_VEHICLE_PRODUCTION";
                break;
            default:
                std::cout<<"ERROR";
                break;
        }
        std::cout<<std::endl;
    }
#endif


namespace my{
    ActionManager::ActionManager(MoveHelper& moveHelper): moveHelper(moveHelper){
    }

    bool ActionManager::action(){
        if (actions.empty())
            return false;

        if (actions.front().getAction() == model::ActionType::NONE)
            isNope = true;
        else
            isNope = false;

        if (actions.front().getAction() == model::ActionType::TACTICAL_NUCLEAR_STRIKE)
            isNuclear = true;
        else
            isNuclear = false;

        #ifdef DEBUG
           print(actions.front().getAction());
        #endif
        moveHelper.assign(actions.front());
        actions.pop();
        return true;
    }

    bool ActionManager::empty(){
        return actions.empty();
    }

    void ActionManager::clear(){
        while (!empty())
            actions.pop();
    }

    void ActionManager::actionOrNope(){
        if (empty())
            nope();
        action();
    }

    void ActionManager::sendNope(){
        model::Move move;
        move.setAction(model::ActionType::NONE);
        moveHelper.assign(move);
        isNope = true;
        isNuclear = false;
        #ifdef DEBUG
           print(model::ActionType::NONE);
        #endif
    }

    bool ActionManager::lastIsNope(){
        return isNope;
    }

    bool ActionManager::lastIsNuclear(){
        return isNuclear;
    }

    void ActionManager::nope(){
        model::Move move;
        move.setAction(model::ActionType::NONE);
        actions.push(move);
    }

    void ActionManager::NopeOrNope(){
        if (!empty() && actions.front().getAction() == model::ActionType::NONE)
            action();
        else
            sendNope();
    }

    void ActionManager::select(const double left, const double top, const double right, const double bottom){
        model::Move move;
        move.setAction(model::ActionType::CLEAR_AND_SELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        actions.push(move);
    }

    void ActionManager::select(const double left, const double top, const double right, const double bottom, const model::VehicleType type){
        model::Move move;
        move.setAction(model::ActionType::CLEAR_AND_SELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        move.setVehicleType(type);
        actions.push(move);
    }

    void ActionManager::select(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::CLEAR_AND_SELECT);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::add(const double left, const double top, const double right, const double bottom){
        model::Move move;
        move.setAction(model::ActionType::ADD_TO_SELECTION);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        actions.push(move);
    }

    void ActionManager::add(const double left, const double top, const double right, const double bottom, const model::VehicleType type){
        model::Move move;
        move.setAction(model::ActionType::ADD_TO_SELECTION);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        move.setVehicleType(type);
        actions.push(move);
    }

    void ActionManager::add(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ADD_TO_SELECTION);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::deselect(const double left, const double top, const double right, const double bottom){
        model::Move move;
        move.setAction(model::ActionType::DESELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        actions.push(move);
    }

    void ActionManager::deselect(const double left, const double top, const double right, const double bottom, const model::VehicleType type){
        model::Move move;
        move.setAction(model::ActionType::DESELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        move.setVehicleType(type);
        actions.push(move);
    }

    void ActionManager::deselect(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::DESELECT);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::assign(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ASSIGN);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::dismiss(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::DISMISS);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::disband(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::DISBAND);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::move(const double dx, const double dy){
        model::Move move;
        move.setAction(model::ActionType::MOVE);
        move.setX(dx);
        move.setY(dy);
        actions.push(move);
    }

    void ActionManager::move(const double dx, const double dy, const double maxSpeed){
        model::Move move;
        move.setAction(model::ActionType::MOVE);
        move.setX(dx);
        move.setY(dy);
        move.setMaxSpeed(maxSpeed);
        actions.push(move);
    }

    void ActionManager::rotate(const double x, const double y, const double angle){

        #ifdef DEBUG
        if (angle > PI || angle < -PI){
            InvalidAngleException exc;
            throw exc;
        }
        #endif // DEBUG

        model::Move move;
        move.setAction(model::ActionType::ROTATE);
        move.setX(x);
        move.setY(y);
        move.setAngle(angle);
        actions.push(move);
    }

    void ActionManager::rotate(const double x, const double y, const double angle, const double maxSpeed){
        #ifdef DEBUG
        if (angle > PI || angle < -PI){
            InvalidAngleException exc;
            throw exc;
        }
        #endif // DEBUG

        model::Move move;
        move.setAction(model::ActionType::ROTATE);
        move.setX(x);
        move.setY(y);
        move.setAngle(angle);
        move.setMaxSpeed(maxSpeed);
        actions.push(move);
    }

    void ActionManager::rotateAng(const double x, const double y, const double angle, const double maxAngularSpeed){
        #ifdef DEBUG
        if (angle > PI || angle < -PI){
            InvalidAngleException exc;
            throw exc;
        }
        #endif // DEBUG

        model::Move move;
        move.setAction(model::ActionType::ROTATE);
        move.setX(x);
        move.setY(y);
        move.setAngle(angle);
        move.setMaxAngularSpeed(maxAngularSpeed);
        actions.push(move);
    }

    void ActionManager::product(long facilityId, model::VehicleType vehicleType){
        model::Move move;
        move.setAction(model::ActionType::SETUP_VEHICLE_PRODUCTION);
        move.setFacilityId(facilityId);
        move.setVehicleType(vehicleType);
        actions.push(move);
    }

    void ActionManager::stopProduct(long facilityId){
        model::Move move;
        move.setAction(model::ActionType::SETUP_VEHICLE_PRODUCTION);
        move.setFacilityId(facilityId);
        actions.push(move);
    }

    void ActionManager::scale(const double x, const double y, const double factor){
        model::Move move;
        move.setAction(model::ActionType::SCALE);
        move.setX(x);
        move.setY(y);
        move.setFactor(factor);
        actions.push(move);
    }

    void ActionManager::scale(const double x, const double y,  const double factor, const double maxSpeed){
        model::Move move;
        move.setAction(model::ActionType::SCALE);
        move.setX(x);
        move.setY(y);
        move.setFactor(factor);
        move.setMaxSpeed(maxSpeed);
        actions.push(move);
    }

    void ActionManager::tactical_nuclear_strike(const long vehicleId, const double x, const double y){
        model::Move move;
        move.setAction(model::ActionType::TACTICAL_NUCLEAR_STRIKE);
        move.setX(x);
        move.setY(y);
        move.setVehicleId(vehicleId);
        actions.push(move);
    }
}
