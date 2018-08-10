//
// Created by vbrau on 4/14/2018.
//

#ifndef LD42_VBRAUN_TEXT_H
#define LD42_VBRAUN_TEXT_H

#include "allegro5/allegro_font.h"
#include "Widget.h"
#include <string>

class Text : public Widget {
public:
    Text(ALLEGRO_FONT *font, int x, int y, const std::string &text);

    void draw() override;

    const std::string &getText() const;
    void setText(const std::string &text);
    void setColor(const ALLEGRO_COLOR &color);

private:
    ALLEGRO_FONT *font;
    int x;
    int y;
    std::string text;

    ALLEGRO_COLOR color;
};


#endif //LD42_VBRAUN_TEXT_H
