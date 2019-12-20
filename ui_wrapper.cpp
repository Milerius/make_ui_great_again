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
void
antara_load_font(t_antara_ui* instance, const char* path, float size_pixel)
{
    if (instance != nullptr) { static_cast<antara_gui*>(instance->obj)->load_font(path, size_pixel); };
}
void
antara_awesome_load_font(t_antara_ui* instance, const char* path, float size_pixel)
{
    if (instance != nullptr) { static_cast<antara_gui*>(instance->obj)->load_awesome_font(path, size_pixel); };
}

t_antara_image
antara_load_image(t_antara_ui* instance, const char* id, const char* path)
{
    opengl_image img;
    if (instance != nullptr) {
        static_cast<antara_gui*>(instance->obj)->load_image(id, path, img);
    };
    return {img.id, img.width, img.height};
}

t_antara_image
antara_get_image(t_antara_ui* instance, const char* id)
{
    if (instance != nullptr) {
        auto res = static_cast<antara_gui*>(instance->obj)->get_image(id);
        return {res.id, res.width, res.height};
    };
    return {};
}
