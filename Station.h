#ifndef METRO_STATION_H
#define METRO_STATION_H


#include <string>
#include <vector>

enum station_id : int;

class Station {
public:
    Station(std::string name, station_id id);

    void Connect(Station *station);

    station_id id;
    std::string name;
    std::vector<station_id> connections;
};


enum branch_id {
    BRANCH_RED = 100,
    BRANCH_BLUE = 1000,
    BRANCH_GREEN = 10000,
    BRANCH_ORANGE = 100000,
    BRANCH_PURPLE = 1000000
};

enum station_id : int {
    DEVYATKINO = BRANCH_RED,
    GRAZHDANSKIY_PROSPEKT,
    AKADEMICHESKAYA,
    POLITEKHNICHESKAYA,
    PLOSHCHAD_MUZHESTVA,
    LESNAYA,
    VYBORGSKAYA,
    PLOSHCHAD_LENINA,
    CHERNYSHEVSKAYA,
    PLOSHCHAD_VOSSTANIYA,
    VLADIMIRSKAYA,
    PUSHKINSKAYA,
    TEKHNOLOGICHESKIY_INSTITUT_RED,
    BALTIYSKAYA,
    NARVSKAYA,
    KIROVSKIY_ZAVOD,
    AVTOVO,
    LENINSKIY_PROSPEKT,
    PROSPEKT_VETERANOV,
    RED_END,
    PARNAS = BRANCH_BLUE,
    PROSPEKT_PROSVESHCHENIYA,
    OZERKI,
    UDELNAYA,
    PIONERSKAYA,
    CHYORNAYA_RECHKA,
    PETROGRADSKAYA,
    GORKOVSKAYA,
    NEVSKIY_PROSPEKT,
    SENNAYA_PLOSHCHAD,
    TEKHNOLOGICHESKIY_INSTITUT_BLUE,
    FRUNZENSKAYA,
    MOSKOVSKIE_VOROTA,
    ELEKTROSILA,
    PARK_POBEDY,
    MOSKOVSKAYA,
    ZVYOZDNAYA,
    KUPCHINO,
    BLUE_END,
    BEGOVAYA = BRANCH_GREEN,
    ZENIT,
    PRIMORSKAYA,
    VASILEOSTROVSKAYA,
    GOSTINY_DVOR,
    MAYAKOVSKAYA,
    PLOSHCHAD_ALEKSANDRA_NEVSKOGO_GREEN,
    ELIZAROVSKAYA,
    LOMONOSOVSKAYA,
    PROLETARSKAYA,
    OBUHOVO,
    RYBATSKOYE,
    GREEN_END,
    SPASSKAYA = BRANCH_ORANGE,
    DOSTOEVSKAYA,
    LIGOVSKIY_PROSPEKT,
    PLOSHCHAD_ALEKSANDRA_NEVSKOGO_ORANGE,
    NOVOCHERKASSKAYA,
    LADOZHSKAYA,
    PROSPEKT_BOLSHEVIKOV,
    ULITSA_DYBENKO,
    ORANGE_END,
    KOMENDANTSKIY_PROSPEKT = BRANCH_PURPLE,
    STARAYA_DEREVNYA,
    KRESTOVSKIY_OSTROV,
    CHKALOVSKAYA,
    SPORTIVNAYA,
    ADMIRALTEYSKAYA,
    SADOVAYA,
    ZVENIGORODSKAYA,
    OBVODNYY_KANAL,
    VOLKOVSKAYA,
    BUKHARESTSKAYA,
    MEZHDUNARODNAYA,
    PROSPECT_SLAVY,
    DUNAYSKAYA,
    SHUSHARY,
    PURPLE_END
};

#endif //METRO_STATION_H