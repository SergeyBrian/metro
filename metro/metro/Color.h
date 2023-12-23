#ifndef METRO_COLOR_H
#define METRO_COLOR_H

#include <string>
#include <random>

namespace metro {
    struct rgb {
        int r;
        int g;
        int b;
    };

    enum ColorID {
        CRIMSON,
        TEAL,
        CORAL,
        OLIVE,
        INDIGO,
        TURQUOISE,
        AMETHYST,
        SIENNA,
        GOLD,
        PLUM,
        SAPPHIRE,
        LIME,
        MAROON,
        AQUAMARINE,
        PEACH,
        LAVENDER,
        CHARCOAL,
        FUCHSIA,
        SAND,
        EMERALD,
        COLORS_COUNT
    };

    extern const std::string ColorName[COLORS_COUNT];
    extern const rgb ColorRGB[COLORS_COUNT];

    struct Color {
        ColorID id;
        rgb rgb;
        std::string name;
    };

    Color getColor(ColorID id);
}

#endif //METRO_COLOR_H
