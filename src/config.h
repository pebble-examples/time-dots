#pragma once

#include <pebble.h>

#define MINUTES_COLOR GColorBlueMoon
#define HOURS_COLOR GColorWhite
#define HOURS_COLOR_INACTIVE GColorBlack
#define BG_COLOR GColorDukeBlue

#define MINUTES_RADIUS PBL_IF_ROUND_ELSE(60, 60)
#define HOURS_RADIUS 3
#define INSET PBL_IF_ROUND_ELSE(5, 3)