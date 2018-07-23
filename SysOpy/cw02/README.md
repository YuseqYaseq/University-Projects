# Zestaw 2 #
### Obs�uga wej�cia/wyj�cia
## Zadanie 1. Por�wnanie wydajno�ci systemowych i bibliotecznych funkcji we/wy
Celem zadania jest napisanie programu por�wnuj�cego wydajno�� systemowych i bibliotecznych funkcji wej�cia/wyj�cia. Program operowa� b�dzie na przechowywanej w pliku tablicy rekord�w. Dla uproszczenia pojedynczy rekord b�dzie tablic� bajt�w o sta�ej wielko�ci. Nazwa pliku, wielko�� oraz ilo�� rekord�w stanowi� b�d� argumenty wywo�ania programu.

Program udost�pnia� powinien operacje:
* *generate* - tworzenie pliku z rekordami wype�nionego wygenerowan� losow� zawarto�ci� (mo�na wykorzysta� wirtualny generator /dev/random lub w wersji uproszczonej funkcj� *rand*)
* *sort* - sortuje rekordy w pliku u�ywaj�c sortowania przez proste wstawianie. Kluczem do sortowania niech b�dzie warto�� pierwszego bajtu rekordu (interpretowanego jako liczba bez znaku - *unsigned char*) Podczas sortowania w pami�ci powinny by� przechowywane jednocze�nie najwy�ej dwa rekordy (sprowadza si� do zamieniania miejscami i por�wnywania dw�ch rekord�w).
* *copy* - kopiuje *plik1* do *pliku2*. Kopiowanie powinno odbywa� si� za pomoc� bufora o zadanej wielko�ci rekordu.

Sortowanie i kopiowanie powinno by� zaimplementowane w dw�ch wariantach:
* *sys* - przy u�yciu funkcji systemowych: *read* i *write*
* *lib* - przy u�yciu funkcji biblioteki C: *fread* i *fwrite*

Rodzaj operacji oraz spos�b dost�pu do plik�w ma by� wybierany na podstawie argumentu wywo�ania - np.:
* *./program generate dane 100 512* powinno losowo generowa� 100 rekord�w o d�ugo�ci 512 bajt�w do pliku *dane*
* *./program sort dane 100 512 sys* powinien sortowa� rekordy w pliku *dane* przy u�yciu funkcji systemowych, zak�adaj�c �e zawiera on 100 rekord�w wielko�ci 512 bajt�w
* *./program copy plik1 plik2 100 512 sys* powinno skopiowa� 100 rekord�w *pliku1* do *pliku2* za pomoc� funkcji bibliotecznych z wykorzystaniem bufora 512 bajt�w

Dla obu wariant�w implementacji przeprowad� pomiary czasu u�ytkownika i czasu systemowego operacji sortowania i kopiowania. Testy wykonaj dla nast�puj�cych rozmiar�w rekordu: 4, 512, 4096 i 8192 bajty. Dla ka�dego rozmiaru rekordu wykonaj dwa testy r�ni�ce si� liczb� rekord�w w sortowanym pliku. Liczby rekord�w dobierz tak, by czas sortowania mie�ci� si� w przedziale od kilku do kilkudziesi�ciu sekund. Por�wnuj�c dwa warianty implementacji nale�y korzysta� z identycznego pliku do sortowania (po wygenerowaniu, a przed sortowaniem, utw�rz jego kopi�). Zmierzone czasy zestaw w pliku *wyniki.txt*. Do pliku dodaj komentarz podsumowuj�cy wnioski z test�w.
## Zadanie 2. Operacje na strukturze katalog�w
Napisz program wyszukuj�cy w drzewie katalogu (�cie�ka do katalogu jest pierwszym argumentem programu), w zale�no�ci od warto�ci drugiego argumentu ('<', '>','=') , pliki zwyk�e z dat� modyfikacji wcze�niejsz�, p�niejsz� lub r�wn� dacie podanej jako trzeci argument programu. Program ma wypisa� na standardowe wyj�cie nast�puj�ce informacje znalezionych plik�w:
* �cie�ka bezwzgl�dna pliku
* rozmiar w bajtach
* prawa dost�pu do pliku (w formacie u�ywanym przez ls -l, np. *r--r--rw-* oznacza prawa odczytu dla wszystkich i zapisu dla w�a�ciciela)
* dat� ostatniej modyfikacji

�cie�ka podana jako argument wywo�ania mo�e by� wzgl�dna lub bezwzgl�dna. Program powinien wyszukiwa� tylko pliki zwyczajne (bez dowi�za�, urz�dze� blokowych, itp). Program nie powinien pod��a� za dowi�zaniami symbolicznymi do katalog�w.

Program nale�y zaimplementowa� w dw�ch wariantach:
* Korzystaj�c z funkcji *opendir*, *readdir* oraz funkcji z rodziny *stat*
* Korzystaj�c z funkcji *nftw*

W ramach testowania funkcji utw�rz w badanej strukturze katalog�w jakie� dowi�zania symboliczne.