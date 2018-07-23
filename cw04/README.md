# Zestaw 4
### Rodzaje sygna��w, sygna�y czasu rzeczywistego, przydatne funkcje systemowe
## Zadanie 1
Napisz program wypisuj�cy w p�tli niesko�czonej aktualn� godzin� Po odebraniu sygna�u *SIGTSTP* (CTRL+Z) program zatrzymuje si�, wypisuj�c komunikat "Oczekuj� na CTRL+Z - kontynuacja albo CTR+C - zakonczenie programu". Po ponownym wys�aniu *SIGTSTP* program powraca do pierwotnego wypisywania.

Program powinien r�wnie� obs�ugiwa� sygna� *SIGINT*. Po jego odebraniu program wypisuje komunikat "Odebrano sygna� SIGINT" i ko�czy dzia�anie. W kodzie programu, do przechwycenia sygna��w u�yj zar�wno funkcji *signal*, jak i *sigaction* (np. *SIGINT* odbierz za pomoc� signal, a *SIGTSTP* za pomoc� *sigaction*).

Zrealizuj powy�sze zadanie, tworz�c program potomny, kt�ry b�dzie wywo�ywa� jedn� z funkcji z rodziny *exec* skrypt shellowy zawieraj�cy zap�tlone systemowe polecenie date. Proces macierzysty b�dzie przychwytywa� powy�sze sygna�y i przekazywa� je do procesu potomnego, tj po otrzymaniu *SIGTSTP* ko�czy proces potomka, a je�li ten zosta� wcze�niej zako�czony, tworzy nowy, wznawiaj�c dzia�anie skryptu, a po otrzymaniu *SIGINT* ko�czy dzia�anie potomka (je�li ten jeszcze pracuje) oraz programu.

## Zadanie 2

Napisz program, kt�ry tworzy N potomk�w i oczekuje na ich pro�by na rozpocz�cie dzia�ania (sygna�y *SIGUSR1*). Po uzyskaniu K pr�b, proces powinien pozwoli� kontynuowa� dzia�anie wszystkim procesom, kt�re poprosi�y o przej�cie (wys�a� im sygna� pozwolenia na rozpocz�cie pracy) i niezw�ocznie akceptowa� ka�d� kolejn� pro�b�. Program powinien wypisa� list� wszystkich otrzymanych sygna��w wraz numerem PID potomka oraz kodem zako�czenia procesu (w przypadku otrzymania sygna�u zako�czenia pracy potomka).

Program ko�czy dzia�anie po zako�czeniu pracy ostatniego potomka albo po otrzymaniu sygna�u *SIGINT* (w tym wypadku nale�y zako�czy� wszystkie dzia�aj�ce procesy potomne).

N i M s� argumentami programu.

Zachowanie dzieci powinno by� nast�puj�ce: Ka�de dziecko najpierw symuluje prac� (usypia na 0-10 sekund). Nast�pnie wysy�a sygna� *SIGUSR1* pro�by o przej�cie, a po uzyskaniu pozwolenia losuje jeden z 32 sygna��w czasu rzeczywistego  (*SIGRTMIN*,*SIGRTMAX*), wysy�a go do rodzica i ko�czy dzia�anie, zwracaj�c liczb� sekund jak� proces wylosowa� do u�pienia.

Program g��wny powinien mie� mo�liwo�� �ledzenia informacji na temat (dla czytelno�ci w �atwy spos�b powinno da� si� je grupami w��czy� i wy��czy�):

* tworzenia procesu potomnego (jego nr PID),
* otrzymanych pr�b od proces�w potomnych,
* wys�anych pozwole� na wys�anie sygna�u rzeczywistego
* otrzymanych sygna��w czasu rzeczywistego(wraz z numerem sygna�u)
* zako�czenia procesu potomnego (wraz ze zwr�con� warto�ci�)

## Zadanie 3

Napisz program kt�ry tworzy proces potomny i wysy�a do niego L sygna��w *SIGUSR1*, a nast�pnie sygna� zako�czenia wysy�ania *SIGUSR2*. Potomek po otrzymaniu sygna��w *SIGUSR1* od rodzica zaczyna je odsy�a� do procesu macierzystego, a po otrzymaniu *SIGUSR2* ko�czy prac�.

Proces macierzysty w zale�no�ci od argumentu *Type* (1,2,3) programu wysy�a sygna�y na trzy r�ne sposoby:

* *SIGUSR1*, *SIGUSR2* za pomoc� funkcji *kill*
* *SIGUSR1*, *SIGUSR2* za pomoc� funkcji *kill*, z tym, �e proces macierzysty wysy�a kolejny sygna� dopiero po otrzymaniu potwierdzenia odebrania poprzedniego
* wybrane 2 sygna�y czasu rzeczywistego za pomoc� *kill*

Program powinien wypisywa� informacje o:

* liczbie wys�anych sygna��w do potomka
* liczbie odebranych sygna��w przez potomka
* liczbie odebranych sygna��w od potomka

Program ko�czy dzia�anie po zako�czeniu pracy potomka albo po otrzymaniu sygna�u *SIGINT* (w tym wypadku od razu wysy�a do potomka sygna� *SIGUSR2*, aby ten zako�czy� prac�. Wszystkie pozosta�e sygna�y s� blokowane w procesie potomnym).

L i Type s� argumentami programu.