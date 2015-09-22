#include "main_window.h"

static Window *s_window;
static Layer *s_canvas;

static int s_hours, s_minutes;

static void layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  GPoint center = grect_center_point(&bounds);

  // 12 hours only, with a minimum size
  s_hours -= (s_hours > 12) ? 12 : 0;

  // Minutes are expanding circle arc
  int radius = MINUTES_RADIUS;
  int minute_angle = (int)(((float)s_minutes / 60.0F) * 360.0F);
  GRect frame = GRect((bounds.size.w / 2) - radius, (bounds.size.h / 2) - radius, 
                      2 * radius, 2 * radius);
  graphics_context_set_fill_color(ctx, MINUTES_COLOR);
  graphics_fill_radial(ctx, frame, GOvalScaleModeFillCircle, 20, 0, DEG_TO_TRIGANGLE(minute_angle));

  // Adjust geometry variables for inner ring
  frame.origin.x += 2 * HOURS_RADIUS;
  frame.origin.y += 3 * HOURS_RADIUS;
  frame.size.w -= 6 * HOURS_RADIUS;
  frame.size.h -= 6 * HOURS_RADIUS;

  // Hours are dots
  for(int i = 0; i < 12; i++) {
    int hour_angle = (int)(((float)i / 12.0F) * 360.0F);
    GPoint pos = gpoint_from_polar(frame, GOvalScaleModeFillCircle, DEG_TO_TRIGANGLE(hour_angle));

    graphics_context_set_fill_color(ctx, i <= s_hours ? HOURS_COLOR : HOURS_COLOR_INACTIVE);
    graphics_fill_circle(ctx, pos, HOURS_RADIUS);
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_canvas = layer_create(bounds);
  layer_set_update_proc(s_canvas, layer_update_proc);
  layer_add_child(window_layer, s_canvas);
}

static void window_unload(Window *window) {
  layer_destroy(s_canvas);
  window_destroy(s_window);
  s_window = NULL;
}

void main_window_push() {
  if(!s_window) {
    s_window = window_create();
    window_set_background_color(s_window, BG_COLOR);
    window_set_window_handlers(s_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
  }
  window_stack_push(s_window, true);
}

void main_window_update(int hours, int minutes) {
  s_hours = hours;
  s_minutes = minutes;
  layer_mark_dirty(s_canvas);
}
