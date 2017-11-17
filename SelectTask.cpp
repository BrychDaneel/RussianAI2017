#include "SelectTask.hpp"


namespace my{
    SelectTask::SelectTask(bool interrupt){
        selectType = SelectType::All;

        this->interrupt = interrupt;
    }

    SelectTask::SelectTask(int groupId, bool interrupt){
        selectType = SelectType::GID;
        gid = groupId;

        this->interrupt = interrupt;
    }

    SelectTask::SelectTask(const char * groupName, bool interrupt){
        selectType = SelectType::Name;
        name = groupName;
        this->interrupt = interrupt;
    }

    SelectTask::SelectTask(double left, double top, double right, double bottom, bool interrupt){
        selectType = SelectType::Rect;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;

        this->interrupt = interrupt;
    }

    SelectTask::SelectTask(double left, double top, double right, double bottom, model::VehicleType type, bool interrupt){
        selectType = SelectType::TypeAndRect;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        this->type = type;

        this->interrupt = interrupt;
    }

    SelectTask::SelectTask(model::VehicleType type, bool interrupt){
        selectType = SelectType::Type;
        this->type = type;

        this->interrupt = interrupt;
    }

    void SelectTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
    }

    bool SelectTask::action(){
        tick++;
        if (tick > 2)
            return false;
        if (tick == 1)
            return true;

        switch (selectType){
            case SelectType::All:
                actionManager->select(0, 0, width, height);
                break;
            case SelectType::GID:
                groupManager->select(gid);
                break;
            case SelectType::Name:
                groupManager->select(name);
                break;
            case SelectType::Rect:
                actionManager->select(left, top, right, bottom);
                break;
            case SelectType::Type:
                actionManager->select(0, 0, width, height, type);
                break;
            case SelectType::TypeAndRect:
                actionManager->select(left, top, right, bottom, type);
                break;
        }

        return true;
    }

    bool SelectTask::canInterrupt(){
        if (tick > 1)
            return false;
        return interrupt;
    }

}
