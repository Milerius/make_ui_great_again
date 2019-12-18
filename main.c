//
// Created by Roman Szterg on 18/12/2019.
//

#include "ui_wrapper.h"

int main(void)
{
    t_antara_ui* instance = antara_ui_create("example", 200, 200);
    while (!antara_is_running(instance)) {
        antara_pre_update(instance);
        antara_show_demo(instance);
        antara_update(instance);
    }
    antara_ui_destroy(instance);
}