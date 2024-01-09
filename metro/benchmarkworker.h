#ifndef METRO_BENCHMARKWORKER_H
#define METRO_BENCHMARKWORKER_H

#include <QObject>
#include <QThread>

#include "metro/tests/Tests.h"
#include "benchmarkupdatemitter.h"

class BenchmarkWorker : public QObject {
Q_OBJECT

    metro::Benchmark *benchmark_obj;
public:
    BenchmarkWorker(metro::Benchmark *benchmark);

    static void publicCallback(int value, void *ptr, void *dialog_ptr);

public slots:

    void run(bool *stop);

signals:

    void workFinished();

};

#endif //METRO_BENCHMARKWORKER_H
