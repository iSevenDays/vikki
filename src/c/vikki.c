#define SPLASH_LOGO

//#if PBL_PLATFORM_TYPE_CURRENT == PlatformTypeBasalt
//##include "src/resource_ids.auto.h"
//#endif

#include "vikki.h"
#include "simply.h"
#include "simply_accel.h"
#include "simply_menu.h"
#include "simply_res.h"
#include "simply_ui.h"
#include "simply_voice.h"
#include "simply_wakeup.h"
#include "simply_window.h"
#include "simply_stage.h"
#include "simply_window_stack.h"
#include "simply_splash.h"



//static Window *s_window;
//static TextLayer *s_text_layer;

// Dictation
static DictationSession *s_dictation_session;
// Declare a buffer for the DictationSession
static char s_last_text[512];

/******************************* Dictation API ********************************/
static void dictation_session_callback(DictationSession *session, DictationSessionStatus status,
                                       char *transcription, void *context) {
  if(status == DictationSessionStatusSuccess) {
    // Display the dictated text
    snprintf(s_last_text, sizeof(s_last_text), "%s", transcription);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Did get dictation text: %s", s_last_text);
  } else {
    // Display the reason for any error
    static char s_failed_buff[128];
    snprintf(s_failed_buff, sizeof(s_failed_buff), "Transcription failed.\n\nError ID:\n%d", (int)status);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed geting dictation text: %s", s_failed_buff);
  }
}
/************************************ App *************************************/

//void select_click_handler(ClickRecognizerRef recognizer, void *context) {
//	Simply *simply = context;
//	APP_LOG(APP_LOG_LEVEL_DEBUG, "Will start dictation session");
//	dictation_session_start(s_dictation_session);
//}
//
//static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
//	text_layer_set_text(s_text_layer, "Up");
//}
//
//static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
//	text_layer_set_text(s_text_layer, "Down");
//}
//
//static void click_config_provider(void *context) {
//	SimplyWindow *simplyWindow = context;
//	Window *window = simplyWindow->window;
//	window_set_click_config_provider_with_context(window, click_config_provider, simplyWindow);
//
//	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	//window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	//window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
//}
//
//static void window_load(Window *window) {
//	Layer *window_layer = window_get_root_layer(window);
//	GRect bounds = layer_get_bounds(window_layer);
//
//	s_text_layer = text_layer_create(GRect(bounds.origin.x, (bounds.size.h - 24) / 2, bounds.size.w, bounds.size.h));
//	text_layer_set_text(s_text_layer, "Press Select to get input!!!");
//	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
//	layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
//}
//
//static void window_unload(Window *window) {
//	text_layer_destroy(s_text_layer);
//}
//
//static void init(void) {
//	s_window = window_create();
//	window_set_click_config_provider(s_window, click_config_provider);
//	window_set_window_handlers(s_window, (WindowHandlers) {
//		.load = window_load,
//		.unload = window_unload,
//	});
//	const bool animated = true;
//	window_stack_push(s_window, animated);
//
//	// Create new dictation session
//	s_dictation_session = dictation_session_create(sizeof(s_last_text), dictation_session_callback, NULL);
//}
//
//static void deinit(void) {
//	// Free the last session data
//	dictation_session_destroy(s_dictation_session);
//	window_destroy(s_window);
//}



void after_splash_shown(void* data) {
	Simply *simply = data;

	APP_LOG(APP_LOG_LEVEL_DEBUG, "Will show title & subtitle");
	if (simply->ui == NULL) {
		APP_LOG(APP_LOG_LEVEL_ERROR, "Simply ui is NULL");
	} else {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Simply ui is NOT NULL");
	}

	simply_window_stack_show(simply->window_stack, &simply->ui->window, false);
	simply_ui_clear(simply->ui, ~0);

	simply_ui_set_text_color(simply->ui, UiSubtitle, GColor8Black);
	simply_ui_set_text(simply->ui, UiSubtitle, "Vikki");
	simply_ui_set_text(simply->ui, UiBody, "Нажмите центральную кнопку и скажите");
	
	// Setup microphone UI
	simply_window_set_action_bar_icon(&simply->ui->window, BUTTON_ID_SELECT, RESOURCE_ID_IMAGE_MIC);

	// Setup microphone select button handler
	//ActionBarLayer *action_bar = simply_window_stack_get_top_window(simply)->action_bar_layer;
	//action_bar_layer_set_click_config_provider(action_bar, click_config_provider);

	//window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_click_handler);

	SimplyWindow *simplyWindow = &simply->ui->window;
	Window *window = simplyWindow->window;
	// Unregister the old click config provider
	//window_set_click_config_provider_with_context(window, NULL, NULL);
	//window_set_click_config_provider_with_context(window, click_config_provider, simplyWindow);

	//window_set_click_config_provider(window, click_config_provider);

	// Setup dictating session
	s_dictation_session = dictation_session_create(sizeof(s_last_text), dictation_session_callback, NULL);

	APP_LOG(APP_LOG_LEVEL_DEBUG, "Did show title & subtitle");
}
//#error test error
bool handle_command(Simply *simply, Packet *packet) {
	switch (packet->type) {
		case CommandWindowHideEvent:
			//WindowHideEventPacket p;
			//WindowHideEventPacket *cpacket = (WindowHideEventPacket*) &packet;

			return true;
		default:
			return false;
	}
}

int main(void) {
	Simply *simply = malloc(sizeof(*simply));
	simply->is_local = true;
	simply->accel = simply_accel_create(simply);
	simply->voice = simply_voice_create(simply);
	simply->res = simply_res_create(simply);
	simply->splash = simply_splash_create(simply);
	simply->stage = simply_stage_create(simply);
	simply->menu = simply_menu_create(simply);
	simply->msg = simply_msg_create(simply);
	simply->ui = simply_ui_create_with_logging(simply, true);
	simply->window_stack = simply_window_stack_create(simply);

	simply_wakeup_init(simply);

	simply_set_msg_packet_handler(simply->msg, handle_command);

	APP_LOG(APP_LOG_LEVEL_DEBUG, "Will register timer");
	app_timer_register(1000, after_splash_shown, simply);

	bool animated = false;
	window_stack_push(simply->splash->window, animated);

	app_event_loop();
	simply_destroy(simply);
	dictation_session_destroy(s_dictation_session);
}
