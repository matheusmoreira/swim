#ifndef SWIM_WINDOW_KEYBOARD_EVENT_HANDLER_H
#define SWIM_WINDOW_KEYBOARD_EVENT_HANDLER_H

#include <swim/keyboard_key.h>

/**
 * Pointer to a function that handles the mouse events of a window.
 */
typedef void (*swim_window_keyboard_event_handler)(swim_keyboard_key key, void * context);

#endif /* SWIM_WINDOW_KEYBOARD_EVENT_HANDLER_H */
