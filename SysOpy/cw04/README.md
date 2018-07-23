# Zestaw 4
### Rodzaje sygna³ów, sygna³y czasu rzeczywistego, przydatne funkcje systemowe
## Zadanie 1
Napisz program wypisuj¹cy w pêtli nieskoñczonej aktualn¹ godzinê Po odebraniu sygna³u *SIGTSTP* (CTRL+Z) program zatrzymuje siê, wypisuj¹c komunikat "Oczekujê na CTRL+Z - kontynuacja albo CTR+C - zakonczenie programu". Po ponownym wys³aniu *SIGTSTP* program powraca do pierwotnego wypisywania.

Program powinien równie¿ obs³ugiwaæ sygna³ *SIGINT*. Po jego odebraniu program wypisuje komunikat "Odebrano sygna³ SIGINT" i koñczy dzia³anie. W kodzie programu, do przechwycenia sygna³ów u¿yj zarówno funkcji *signal*, jak i *sigaction* (np. *SIGINT* odbierz za pomoc¹ signal, a *SIGTSTP* za pomoc¹ *sigaction*).

Zrealizuj powy¿sze zadanie, tworz¹c program potomny, który bêdzie wywo³ywa³ jedn¹ z funkcji z rodziny *exec* skrypt shellowy zawieraj¹cy zapêtlone systemowe polecenie date. Proces macierzysty bêdzie przychwytywa³ powy¿sze sygna³y i przekazywa³ je do procesu potomnego, tj po otrzymaniu *SIGTSTP* koñczy proces potomka, a jeœli ten zosta³ wczeœniej zakoñczony, tworzy nowy, wznawiaj¹c dzia³anie skryptu, a po otrzymaniu *SIGINT* koñczy dzia³anie potomka (jeœli ten jeszcze pracuje) oraz programu.

## Zadanie 2

Napisz program, który tworzy N potomków i oczekuje na ich proœby na rozpoczêcie dzia³ania (sygna³y *SIGUSR1*). Po uzyskaniu K próœb, proces powinien pozwoliæ kontynuowaæ dzia³anie wszystkim procesom, które poprosi³y o przejœcie (wys³aæ im sygna³ pozwolenia na rozpoczêcie pracy) i niezw³ocznie akceptowaæ ka¿d¹ kolejn¹ proœbê. Program powinien wypisaæ listê wszystkich otrzymanych sygna³ów wraz numerem PID potomka oraz kodem zakoñczenia procesu (w przypadku otrzymania sygna³u zakoñczenia pracy potomka).

Program koñczy dzia³anie po zakoñczeniu pracy ostatniego potomka albo po otrzymaniu sygna³u *SIGINT* (w tym wypadku nale¿y zakoñczyæ wszystkie dzia³aj¹ce procesy potomne).

N i M s¹ argumentami programu.

Zachowanie dzieci powinno byæ nastêpuj¹ce: Ka¿de dziecko najpierw symuluje pracê (usypia na 0-10 sekund). Nastêpnie wysy³a sygna³ *SIGUSR1* proœby o przejœcie, a po uzyskaniu pozwolenia losuje jeden z 32 sygna³ów czasu rzeczywistego  (*SIGRTMIN*,*SIGRTMAX*), wysy³a go do rodzica i koñczy dzia³anie, zwracaj¹c liczbê sekund jak¹ proces wylosowa³ do uœpienia.

Program g³ówny powinien mieæ mo¿liwoœæ œledzenia informacji na temat (dla czytelnoœci w ³atwy sposób powinno daæ siê je grupami w³¹czyæ i wy³¹czyæ):

* tworzenia procesu potomnego (jego nr PID),
* otrzymanych próœb od procesów potomnych,
* wys³anych pozwoleñ na wys³anie sygna³u rzeczywistego
* otrzymanych sygna³ów czasu rzeczywistego(wraz z numerem sygna³u)
* zakoñczenia procesu potomnego (wraz ze zwrócon¹ wartoœci¹)

## Zadanie 3

Napisz program który tworzy proces potomny i wysy³a do niego L sygna³ów *SIGUSR1*, a nastêpnie sygna³ zakoñczenia wysy³ania *SIGUSR2*. Potomek po otrzymaniu sygna³ów *SIGUSR1* od rodzica zaczyna je odsy³aæ do procesu macierzystego, a po otrzymaniu *SIGUSR2* koñczy pracê.

Proces macierzysty w zale¿noœci od argumentu *Type* (1,2,3) programu wysy³a sygna³y na trzy ró¿ne sposoby:

* *SIGUSR1*, *SIGUSR2* za pomoc¹ funkcji *kill*
* *SIGUSR1*, *SIGUSR2* za pomoc¹ funkcji *kill*, z tym, ¿e proces macierzysty wysy³a kolejny sygna³ dopiero po otrzymaniu potwierdzenia odebrania poprzedniego
* wybrane 2 sygna³y czasu rzeczywistego za pomoc¹ *kill*

Program powinien wypisywaæ informacje o:

* liczbie wys³anych sygna³ów do potomka
* liczbie odebranych sygna³ów przez potomka
* liczbie odebranych sygna³ów od potomka

Program koñczy dzia³anie po zakoñczeniu pracy potomka albo po otrzymaniu sygna³u *SIGINT* (w tym wypadku od razu wysy³a do potomka sygna³ *SIGUSR2*, aby ten zakoñczy³ pracê. Wszystkie pozosta³e sygna³y s¹ blokowane w procesie potomnym).

L i Type s¹ argumentami programu.