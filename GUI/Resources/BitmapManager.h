//
// Created by vbrau on 6/30/2018.
//

#ifndef LD42_VBRAUN_BITMAPMANAGER_H
#define LD42_VBRAUN_BITMAPMANAGER_H


#include <allegro5/bitmap.h>
#include <map>

class BitmapManager {
public:
    explicit BitmapManager(const char* yamlfile);
    ALLEGRO_BITMAP* get(const char* key);

    virtual ~BitmapManager();

private:
    std::map<std::string, ALLEGRO_BITMAP*> bitmaps;
};


#endif //LD42_VBRAUN_BITMAPMANAGER_H
