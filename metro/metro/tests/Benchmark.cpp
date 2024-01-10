#include "Benchmark.h"

metro::Benchmark::Benchmark(metro::Params max_params) {
    this->metro = new Metro();
    this->max_params = max_params;
}

std::vector<metro::BenchmarkResult> metro::Benchmark::getResults(RouteSearchMethod method) {
    return results.at(method);
}

void
metro::Benchmark::register_callback(metro::CallbackFunc func, void *cb_obj, metro::CallbackType type, void *emitter) {
    cb_fun_ptr[type] = func;
    cb_obj_ptr[type] = cb_obj;
    cb_emitter_ptr[type] = emitter;
}

void metro::Benchmark::run(bool *stop) {
    Params params{
            .branch_count = 1,
            .stations_count = 2,
            .branch_threshold = 3,
            .min_distance = 3,
            .intersect_threshold = 5,
    };
    while (params.stations_count < max_params.stations_count) {
        if (stop && *stop) return;
        std::unordered_map<RouteSearchMethod, std::vector<Station *>> routes;
        metro->generate(params);

        for (int i = 0; i < ROUTE_SEARCH_METHOD_COUNT; i++) {
            auto method = static_cast<RouteSearchMethod>(i);
            if (disabled_methods[method]) continue;
            routes[method] = {};
            ISearcher *searcher = getSearcher(method);
            std::chrono::milliseconds time;
            int stations_count_cb_param = 0;
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < metro->stations.size(); j++) {
                if (stop && *stop) return;
                for (int k = 0; k < metro->stations.size(); k++) {
                    if (stop && *stop) return;
                    if (j == k) continue;
                    searcher->findShortestRoute({&metro->stations.at(j), &metro->stations.at(k)}, &routes.at(method),
                                                stop);
                }
                stations_count_cb_param++;
                double stations_count_cb_prcnt = (double) stations_count_cb_param / (double) metro->stations.size();
                stations_count_cb_prcnt *= 100;
                cb_fun_ptr[CALLBACK_STATION_COUNT]((int) stations_count_cb_prcnt,
                                                   cb_obj_ptr[CALLBACK_STATION_COUNT],
                                                   cb_emitter_ptr[CALLBACK_STATION_COUNT]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            results[method].push_back({
                                              params,
                                              time
                                      });
            delete searcher;
        }

        params.stations_count += 10;
        params.branch_count = params.stations_count / 3;
        params.branch_threshold = (params.stations_count > 500) ? 1 : 3;
        params.min_distance = (params.stations_count > 200) ? 0 : 3;
        params.intersect_threshold = (params.stations_count > 500) ? 3 : 5;
        printf("%d\n", (int) (((double) params.stations_count / (double) max_params.stations_count) * 100));
        cb_fun_ptr[CALLBACK_STAGE]((int) (((double) params.stations_count / (double) max_params.stations_count) * 100),
                                   cb_obj_ptr[CALLBACK_STAGE], cb_emitter_ptr[CALLBACK_STAGE]);
    }
    cb_fun_ptr[CALLBACK_STAGE](100, cb_obj_ptr[CALLBACK_STAGE], cb_emitter_ptr[CALLBACK_STAGE]);

    printf("=== BENCHMARK RESULTS ===\n");
    for (int i = 0; i < metro::ROUTE_SEARCH_METHOD_COUNT; i++) {
        auto method = static_cast<metro::RouteSearchMethod>(i);
        if (disabled_methods[method]) continue;
        std::vector<metro::BenchmarkResult> rr = this->getResults(method);
        printf("%s\n", metro::search_method_name[i].c_str());
        for (const auto &result: rr) {
            printf("\tStations: %d time: %lld\n", result.params.stations_count, result.time.count());
        }
    }
}


void metro::Benchmark::disable_method(metro::RouteSearchMethod method) {
    disabled_methods[method] = true;
}

metro::Params metro::Benchmark::getMaxParams() {
    return max_params;
}

