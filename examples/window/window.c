#include <swim/window.h>

int main(int argc, char * argv[]) {
    swim_window * window = swim_window_new("Window Example", 50, 50, 50, 50);
    swim_window_set_visible(window, 1);
    swim_window_handle_events(window);
    swim_window_destroy(window);
    return 0;
}
