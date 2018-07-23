# Zestaw 2 #
### Obs³uga wejœcia/wyjœcia
## Zadanie 1. Porównanie wydajnoœci systemowych i bibliotecznych funkcji we/wy
Celem zadania jest napisanie programu porównuj¹cego wydajnoœæ systemowych i bibliotecznych funkcji wejœcia/wyjœcia. Program operowa³ bêdzie na przechowywanej w pliku tablicy rekordów. Dla uproszczenia pojedynczy rekord bêdzie tablic¹ bajtów o sta³ej wielkoœci. Nazwa pliku, wielkoœæ oraz iloœæ rekordów stanowiæ bêd¹ argumenty wywo³ania programu.

Program udostêpniaæ powinien operacje:
* *generate* - tworzenie pliku z rekordami wype³nionego wygenerowan¹ losow¹ zawartoœci¹ (mo¿na wykorzystaæ wirtualny generator /dev/random lub w wersji uproszczonej funkcjê *rand*)
* *sort* - sortuje rekordy w pliku u¿ywaj¹c sortowania przez proste wstawianie. Kluczem do sortowania niech bêdzie wartoœæ pierwszego bajtu rekordu (interpretowanego jako liczba bez znaku - *unsigned char*) Podczas sortowania w pamiêci powinny byæ przechowywane jednoczeœnie najwy¿ej dwa rekordy (sprowadza siê do zamieniania miejscami i porównywania dwóch rekordów).
* *copy* - kopiuje *plik1* do *pliku2*. Kopiowanie powinno odbywaæ siê za pomoc¹ bufora o zadanej wielkoœci rekordu.

Sortowanie i kopiowanie powinno byæ zaimplementowane w dwóch wariantach:
* *sys* - przy u¿yciu funkcji systemowych: *read* i *write*
* *lib* - przy u¿yciu funkcji biblioteki C: *fread* i *fwrite*

Rodzaj operacji oraz sposób dostêpu do plików ma byæ wybierany na podstawie argumentu wywo³ania - np.:
* *./program generate dane 100 512* powinno losowo generowaæ 100 rekordów o d³ugoœci 512 bajtów do pliku *dane*
* *./program sort dane 100 512 sys* powinien sortowaæ rekordy w pliku *dane* przy u¿yciu funkcji systemowych, zak³adaj¹c ¿e zawiera on 100 rekordów wielkoœci 512 bajtów
* *./program copy plik1 plik2 100 512 sys* powinno skopiowaæ 100 rekordów *pliku1* do *pliku2* za pomoc¹ funkcji bibliotecznych z wykorzystaniem bufora 512 bajtów

Dla obu wariantów implementacji przeprowadŸ pomiary czasu u¿ytkownika i czasu systemowego operacji sortowania i kopiowania. Testy wykonaj dla nastêpuj¹cych rozmiarów rekordu: 4, 512, 4096 i 8192 bajty. Dla ka¿dego rozmiaru rekordu wykonaj dwa testy ró¿ni¹ce siê liczb¹ rekordów w sortowanym pliku. Liczby rekordów dobierz tak, by czas sortowania mieœci³ siê w przedziale od kilku do kilkudziesiêciu sekund. Porównuj¹c dwa warianty implementacji nale¿y korzystaæ z identycznego pliku do sortowania (po wygenerowaniu, a przed sortowaniem, utwórz jego kopiê). Zmierzone czasy zestaw w pliku *wyniki.txt*. Do pliku dodaj komentarz podsumowuj¹cy wnioski z testów.
## Zadanie 2. Operacje na strukturze katalogów
Napisz program wyszukuj¹cy w drzewie katalogu (œcie¿ka do katalogu jest pierwszym argumentem programu), w zale¿noœci od wartoœci drugiego argumentu ('<', '>','=') , pliki zwyk³e z dat¹ modyfikacji wczeœniejsz¹, póŸniejsz¹ lub równ¹ dacie podanej jako trzeci argument programu. Program ma wypisaæ na standardowe wyjœcie nastêpuj¹ce informacje znalezionych plików:
* œcie¿ka bezwzglêdna pliku
* rozmiar w bajtach
* prawa dostêpu do pliku (w formacie u¿ywanym przez ls -l, np. *r--r--rw-* oznacza prawa odczytu dla wszystkich i zapisu dla w³aœciciela)
* datê ostatniej modyfikacji

Œcie¿ka podana jako argument wywo³ania mo¿e byæ wzglêdna lub bezwzglêdna. Program powinien wyszukiwaæ tylko pliki zwyczajne (bez dowi¹zañ, urz¹dzeñ blokowych, itp). Program nie powinien pod¹¿aæ za dowi¹zaniami symbolicznymi do katalogów.

Program nale¿y zaimplementowaæ w dwóch wariantach:
* Korzystaj¹c z funkcji *opendir*, *readdir* oraz funkcji z rodziny *stat*
* Korzystaj¹c z funkcji *nftw*

W ramach testowania funkcji utwórz w badanej strukturze katalogów jakieœ dowi¹zania symboliczne.