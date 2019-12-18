when defined(macosx):
    {.passL: "-lui_workflow".}
    {.passC: "-DCIMGUI_DEFINE_ENUMS_AND_STRUCTS".}

include ui_workflow_nim/nimgui

const
    ui = "<ui_wrapper.h>"

type
    t_antara_ui* {.importc: "t_antara_ui", header: ui, pure,
            incompleteStruct.} = object

proc antara_ui_create*(title: cstring; width: csize; height: csize) : ptr t_antara_ui {.importc: "antara_ui_create", header: ui.} 
proc antara_ui_destroy*(instance: ptr t_antara_ui) {.importc: "antara_ui_destroy", header: ui.} 
proc antara_pre_update*(instance: ptr t_antara_ui) {.importc: "antara_pre_update", header: ui.} 
proc antara_update*(instance: ptr t_antara_ui) {.importc: "antara_update", header: ui.} 
proc antara_is_running*(instance: ptr t_antara_ui): cint {.importc: "antara_is_running", header: ui.}
proc antara_show_demo*(instance: ptr t_antara_ui) {.importc: "antara_show_demo", header: ui.}