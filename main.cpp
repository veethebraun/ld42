#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#include "GUI/UserInterface.h"

int main(int argc, char **argv) {
    //std::cout << "Hello, World!" << std::endl;

    al_init(); // NOLINT

    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();

    al_install_audio();
    al_init_acodec_addon();

    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    UserInterface ui;

    ui.init();
    ui.run();

    return 0;
}