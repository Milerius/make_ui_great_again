//
// Created by Roman Szterg on 18/12/2019.
//

#include "ui.wrapper.hpp"

int main()
{
    antara_gui gui("example", 200, 200);
    while (not gui.is_close()) {
        gui.pre_update();
        gui.show_demo();
        gui.update();
    }
}