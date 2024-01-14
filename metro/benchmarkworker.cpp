#include "benchmarkworker.h"

void BenchmarkWorker::run(bool *stop) {
    benchmark_obj->run(stop);
    emit workFinished();
    this->thread()->quit();
}

BenchmarkWorker::BenchmarkWorker(metro::Benchmark *benchmark) : QObject() {
    this->benchmark_obj = benchmark;
}

void BenchmarkWorker::publicCallback(int value, void *ptr, void *emitter_ptr) {
    auto emitter = static_cast<BenchmarkUpdateEmitter *>(emitter_ptr);
    emit emitter->publicCallback(value, ptr);
}

