#pragma once

#include "simply_msg.h"

#include "simply.h"

#include "../util/color.h"
#include "../util/sdk.h"
#include "../util/status_bar_layer.h"

#include <pebble.h>

typedef struct SimplyWindow SimplyWindow;

struct SimplyWindow {
  Simply *simply;
  Window *window;
  StatusBarLayer *status_bar_layer;
  ScrollLayer *scroll_layer;
  Layer *layer;
  ActionBarLayer *action_bar_layer;
  const WindowHandlers *window_handlers;
  uint32_t id;
  ButtonId button_mask:4;
  GColor8 background_color;
  bool is_scrollable:1;
  bool is_paging:1;
  bool use_scroll_layer:1;
  bool use_status_bar:1;
  bool use_action_bar:1;
#if defined(PBL_ROUND)
  bool status_bar_insets_bottom:1;
#endif
};

typedef struct ClickPacket ClickPacket;

struct __attribute__((__packed__)) ClickPacket {
	Packet packet;
	ButtonId button:8;
};

typedef ClickPacket LongClickPacket;


/// Allocates Window, sets use_status_bar to false
/// @param simply Simply instance
SimplyWindow *simply_window_init(SimplyWindow *self, Simply *simply);
void simply_window_deinit(SimplyWindow *self);
void simply_window_show(SimplyWindow *self);
void simply_window_hide(SimplyWindow *self);


/// Allocates Window, sets clear background, adds window_handlers
void simply_window_preload(SimplyWindow *self);
void simply_window_load(SimplyWindow *self);
void simply_window_unload(SimplyWindow *self);
bool simply_window_appear(SimplyWindow *self);
bool simply_window_disappear(SimplyWindow *self);


/// Back button handler. If pressed and window is not showing - sends CommandWindowHideEvent
/// @param recognizer click recognizer
/// @param context context
void simply_window_single_click_handler(ClickRecognizerRef recognizer, void *context);

void simply_window_set_scrollable(SimplyWindow *self, bool is_scrollable, bool is_paging,
                                  bool animated, bool reset);
void simply_window_set_status_bar(SimplyWindow *self, bool use_status_bar);
void simply_window_set_background_color(SimplyWindow *self, GColor8 background_color);

void simply_window_set_button(SimplyWindow *self, ButtonId button, bool enable);


/// @discussion Enable or disable action bar. Usage:
/// @code
/// simply_window_set_action_bar(&simply->ui->window, true);
/// @endcode
/// @param is_action_bar true if action bar is active, false if not
void simply_window_set_action_bar(SimplyWindow *self, bool is_action_bar);

/// @discussion Set action bar icon. Automatically calls simply_window_set_action_bar(true). Usage:
/// @code
/// simply_window_set_action_bar_icon(&simply->ui->window, BUTTON_ID_SELECT, RESOURCE_ID_IMAGE_MIC);
/// @endcode
/// @param button Button ientifier like BUTTON_ID_SELECT
void simply_window_set_action_bar_icon(SimplyWindow *self, ButtonId button, uint32_t id);
void simply_window_set_action_bar_background_color(SimplyWindow *self, GColor8 background_color);
void simply_window_action_bar_clear(SimplyWindow *self);

bool simply_window_handle_packet(Simply *simply, Packet *packet);
