#ifndef METRO_MOSCOWSTARSEARCHER_H
#define METRO_MOSCOWSTARSEARCHER_H


#include "AStarSearcher.h"

namespace metro {
    struct BranchVertex {
        Branch *branch;
        std::vector<BranchVertex *> connections;
    };

    class MoscowStarSearcher : public ISearcher {
        Station *begin;
        Station *target;

        bool MSAlg(std::vector<Station *> *route);

        bool prep_done;

        void prepare();

        std::unordered_map<int, std::unordered_map<int, bool>> branch_connections_matrix;
        std::unordered_map<int, std::vector<int>> branches_connections;
        std::unordered_map<int, bool> useful_branches;

        int heuristicCost(Station *a);

        std::unordered_map<int, bool> visited;
        std::vector<Vertex *> vertexes;

    public:
        ~MoscowStarSearcher() override;

        bool findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route,
                               bool *stop) override;
    };
}

#endif //METRO_MOSCOWSTARSEARCHER_H
