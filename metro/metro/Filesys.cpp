#include "Filesys.h"

#define METRO_FILETYPE_MARKER_STR "METRO_SCHEME"
#define METRO_FILETYPE_VERSION 3

void metro::saveToFile(const std::string &filename, metro::Metro *metro) {
    auto file = std::ofstream(filename, std::ios::binary | std::ios::out);
    int version = METRO_LIB_VERSION;
    int filetype_version = METRO_FILETYPE_VERSION;
    const char filetype_marker[] = METRO_FILETYPE_MARKER_STR;
    file.write(filetype_marker, sizeof(filetype_marker));
    file.write(reinterpret_cast<const char *>(&version), sizeof(version));
    file.write(reinterpret_cast<const char *>(&filetype_version), sizeof(filetype_version));
    unsigned long station_count = metro->stations.size();
    file.write(reinterpret_cast<const char *>(&station_count), sizeof(station_count));
    for (const auto &station: metro->stations) {
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
        file.write(reinterpret_cast<const char *>(&fbranch.id), sizeof(fbranch.id));
        file.write(reinterpret_cast<const char *>(&fbranch.begin_id), sizeof(fbranch.begin_id));
        file.write(reinterpret_cast<const char *>(&fbranch.end_id), sizeof(fbranch.end_id));
        file.write(reinterpret_cast<const char *>(&fbranch.color.id), sizeof(fbranch.color.id));
        size_t color_name_size = fbranch.color.name.length();
        file.write(reinterpret_cast<const char *>(&color_name_size), sizeof(color_name_size));
        file.write(reinterpret_cast<const char *>(fbranch.color.name.data()), color_name_size);
        file.write(reinterpret_cast<const char *>(&fbranch.color.rgb.r), sizeof(fbranch.color.rgb.r));
        file.write(reinterpret_cast<const char *>(&fbranch.color.rgb.g), sizeof(fbranch.color.rgb.g));
        file.write(reinterpret_cast<const char *>(&fbranch.color.rgb.b), sizeof(fbranch.color.rgb.b));
        file.write(reinterpret_cast<const char *>(&fbranch.stations_count), sizeof(fbranch.stations_count));
    }
    file.write(reinterpret_cast<const char *>(&metro->center), sizeof(metro->center));
    file.close();
}

void metro::loadFromFile(const std::string &filename, metro::Metro *metro) {
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
    if (version != METRO_LIB_VERSION) throw InvalidVersionException(version);
    if (filetype_version != METRO_FILETYPE_VERSION) throw InvalidVersionException(filetype_version);
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
        file.read(reinterpret_cast<char *>(&fbranch.id), sizeof(fbranch.id));
        file.read(reinterpret_cast<char *>(&fbranch.begin_id), sizeof(fbranch.begin_id));
        file.read(reinterpret_cast<char *>(&fbranch.end_id), sizeof(fbranch.end_id));
        file.read(reinterpret_cast<char *>(&fbranch.color.id), sizeof(fbranch.color.id));
        size_t color_name_size;
        file.read(reinterpret_cast<char *>(&color_name_size), sizeof(color_name_size));
        std::vector<char> color_name_buf(color_name_size);
        file.read(reinterpret_cast<char *>(color_name_buf.data()), color_name_size);
        fbranch.color.name = std::string(color_name_buf.begin(), color_name_buf.end());
        file.read(reinterpret_cast<char *>(&fbranch.color.rgb.r), sizeof(fbranch.color.rgb.r));
        file.read(reinterpret_cast<char *>(&fbranch.color.rgb.g), sizeof(fbranch.color.rgb.g));
        file.read(reinterpret_cast<char *>(&fbranch.color.rgb.b), sizeof(fbranch.color.rgb.b));
        file.read(reinterpret_cast<char *>(&fbranch.stations_count), sizeof(fbranch.stations_count));
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

