#include "Color.h"

namespace metro {
    const std::string ColorName[] = {
            "crimson",
            "teal",
            "coral",
            "olive",
            "indigo",
            "turquoise",
            "amethyst",
            "sienna",
            "gold",
            "plum",
            "sapphire",
            "lime",
            "maroon",
            "aquamarine",
            "peach",
            "lavender",
            "charcoal",
            "fuchsia",
            "sand",
            "emerald",
    };

    const rgb ColorRGB[COLORS_COUNT] = {
            {220, 20,  60},
            {0,   128, 128},
            {255, 127, 80},
            {128, 128, 0},
            {75,  0,   130},
            {64,  224, 208},
            {153, 102, 204},
            {160, 82,  45},
            {255, 215, 0},
            {221, 160, 221},
            {15,  82,  186},
            {0,   255, 0},
            {128, 0,   0},
            {127, 255, 212},
            {255, 229, 180},
            {230, 230, 250},
            {250, 250, 250},
            {255, 0,   255},
            {194, 178, 128},
            {80,  200, 120},
    };

    Color getColor(ColorID id) {
        id = static_cast<ColorID>(id % COLORS_COUNT);
        return Color{
                .id = id,
                .rgb = ColorRGB[id],
                .name = ColorName[id],
        };
    }
}
