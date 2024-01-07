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
        while (!priority_queue.empty()) {
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
                        current->g + getDistanceSquared(station->pos, current->s->pos),
                        heuristicCost(station),
                        current
                ));
            }
            std::sort(priority_queue.begin(), priority_queue.end(), [](Vertex const *a, Vertex const *b) {
                printf("%s: %d > %s: %d\n", a->s->name.c_str(), a->g + a->h, b->s->name.c_str(), b->g + b->h);
                return a->g + a->h > b->g + b->h;
            });
        }
        return false;
    }

    bool AStarSearcher::findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route) {
        begin = targetStations.front();
        target = targetStations.back();
        bool status = AStarAlg(route);
        return status;
    }

    int AStarSearcher::heuristicCost(Station *a) {
        return 3 * getDistanceSquared(a->pos, target->pos);
    }
}
