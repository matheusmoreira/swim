#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <swim/stdlib.h>
#include <swim/native/window.h>
#include <swim/keyboard_key.h>
#include <swim/mouse_button.h>

/**
 * X11 window data.
 */
typedef struct {
    Display * display; /** Pointer to the display connection. */
    int screen; /** Window's screen. */
    Window window; /** The window. */
    Atom close_event_atom; /** Atom that identifies the window close event. */
} swim_native_window_x11;

/* Helper function prototypes */

static inline XWindowAttributes
swim_native_window_x11_get_attributes(swim_native_window_x11 * x11);

static Bool is_from(Display * display, XEvent * event, XPointer arg);

static swim_keyboard_key convert_to_keyboard_key(XKeyEvent key);

/* Native window interface implementation */

void * swim_native_window_new(char * name, int x, int y, unsigned int w, unsigned int h) {
    swim_native_window_x11 * x11 = NULL;
    unsigned long white = 0L;

    if ((x11 = swim_malloc(sizeof(swim_native_window_x11))) == NULL) {
        /* Memory unavailable */
    }

    if ((x11->display = XOpenDisplay(NULL)) == NULL) {
        /* Connection to the Display server could not be established */
    }

    x11->screen = XDefaultScreen(x11->display);
    white = XWhitePixel(x11->display, x11->screen);

    x11->window = XCreateSimpleWindow(x11->display,
                                      RootWindow(x11->display,
                                                 x11->screen),
                                      x, y, w, h, 0, white, white);

    x11->close_event_atom = XInternAtom(x11->display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(x11->display, x11->window, &x11->close_event_atom, 1);

    return x11;
}

void swim_native_window_destroy(void * native_window) {
    swim_native_window_x11 * x11 = native_window;

    if (x11 != NULL) {
        XDestroyWindow(x11->display, x11->window);
        XCloseDisplay(x11->display);
        swim_free(x11);
    }
}

int swim_native_window_x(void * native_window) {
    return swim_native_window_x11_get_attributes(native_window).x;
}

int swim_native_window_y(void * native_window) {
    return swim_native_window_x11_get_attributes(native_window).y;
}

unsigned int swim_native_window_width(void * native_window) {
    return swim_native_window_x11_get_attributes(native_window).width;
}

unsigned int swim_native_window_height(void * native_window) {
    return swim_native_window_x11_get_attributes(native_window).height;
}

char * swim_native_window_name(void * native_window) {
    swim_native_window_x11 * x11 = native_window;
    char * name = NULL;
    char * name_dup = NULL;

    XFetchName(x11->display, x11->window, &name);

    if (name != NULL) {
        name_dup = swim_strdup(name);
        XFree(name);
    } else {
        name_dup = swim_strdup("");
    }

    return name_dup;
}

int swim_native_window_visible(void * native_window) {
    return swim_native_window_x11_get_attributes(native_window).map_state != IsUnmapped;
}

void swim_native_window_set_x(void * native_window, int x) {
    swim_native_window_set_position(native_window, x, swim_native_window_y(native_window));
}

void swim_native_window_set_y(void * native_window, int y) {
    swim_native_window_set_position(native_window, swim_native_window_x(native_window), y);
}

void swim_native_window_set_width(void * native_window, unsigned int w) {
    swim_native_window_set_size(native_window, w, swim_native_window_height(native_window));
}

void swim_native_window_set_height(void * native_window, unsigned int h) {
    swim_native_window_set_size(native_window, swim_native_window_width(native_window), h);
}

void swim_native_window_set_position(void * native_window, int x, int y) {
    swim_native_window_x11 * x11 = native_window;

    XMoveWindow(x11->display, x11->window, x, y);
    XFlush(x11->display);
}

void swim_native_window_set_size(void * native_window, unsigned int w, unsigned int h) {
    swim_native_window_x11 * x11 = native_window;

    XResizeWindow(x11->display, x11->window, w, h);
    XFlush(x11->display);
}

void swim_native_window_set_area(void * native_window,
                                 int x, int y, unsigned int w, unsigned int h) {
    swim_native_window_x11 * x11 = native_window;

    XMoveResizeWindow(x11->display, x11->window, x, y, w, h);
    XFlush(x11->display);
}

void swim_native_window_set_name(void * native_window, char * name) {
    swim_native_window_x11 * x11 = native_window;

    XStoreName(x11->display, x11->window, name);
    XFlush(x11->display);
}

void swim_native_window_set_visible(void * native_window, int visible) {
    swim_native_window_x11 * x11 = native_window;

    if (visible) {
        XMapWindow(x11->display, x11->window);
    } else {
        XUnmapWindow(x11->display, x11->window);
    }
    XFlush(x11->display);
}

void swim_native_window_set_fullscreen(void * native_window, int fullscreen) {}

void swim_native_window_handle_events(void * native_window,
                                      swim_window_event_handlers * handlers) {
    swim_native_window_x11 * x11 = native_window;
    XEvent event;

    if (handlers == NULL) { return; }

    while (XCheckIfEvent(x11->display, &event, is_from, (XPointer) x11->window)) {
        switch (event.type) {
            /* Window is about to be destroyed by X */
            case DestroyNotify: {
                break;
            }
            /* Window was closed by the user */
            /*case ClientMessage: {
                if (xevent.xclient.format == 32 &&
                    xevent.xclient.data.l[0] == (long) event->close_event_atom) {
                }
                break;
            }*/
            /* Key was pressed */
            case KeyPress: {
                if (handlers->key_pressed != NULL) {
                    handlers->key_pressed(convert_to_keyboard_key(event.xkey),
                                          handlers->context);
                }
                break;
            }
            /* Key was released */
            case KeyRelease: {
                if(handlers->key_released != NULL) {
                    handlers->key_released(convert_to_keyboard_key(event.xkey),
                                           handlers->context);
                }
                break;
            }
        }
    }
}

/* Helper function implementations */

static inline XWindowAttributes
swim_native_window_x11_get_attributes(swim_native_window_x11 * x11) {
    XWindowAttributes attributes;

    XGetWindowAttributes(x11->display, x11->window, &attributes);
    return attributes;
}

static Bool is_from(Display * display, XEvent * event, XPointer arg) {
    return event->xany.window == (Window) arg;
}

static swim_keyboard_key convert_to_keyboard_key(XKeyEvent event) {
    static const int buffer_size = 32;
    char buffer[buffer_size];
    KeySym key, lower, upper;

    XLookupString(&event, buffer, buffer_size, &key, 0);
    XConvertCase(key, &lower, &upper);

    switch (upper) {
        case XK_A: { return swim_keyboard_key_a;       break; }
        case XK_B: { return swim_keyboard_key_b;       break; }
        case XK_C: { return swim_keyboard_key_c;       break; }
        case XK_D: { return swim_keyboard_key_d;       break; }
        case XK_E: { return swim_keyboard_key_e;       break; }
        case XK_F: { return swim_keyboard_key_f;       break; }
        case XK_G: { return swim_keyboard_key_g;       break; }
        case XK_H: { return swim_keyboard_key_h;       break; }
        case XK_I: { return swim_keyboard_key_i;       break; }
        case XK_J: { return swim_keyboard_key_j;       break; }
        case XK_K: { return swim_keyboard_key_k;       break; }
        case XK_L: { return swim_keyboard_key_l;       break; }
        case XK_M: { return swim_keyboard_key_m;       break; }
        case XK_N: { return swim_keyboard_key_n;       break; }
        case XK_O: { return swim_keyboard_key_o;       break; }
        case XK_P: { return swim_keyboard_key_p;       break; }
        case XK_Q: { return swim_keyboard_key_q;       break; }
        case XK_R: { return swim_keyboard_key_r;       break; }
        case XK_S: { return swim_keyboard_key_s;       break; }
        case XK_T: { return swim_keyboard_key_t;       break; }
        case XK_U: { return swim_keyboard_key_u;       break; }
        case XK_V: { return swim_keyboard_key_v;       break; }
        case XK_W: { return swim_keyboard_key_w;       break; }
        case XK_X: { return swim_keyboard_key_x;       break; }
        case XK_Y: { return swim_keyboard_key_y;       break; }
        case XK_Z: { return swim_keyboard_key_z;       break; }
        default:   { return swim_keyboard_key_unknown; break; }
    }

    return swim_keyboard_key_unknown;
}
