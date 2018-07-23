# README #

Stwórz system, który na podstawie argumentów zawartych w linii komend:
- [ ]  Wypisuje obowiązującą cenę złota oraz cenę podanej waluty (tabela A) w podanym dniu
- [ ]  Oblicza średnią cenę złota za podany okres
- [ ]  Odszukuje walutę (tabela A), której kurs, począwszy od podanego dnia, uległ największym wahaniom (waluta, której amplituda zmian kursu jest największa)
- [ ]  Odszukuje walutę (tabela C), której kurs kupna był najmniejszy w podanym dniu
- [ ]  Wypisuje N walut (tabela C), posortowanych względem różnicy pomiędzy ceną sprzedaży a ceną kupna, w podanym dniu
- [ ]  Dla podanej waluty (tabela A) wypisuje informację kiedy dana waluta była najtańsza, a kiedy najdroższa
- [ ]  Rysuje (w trybie tekstowym) wspólny (dla wszystkich tygodni) wykres zmian ceny (np. wykres słupkowy, za pomocą różnorodnych znaków ASCII) podanej waluty (tabela A) w układzie tygodniowym, tzn. jaka była cena w poniedziałek, wtorek, itd. w pierwszym tygodniu, drugim tygodniu, ...

#### Wymagania ####
* Jako parametry wejściowe podajemy symbol waluty oraz dwa okresy: początkowy oraz końcowy
* Każdy z okresów podajemy w postaci: rok, miesiąc, numer tygodnia
* Przyjmujemy, że pierwszym dniem okresu początkowego jest poniedziałek, a ostatnim dniem okresu końcowego jest piątek
* Po wywołaniu programu bez argumentów wyświetla pomoc (opis opcji oraz sposobu uruchamiania programu)
* Końcowa wersja programu (pliki '*.class') ma być dostępna w postaci archiwum jar (opis tworzenia wykonywalnego jar-a z poziomu Eclipse'a); uruchamianie programu ma się odbywać za pomocą komendy java -jar nazwaArchiwum.jar ...
* Proszę zaprojektować swój system tak, aby w przyszłości dało się go, po niewielkich przeróbkach, użyć do obsługi innych serwisów, np. Krajowy Rejestr Sądowy - https://mojepanstwo.pl/api/krs
* Postaraj się użyć (o ile potrafisz), co najmniej jednego, wzorca projektowego
* Należy przyjąć, że okresy określone w punkcie 3 mogą obejmować:
⋅⋅⋅ - lata 2002-2017 w przypadku kursów walut
⋅⋅⋅ - lata 2013-2017 w przypadku cen złota
