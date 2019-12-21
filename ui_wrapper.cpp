#include <memory>

#include "ui.wrapper.hpp"
#include "ui_wrapper.h"

#define TO_CPP(a) (reinterpret_cast<antara_gui*>(a))
#define TO_C(a)   (reinterpret_cast<antara_ui*>(a))

/*struct antara_ui
{
    std::unique_ptr<antara_gui> obj;
};*/

t_antara_ui*
antara_ui_create(const char* title, size_t width, size_t height)
{
    t_antara_ui* instance;
    //antara_gui*  obj;

    //instance      = (t_antara_ui*)malloc(sizeof(*instance));
    //obj           = new antara_gui(title, width, height);
    instance = TO_C(new antara_gui(title, width, height));

    return instance;
}
void
antara_ui_destroy(t_antara_ui* instance)
{
    if (instance != nullptr)
    {
        delete TO_CPP( instance);
        //delete TO_CPP(instance);
        //free(instance);
    }
}
void
antara_pre_update(t_antara_ui* instance)
{
    if (instance != nullptr) { TO_CPP(instance)->pre_update(); }
}

void
antara_update(t_antara_ui* instance)
{
    if (instance != nullptr) { TO_CPP(instance)->update(); }
}

int
antara_is_running(t_antara_ui* instance)
{
    if (instance != nullptr) { return static_cast<int>(TO_CPP(instance)->is_close()); }
    return 0;
}

void
antara_show_demo(t_antara_ui* instance)
{
    if (instance != nullptr) { TO_CPP(instance)->show_demo(); }
}

void
antara_close_window(t_antara_ui* instance)
{
    if (instance != nullptr) { TO_CPP(instance)->set_close(true); };
}
void
antara_load_font(t_antara_ui* instance, const char* path, float size_pixel)
{
    if (instance != nullptr) { TO_CPP(instance)->load_font(path, size_pixel); };
}
void
antara_awesome_load_font(t_antara_ui* instance, const char* path, float size_pixel)
{
    if (instance != nullptr) { TO_CPP(instance)->load_awesome_font(path, size_pixel); };
}

t_antara_image
antara_load_image(t_antara_ui* instance, const char* id, const char* path)
{
    opengl_image img;
    if (instance != nullptr) {
        TO_CPP(instance)->load_image(id, path, img);
    };
    return {img.id, img.width, img.height};
}

t_antara_image
antara_get_image(t_antara_ui* instance, const char* id)
{
    if (instance != nullptr) {
        auto res = TO_CPP(instance)->get_image(id);
        return {res.id, res.width, res.height};
    };
    return {};
}

t_antara_image
antara_load_image_ws(t_antara_ui* instance, const char* path)
{
    opengl_image img;
    if (instance != nullptr) {
        TO_CPP(instance)->load_image(path, img);
    };
    return {img.id, img.width, img.height};
}
