#ifndef UI_WORKFLOW_UI_WRAPPER_H
#define UI_WORKFLOW_UI_WRAPPER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum awesome_icon
    {
        value
    } e_awesome_icon;

    struct antara_ui;
    typedef struct antara_ui t_antara_ui;

    t_antara_ui* antara_ui_create(const char* title, size_t width, size_t height);
    void         antara_ui_destroy(t_antara_ui* instance);
    void         antara_pre_update(t_antara_ui* instance);
    void         antara_update(t_antara_ui* instance);
    int          antara_is_running(t_antara_ui* instance);
    void         antara_show_demo(t_antara_ui* instance);
    void         antara_close_window(t_antara_ui* instance);
    void         antara_load_font(t_antara_ui* instance, const char* path, float size_pixel);
    void         antara_awesome_load_font(t_antara_ui* instance, const char* path, float size_pixel);
    const char*  icon(e_awesome_icon id);


#ifdef __cplusplus
}
#endif

#endif // UI_WORKFLOW_UI_WRAPPER_H
