//
// Created by vbrau on 4/14/2018.
//

#include "Text.h"

Text::Text(ALLEGRO_FONT *font, int x, int y, const std::string &text) : font(font), x(x), y(y), text(text), color(al_map_rgb(0,120,255)) {}

void Text::draw() {
    al_draw_text(font, color, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
}

void Text::setText(const std::string &text) {
    Text::text = text;
}

const std::string &Text::getText() const {
    return text;
}

void Text::setColor(const ALLEGRO_COLOR &color) {
    Text::color = color;
}
