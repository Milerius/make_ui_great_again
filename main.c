//
// Created by Roman Szterg on 18/12/2019.
//

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include "ui_wrapper.h"

int
main(void)
{
    antara_gui* instance = antara_ui_create("example", 200, 200);
    while (!antara_is_running(instance))
    {
        antara_pre_update(instance);
        ImVec2 dummy;
        dummy.x = 1280;
        dummy.y = 720;
        igSetNextWindowSize(dummy, ImGuiCond_FirstUseEver);
        static bool is_open = true;
        igBegin("atomicDex", &is_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
        printf("%f", igGetWindowSize().x); //< Crash Here
        if (!is_open) { antara_close_window(instance); }
        igEnd();
        // antara_show_demo(instance);
        antara_update(instance);
    }
    antara_ui_destroy(instance);
}