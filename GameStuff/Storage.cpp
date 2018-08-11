//
// Created by vbrau on 8/11/2018.
//

#include "Storage.h"

void Storage::onBuild(Resources *resources) {
    Building::onBuild(resources);

    resources->addStorage(this->getStorage());
}

void Storage::onDestroy(Resources *resources) {
        resources->addStorage(this->getStorage()*-1);
}
