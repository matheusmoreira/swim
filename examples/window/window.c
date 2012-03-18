#include <swim/window.h>

void window_closed(swim_window * window, void * context) {
    swim_window_stop_handling_events(window);
}

int main(int argc, char * argv[]) {
    swim_window * window = swim_window_new("Window Example", 50, 50, 50, 50);
    swim_window_callbacks(window)->window_closed = window_closed;
    swim_window_set_visible(window, 1);
    swim_window_handle_events(window);
    swim_window_destroy(window);
    return 0;
}
