# Podstawy baz danych - projekt i implementacja systemu bazodanowego
## System zarz�dzania konferencjami
#### Opis problemu
Projekt dotyczy systemu wspomagania dzia�alno�ci firmy organizuj�cej konferencje.
#### Og�lne informacje
Firma organizuje konferencje, kt�re mog� by� jedno- lub kilkudniowe. Klienci powinni m�c rejestrowa� si� na konferencje za pomoc� systemu www. Klientami mog� by� zar�wno indywidualne osoby jak i firmy, natomiast uczestnikami konferencji s� osoby (firma nie musi podawa� od razu przy rejestracji listy uczestnik�w - mo�e zarezerwowa� odpowiedni� ilo�� miejsc na okre�lone dni oraz na warsztaty, natomiast na 2 tygodnie przed rozpocz�ciem musi te dane uzupe�ni� - a je�li sama nie uzupe�ni do tego czasu, to pracownicy dzwoni� do firmy i ustalaj� takie informacje). Ka�dy uczestnik konferencji otrzymuje identyfikator imienny (+ ew. informacja o firmie na nim). Dla konferencji kilkudniowych, uczestnicy mog� rejestrowa� si� na dowolne z tych dni.
#### Warsztaty
Ponadto z konferencj� zwi�zane s� warsztaty, na kt�re uczestnicy tak�e mog� si� zarejestrowa� - musz� by� jednak zarejestrowani tego dnia na konferencj�, aby m�c w nich uczestniczy�. Kilka warsztat�w mo�e trwa� r�wnocze�nie, ale uczestnik nie mo�e zarejestrowa� si� na wi�cej ni� jeden warsztat, kt�ry trwa w tym samym czasie. Jest tak�e ograniczona ilo�� miejsc na ka�dy warsztat i na ka�dy dzie� konferencji. Cz�� warsztat�w mo�e by� p�atna, a cz�� jest darmowa.
#### Op�aty
Op�ata za udzia� w konferencji zale�y nie tylko od zarezerwowanych us�ug, ale tak�e od terminu ich rezerwacji - jest kilka prog�w ceny (progi ceny dotycz� tylko udzia�u w konferencji, cena warsztat�w jest sta�a) i im bli�ej rozpocz�cia konferencji, tym cena jest wy�sza (jest tak�e zni�ka procentowa dla student�w i w takim wypadku przy rezerwacji trzeba poda� nr legitymacji studenckiej). Na zap�at� klienci maj� tydzie� od rezerwacji na konferencj� - je�li do tego czasu nie pojawi si� op�ata, rezerwacja jest anulowana.
#### Raporty
Dla organizatora najbardziej istotne s� listy osobowe uczestnik�w na ka�dy dzie� konferencji i na ka�dy warsztat, a tak�e informacje o p�atno�ciach klient�w. Ponadto organizator chcia�by mie� informacj� o klientach, kt�rzy najcz�ciej korzystaj� z jego us�ug.
#### Specyfika firmy
Firma organizuje �rednio 2 konferencje w miesi�cu, ka�da z nich trwa zwykle 2-3 dni, w tym �rednio w ka�dym dniu s� 4 warsztaty. Na ka�d� konferencj� �rednio rejestruje si� 200 os�b. Stworzona baza danych powinna zosta� wype�niona w takim stopniu, aby odpowiada�a 3-letniej dzia�alno�ci firmy.
#### Wymagane elementy w projekcie
* propozycja funkcji realizowanych przez system - wraz z okre�leniem kt�ry
u�ytkownik jakie funkcje mo�e realizowa� (kr�tka lista)
* projekt bazy danych
* zdefiniowanie bazy danych
* zdefiniowanie warunk�w integralno�ci: wykorzystanie warto�ci domy�lnych, ustawienie dopuszczalnych zakres�w warto�ci, unikalno�� warto�ci w polach, czy dane pole mo�e nie zosta� wype�nione, z�o�one warunki integralno�ciowe
* propozycja oraz zdefiniowanie operacji na danych (procedury sk�adowane, triggery, funkcje) - powinny zosta� zdefiniowane procedury sk�adowane do wprowadzania danych (tak�e do zmian konfiguracyjnych np. do zmiany ilo�ci miejsc dla wybranego warsztatu). Nale�y stworzy� tak�e funkcje zwracaj�ce istotne ilo�ciowe informacje np. ile jest wolnych miejsc w danym warsztacie. Triggery nale�y wykorzysta� do zapewnienia sp�jno�ci oraz spe�nienia przez system specyficznych wymaga� klienta (np. okre�lona ilo�� miejsc dla danego warsztatu)
* propozycja oraz zdefiniowanie struktury widok�w u�atwiaj�cych dost�p do danych - widoki powinny prezentowa� dla u�ytkownik�w to, co ich najbardziej interesuje. Ponadto powinny zosta� zdefiniowane widoki dla r�nego typu raport�w np. najpopularniejsze warsztaty
* propozycja oraz zdefiniowanie indeks�w
* wygenerowanie przyk�adowych danych i wype�nienie nimi bazy - konieczny jest generator danych, kt�ry powinien wype�ni� baz� w stopniu odpowiadaj�cym 3-letniej dzia�alno�ci firmy
* propozycja oraz okre�lenie uprawnie� do danych - nale�y zaproponowa� role oraz ich uprawnienia do operacji, widok�w, procedur.

#### Sprawozdanie powinno zawiera�
* opis funkcji systemu wraz z informacj�, co jaki u�ytkownik mo�e wykonywa� w systemie
* schemat bazy danych (w postaci diagramu) + opis poszczeg�lnych tabel (nazwy p�l, typ danych i znaczenie ka�dego pola, a tak�e opis warunk�w integralno�ci, jakie zosta�y zdefiniowane dla danego pola + kod generuj�cy dan� tabel�), informacja, do jakich p�l stworzone s� indeksy
* spis widok�w wraz z kodem, kt�ry je tworzy oraz informacj� co one przedstawiaj�
* spis procedur sk�adowanych, trigger�w, funkcji wraz z ich kodem i informacj� co one robi�
* informacje odno�nie wygenerowanych danych (np. ile jest klient�w)
* okre�lenie uprawnie� do danych - opis r�l wraz z przyporz�dkowaniem do jakich element�w dana rola powinna mie� uprawnienia.

Projekt powinien zosta� zaimplementowany przy u�yciu MS SQL Server (chyba �e zosta�o inaczej ustalone z prowadz�cym). 