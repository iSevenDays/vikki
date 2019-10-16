#pragma once

#include "simply_window.h"

#include "simply_msg.h"

#include "simply.h"

#include "../util/sdk.h"

#include <pebble.h>

typedef struct SimplyWindowStack SimplyWindowStack;

struct SimplyWindowStack {
  Simply *simply;
  IF_SDK_2_ELSE(Window *pusher, NONE);
  bool is_showing:1;
  bool is_hiding:1;
};

typedef enum WindowType WindowType;

enum WindowType {
  WindowTypeWindow = 0,
  WindowTypeMenu,
  WindowTypeCard,
  WindowTypeLast,
};

typedef struct WindowShowPacket WindowShowPacket;

struct __attribute__((__packed__)) WindowShowPacket {
  Packet packet;
  WindowType type:8;
  bool pushing;
};

typedef struct WindowSignalPacket WindowSignalPacket;

struct __attribute__((__packed__)) WindowSignalPacket {
  Packet packet;
  uint32_t id;
};

typedef WindowSignalPacket WindowHidePacket;

typedef WindowHidePacket WindowEventPacket;

typedef WindowEventPacket WindowShowEventPacket;

typedef WindowEventPacket WindowHideEventPacket;

/// Allocates SimplyWindowStack and sets its 'simply' property to the provided argument
/// @param simply Simply instance
SimplyWindowStack *simply_window_stack_create(Simply *simply);
void simply_window_stack_destroy(SimplyWindowStack *self);

bool simply_window_stack_set_broadcast(bool broadcast);


/// Returns top window or NULL in case not found OR NULL in case it is simply->splash
/// @param simply Simply instance
SimplyWindow *simply_window_stack_get_top_window(Simply *simply);


/// @discussion Push the window. If you need to dismiss the default splash screen, use the following code to dismiss the splash screen and to show default simply ui window
/// @code
/// simply_window_stack_show(simply->window_stack, &simply->ui->window, false);
/// @endcode 
/// @param window SimplyWindow instance
/// @param is_push ignored for SDK 3
void simply_window_stack_show(SimplyWindowStack *self, SimplyWindow *window, bool is_push);
void simply_window_stack_pop(SimplyWindowStack *self, SimplyWindow *window);
void simply_window_stack_back(SimplyWindowStack *self, SimplyWindow *window);

void simply_window_stack_send_show(SimplyWindowStack *self, SimplyWindow *window);
void simply_window_stack_send_hide(SimplyWindowStack *self, SimplyWindow *window);

/**
 Handles commands:
 CommandWindowShow
 CommandWindowHide

 @param simply Simply instance
 @param packet packet with the corresponding command
 @return returns true if handles, false if not
 */
bool simply_window_stack_handle_packet(Simply *simply, Packet *packet);
