

  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Adam', 'Kowalski', '87654321', 'tel: 6623');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Jan', 'Nowak', '12345678', 'tel: 2312, dzwonić po 18.00');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Dzozef', 'Dzasek', '12345678', 'al Jana Pawla 2');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('qwer', 'sadf', '12345678', 'tel: 2000');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Krzysztof', 'Krafczyk', '4543545', 'tel: 6623');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Mateusz', 'Lewandowski', '7886578', 'tel: 6623');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Zbigniew', 'Włodecki', '3143214', 'tel: 6623');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Jarosław', 'Mucha', '8647567', 'tel: 6623');
  INSERT INTO osoby (imie, nazwisko, pesel, kontakt)
  VALUES ('Magdalena', 'Środa', '87654365321', 'tel: 6623');


  INSERT INTO wycieczki (nazwa, kraj, data, opis, liczba_miejsc)
  VALUES ('Wycieczka do Paryza', 'Francja', TO_DATE('2016-01-01', 'YYYY-MM-DD'), 'Ciekawa wycieczka ...', 3);
  INSERT INTO wycieczki (nazwa, kraj, data, opis, liczba_miejsc)
  VALUES ('Piękny Kraków', 'Polska', TO_DATE('2017-02-03', 'YYYY-MM-DD'), 'Najciekawa wycieczka ...', 2);
  INSERT INTO wycieczki (nazwa, kraj, data, opis, liczba_miejsc)
  VALUES ('Wieliczka', 'Polska', TO_DATE('2017-03-03', 'YYYY-MM-DD'), 'Zadziwiająca kopalnia ...', 2);
  INSERT INTO wycieczki (nazwa, kraj, data, opis, liczba_miejsc)
  VALUES ('Przyszla wycieczka',
          'Korea',
          TO_DATE('2019-06-06', 'YYYY-MM-DD'),
          'Wycieczka ktora jeszcze sie nie odbyla',
          5);
  INSERT INTO wycieczki (nazwa, kraj, data, opis, liczba_miejsc)
  VALUES ('Przyszla wycieczka bez miejsc', 'Japonia', TO_DATE('2019-06-06', 'YYYY-MM-DD'), 'nie ma juz miejsc', 1);
  INSERT INTO wycieczki (nazwa, kraj, data, opis, liczba_miejsc)
  VALUES ('Wycieczka tuz tuz', 'Luxemburg', TO_DATE('2018-11-01', 'YYYY-MM-DD'), 'rezerwacje sa anulowane', 1);



  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (1, 1, 'N');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (2, 2, 'P');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (21, 21, 'Z');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (21, 22, 'Z');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (22, 21, 'Z');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (23, 21, 'N');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (21, 41, 'N');
  INSERT INTO rezerwacje (id_wycieczki, id_osoby, status)
  VALUES (21, 43, 'N');


  INSERT INTO wycieczki2 (id_wycieczki, nazwa, kraj, data, opis, liczba_miejsc)
  VALUES (3, 'Wycieczka do Paryza', 'Francja', TO_DATE('2016-01-01', 'YYYY-MM-DD'), 'Ciekawa wycieczka ...', 3);
  INSERT INTO wycieczki2 (id_wycieczki, nazwa, kraj, data, opis, liczba_miejsc)
  VALUES (4, 'Piękny Kraków', 'Polska', TO_DATE('2017-02-03', 'YYYY-MM-DD'), 'Najciekawa wycieczka ...', 2);
  INSERT INTO wycieczki2 (id_wycieczki, nazwa, kraj, data, opis, liczba_miejsc)
  VALUES (5, 'Wieliczka', 'Polska', TO_DATE('2017-03-03', 'YYYY-MM-DD'), 'Zadziwiająca kopalnia ...', 2);
  INSERT INTO wycieczki2 (id_wycieczki, nazwa, kraj, data, opis, liczba_miejsc)
  VALUES (21,
          'Przyszla wycieczka',
          'Korea',
          TO_DATE('2019-06-06', 'YYYY-MM-DD'),
          'Wycieczka ktora jeszcze sie nie odbyla',
          5);
  INSERT INTO wycieczki2 (id_wycieczki, nazwa, kraj, data, opis, liczba_miejsc)
  VALUES (22, 'Przyszla wycieczka bez miejsc', 'Japonia', TO_DATE('2019-06-06', 'YYYY-MM-DD'), 'nie ma juz miejsc', 1);
  INSERT INTO wycieczki2 (id_wycieczki, nazwa, kraj, data, opis, liczba_miejsc)
  VALUES (23, 'Wycieczka tuz tuz', 'Luxemburg', TO_DATE('2018-11-01', 'YYYY-MM-DD'), 'rezerwacje sa anulowane', 1);
