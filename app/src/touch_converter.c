#include "touch_converter.h"

#include <assert.h>
#include <math.h>

#include "util/log.h"

/**
 * Minimum distance to consider as a valid drag motion (in pixels)
 */
#define TOUCH_CONVERTER_MIN_MOTION_PIXELS 2

void
sc_touch_converter_init(struct sc_touch_converter *converter) {
    assert(converter);
    
    converter->enabled = true;
    converter->mouse_down = false;
    converter->last_position = (struct sc_point) {0, 0};
    converter->pointer_id = 1;
    converter->sensitivity = 100; // 100% = normal sensitivity
}

void
sc_touch_converter_set_enabled(struct sc_touch_converter *converter,
                               bool enabled) {
    assert(converter);
    converter->enabled = enabled;
    
    if (!enabled) {
        sc_touch_converter_reset(converter);
    }
}

static float
calculate_distance(struct sc_point p1, struct sc_point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrtf((float)(dx * dx + dy * dy));
}

bool
sc_touch_converter_process_mouse_motion(struct sc_touch_converter *converter,
                                        const struct sc_mouse_motion_event *event,
                                        struct sc_point *out_position) {
    assert(converter);
    assert(event);
    assert(out_position);
    
    if (!converter->enabled || !converter->mouse_down) {
        return false;
    }
    
    struct sc_point current_position = event->position.point;
    
    // Calculate distance moved
    float distance = calculate_distance(converter->last_position, current_position);
    
    // Only send motion event if movement is significant enough
    if (distance < TOUCH_CONVERTER_MIN_MOTION_PIXELS) {
        return false;
    }
    
    converter->last_position = current_position;
    *out_position = current_position;
    
    return true;
}

void
sc_touch_converter_on_mouse_down(struct sc_touch_converter *converter,
                                 const struct sc_point *position) {
    assert(converter);
    assert(position);
    
    if (!converter->enabled) {
        return;
    }
    
    converter->mouse_down = true;
    converter->last_position = *position;
    
    LOGD("Touch converter: mouse down at (%d, %d)", position->x, position->y);
}

void
sc_touch_converter_on_mouse_up(struct sc_touch_converter *converter) {
    assert(converter);
    
    if (!converter->enabled) {
        return;
    }
    
    converter->mouse_down = false;
    converter->last_position = (struct sc_point) {0, 0};
    
    LOGD("Touch converter: mouse up");
}

void
sc_touch_converter_reset(struct sc_touch_converter *converter) {
    assert(converter);
    
    converter->mouse_down = false;
    converter->last_position = (struct sc_point) {0, 0};
}
