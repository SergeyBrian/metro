#include "benchmarkworker.h"

void BenchmarkWorker::run(bool *stop) {
    try {

        benchmark_obj->run(stop);
        emit workFinished();
    } catch (const metro::MethodDidntMatchTheReferenceException &e) {
        printf("[ERROR] Invalid route found\n");
    } catch (const std::runtime_error &e) {
        printf("[ERROR] %s\n", e.what());
    }
    this->thread()->quit();
}

BenchmarkWorker::BenchmarkWorker(metro::Benchmark *benchmark) : QObject() {
    this->benchmark_obj = benchmark;
}

void BenchmarkWorker::publicCallback(int value, void *ptr, void *emitter_ptr) {
    auto emitter = static_cast<BenchmarkUpdateEmitter *>(emitter_ptr);
    emit emitter->publicCallback(value, ptr);
}

