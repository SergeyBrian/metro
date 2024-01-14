#include "AStarSearcher.h"

namespace metro {
    AStarSearcher::~AStarSearcher() = default;

    Vertex::Vertex(Station *s, int g, int h, Vertex *parent) {
        this->s = s;
        this->g = g;
        this->h = h;
        this->parent = parent;
    }

    bool AStarSearcher::AStarAlg(std::vector<Station *> *route) {
        std::vector<Vertex *> priority_queue;
        priority_queue.push_back(new Vertex(
                begin,
                0,
                heuristicCost(begin),
                nullptr
        ));
        vertexes.push_back(priority_queue.back());
        while (!priority_queue.empty()) {
            if (stop && *stop) return false;
            Vertex *current = priority_queue.back();
            if (visited.contains(current->s->id)) {
                priority_queue.pop_back();
                continue;
            }
            visited[current->s->id] = true;
            if (current->s == target) {
                while (current) {
                    route->insert(route->begin(), current->s);
                    current = current->parent;
                }
                return true;
            }
            for (const auto &station: current->s->connections) {
                if (visited.contains(station->id)) continue;
                priority_queue.push_back(new Vertex(
                        station,
                        current->g + 5 * getDistanceSquared(station->pos, current->s->pos),
                        heuristicCost(station),
                        current
                ));
                vertexes.push_back(priority_queue.back());
            }
            std::sort(priority_queue.begin(), priority_queue.end(), [](Vertex const *a, Vertex const *b) {
                return a->g + a->h > b->g + b->h;
            });
        }
        return false;
    }

    bool AStarSearcher::findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route,
                                          bool *stop) {
        begin = targetStations.front();
        target = targetStations.back();
        this->stop = stop;
        bool status = AStarAlg(route);
        for (auto vertex: vertexes) {
            delete vertex;
        }
        vertexes.clear();
        return status;
    }

    int AStarSearcher::heuristicCost(Station *a) {
        int res = getDistanceSquared(a->pos, target->pos);
        return res;
    }
}
