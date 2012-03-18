#include <swim/stdlib.h>
#include <swim/window/event_handlers.h>

swim_window_event_handlers * swim_window_event_handlers_new() {
    return swim_malloc(sizeof(swim_window_event_handlers));
}

void swim_window_event_handlers_destroy(swim_window_event_handlers * handlers) {
    swim_free(handlers);
}
