# Pollution

Utwórz nowy modul o nazwie _pollution_, który bedzie zbieral i przetwarzal dane ze stacji mierzacych jakosc powietrza. Modul powinien przechowywac:



* informacje o stacjach pomiarowych,

  * wspólrzedne geograficzne,

  * nazwy stacji pomiarowych,

* zmierzone wartosci pomiarów, np stezenia pylów PM10, PM2.5 czy wartosci temperatury (wraz z data i godzina pomiaru).



Nie powinno byc mozliwe:



* dodanie dwóch stacji pomiarowych o tej samej nazwie lub tych samych wspólrzednych;

* dodanie dwóch pomiarów o tych samych:

  * wspólrzednych,

  * dacie i godzinie,

  * typie (PM10, PM2.5, temperatura, …);

* dodanie pomiaru do nieistniejacej stacji.



Zaprojektuj strukture danych dla przechowywania takich informacji (jest przynajmniej kilka dobrych rozwiazan tego problemu).



Zaimplementuj funkcje w module pollution:


* _createMonitor/0_ - tworzy i zwraca nowy monitor zanieczyszczen;

* _addStation/3_ - dodaje do monitora wpis o nowej stacji pomiarowej (nazwa i wspólrzedne geograficzne), zwraca zaktualizowany monitor;

* _addValue/5_ - dodaje odczyt ze stacji (wspólrzedne geograficzne lub nazwa stacji, data, typ pomiaru, wartosc), zwraca zaktualizowany monitor;

* _removeValue/4_ - usuwa odczyt ze stacji (wspólrzedne geograficzne lub nazwa stacji, data, typ pomiaru), zwraca zaktualizowany monitor;

* _getOneValue/4_ - zwraca wartosc pomiaru o zadanym typie, z zadanej daty i stacji;

* _getStationMean/3_ - zwraca srednia wartosc parametru danego typu z zadanej stacji;

* _getDailyMean/3_ - zwraca srednia wartosc parametru danego typu, danego dnia na wszystkich stacjach;



W funkcjach uzywaj nastepujacych typów i formatów danych:


* do przechowywania dat uzyj struktur z modulu calendar (zob. calendar:local_time(). ),

* wspólrzedne geograficzne to para (krotka) liczb,

* nazwy, typy to ciagi znaków.



Napisz testy do modulu _pollution_ z wykorzystaniem EUnit.
