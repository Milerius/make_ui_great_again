import os

when defined(linux):
    {.passL: "-lui_workflow -ldl -pthread -L" & os.getEnv("VCPKG_ROOT") & "/installed/x64-linux/lib -lglad -lSDL2".}
    {.passC: "-std=c++17 -DUI_WORKFLOW_STATIC_DEFINE -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS".}

when defined(macosx):
    {.passL: "-lui_workflow -L" & os.getEnv("VCPKG_ROOT") & "/installed/x64-osx/lib -lglad -lSDL2 -liconv -framework CoreVideo -framework Cocoa -framework IOKit -framework ForceFeedback -framework Carbon -framework CoreAudio -framework AudioToolbox".}
    {.passC: "-std=c++17 -DUI_WORKFLOW_STATIC_DEFINE -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS".}

when defined(windows):
    {.passL: "-L\"" & os.getEnv("ProgramFiles(x86)") & "/ui_workflow/lib\"" &
            " -lui_workflow -L\"" & os.getEnv("VCPKG_ROOT") & "/installed/x64-windows-static/lib\" -lglad -lSDL2 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -lwinmm.lib -lversion.lib -lsetupapi.lib".}
    {.passC: "-std=c++17 -DUI_WORKFLOW_STATIC_DEFINE -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS -I\"" & os.getEnv(
            "ProgramFiles(x86)") & "/ui_workflow/include\"".}

include ui_workflow_nim/nimgui

##! CWrapper
const
    ui = "<ui_wrapper.h>"

type
    e_awesome_icon* = enum
        value
    t_antara_image* {.importc: "t_antara_image", header: ui.} = object
        id* {.importc: "id".}: cuint
        width* {.importc: "width".}: cint
        height* {.importc: "height".}: cint
    t_antara_ui* {.importc: "antara_gui", header: ui, pure,
            incompleteStruct.} = object

proc antara_ui_create*(title: cstring; width: csize;
        height: csize): ptr t_antara_ui {.importc: "antara_ui_create", header: ui.}
proc antara_ui_destroy*(instance: ptr t_antara_ui) {.
        importc: "antara_ui_destroy", header: ui.}
proc antara_pre_update*(instance: ptr t_antara_ui) {.
        importc: "antara_pre_update", header: ui.}
proc antara_update*(instance: ptr t_antara_ui) {.importc: "antara_update", header: ui.}
proc antara_is_running*(instance: ptr t_antara_ui): cint {.
        importc: "antara_is_running", header: ui.}
proc antara_show_demo*(instance: ptr t_antara_ui) {.importc: "antara_show_demo", header: ui.}
proc antara_close_window*(instance: ptr t_antara_ui) {.
        importc: "antara_close_window", header: ui.}
proc antara_load_font*(instance: ptr t_antara_ui; path: cstring;
        size_pixel: cfloat) {.importc: "antara_load_font", header: ui.}
proc antara_awesome_load_font*(instance: ptr t_antara_ui; path: cstring;
        size_pixel: cfloat) {.importc: "antara_awesome_load_font", header: ui.}
proc icon*(id: e_awesome_icon): cstring {.importc: "icon", header: ui.}
proc antara_load_image*(instance: ptr t_antara_ui, id: cstring, path: cstring): t_antara_image {.importc: "antara_load_image", header: ui.}
proc antara_load_image_ws*(instance: ptr t_antara_ui, path: cstring): t_antara_image {.importc: "antara_load_image_ws", header: ui.}
proc antara_get_image*(instance: ptr t_antara_ui, id: cstring): t_antara_image {.importc: "antara_get_image", header: ui.}

##! C++ Wrapper
const
        uicpp = "<ui.wrapper.hpp>"

type
  AntaraUI {.importcpp: "antara_gui", header: uicpp.} = object

proc newAntaraUI*(title: cstring, width: csize, height: csize): ptr AntaraUI {.importcpp: "new antara_gui(#,#,#)".}
proc destroyAntaraUI*(instance: ptr AntaraUI){.importcpp: "delete #".}
proc antaraUpdate*(instance: ptr AntaraUI) {.importcpp: "#->update()", header: uicpp.}
proc antaraIsClose*(instance: ptr AntaraUI): bool {.importcpp: "#->is_close()", header: uicpp.}
proc antaraPreUpdate*(instance: ptr AntaraUI) {.importcpp: "#->pre_update()", header: uicpp.}
proc antaraShowDemo*(instance: ptr AntaraUI) {.importcpp: "#->show_demo()", header: uicpp.}
proc antaraSetClose*(instance: ptr AntaraUI, closing: bool) {.importcpp: "#->set_close(#)", header: uicpp.}

##! ImGui C++ Extras
#const
#        imguicpp = "<imgui.h>"

#type
#   FFIImVec2 {.importcpp: "ImVec2", header: imguicpp} = object
#        x* {.importc: "x".}: cfloat
#        y* {.importc: "y".}: cfloat


#proc ffiGetWindowSize*() : FFIImVec2 {.importcpp: "ImGui::GetWindowSize()", header: imguicpp.}

