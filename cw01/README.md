# Zestaw 1 #
### Zarz�dzanie pami�ci�, biblioteki, pomiar czasu ###
## Zadanie 1. Alokacja tablicy z wska�nikami na bloki pami�ci zawieraj�ce znaki ##

Zaprojektuj i przygotuj zestaw funkcji (bibliotek�) do zarz�dzania tablic� blok�w zawieraj�cych znaki.

Biblioteka powinna umo�liwia�:
* tworzenie i usuwanie tablicy
* dodanie i usuni�cie blok�w na kt�re wskazuj� wybrane indeksy element�w tablicy 
* wyszukiwanie bloku w tablicy, kt�rego suma znak�w (kod�w ASCII) w bloku jest najbli�sza elementowi o zadanym numerze

Tablice i bloki powinny by� alokowane przy pomocy funkcji *calloc* (alokacja dynamiczna) jak r�wnie� powinny wykorzystywa� tablic� dwuwymiarow� (statyczny przydzia� pami�ci).

Przygotuj plik *Makefile*, zawieraj�cy polecenia kompiluj�ce pliki �r�d�owe biblioteki oraz tworz�ce biblioteki w dw�ch wersjach: statyczn� i dzielon�.

## Zadanie 2. Program korzystaj�cy z biblioteki ##

Napisz program testuj�cy dzia�anie funkcji z biblioteki z zadania 1.

Jako argumenty przeka� liczb� element�w tablicy, rozmiar bloku, spos�b alokacji  pami�ci oraz spis wykonywanych operacji. Zak�adamy, �e mo�liwe jest zlecenie trzech operacji (np. stworzenie tablicy, wyszukanie elementu oraz usuni�cie i dodanie zadanej liczby blok�w albo stworzenie tablicy, usuni�cie i dodanie zadanej liczby blok�w i naprzemienne usuni�cie i dodanie zadanej liczby blok�w).

Operacje mog� by� specyfikowane w linii polece� na przyk�ad jak poni�ej:
* *create_table rozmiar rozmiar_bloku* - stworzenie tablicy o rozmiarze "rozmiar" i blokach o rozmiarach "rozmiar bloku" 
* *search_element warto��* - wyszukanie elementu o warto�ci ASCII zbli�onej do pozycji "wartos�" 
* *remove number* - usu� "number" blok�w 
* *add  number* - dodaj "number" blok�w 
* *remove_and_add number* - usuwaj i dodawaj na przemian blok 
  "number" razy

Program powinien stworzy� tablice blok�w o zadanej liczbie element�w i rozmiarze blok�w. Dane mo�na wygenerowa� na stronach typu generatedata.com albo u�y� danych losowych.

W programie zmierz, wypisz na konsol� i zapisz  do pliku z raportem  czasy realizacji podstawowych operacji:
* stworzenie tablicy z zadan� liczb� blok�w o zdanym rozmiarze i przy pomocy wybranej funkcji alokuj�cej,
* wyszukanie najbardziej podobnego elementu z punktu widzenia sumy znak�w do elementu zadanego jako argument
* usuni�cie kolejno zadanej liczby blok�w a nast�pnie dodanie  na ich miejsce nowych blok�w
* na przemian usuni�cie i dodanie zadanej liczby blok�w 

Mierz�c czasy poszczeg�lnych operacji zapisz trzy warto�ci: czas rzeczywisty, czas u�ytkownika i czas systemowy. Rezultaty umie�� pliku raport2.txt i do��cz do archiwum zadania.

## Zadanie 3. Testy i pomiary ##
a) Przygotuj plik *Makefile*, zawieraj�cy polecenia kompiluj�ce program z zad 2 na trzy sposoby:
* z wykorzystaniem bibliotek statycznych,
* z wykorzystaniem bibliotek dzielonych (dynamiczne, �adowane przy uruchomieniu programu),
* z wykorzystaniem bibliotek �adowanych dynamicznie (dynamiczne, �adowane przez program),
oraz uruchamiaj�cy testy

Wyniki pomiar�w zbierz w pliku results3a.txt. Otrzymane wyniki kr�tko skomentuj.

b) Rozszerz plik *Makefile* z punktu 3a) dodaj�c mo�liwo�� skompilowania programu na trzech r�nych  poziomach optymalizacji -O0...-Os. Przeprowad� ponownie pomiary kompiluj�c i uruchamiaj�c program na ro�nych poziomach optymalizacji.

Wyniki pomiar�w dodaj do pliku results3b.txt. Otrzymane wyniki krotko skomentuj.

 Wygenerowane pliki z raportami za��cz jako element rozwi�zania.