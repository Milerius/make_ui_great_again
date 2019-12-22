#include <memory>

#include "ui.wrapper.hpp"
#include "ui_wrapper.h"


/*struct antara_ui
{
    std::unique_ptr<antara_gui> obj;
};*/

antara_gui*
antara_ui_create(const char* title, size_t width, size_t height)
{
    antara_gui* instance;
    //antara_gui*  obj;

    //instance      = (antara_gui*)malloc(sizeof(*instance));
    //obj           = new antara_gui(title, width, height);
    instance = new antara_gui(title, width, height);

    return instance;
}
void
antara_ui_destroy(antara_gui* instance)
{
    if (instance != nullptr)
    {
        delete  instance;
        //delete instance);
        //free(instance);
    }
}
void
antara_pre_update(antara_gui* instance)
{
    if (instance != nullptr) { instance->pre_update(); }
}

void
antara_update(antara_gui* instance)
{
    if (instance != nullptr) { instance->update(); }
}

int
antara_is_running(antara_gui* instance)
{
    if (instance != nullptr) { return static_cast<int>(instance->is_close()); }
    return 0;
}

void
antara_show_demo(antara_gui* instance)
{
    if (instance != nullptr) { instance->show_demo(); }
}

void
antara_close_window(antara_gui* instance)
{
    if (instance != nullptr) { instance->set_close(true); };
}
void
antara_load_font(antara_gui* instance, const char* path, float size_pixel)
{
    if (instance != nullptr) { instance->load_font(path, size_pixel); };
}
void
antara_awesome_load_font(antara_gui* instance, const char* path, float size_pixel)
{
    if (instance != nullptr) { instance->load_awesome_font(path, size_pixel); };
}

t_antara_image
antara_load_image(antara_gui* instance, const char* id, const char* path)
{
    opengl_image img;
    if (instance != nullptr) {
        instance->load_image(id, path, img);
    };
    return {img.id, img.width, img.height};
}

t_antara_image
antara_get_image(antara_gui* instance, const char* id)
{
    if (instance != nullptr) {
        auto res = instance->get_image(id);
        return {res.id, res.width, res.height};
    };
    return {};
}

t_antara_image
antara_load_image_ws(antara_gui* instance, const char* path)
{
    opengl_image img;
    if (instance != nullptr) {
        instance->load_image(path, img);
    };
    return {img.id, img.width, img.height};
}
