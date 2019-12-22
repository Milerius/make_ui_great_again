#ifndef UI_WORKFLOW_UI_WRAPPER_H
#define UI_WORKFLOW_UI_WRAPPER_H

#ifdef UI_WORKFLOW_STATIC_DEFINE
#  define UI_WORKFLOW_EXPORT
#  define UI_WORKFLOW_NO_EXPORT
#else
#  ifndef UI_WORKFLOW_EXPORT
#    ifdef ui_workflow_EXPORTS
/* We are building this library */
#      define UI_WORKFLOW_EXPORT __declspec(dllexport)
#    else
/* We are using this library */
#      define UI_WORKFLOW_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef UI_WORKFLOW_NO_EXPORT
#    define UI_WORKFLOW_NO_EXPORT
#  endif
#endif

#ifndef UI_WORKFLOW_DEPRECATED
#  define UI_WORKFLOW_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef UI_WORKFLOW_DEPRECATED_EXPORT
#  define UI_WORKFLOW_DEPRECATED_EXPORT UI_WORKFLOW_EXPORT UI_WORKFLOW_DEPRECATED
#endif

#ifndef UI_WORKFLOW_DEPRECATED_NO_EXPORT
#  define UI_WORKFLOW_DEPRECATED_NO_EXPORT UI_WORKFLOW_NO_EXPORT UI_WORKFLOW_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef UI_WORKFLOW_NO_DEPRECATED
#    define UI_WORKFLOW_NO_DEPRECATED
#  endif
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum awesome_icon
    {
        value
    } e_awesome_icon;

    typedef struct antara_image
    {
        unsigned int id;
        int          width;
        int          height;
    } t_antara_image;
    
    typedef struct antara_gui antara_gui;

    UI_WORKFLOW_EXPORT antara_gui*   antara_ui_create(const char* title, size_t width, size_t height);
    UI_WORKFLOW_EXPORT void           antara_ui_destroy(antara_gui* instance);
    UI_WORKFLOW_EXPORT void           antara_pre_update(antara_gui* instance);
    UI_WORKFLOW_EXPORT void           antara_update(antara_gui* instance);
    UI_WORKFLOW_EXPORT int            antara_is_running(antara_gui* instance);
    UI_WORKFLOW_EXPORT  void           antara_show_demo(antara_gui* instance);
    UI_WORKFLOW_EXPORT void           antara_close_window(antara_gui* instance);
    UI_WORKFLOW_EXPORT void           antara_load_font(antara_gui* instance, const char* path, float size_pixel);
    UI_WORKFLOW_EXPORT void           antara_awesome_load_font(antara_gui* instance, const char* path, float size_pixel);
    UI_WORKFLOW_EXPORT const char*    icon(e_awesome_icon id);
    UI_WORKFLOW_EXPORT t_antara_image antara_load_image(antara_gui* instance, const char* id, const char* path);
    UI_WORKFLOW_EXPORT t_antara_image antara_load_image_ws(antara_gui* instance, const char* path);;
    UI_WORKFLOW_EXPORT t_antara_image antara_get_image(antara_gui* instance, const char* id);
    UI_WORKFLOW_EXPORT t_antara_image antara_draw_image(antara_gui* instance, t_antara_image img);

#ifdef __cplusplus
}
#endif

#endif // UI_WORKFLOW_UI_WRAPPER_H
