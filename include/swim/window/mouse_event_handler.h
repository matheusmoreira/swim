#ifndef SWIM_WINDOW_MOUSE_EVENT_HANDLER_H
#define SWIM_WINDOW_MOUSE_EVENT_HANDLER_H

#include <swim/mouse_button.h>

typedef struct swim_window swim_window;

/**
 * Pointer to a function that handles the keyboard events of a window.
 */
typedef void (*swim_window_mouse_event_handler)(swim_window * window,
                                                swim_mouse_button button,
                                                void * context);

#endif /* SWIM_WINDOW_MOUSE_EVENT_HANDLER_H */
