#include "StationList.h"

StationList::StationList() {
    // Red branch
    stationsList.insert(std::pair(DEVYATKINO, new Station("Девяткино", DEVYATKINO)));
    stationsList.insert(std::pair(GRAZHDANSKIY_PROSPEKT, new Station("Гражданский проспект", GRAZHDANSKIY_PROSPEKT)));
    stationsList.insert(std::pair(AKADEMICHESKAYA, new Station("Академическая", AKADEMICHESKAYA)));
    stationsList.insert(std::pair(POLITEKHNICHESKAYA, new Station("Политехническая", POLITEKHNICHESKAYA)));
    stationsList.insert(std::pair(PLOSHCHAD_MUZHESTVA, new Station("Площадь Мужества", PLOSHCHAD_MUZHESTVA)));
    stationsList.insert(std::pair(LESNAYA, new Station("Лесная", LESNAYA)));
    stationsList.insert(std::pair(VYBORGSKAYA, new Station("Выборгская", VYBORGSKAYA)));
    stationsList.insert(std::pair(PLOSHCHAD_LENINA, new Station("Площадь Ленина", PLOSHCHAD_LENINA)));
    stationsList.insert(std::pair(CHERNYSHEVSKAYA, new Station("Чернышевская", CHERNYSHEVSKAYA)));
    stationsList.insert(std::pair(PLOSHCHAD_VOSSTANIYA, new Station("Площадь Восстания", PLOSHCHAD_VOSSTANIYA)));
    stationsList.insert(std::pair(VLADIMIRSKAYA, new Station("Владимирская", VLADIMIRSKAYA)));
    stationsList.insert(std::pair(PUSHKINSKAYA, new Station("Пушкинская", PUSHKINSKAYA)));
    stationsList.insert(std::pair(TEKHNOLOGICHESKIY_INSTITUT_RED,
                                  new Station("Технологический институт", TEKHNOLOGICHESKIY_INSTITUT_RED)));
    stationsList.insert(std::pair(BALTIYSKAYA, new Station("Балтийская", BALTIYSKAYA)));
    stationsList.insert(std::pair(NARVSKAYA, new Station("Нарвская", NARVSKAYA)));
    stationsList.insert(std::pair(KIROVSKIY_ZAVOD, new Station("Кировский завод", KIROVSKIY_ZAVOD)));
    stationsList.insert(std::pair(AVTOVO, new Station("Автово", AVTOVO)));
    stationsList.insert(std::pair(LENINSKIY_PROSPEKT, new Station("Ленинский проспект", LENINSKIY_PROSPEKT)));
    stationsList.insert(std::pair(PROSPEKT_VETERANOV, new Station("Проспект Ветеранов", PROSPEKT_VETERANOV)));

    // Blue branch

    stationsList.insert(std::pair(PARNAS, new Station("Парнас", PARNAS)));
    stationsList.insert(
            std::pair(PROSPEKT_PROSVESHCHENIYA, new Station("Проспект Просвещения", PROSPEKT_PROSVESHCHENIYA)));
    stationsList.insert(std::pair(OZERKI, new Station("Озерки", OZERKI)));
    stationsList.insert(std::pair(UDELNAYA, new Station("Удельная", UDELNAYA)));
    stationsList.insert(std::pair(PIONERSKAYA, new Station("Пионерская", PIONERSKAYA)));
    stationsList.insert(std::pair(CHYORNAYA_RECHKA, new Station("Чёрная речка", CHYORNAYA_RECHKA)));
    stationsList.insert(std::pair(PETROGRADSKAYA, new Station("Петроградская", PETROGRADSKAYA)));
    stationsList.insert(std::pair(GORKOVSKAYA, new Station("Горьковская", GORKOVSKAYA)));
    stationsList.insert(std::pair(NEVSKIY_PROSPEKT, new Station("Невский проспект", NEVSKIY_PROSPEKT)));
    stationsList.insert(std::pair(SENNAYA_PLOSHCHAD, new Station("Сенная площадь", SENNAYA_PLOSHCHAD)));
    stationsList.insert(std::pair(TEKHNOLOGICHESKIY_INSTITUT_BLUE,
                                  new Station("Технологический институт", TEKHNOLOGICHESKIY_INSTITUT_BLUE)));
    stationsList.insert(std::pair(FRUNZENSKAYA, new Station("Фрунзенская", FRUNZENSKAYA)));
    stationsList.insert(std::pair(MOSKOVSKIE_VOROTA, new Station("Московские ворота", MOSKOVSKIE_VOROTA)));
    stationsList.insert(std::pair(ELEKTROSILA, new Station("Электросила", ELEKTROSILA)));
    stationsList.insert(std::pair(PARK_POBEDY, new Station("Парк Победы", PARK_POBEDY)));
    stationsList.insert(std::pair(MOSKOVSKAYA, new Station("Московская", MOSKOVSKAYA)));
    stationsList.insert(std::pair(ZVYOZDNAYA, new Station("Звёздная", ZVYOZDNAYA)));
    stationsList.insert(std::pair(KUPCHINO, new Station("Купчино", KUPCHINO)));

    // Green branch


    stationsList.insert(std::pair(BEGOVAYA, new Station("Беговая", BEGOVAYA)));
    stationsList.insert(std::pair(ZENIT, new Station("Зенит", ZENIT)));
    stationsList.insert(std::pair(PRIMORSKAYA, new Station("Приморская", PRIMORSKAYA)));
    stationsList.insert(std::pair(VASILEOSTROVSKAYA, new Station("Василеостровская", VASILEOSTROVSKAYA)));
    stationsList.insert(std::pair(GOSTINY_DVOR, new Station("Гостиный двор", GOSTINY_DVOR)));
    stationsList.insert(std::pair(MAYAKOVSKAYA, new Station("Маяковская", MAYAKOVSKAYA)));
    stationsList.insert(std::pair(PLOSHCHAD_ALEKSANDRA_NEVSKOGO_GREEN,
                                  new Station("Площадь Александра Невского", PLOSHCHAD_ALEKSANDRA_NEVSKOGO_GREEN)));
    stationsList.insert(std::pair(ELIZAROVSKAYA, new Station("Елизаровская", ELIZAROVSKAYA)));
    stationsList.insert(std::pair(LOMONOSOVSKAYA, new Station("Ломоносовская", LOMONOSOVSKAYA)));
    stationsList.insert(std::pair(PROLETARSKAYA, new Station("Пролетарская", PROLETARSKAYA)));
    stationsList.insert(std::pair(OBUHOVO, new Station("Обухово", OBUHOVO)));
    stationsList.insert(std::pair(RYBATSKOYE, new Station("Рыбацкое", RYBATSKOYE)));

    // Orange branch

    stationsList.insert(std::pair(SPASSKAYA, new Station("Спасская", SPASSKAYA)));
    stationsList.insert(std::pair(DOSTOEVSKAYA, new Station("Достоевская", DOSTOEVSKAYA)));
    stationsList.insert(std::pair(LIGOVSKIY_PROSPEKT, new Station("Лиговский проспект", LIGOVSKIY_PROSPEKT)));
    stationsList.insert(std::pair(PLOSHCHAD_ALEKSANDRA_NEVSKOGO_ORANGE,
                                  new Station("Площадь Александра Невского", PLOSHCHAD_ALEKSANDRA_NEVSKOGO_ORANGE)));
    stationsList.insert(std::pair(NOVOCHERKASSKAYA, new Station("Новочеркасская", NOVOCHERKASSKAYA)));
    stationsList.insert(std::pair(LADOZHSKAYA, new Station("Ладожская", LADOZHSKAYA)));
    stationsList.insert(std::pair(PROSPEKT_BOLSHEVIKOV, new Station("Проспект Большевиков", PROSPEKT_BOLSHEVIKOV)));
    stationsList.insert(std::pair(ULITSA_DYBENKO, new Station("Улица Дыбенко", ULITSA_DYBENKO)));

    // Purple branch

    stationsList.insert(
            std::pair(KOMENDANTSKIY_PROSPEKT, new Station("Комендантский проспект", KOMENDANTSKIY_PROSPEKT)));
    stationsList.insert(std::pair(STARAYA_DEREVNYA, new Station("Старая Деревня", STARAYA_DEREVNYA)));
    stationsList.insert(std::pair(KRESTOVSKIY_OSTROV, new Station("Крестовский остров", KRESTOVSKIY_OSTROV)));
    stationsList.insert(std::pair(CHKALOVSKAYA, new Station("Чкаловская", CHKALOVSKAYA)));
    stationsList.insert(std::pair(SPORTIVNAYA, new Station("Спортивная", SPORTIVNAYA)));
    stationsList.insert(std::pair(ADMIRALTEYSKAYA, new Station("Адмиралтейская", ADMIRALTEYSKAYA)));
    stationsList.insert(std::pair(SADOVAYA, new Station("Садовая", SADOVAYA)));
    stationsList.insert(std::pair(ZVENIGORODSKAYA, new Station("Звенигородская", ZVENIGORODSKAYA)));
    stationsList.insert(std::pair(OBVODNYY_KANAL, new Station("Обводный канал", OBVODNYY_KANAL)));
    stationsList.insert(std::pair(VOLKOVSKAYA, new Station("Волковская", VOLKOVSKAYA)));
    stationsList.insert(std::pair(BUKHARESTSKAYA, new Station("Бухарестская", BUKHARESTSKAYA)));
    stationsList.insert(std::pair(MEZHDUNARODNAYA, new Station("Международная", MEZHDUNARODNAYA)));
    stationsList.insert(std::pair(PROSPECT_SLAVY, new Station("Проспект славы", PROSPECT_SLAVY)));
    stationsList.insert(std::pair(DUNAYSKAYA, new Station("Дунайская", DUNAYSKAYA)));
    stationsList.insert(std::pair(SHUSHARY, new Station("Шушары", SHUSHARY)));


    for (int i = BRANCH_RED; i < RED_END - 1; i++) {
        this->getStation((station_id) i)->Connect(this->getStation((station_id) (i + 1)));
    }
    for (int i = BRANCH_BLUE; i < BLUE_END - 1; i++) {
        this->getStation((station_id) i)->Connect(this->getStation((station_id) (i + 1)));
    }
    for (int i = BRANCH_GREEN; i < GREEN_END - 1; i++) {
        this->getStation((station_id) i)->Connect(this->getStation((station_id) (i + 1)));
    }
    for (int i = BRANCH_ORANGE; i < ORANGE_END - 1; i++) {
        this->getStation((station_id) i)->Connect(this->getStation((station_id) (i + 1)));
    }
    for (int i = BRANCH_PURPLE; i < PURPLE_END - 1; i++) {
        this->getStation((station_id) i)->Connect(this->getStation((station_id) (i + 1)));
    }


    getStation(PLOSHCHAD_VOSSTANIYA)->Connect(getStation(MAYAKOVSKAYA));
    getStation(DOSTOEVSKAYA)->Connect(getStation(VLADIMIRSKAYA));
    getStation(ZVENIGORODSKAYA)->Connect(getStation(PUSHKINSKAYA));
    getStation(PLOSHCHAD_ALEKSANDRA_NEVSKOGO_GREEN)->Connect(getStation(PLOSHCHAD_ALEKSANDRA_NEVSKOGO_ORANGE));
    getStation(TEKHNOLOGICHESKIY_INSTITUT_RED)->Connect(getStation(TEKHNOLOGICHESKIY_INSTITUT_BLUE));
    getStation(NEVSKIY_PROSPEKT)->Connect(getStation(GOSTINY_DVOR));
    getStation(SADOVAYA)->Connect(getStation(SENNAYA_PLOSHCHAD));
    getStation(SENNAYA_PLOSHCHAD)->Connect(getStation(SPASSKAYA));
    getStation(SPASSKAYA)->Connect(getStation(SADOVAYA));
}

Station *StationList::getStation(station_id id) {
    return stationsList.at(id);
}
