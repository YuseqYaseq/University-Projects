# Zestaw 5
### Potoki nazwane i nienazwane
## Zadanie 1
Nale¿y rozszerzyæ interpreter poleceñ z zadania 2 w zestawie 3 (Procesy) tak, by obs³ugiwa³ operator pipe - "|". Interpreter czyta kolejne linie z podanego pliku, ka¿da linia ma format

*prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progN arg1 ... argnN*

Dla takiej linii interpreter powinien uruchomiæ wszystkie N poleceñ w osobnych procesach, zapewniaj¹c przy u¿yciu potoków nienazwanych oraz funkcji *dup2*, by wyjœcie standardowe procesu k by³o przekierowane do wejœcia standardowego procesu (k+1). Mo¿na za³o¿yæ ograniczenie górne na iloœæ obs³ugiwanych argumentów oraz iloœæ po³¹czonych komend w pojedynczym poleceniu (co najmniej 5). Po uruchomieniu ci¹gu programów sk³adaj¹cych siê na pojedczyne polecenie (linijkê) interpreter powinien oczekiwaæ na zakoñczenie wszystkich tych programów.

**Uwaga**: nale¿y u¿yæ *pipe*/*fork*/*exec*, nie *popen*


## Zadanie 2
Nale¿y napisaæ dwa programy - master oraz slave - które bêd¹ komunikowaæ siê poprzez potok nazwany (kolejkê FIFO), do której œcie¿kê bêd¹ dostawaæ jako argument wywo³ania. Do potoku pisaæ bêdzie wiele procesów wykonuj¹cych program slave, a czyta³ bêdzie z niej jeden proces master.

Master przyjmuje jeden argument - œcie¿kê do potoku nazwanego. Tworzy on ten potok nazwany, a nastêpnie czyta kolejne linijki z potoku nazwanego i wypisuje je na ekran.

Slave przyjmuje dwa argumenty - œcie¿kê do potoku nazwanego i liczbê ca³kowit¹ N. Wykonuje nastêpuj¹ce akcje:

* otwiera potok nazwany
* wypisuje swój PID na wyjœcie standardowe
* N razy zapisuje do potoku nazwanego linijkê sk³adaj¹c¹ siê ze swojego PIDu oraz obecnej daty
   * datê nale¿y wygenerowaæ programem date uruchomionym przy u¿yciu funkcji *popen*
   * po ka¿dym zapisie nale¿y odczekaæ losow¹ iloœæ czasu (np. 2-5 sekund)