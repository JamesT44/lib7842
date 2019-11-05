#include "test.hpp"

#include "lvgl/lvgl.h"

#include "lib7842/api/gui/odomDebug.hpp"
#include "lib7842/api/gui/screen.hpp"

void lvglTest() {

  Screen scr(lv_scr_act(), LV_COLOR_ORANGE);

  scr.makePage<OdomDebug>().attachOdom(nullptr).attachResetter(nullptr);

  scr.startTask("Screen");

  while (true) {
    pros::delay(100);
  }
}