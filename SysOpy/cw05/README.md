# Zestaw 5
### Potoki nazwane i nienazwane
## Zadanie 1
Nale�y rozszerzy� interpreter polece� z zadania 2 w zestawie 3 (Procesy) tak, by obs�ugiwa� operator pipe - "|". Interpreter czyta kolejne linie z podanego pliku, ka�da linia ma format

*prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progN arg1 ... argnN*

Dla takiej linii interpreter powinien uruchomi� wszystkie N polece� w osobnych procesach, zapewniaj�c przy u�yciu potok�w nienazwanych oraz funkcji *dup2*, by wyj�cie standardowe procesu k by�o przekierowane do wej�cia standardowego procesu (k+1). Mo�na za�o�y� ograniczenie g�rne na ilo�� obs�ugiwanych argument�w oraz ilo�� po��czonych komend w pojedynczym poleceniu (co najmniej 5). Po uruchomieniu ci�gu program�w sk�adaj�cych si� na pojedczyne polecenie (linijk�) interpreter powinien oczekiwa� na zako�czenie wszystkich tych program�w.

**Uwaga**: nale�y u�y� *pipe*/*fork*/*exec*, nie *popen*


## Zadanie 2
Nale�y napisa� dwa programy - master oraz slave - kt�re b�d� komunikowa� si� poprzez potok nazwany (kolejk� FIFO), do kt�rej �cie�k� b�d� dostawa� jako argument wywo�ania. Do potoku pisa� b�dzie wiele proces�w wykonuj�cych program slave, a czyta� b�dzie z niej jeden proces master.

Master przyjmuje jeden argument - �cie�k� do potoku nazwanego. Tworzy on ten potok nazwany, a nast�pnie czyta kolejne linijki z potoku nazwanego i wypisuje je na ekran.

Slave przyjmuje dwa argumenty - �cie�k� do potoku nazwanego i liczb� ca�kowit� N. Wykonuje nast�puj�ce akcje:

* otwiera potok nazwany
* wypisuje sw�j PID na wyj�cie standardowe
* N razy zapisuje do potoku nazwanego linijk� sk�adaj�c� si� ze swojego PIDu oraz obecnej daty
   * dat� nale�y wygenerowa� programem date uruchomionym przy u�yciu funkcji *popen*
   * po ka�dym zapisie nale�y odczeka� losow� ilo�� czasu (np. 2-5 sekund)