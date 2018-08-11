//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_SELECTBUILDINGCOMMAND_H
#define LD42_SELECTBUILDINGCOMMAND_H


#include "GameCommand.h"
#include "../../GameStuff/BuildingFactory.h"

class SelectBuildingCommand : public GameCommand  {
public:
    explicit SelectBuildingCommand(BuildingType buildingType) : buildingType(buildingType), GameCommand(0) {};
private:
    BuildingType buildingType;
public:
    BuildingType getBuildingType() const {
        return buildingType;
    }
};


#endif //LD42_SELECTBUILDINGCOMMAND_H
