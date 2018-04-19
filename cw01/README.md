# Zestaw 1 #
### Zarz¹dzanie pamiêci¹, biblioteki, pomiar czasu ###
## Zadanie 1. Alokacja tablicy z wskaŸnikami na bloki pamiêci zawieraj¹ce znaki ##

Zaprojektuj i przygotuj zestaw funkcji (bibliotekê) do zarz¹dzania tablic¹ bloków zawieraj¹cych znaki.

Biblioteka powinna umo¿liwiaæ:
* tworzenie i usuwanie tablicy
* dodanie i usuniêcie bloków na które wskazuj¹ wybrane indeksy elementów tablicy 
* wyszukiwanie bloku w tablicy, którego suma znaków (kodów ASCII) w bloku jest najbli¿sza elementowi o zadanym numerze

Tablice i bloki powinny byæ alokowane przy pomocy funkcji *calloc* (alokacja dynamiczna) jak równie¿ powinny wykorzystywaæ tablicê dwuwymiarow¹ (statyczny przydzia³ pamiêci).

Przygotuj plik *Makefile*, zawieraj¹cy polecenia kompiluj¹ce pliki Ÿród³owe biblioteki oraz tworz¹ce biblioteki w dwóch wersjach: statyczn¹ i dzielon¹.

## Zadanie 2. Program korzystaj¹cy z biblioteki ##

Napisz program testuj¹cy dzia³anie funkcji z biblioteki z zadania 1.

Jako argumenty przeka¿ liczbê elementów tablicy, rozmiar bloku, sposób alokacji  pamiêci oraz spis wykonywanych operacji. Zak³adamy, ¿e mo¿liwe jest zlecenie trzech operacji (np. stworzenie tablicy, wyszukanie elementu oraz usuniêcie i dodanie zadanej liczby bloków albo stworzenie tablicy, usuniêcie i dodanie zadanej liczby bloków i naprzemienne usuniêcie i dodanie zadanej liczby bloków).

Operacje mog¹ byæ specyfikowane w linii poleceñ na przyk³ad jak poni¿ej:
* *create_table rozmiar rozmiar_bloku* - stworzenie tablicy o rozmiarze "rozmiar" i blokach o rozmiarach "rozmiar bloku" 
* *search_element wartoœæ* - wyszukanie elementu o wartoœci ASCII zbli¿onej do pozycji "wartosæ" 
* *remove number* - usuñ "number" bloków 
* *add  number* - dodaj "number" bloków 
* *remove_and_add number* - usuwaj i dodawaj na przemian blok 
  "number" razy

Program powinien stworzyæ tablice bloków o zadanej liczbie elementów i rozmiarze bloków. Dane mo¿na wygenerowaæ na stronach typu generatedata.com albo u¿yæ danych losowych.

W programie zmierz, wypisz na konsolê i zapisz  do pliku z raportem  czasy realizacji podstawowych operacji:
* stworzenie tablicy z zadan¹ liczb¹ bloków o zdanym rozmiarze i przy pomocy wybranej funkcji alokuj¹cej,
* wyszukanie najbardziej podobnego elementu z punktu widzenia sumy znaków do elementu zadanego jako argument
* usuniêcie kolejno zadanej liczby bloków a nastêpnie dodanie  na ich miejsce nowych bloków
* na przemian usuniêcie i dodanie zadanej liczby bloków 

Mierz¹c czasy poszczególnych operacji zapisz trzy wartoœci: czas rzeczywisty, czas u¿ytkownika i czas systemowy. Rezultaty umieœæ pliku raport2.txt i do³¹cz do archiwum zadania.

## Zadanie 3. Testy i pomiary ##
a) Przygotuj plik *Makefile*, zawieraj¹cy polecenia kompiluj¹ce program z zad 2 na trzy sposoby:
* z wykorzystaniem bibliotek statycznych,
* z wykorzystaniem bibliotek dzielonych (dynamiczne, ³adowane przy uruchomieniu programu),
* z wykorzystaniem bibliotek ³adowanych dynamicznie (dynamiczne, ³adowane przez program),
oraz uruchamiaj¹cy testy

Wyniki pomiarów zbierz w pliku results3a.txt. Otrzymane wyniki krótko skomentuj.

b) Rozszerz plik *Makefile* z punktu 3a) dodaj¹c mo¿liwoœæ skompilowania programu na trzech ró¿nych  poziomach optymalizacji -O0...-Os. PrzeprowadŸ ponownie pomiary kompiluj¹c i uruchamiaj¹c program na ro¿nych poziomach optymalizacji.

Wyniki pomiarów dodaj do pliku results3b.txt. Otrzymane wyniki krotko skomentuj.

 Wygenerowane pliki z raportami za³¹cz jako element rozwi¹zania.