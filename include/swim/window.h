#ifndef SWIM_WINDOW_H
#define SWIM_WINDOW_H

#include <swim/window/event_handlers.h>

/**
 * A window with associated event handlers.
 */
typedef struct swim_window {
    swim_window_event_handlers * event_handlers;
    void * native_window;
} swim_window;

/**
 * Creates a new window at the given coordinates with the given size and name.
 */
extern swim_window * swim_window_new(char * name,
                                     int x, int y,
                                     unsigned int w, unsigned int h);

/**
 * Frees the memory used by the given window.
 */
extern swim_window * swim_window_destroy(swim_window * window);

/**
 * Returns the X coordinate of the window.
 */
extern int swim_window_x(swim_window * window);

/**
 * Returns the Y coordinate of the window.
 */
extern int swim_window_y(swim_window * window);

/**
 * Returns the width of the window.
 */
extern unsigned int swim_window_width(swim_window * window);

/**
 * Returns the height of the window.
 */
extern unsigned int swim_window_height(swim_window * window);

/**
 * Returns the name of the window.
 */
extern char * swim_window_name(swim_window * window);

/**
 * Returns whether or not the window is visible.
 */
extern int swim_window_visible(swim_window * window);

/**
 * Returns the window's event handlers.
 */
extern swim_window_event_handlers * swim_window_callbacks(swim_window * window);

/**
 * Sets the X coordinate of the window.
 */
extern void swim_window_set_x(swim_window * window, int x);

/**
 * Sets the Y coordinate of the window.
 */
extern void swim_window_set_y(swim_window * window, int y);

/**
 * Sets the width of the window.
 */
extern void swim_window_set_width(swim_window * window, unsigned int w);

/**
 * Sets the height coordinate of the window.
 */
extern void swim_window_set_height(swim_window * window, unsigned int h);

/**
 * Sets the position of the window in 2D space.
 */
extern void swim_window_set_position(swim_window * window,
                                     int x, int y);

/**
 * Sets the size of the window.
 */
extern void swim_window_set_size(swim_window * window,
                                 unsigned int w, unsigned int h);

/**
 * Sets the area of the window.
 */
extern void swim_window_set_area(swim_window * window,
                                 int x, int y,
                                 unsigned int w, unsigned int h);

/**
 * Sets the name of the window.
 */
extern void swim_window_set_name(swim_window * window, char * name);

/**
 * Sets the visibility of the window.
 */
extern void swim_window_set_visible(swim_window * window, int visible);

/**
 * Makes the window span the entire screen.
 */
extern void swim_window_set_fullscreen(swim_window * window, int fullscreen);

/**
 * Sets the window's event handlers. This function will not free the memory used
 * by the window's current set of event handlers.
 */
extern void swim_window_set_event_handlers(swim_window * window,
                                           swim_window_event_handlers * handlers);

/**
 * Starts the event loop.
 */
extern void swim_window_handle_events(swim_window * window);

/**
 * Stops the event loop. Usually called when the user closes the window.
 */
extern void swim_window_stop_handling_events(swim_window * window);

#endif /* SWIM_WINDOW_H */
