# This is just an example to get you started. You may wish to put all of your
# tests into a single file, or separate them into multiple `test1`, `test2`
# etc. files (better names are recommended, just make sure the name starts with
# the letter 't').
#
# To run these tests, simply execute `nimble test`.

import unittest

import ui_workflow_nim

var ctx = antara_ui_create("Hello", 200, 200)
#antara_load_font(ctx, "Ruda-Bold.ttf", 15.0)
#antara_awesome_load_font(ctx, "fa-solid-900.ttf", 16.0)
#var res = antara_load_image(ctx, "btc", "btc.png")
#echo res
while antara_is_running(ctx) == 0:
  antara_pre_update(ctx)
  var is_open = true
  igSetNextWindowSize(ImVec2(x: 1280, y: 720), ImGuiCond.FirstUseEver)
  igBegin("atomicDex", addr is_open, (ImGuiWindowFlags.NoCollapse.int32 or
      ImGuiWindowFlags.MenuBar.int32).ImGuiWindowFlags)
  echo "ET LA ???", igGetWindowSize().x
  if not is_open:
      antara_close_window(ctx)
  igEnd()
  #igBegin("Foo")
  #igButton("Hello")
  #igEnd()
  #igImage(ImTextureID(cast[pointer](cast[ptr cuint](res.id))), ImVec2(x: res.width.float32, y: res.height.float32))
  #antara_show_demo(ctx)
  antara_update(ctx)
antara_close_window(ctx)  
antara_ui_destroy(ctx)