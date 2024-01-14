#ifndef METRO_BENCHMARK_H
#define METRO_BENCHMARK_H

#include <chrono>
#include <thread>

#include "../Metro.h"
#include "../Filesys.h"

#include "Exceptions.h"

namespace metro {
    struct BenchmarkResult {
        Params params;
        double time;
    };

    typedef void (*CallbackFunc)(int, void *, void *);

    enum CallbackType {
        CALLBACK_STAGE,
        CALLBACK_STATION_COUNT,
        CALLBACKS_COUNT
    };

    class Benchmark {
        Metro *metro;
        Params max_params{};
        std::unordered_map<RouteSearchMethod, std::vector<BenchmarkResult>> results;
        CallbackFunc cb_fun_ptr[CALLBACKS_COUNT];
        void *cb_obj_ptr[CALLBACKS_COUNT];
        void *cb_emitter_ptr[CALLBACKS_COUNT];
        bool disabled_methods[ROUTE_SEARCH_METHOD_COUNT];

    public:
        explicit Benchmark(Params max_params = {
                .stations_count = 1000,
        });

        void run(bool *stop = nullptr);

        std::vector<BenchmarkResult> getResults(RouteSearchMethod method);

        void register_callback(CallbackFunc func, void *cb_obj, CallbackType type, void *cb_emitter);

        void disable_method(RouteSearchMethod method);

        metro::Params getMaxParams();
    };
}

#endif //METRO_BENCHMARK_H
