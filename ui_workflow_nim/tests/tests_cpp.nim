import ui_workflow_nim

var ctx = newAntaraUI("Hello", 200, 200)
while (not ctx.antaraIsClose()):
    ctx.antaraPreUpdate()
    var is_open = true
    igSetNextWindowSize(ImVec2(x: 1280, y: 720), ImGuiCond.FirstUseEver)
    igBegin("atomicDex", addr is_open, (ImGuiWindowFlags.NoCollapse.int32 or
        ImGuiWindowFlags.MenuBar.int32).ImGuiWindowFlags)
    echo igGetWindowSize().x
    if not is_open:
        ctx.antaraSetClose(true)
    igEnd()
    ctx.antaraUpdate()
ctx.destroyAntaraUI