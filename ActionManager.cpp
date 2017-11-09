#include "ActionManager.hpp"


#include "InvalidAngleException.hpp"
#define PI 	3.14159265358979323846264338327
#ifdef DEBUG
    #include <iostream>
    void print(model::ActionType type){
        switch (type){
            case model::ActionType::ACTION_NONE:
                std::cout<<"ACTION_NONE";
                break;
            case model::ActionType::ACTION_CLEAR_AND_SELECT:
                std::cout<<"ACTION_CLEAR_AND_SELECT";
                break;
            case model::ActionType::ACTION_ADD_TO_SELECTION:
                std::cout<<"ACTION_ADD_TO_SELECTION";
                break;
            case model::ActionType::ACTION_DESELECT:
                std::cout<<"ACTION_DESELECT";
                break;
            case model::ActionType::ACTION_ASSIGN :
                std::cout<<"ACTION_ASSIGN";
                break;
            case model::ActionType::ACTION_DISMISS:
                std::cout<<"ACTION_DISMISS";
                break;
            case model::ActionType::ACTION_DISBAND:
                std::cout<<"ACTION_DISBAND";
                break;
            case model::ActionType::ACTION_MOVE:
                std::cout<<"ACTION_MOVE";
                break;
            case model::ActionType::ACTION_ROTATE:
                std::cout<<"ACTION_ROTATE";
                break;
            case model::ActionType::ACTION_SETUP_VEHICLE_PRODUCTION:
                std::cout<<"ACTION_SETUP_VEHICLE_PRODUCTION";
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

        if (actions.front().getAction() == model::ActionType::ACTION_NONE)
            isNope = true;
        else
            isNope = false;

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

    void ActionManager::actionOrNope(){
        if (ActionManager::empty())
            nope();
        action();
    }

    void ActionManager::sendNope(){
        model::Move move;
        move.setAction(model::ActionType::ACTION_NONE);
        moveHelper.assign(move);
        isNope = true;
        #ifdef DEBUG
           print(model::ActionType::ACTION_NONE);
        #endif
    }

    bool ActionManager::lastIsNope(){
        return isNope;
    }

    void ActionManager::nope(){
        model::Move move;
        move.setAction(model::ActionType::ACTION_NONE);
        actions.push(move);
    }

    void ActionManager::NopeOrNope(){
        if (actions.front().getAction() == model::ActionType::ACTION_NONE)
            action();
        else
            sendNope();
    }

    void ActionManager::select(const double left, const double top, const double right, const double bottom){
        model::Move move;
        move.setAction(model::ActionType::ACTION_CLEAR_AND_SELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        actions.push(move);
    }

    void ActionManager::select(const double left, const double top, const double right, const double bottom, const model::VehicleType type){
        model::Move move;
        move.setAction(model::ActionType::ACTION_CLEAR_AND_SELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        move.setVehicleType(type);
        actions.push(move);
    }

    void ActionManager::select(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_CLEAR_AND_SELECT);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::add(const double left, const double top, const double right, const double bottom){
        model::Move move;
        move.setAction(model::ActionType::ACTION_ADD_TO_SELECTION);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        actions.push(move);
    }

    void ActionManager::add(const double left, const double top, const double right, const double bottom, const model::VehicleType type){
        model::Move move;
        move.setAction(model::ActionType::ACTION_ADD_TO_SELECTION);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        move.setVehicleType(type);
        actions.push(move);
    }

    void ActionManager::add(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_ADD_TO_SELECTION);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::deselect(const double left, const double top, const double right, const double bottom){
        model::Move move;
        move.setAction(model::ActionType::ACTION_DESELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        actions.push(move);
    }

    void ActionManager::deselect(const double left, const double top, const double right, const double bottom, const model::VehicleType type){
        model::Move move;
        move.setAction(model::ActionType::ACTION_DESELECT);
        move.setLeft(left);
        move.setTop(top);
        move.setRight(right);
        move.setBottom(bottom);
        move.setVehicleType(type);
        actions.push(move);
    }

    void ActionManager::deselect(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_DESELECT);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::assign(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_ASSIGN);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::dismiss(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_DISMISS);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::disband(const int groupId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_DISBAND);
        move.setGroup(groupId);
        actions.push(move);
    }

    void ActionManager::move(const double dx, const double dy){
        model::Move move;
        move.setAction(model::ActionType::ACTION_MOVE);
        move.setX(dx);
        move.setY(dy);
        actions.push(move);
    }

    void ActionManager::move(const double dx, const double dy, const double maxSpeed){
        model::Move move;
        move.setAction(model::ActionType::ACTION_MOVE);
        move.setX(dx);
        move.setY(dy);
        move.setMaxSpeed(maxSpeed);
        actions.push(move);
    }

    void ActionManager::rotate(const double x, const double y, const double angle){
        if (angle > PI || angle < -PI){
            InvalidAngleException exc;
            throw exc;
        }
        model::Move move;
        move.setAction(model::ActionType::ACTION_ROTATE);
        move.setX(x);
        move.setY(y);
        actions.push(move);
    }

    void ActionManager::rotate(const double x, const double y, const double angle, const double maxSpeed){
        if (angle > PI || angle < -PI){
            InvalidAngleException exc;
            throw exc;
        }
        model::Move move;
        move.setAction(model::ActionType::ACTION_ROTATE);
        move.setX(x);
        move.setY(y);
        move.setMaxSpeed(maxSpeed);
        actions.push(move);
    }

    void ActionManager::rotateAng(const double x, const double y, const double angle, const double maxAngularSpeed){
        if (angle > PI || angle < -PI){
            InvalidAngleException exc;
            throw exc;
        }
        model::Move move;
        move.setAction(model::ActionType::ACTION_ROTATE);
        move.setX(x);
        move.setY(y);
        move.setMaxAngularSpeed(maxAngularSpeed);
        actions.push(move);
    }

    void ActionManager::product(long facilityId, model::VehicleType vehicleType){
        model::Move move;
        move.setAction(model::ActionType::ACTION_SETUP_VEHICLE_PRODUCTION);
        move.setFacilityId(facilityId);
        move.setVehicleType(vehicleType);
        actions.push(move);
    }

    void ActionManager::stopProduct(long facilityId){
        model::Move move;
        move.setAction(model::ActionType::ACTION_SETUP_VEHICLE_PRODUCTION);
        move.setFacilityId(facilityId);
        actions.push(move);
    }
}
