//
// Created by vbrau on 6/30/2018.
//

#ifndef LD42_VBRAUN_FONTHOLDER_H
#define LD42_VBRAUN_FONTHOLDER_H


#include <string>
#include <allegro5/allegro_font.h>
#include <map>

class FontManager {
public:
    explicit FontManager(const char *filename);
    ALLEGRO_FONT* get(const char* key);

    virtual ~FontManager();

private:
    std::map<std::string, ALLEGRO_FONT*> fonts;
};


#endif //LD42_VBRAUN_FONTHOLDER_H
