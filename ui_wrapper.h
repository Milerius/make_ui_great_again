#ifndef UI_WORKFLOW_UI_WRAPPER_H
#define UI_WORKFLOW_UI_WRAPPER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct antara_ui;
    typedef struct antara_ui t_antara_ui;

    t_antara_ui* antara_ui_create(const char* title, size_t width, size_t height);
    void         antara_ui_destroy(t_antara_ui* instance);
    void         antara_pre_update(t_antara_ui* instance);
    void         antara_update(t_antara_ui* instance);
    int          antara_is_running(t_antara_ui* instance);
    void         antara_show_demo(t_antara_ui* instance);


#ifdef __cplusplus
}
#endif

#endif // UI_WORKFLOW_UI_WRAPPER_H
