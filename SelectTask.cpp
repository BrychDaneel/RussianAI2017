#include "SelectTask.hpp"


namespace my{
    SelectTask::SelectTask(){
        selectType = SelectType::All;
    }

    SelectTask::SelectTask(int groupId){
        selectType = SelectType::GID;
        gid = groupId;
    }

    SelectTask::SelectTask(const std::string & groupName){
        selectType = SelectType::Name;
        name = groupName;
    }

    SelectTask::SelectTask(double left, double top, double right, double bottom){
        selectType = SelectType::Rect;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }

    void SelectTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
    }

    bool SelectTask::action(){
        if (!firstRun)
            return false;

        firstRun = false;

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
        }

        return true;
    }

}
