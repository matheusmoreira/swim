#ifndef SWIM_NATIVE_WINDOW_H
#define SWIM_NATIVE_WINDOW_H

typedef struct swim_window swim_window;

/**
 *
 */
extern void * swim_native_window_new(char * name,
                                     int x, int y,
                                     unsigned int w, unsigned int h);

extern void swim_native_window_destroy(void * native_window);

extern int swim_native_window_x(void * native_window);

extern int swim_native_window_y(void * native_window);

extern unsigned int swim_native_window_width(void * native_window);

extern unsigned int swim_native_window_height(void * native_window);

/**
 * Returns the name of the window.
 *
 * The caller will be responsible for freeing the string returned by this
 * function.
 */
extern char * swim_native_window_name(void * native_window);

extern int swim_native_window_visible(void * native_window);

extern void swim_native_window_set_x(void * native_window, int x);

extern void swim_native_window_set_y(void * native_window, int y);

extern void swim_native_window_set_width(void * native_window, unsigned int w);

extern void swim_native_window_set_height(void * native_window, unsigned int h);

extern void swim_native_window_set_position(void * native_window,
                                            int x, int y);

extern void swim_native_window_set_size(void * native_window,
                                        unsigned int w, unsigned int h);

extern void swim_native_window_set_area(void * native_window,
                                        int x, int y,
                                        unsigned int w, unsigned int h);

extern void swim_native_window_set_name(void * native_window, char * name);

extern void swim_native_window_set_visible(void * native_window, int visible);

extern void swim_native_window_set_fullscreen(void * native_window, int fullscreen);

/**
 * Intercepts window events and calls the appropriate callbacks.
 *
 * This function returns immediately if either window or its event handlers is
 * NULL.
 */
extern void swim_native_window_handle_events(void * native_window, swim_window * window);

extern void swim_native_window_stop_handling_events(void * native_window);

#endif /* SWIM_NATIVE_WINDOW_H */
