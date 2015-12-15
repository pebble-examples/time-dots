#pragma once

#include <pebble.h>

#define MINUTES_COLOR PBL_IF_COLOR_ELSE(GColorBlueMoon, GColorBlack)
#define HOURS_COLOR GColorWhite
#define HOURS_COLOR_INACTIVE PBL_IF_COLOR_ELSE(GColorBlack, GColorDarkGray)
#define BG_COLOR PBL_IF_COLOR_ELSE(GColorDukeBlue, GColorWhite)

#define MINUTES_RADIUS PBL_IF_ROUND_ELSE(60, 60)
#define HOURS_RADIUS 3
#define INSET PBL_IF_ROUND_ELSE(5, 3)