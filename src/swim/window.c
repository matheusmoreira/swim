#include <swim/stdlib.h>
#include <swim/window.h>
#include <swim/native/window.h>

/* Window interface implementation */

swim_window * swim_window_new(char * name, int x, int y, unsigned int w, unsigned int h) {
    swim_window * window = swim_malloc(sizeof(swim_window));
    window->native_window = swim_native_window_new(name, x, y, w, h);
    window->event_handlers = swim_window_event_handlers_new();
    return window;
}

swim_window * swim_window_destroy(swim_window * window) {
    if (window != NULL) {
        if (window->native_window != NULL) {
            swim_native_window_destroy(window->native_window);
            window->native_window = NULL;
        }
        if (window->event_handlers != NULL) {
            swim_window_event_handlers_destroy(window->event_handlers);
            window->event_handlers = NULL;
        }
        swim_free(window);
    }
}

int swim_window_x(swim_window * window) {
    return swim_native_window_x(window->native_window);
}

int swim_window_y(swim_window * window) {
    return swim_native_window_y(window->native_window);
}

unsigned int swim_window_width(swim_window * window) {
    return swim_native_window_width(window->native_window);
}

unsigned int swim_window_height(swim_window * window) {
    return swim_native_window_height(window->native_window);
}

char * swim_window_name(swim_window * window) {
    return swim_native_window_name(window->native_window);
}

int swim_window_visible(swim_window * window) {
    return swim_native_window_visible(window->native_window);
}

swim_window_event_handlers * swim_window_callbacks(swim_window * window) {
    return window->event_handlers;
}

void swim_window_set_x(swim_window * window, int x) {
    swim_native_window_set_x(window->native_window, x);
}

void swim_window_set_y(swim_window * window, int y) {
    swim_native_window_set_y(window->native_window, y);
}

void swim_window_set_width(swim_window * window, unsigned int width) {
    swim_native_window_set_width(window->native_window, width);
}

void swim_window_set_height(swim_window * window, unsigned int height) {
    swim_native_window_set_height(window->native_window, height);
}

void swim_window_set_position(swim_window * window, int x, int y) {
    swim_native_window_set_position(window->native_window, x, y);
}

void swim_window_set_size(swim_window * window, unsigned int w, unsigned int h) {
    swim_native_window_set_size(window->native_window, w, h);
}

void swim_window_set_area(swim_window * window, int x, int y, unsigned int w, unsigned int h) {
    swim_native_window_set_area(window->native_window, x, y, w, h);
}

void swim_window_set_name(swim_window * window, char * name) {
    swim_native_window_set_name(window->native_window, name);
}

void swim_window_set_visible(swim_window * window, int visible) {
    swim_native_window_set_visible(window->native_window, visible);
}

void swim_window_set_fullscreen(swim_window * window, int fullscreen) {
    swim_native_window_set_fullscreen(window->native_window, fullscreen);
}

void swim_window_set_event_handlers(swim_window * window, swim_window_event_handlers * handlers) {
    window->event_handlers = handlers;
}

void swim_window_handle_events(swim_window * window) {
    swim_native_window_handle_events(window->native_window, window->event_handlers);
}
