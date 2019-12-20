# This is just an example to get you started. You may wish to put all of your
# tests into a single file, or separate them into multiple `test1`, `test2`
# etc. files (better names are recommended, just make sure the name starts with
# the letter 't').
#
# To run these tests, simply execute `nimble test`.

import unittest

import ui_workflow_nim

var ctx = antara_ui_create("Hello", 200, 200)
antara_load_font(ctx, "Ruda-Bold.ttf", 15.0)
antara_awesome_load_font(ctx, "fa-solid-900.ttf", 16.0)
var res = antara_load_image(ctx, "btc", "btc.png")
echo res
while antara_is_running(ctx) == 0:
  antara_pre_update(ctx)
  igBegin("Foo")
  igButton("Hello")
  igEnd()
  igImage(ImTextureID(cast[pointer](cast[ptr cuint](res.id))), ImVec2(x: res.width.float32, y: res.height.float32))
  antara_show_demo(ctx)
  antara_update(ctx)
antara_close_window(ctx)  
antara_ui_destroy(ctx)