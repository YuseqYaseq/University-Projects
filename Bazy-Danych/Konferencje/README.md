# Podstawy baz danych - projekt i implementacja systemu bazodanowego
## System zarz¹dzania konferencjami
#### Opis problemu
Projekt dotyczy systemu wspomagania dzia³alnoœci firmy organizuj¹cej konferencje.
#### Ogólne informacje
Firma organizuje konferencje, które mog¹ byæ jedno- lub kilkudniowe. Klienci powinni móc rejestrowaæ siê na konferencje za pomoc¹ systemu www. Klientami mog¹ byæ zarówno indywidualne osoby jak i firmy, natomiast uczestnikami konferencji s¹ osoby (firma nie musi podawaæ od razu przy rejestracji listy uczestników - mo¿e zarezerwowaæ odpowiedni¹ iloœæ miejsc na okreœlone dni oraz na warsztaty, natomiast na 2 tygodnie przed rozpoczêciem musi te dane uzupe³niæ - a jeœli sama nie uzupe³ni do tego czasu, to pracownicy dzwoni¹ do firmy i ustalaj¹ takie informacje). Ka¿dy uczestnik konferencji otrzymuje identyfikator imienny (+ ew. informacja o firmie na nim). Dla konferencji kilkudniowych, uczestnicy mog¹ rejestrowaæ siê na dowolne z tych dni.
#### Warsztaty
Ponadto z konferencj¹ zwi¹zane s¹ warsztaty, na które uczestnicy tak¿e mog¹ siê zarejestrowaæ - musz¹ byæ jednak zarejestrowani tego dnia na konferencjê, aby móc w nich uczestniczyæ. Kilka warsztatów mo¿e trwaæ równoczeœnie, ale uczestnik nie mo¿e zarejestrowaæ siê na wiêcej ni¿ jeden warsztat, który trwa w tym samym czasie. Jest tak¿e ograniczona iloœæ miejsc na ka¿dy warsztat i na ka¿dy dzieñ konferencji. Czêœæ warsztatów mo¿e byæ p³atna, a czêœæ jest darmowa.
#### Op³aty
Op³ata za udzia³ w konferencji zale¿y nie tylko od zarezerwowanych us³ug, ale tak¿e od terminu ich rezerwacji - jest kilka progów ceny (progi ceny dotycz¹ tylko udzia³u w konferencji, cena warsztatów jest sta³a) i im bli¿ej rozpoczêcia konferencji, tym cena jest wy¿sza (jest tak¿e zni¿ka procentowa dla studentów i w takim wypadku przy rezerwacji trzeba podaæ nr legitymacji studenckiej). Na zap³atê klienci maj¹ tydzieñ od rezerwacji na konferencjê - jeœli do tego czasu nie pojawi siê op³ata, rezerwacja jest anulowana.
#### Raporty
Dla organizatora najbardziej istotne s¹ listy osobowe uczestników na ka¿dy dzieñ konferencji i na ka¿dy warsztat, a tak¿e informacje o p³atnoœciach klientów. Ponadto organizator chcia³by mieæ informacjê o klientach, którzy najczêœciej korzystaj¹ z jego us³ug.
#### Specyfika firmy
Firma organizuje œrednio 2 konferencje w miesi¹cu, ka¿da z nich trwa zwykle 2-3 dni, w tym œrednio w ka¿dym dniu s¹ 4 warsztaty. Na ka¿d¹ konferencjê œrednio rejestruje siê 200 osób. Stworzona baza danych powinna zostaæ wype³niona w takim stopniu, aby odpowiada³a 3-letniej dzia³alnoœci firmy.
#### Wymagane elementy w projekcie
* propozycja funkcji realizowanych przez system - wraz z okreœleniem który
u¿ytkownik jakie funkcje mo¿e realizowaæ (krótka lista)
* projekt bazy danych
* zdefiniowanie bazy danych
* zdefiniowanie warunków integralnoœci: wykorzystanie wartoœci domyœlnych, ustawienie dopuszczalnych zakresów wartoœci, unikalnoœæ wartoœci w polach, czy dane pole mo¿e nie zostaæ wype³nione, z³o¿one warunki integralnoœciowe
* propozycja oraz zdefiniowanie operacji na danych (procedury sk³adowane, triggery, funkcje) - powinny zostaæ zdefiniowane procedury sk³adowane do wprowadzania danych (tak¿e do zmian konfiguracyjnych np. do zmiany iloœci miejsc dla wybranego warsztatu). Nale¿y stworzyæ tak¿e funkcje zwracaj¹ce istotne iloœciowe informacje np. ile jest wolnych miejsc w danym warsztacie. Triggery nale¿y wykorzystaæ do zapewnienia spójnoœci oraz spe³nienia przez system specyficznych wymagañ klienta (np. okreœlona iloœæ miejsc dla danego warsztatu)
* propozycja oraz zdefiniowanie struktury widoków u³atwiaj¹cych dostêp do danych - widoki powinny prezentowaæ dla u¿ytkowników to, co ich najbardziej interesuje. Ponadto powinny zostaæ zdefiniowane widoki dla ró¿nego typu raportów np. najpopularniejsze warsztaty
* propozycja oraz zdefiniowanie indeksów
* wygenerowanie przyk³adowych danych i wype³nienie nimi bazy - konieczny jest generator danych, który powinien wype³niæ bazê w stopniu odpowiadaj¹cym 3-letniej dzia³alnoœci firmy
* propozycja oraz okreœlenie uprawnieñ do danych - nale¿y zaproponowaæ role oraz ich uprawnienia do operacji, widoków, procedur.

#### Sprawozdanie powinno zawieraæ
* opis funkcji systemu wraz z informacj¹, co jaki u¿ytkownik mo¿e wykonywaæ w systemie
* schemat bazy danych (w postaci diagramu) + opis poszczególnych tabel (nazwy pól, typ danych i znaczenie ka¿dego pola, a tak¿e opis warunków integralnoœci, jakie zosta³y zdefiniowane dla danego pola + kod generuj¹cy dan¹ tabelê), informacja, do jakich pól stworzone s¹ indeksy
* spis widoków wraz z kodem, który je tworzy oraz informacj¹ co one przedstawiaj¹
* spis procedur sk³adowanych, triggerów, funkcji wraz z ich kodem i informacj¹ co one robi¹
* informacje odnoœnie wygenerowanych danych (np. ile jest klientów)
* okreœlenie uprawnieñ do danych - opis ról wraz z przyporz¹dkowaniem do jakich elementów dana rola powinna mieæ uprawnienia.

Projekt powinien zostaæ zaimplementowany przy u¿yciu MS SQL Server (chyba ¿e zosta³o inaczej ustalone z prowadz¹cym). 