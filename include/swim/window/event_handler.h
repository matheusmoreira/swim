#ifndef SWIM_WINDOW_EVENT_HANDLER_H
#define SWIM_WINDOW_EVENT_HANDLER_H

typedef struct swim_window swim_window;

/**
 * Pointer to a generic event handler function.
 */
typedef void (*swim_window_event_handler)(swim_window * window, void * context);

#endif /* SWIM_WINDOW_EVENT_HANDLER_H */
