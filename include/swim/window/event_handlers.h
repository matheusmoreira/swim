#ifndef SWIM_WINDOW_EVENT_HANDLERS_H
#define SWIM_WINDOW_EVENT_HANDLERS_H

#include <swim/window/keyboard_event_handler.h>
#include <swim/window/mouse_event_handler.h>

/**
 * Pointers to functions that handle window events.
 */
typedef struct {
    swim_window_keyboard_event_handler key_pressed,
                                       key_released;
    swim_window_mouse_event_handler button_pressed,
                                    button_released;
    void * context;
} swim_window_event_handlers;

/**
 * Returns a pointer to a new set of window event handlers.
 */
extern swim_window_event_handlers * swim_window_event_handlers_new();

/**
 * Frees the memory used by the given set of window event handlers.
 */
extern void swim_window_event_handlers_destroy(swim_window_event_handlers * handlers);

#endif /* SWIM_WINDOW_EVENT_HANDLERS_H */
