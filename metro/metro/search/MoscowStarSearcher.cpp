#include "MoscowStarSearcher.h"

metro::MoscowStarSearcher::~MoscowStarSearcher() = default;


bool metro::MoscowStarSearcher::findShortestRoute(const std::vector<Station *> &targetStations,
                                                  std::vector<Station *> *route, bool *stop) {
    begin = targetStations.front();
    target = targetStations.back();
    this->stop = stop;
    if (!prep_done) prepare();
    bool result = MSAlg(route);
    for (auto vertex: vertexes) {
        delete vertex;
    }
    vertexes.clear();
    return result;
}

bool metro::MoscowStarSearcher::MSAlg(std::vector<Station *> *route) {
    std::unordered_map<int, bool> processed_branches;
    std::vector<int> branches_queue;

    branches_queue.push_back(target->branch_id);

    useful_branches[target->branch_id] = true;

    if (branches_connections.empty() && begin->branch_id != target->branch_id) return false;

    while (!branches_queue.empty()) {
        int curr_branch = branches_queue.back();
        if (processed_branches.contains(curr_branch)) {
            branches_queue.pop_back();
            continue;
        }
        processed_branches[curr_branch] = true;
        if (!branches_connections.contains(curr_branch)) {
            if (begin->branch_id != target->branch_id) return false;
            break;
        }

        for (const auto &branch: branches_connections.at(curr_branch)) {
            if (processed_branches.contains(branch)) {
                continue;
            }
            branches_queue.push_back(branch);
            useful_branches[branch] = true;
        }
    }

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
        if (visited.contains(current->s->id) || !useful_branches.contains(current->s->branch_id)) {
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

void metro::MoscowStarSearcher::prepare() {
    prep_done = true;

    std::unordered_map<int, bool> processed_stations;
    std::vector<Station *> stations_queue;

    stations_queue.push_back(begin);
    while (!stations_queue.empty()) {
        Station *curr_station = stations_queue.back();
        if (processed_stations.contains(curr_station->id)) {
            stations_queue.pop_back();
            continue;
        }
        processed_stations[curr_station->id] = true;

        for (const auto &station: curr_station->connections) {
            stations_queue.push_back(station);
            if (curr_station->branch_id != station->branch_id) {
                branches_connections[curr_station->branch_id].push_back(station->branch_id);
                branches_connections[station->branch_id].push_back(curr_station->branch_id);
            }
        }
    }
}

int metro::MoscowStarSearcher::heuristicCost(Station *a) {
    return getDistanceSquared(a->pos, target->pos);
}
