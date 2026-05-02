#ifndef SC_TOUCH_CONVERTER_H
#define SC_TOUCH_CONVERTER_H

#include <stdbool.h>
#include <stdint.h>

#include "android/input.h"
#include "coords.h"
#include "input_events.h"

/**
 * Touch converter module for converting mouse motion events to touch gestures
 * Useful for games that rely on touch input rather than raw mouse events
 */

struct sc_touch_converter {
    bool enabled;
    bool mouse_down;
    struct sc_point last_position;
    uint64_t pointer_id;
    int sensitivity;
};

/**
 * Initialize the touch converter
 */
void
sc_touch_converter_init(struct sc_touch_converter *converter);

/**
 * Enable or disable touch conversion
 */
void
sc_touch_converter_set_enabled(struct sc_touch_converter *converter,
                               bool enabled);

/**
 * Convert mouse motion event to touch gesture
 * Returns true if a touch event should be sent
 */
bool
sc_touch_converter_process_mouse_motion(struct sc_touch_converter *converter,
                                        const struct sc_mouse_motion_event *event,
                                        struct sc_point *out_position);

/**
 * Handle mouse button press (start of touch gesture)
 */
void
sc_touch_converter_on_mouse_down(struct sc_touch_converter *converter,
                                 const struct sc_point *position);

/**
 * Handle mouse button release (end of touch gesture)
 */
void
sc_touch_converter_on_mouse_up(struct sc_touch_converter *converter);

/**
 * Reset the converter state
 */
void
sc_touch_converter_reset(struct sc_touch_converter *converter);

#endif
