#include "Filesys.h"

void metro::saveToFile(const std::string &filename, metro::Metro *metro) {
    auto file = std::ofstream(filename, std::ios::binary | std::ios::out);
    char version = METRO_LIB_VERSION;
    file.write(&version, sizeof(version));
    unsigned long station_count = metro->stations.size();
    file.write(reinterpret_cast<const char *>(&station_count), sizeof(station_count));
    for (const auto &station: metro->stations) {
        if (station.branch_id == -1) continue;
        auto fstation = FStation(&station);
        file.write(reinterpret_cast<const char *>(&fstation.id), sizeof(fstation.id));
        size_t name_size = fstation.name.length();
        file.write(reinterpret_cast<const char *>(&name_size), sizeof(name_size));
        file.write(reinterpret_cast<const char *>(fstation.name.data()), fstation.name.length());
        file.write(reinterpret_cast<const char *>(&fstation.branch_id), sizeof(fstation.branch_id));
        file.write(reinterpret_cast<const char *>(&fstation.pos), sizeof(fstation.pos));
        size_t connections_size = fstation.connections.size();
        file.write(reinterpret_cast<const char *>(&connections_size), sizeof(connections_size));
        file.write(reinterpret_cast<const char *>(fstation.connections.data()), sizeof(int) * connections_size);
    }
    unsigned long branch_count = metro->branches.size();
    file.write(reinterpret_cast<const char *>(&branch_count), sizeof(&branch_count));
    for (const auto &branch: metro->branches) {
        auto fbranch = FBranch(&branch.second);
        file.write(reinterpret_cast<const char *>(&fbranch), sizeof(fbranch));
    }
    file.write(reinterpret_cast<const char *>(&metro->center), sizeof(metro->center));
    file.close();
}

void metro::loadFromFile(const std::string &filename, metro::Metro *metro) {
    metro->stations.clear();
    std::unordered_map<int, FStation> fstations;
    std::unordered_map<int, FBranch> fbranches;
    auto file = std::ifstream(filename, std::ios::binary | std::ios::in);
    char version;
    file.read(&version, sizeof(version));
    if (version != 2) throw InvalidVersionException();
    unsigned long station_count;
    file.read(reinterpret_cast<char *>(&station_count), sizeof(station_count));
    for (int i = 0; i < station_count; i++) {
        FStation fstation = {};
        file.read(reinterpret_cast<char *>(&fstation.id), sizeof(fstation.id));
        size_t name_size = 0;
        file.read(reinterpret_cast<char *>(&name_size), sizeof(name_size));
        std::vector<char> name_buf(name_size);
        file.read(reinterpret_cast<char *>(name_buf.data()), name_size);
        fstation.name = std::string(name_buf.begin(), name_buf.end());
        file.read(reinterpret_cast<char *>(&fstation.branch_id), sizeof(fstation.branch_id));
        file.read(reinterpret_cast<char *>(&fstation.pos), sizeof(fstation.pos));
        size_t connections_size = 0;
        file.read(reinterpret_cast<char *>(&connections_size), sizeof(connections_size));
        fstation.connections = std::vector<int>(connections_size);
        file.read(reinterpret_cast<char *>(fstation.connections.data()), sizeof(int) * connections_size);
        fstations.insert({fstation.id, fstation});
    }
    unsigned long branch_count;
    file.read(reinterpret_cast<char *>(&branch_count), sizeof(branch_count));
    for (int i = 0; i < branch_count; i++) {
        FBranch fbranch = {};
        file.read(reinterpret_cast<char *>(&fbranch), sizeof(fbranch));
        fbranches.insert({fbranch.id, fbranch});
    }
    std::unordered_map<int, Station *> stations_map;
    for (const auto &[id, fstation]: fstations) {
        metro->stations.push_back({
                                          .id = fstation.id,
                                          .name = fstation.name,
                                          .pos = fstation.pos,
                                          .branch_id = fstation.branch_id,
                                          .connections = std::vector<Station *>(),
                                  });
    }
    for (int i = 0; i < metro->stations.size(); i++) {
        stations_map.insert({metro->stations[i].id, &metro->stations[i]});
    }

    for (const auto &[id, fbranch]: fbranches) {
        metro->branches[id] = {
                .id = fbranch.id,
                .stations_count = fbranch.stations_count,
                .color = fbranch.color,
                .begin = nullptr,
                .end = nullptr,
        };
    }
    for (int i = 0; i < metro->stations.size(); i++) {
        Station *station = &metro->stations[i];
        FStation fstation = fstations.at(station->id);
        for (int connection: fstation.connections) {
            station->connections.push_back(stations_map.at(connection));
        }
    }
    for (const auto &[id, fbranch]: fbranches) {
        Branch *branch = &metro->branches.at(id);
        branch->begin = stations_map.at(fbranch.begin_id);
        branch->end = stations_map.at(fbranch.end_id);
    }
    file.read(reinterpret_cast<char *>(&metro->center), sizeof(metro->center));
    file.close();
}

metro::FStation::FStation(const metro::Station *station) {
    id = station->id;
    name = station->name;
    pos = station->pos;
    branch_id = station->branch_id;
    for (const auto &connection: station->connections) {
        connections.push_back(connection->id);
    }
}

metro::FStation::FStation() = default;

metro::FBranch::FBranch() = default;

metro::FBranch::FBranch(const metro::Branch *branch) {
    id = branch->id;
    stations_count = branch->stations_count;
    color = branch->color;
    begin_id = branch->begin->id;
    end_id = branch->end->id;
}

