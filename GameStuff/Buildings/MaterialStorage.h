//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_MATERIALSTORAGE_H
#define LD42_MATERIALSTORAGE_H


#include "../Storage.h"

class MaterialStorage : public Storage {
public:
    MaterialStorage(int x, int y);

    void resourceGeneration(Resources* resources) override {};
protected:
    std::valarray<int> getCost() override;
    std::valarray<int> getStorage() override;

};


#endif //LD42_MATERIALSTORAGE_H
