#include <memory>

#include "ui.wrapper.hpp"
#include "ui_wrapper.h"

struct antara_ui
{
    void* obj;
};

t_antara_ui*
antara_ui_create(const char* title, size_t width, size_t height)
{
    t_antara_ui* instance;
    antara_gui*  obj;

    instance      = (t_antara_ui*)malloc(sizeof(*instance));
    obj           = new antara_gui(title, width, height);
    instance->obj = obj;

    return instance;
}
void
antara_ui_destroy(t_antara_ui* instance)
{
    if (instance != nullptr)
    {
        delete static_cast<antara_gui*>(instance->obj);
        free(instance);
    }
}
void
antara_pre_update(t_antara_ui* instance)
{
    if (instance != nullptr) { static_cast<antara_gui*>(instance->obj)->pre_update(); }
}

void
antara_update(t_antara_ui* instance)
{
    if (instance != nullptr) { static_cast<antara_gui*>(instance->obj)->update(); }
}

int
antara_is_running(t_antara_ui* instance)
{
    if (instance != nullptr) { return static_cast<int>(static_cast<antara_gui*>(instance->obj)->is_close()); }
    return 0;
}

void
antara_show_demo(t_antara_ui* instance)
{
    if (instance != nullptr) { static_cast<antara_gui*>(instance->obj)->show_demo(); }
}

void
antara_close_window(t_antara_ui* instance)
{
    if (instance != nullptr) { static_cast<antara_gui*>(instance->obj)->set_close(true); };
}
