#ifndef METRO_PARAMS_H
#define METRO_PARAMS_H

namespace metro {
    struct Params {
        int branch_count;
        int stations_count;
        int branch_threshold;
        int min_distance;
        int intersect_threshold;
    };
}

#endif //METRO_PARAMS_H
