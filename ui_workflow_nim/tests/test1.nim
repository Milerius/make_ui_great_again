# This is just an example to get you started. You may wish to put all of your
# tests into a single file, or separate them into multiple `test1`, `test2`
# etc. files (better names are recommended, just make sure the name starts with
# the letter 't').
#
# To run these tests, simply execute `nimble test`.

import unittest

import ui_workflow_nim

var ctx = antara_ui_create("Hello", 200, 200)
while antara_is_running(ctx) == 0:
  antara_pre_update(ctx)
  igBegin("Foo")
  igButton("Hello")
  igEnd()
  antara_show_demo(ctx)
  antara_update(ctx)
antara_ui_destroy(ctx)