#include "Station.h"

namespace metro {
    void bindStations(Station *a, Station *b) {
        if (std::find(a->connections.begin(), a->connections.end(), b) == a->connections.end()) {
            a->connections.push_back(b);
        }
        if (std::find(b->connections.begin(), b->connections.end(), a) == b->connections.end()) {
            b->connections.push_back(a);
        }
/*      Без этого кода вроде лучше генерация, но чекни с ним тоже на всякий случай
 *      (здесь все станции-пересадки должны вставать в одну координату, но чет не бим-бим бам-бам)
        if (a->branch_id != b->branch_id) {
            for (auto connection: b->connections) {
                if (connection->branch_id == b->branch_id) continue;
                connection->pos = a->pos;
            }
        }
*/
    }
}
