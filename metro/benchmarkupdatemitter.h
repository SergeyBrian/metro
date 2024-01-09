#ifndef METRO_BENCHMARKUPDATEMITTER_H
#define METRO_BENCHMARKUPDATEMITTER_H

#include <QObject>

class BenchmarkUpdateEmitter : public QObject {
Q_OBJECT

public:
    BenchmarkUpdateEmitter();

signals:

    void publicCallback(int value, void *ptr);

};

#endif //METRO_BENCHMARKUPDATEMITTER_H
