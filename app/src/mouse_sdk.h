#ifndef SC_MOUSE_SDK_H
#define SC_MOUSE_SDK_H

#include "common.h"

#include <stdbool.h>

#include "controller.h"
#include "touch_converter.h"
#include "trait/mouse_processor.h"

struct sc_mouse_sdk {
    struct sc_mouse_processor mouse_processor; // mouse processor trait

    struct sc_controller *controller;
    bool mouse_hover;
    
    // Touch converter for game compatibility
    struct sc_touch_converter touch_converter;
};

void
sc_mouse_sdk_init(struct sc_mouse_sdk *m, struct sc_controller *controller,
                  bool mouse_hover);

#endif
