#include "Filesys_v2.h"

#define METRO_FILETYPE_MARKER_STR "METRO_SCHEME"

void metro::legacy::filesys_v2::loadFromFile(const std::string &filename, metro::Metro *metro) {
    metro->stations.clear();
    std::unordered_map<int, FStation> fstations;
    std::unordered_map<int, FBranch> fbranches;
    auto file = std::ifstream(filename, std::ios::binary | std::ios::in);
    if (file.fail()) throw FileNotFoundException();
    int version;
    int filetype_version;
    char filetype_marker[sizeof(METRO_FILETYPE_MARKER_STR)];
    file.read(filetype_marker, sizeof(METRO_FILETYPE_MARKER_STR));
    if (std::strcmp(filetype_marker, METRO_FILETYPE_MARKER_STR)) throw NotMetroFileException();
    file.read(reinterpret_cast<char *>(&version), sizeof(version));
    file.read(reinterpret_cast<char *>(&filetype_version), sizeof(filetype_version));
    if (version != 2) throw InvalidVersionException(version);
    if (filetype_version != 2) throw InvalidVersionException(filetype_version);
    unsigned long station_count;
    file.read(reinterpret_cast<char *>(&station_count), sizeof(station_count));
    if (station_count < METRO_MIN_STATIONS_COUNT || station_count > METRO_MAX_STATIONS_COUNT)
        throw DamagedFileException();
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
    if (branch_count < METRO_MIN_BRANCHES_COUNT || branch_count > METRO_MAX_BRANCHES_COUNT(station_count))
        throw DamagedFileException();
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


metro::legacy::filesys_v2::FStation::FStation(const metro::Station *station) {
    id = station->id;
    name = station->name;
    pos = station->pos;
    branch_id = station->branch_id;
    for (const auto &connection: station->connections) {
        connections.push_back(connection->id);
    }
}

metro::legacy::filesys_v2::FStation::FStation() = default;

metro::legacy::filesys_v2::FBranch::FBranch() = default;

metro::legacy::filesys_v2::FBranch::FBranch(const metro::Branch *branch) {
    id = branch->id;
    stations_count = branch->stations_count;
    color = branch->color;
    begin_id = branch->begin->id;
    end_id = branch->end->id;
}

#undef METRO_FILETYPE_MARKER_STR
