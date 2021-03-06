CREATE PACKAGE lab1 AS

  TYPE WYCIECZKI_OSOBY_REC IS RECORD (
  id_wycieczki INT,
  kraj VARCHAR2(50),
  data_wycieczki DATE,
  nazwa_wycieczki VARCHAR2(50),
  imie VARCHAR2(50),
  nazwisko VARCHAR2(50),
  status_rezerwacji CHAR(1));

  TYPE WYCIECZKI_OSOBY_TAB IS TABLE OF WYCIECZKI_OSOBY_REC;


  TYPE WYCIECZKI_REC IS RECORD (
  id_wycieczki INT,
  kraj VARCHAR2(50),
  data_wycieczki DATE,
  nazwa_wycieczki VARCHAR2(50),
  liczba_miejsc INT,
  liczba_wolnych_miejsc INT);

  TYPE WYCIECZKI_TAB IS TABLE OF WYCIECZKI_REC;
  -----------------------------------
  FUNCTION UCZESTNICY_WYCIECZKI
    (pv_id_wycieczki IN INT)
    RETURN WYCIECZKI_OSOBY_TAB PIPELINED;

  FUNCTION REZERWACJE_OSOBY
    (pv_id_osoby IN INT)
    RETURN WYCIECZKI_OSOBY_TAB PIPELINED;

  FUNCTION PRZYSZLE_REZERWACJE_OSOBY
    (pv_id_osoby IN INT)
    RETURN WYCIECZKI_OSOBY_TAB PIPELINED;

  FUNCTION DOSTEPNE_WYCIECZKI
    (pv_kraj VARCHAR2, pv_data_od DATE, pv_data_do DATE)
    RETURN WYCIECZKI_TAB PIPELINED;
END;


CREATE PACKAGE BODY lab1 AS
  ------------------------------------------------------------------------------------------------------------------------

  FUNCTION UCZESTNICY_WYCIECZKI
    (pv_id_wycieczki IN INT)
    RETURN WYCIECZKI_OSOBY_TAB PIPELINED IS
    check1                      NUMBER; --czy wycieczka o podanym ID istnieje?
    v_exc_niepoprawna_wycieczka VARCHAR2(4000) := 'Exception: wycieczka jest niepoprawna';
    BEGIN

      SELECT COUNT(*)
          INTO check1 FROM wycieczki w WHERE w.id_wycieczki = pv_id_wycieczki;

      IF check1 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20001, v_exc_niepoprawna_wycieczka);
      END IF;

      FOR i IN (SELECT w.id_wycieczki, w.kraj, w.data, w.nazwa, o.imie, o.nazwisko, r.status
                FROM wycieczki w
                       JOIN rezerwacje r ON w.id_wycieczki = r.id_wycieczki
                       JOIN osoby o ON r.id_osoby = o.id_osoby
                WHERE w.id_wycieczki = pv_id_wycieczki)
      LOOP
        PIPE ROW (i);
      END LOOP;
    END;

  ------------------------------------------------------------------------------------------------------------------------

  FUNCTION REZERWACJE_OSOBY
    (pv_id_osoby IN INT)
    RETURN WYCIECZKI_OSOBY_TAB PIPELINED IS
    check1           NUMBER; --czy osoba o podanym ID istnieje?
    v_exc_brak_osoby VARCHAR2(4000) := 'Exception: osoba o tym id nie istnieje';
    BEGIN

      SELECT COUNT(*)
          INTO check1 FROM osoby o WHERE o.id_osoby = pv_id_osoby;

      IF check1 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20002, v_exc_brak_osoby);
      END IF;

      FOR i IN (SELECT w.id_wycieczki, w.kraj, w.data, w.nazwa, o.imie, o.nazwisko, r.status
                FROM wycieczki w
                       JOIN rezerwacje r ON w.id_wycieczki = r.id_wycieczki
                       JOIN osoby o ON r.id_osoby = o.id_osoby
                WHERE o.id_osoby = pv_id_osoby)
      LOOP
        PIPE ROW (i);
      END LOOP;
    END;

  ------------------------------------------------------------------------------------------------------------------------

  FUNCTION PRZYSZLE_REZERWACJE_OSOBY
    (pv_id_osoby IN INT)
    RETURN WYCIECZKI_OSOBY_TAB PIPELINED IS
    check1           NUMBER; --czy osoba o podanym ID istnieje?
    v_exc_brak_osoby VARCHAR2(4000) := 'Exception: osoba o tym id nie istnieje';
    BEGIN

      SELECT COUNT(*)
          INTO check1 FROM osoby o WHERE o.id_osoby = pv_id_osoby;

      IF check1 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20002, v_exc_brak_osoby);
      END IF;

      FOR i IN (SELECT w.id_wycieczki, w.kraj, w.data, w.nazwa, o.imie, o.nazwisko, r.status
                FROM wycieczki w
                       JOIN rezerwacje r ON w.id_wycieczki = r.id_wycieczki
                       JOIN osoby o ON r.id_osoby = o.id_osoby
                WHERE o.id_osoby = pv_id_osoby
                  AND w.data > TRUNC(SYSDATE))
      LOOP
        PIPE ROW (i);
      END LOOP;
    END;

  ------------------------------------------------------------------------------------------------------------------------

  FUNCTION DOSTEPNE_WYCIECZKI
    (pv_kraj VARCHAR2, pv_data_od DATE, pv_data_do DATE)
    RETURN WYCIECZKI_TAB PIPELINED IS

    BEGIN
      FOR i IN (SELECT *
                FROM dostepne_wycieczki dw
                WHERE (dw.data BETWEEN pv_data_od AND pv_data_do)
                  AND dw.kraj = pv_kraj)
      LOOP
        PIPE ROW (i);
      END LOOP;
    END;

  ----------------------

  FUNCTION DOSTEPNE_WYCIECZKI2
    (pv_kraj VARCHAR2, pv_data_od DATE, pv_data_do DATE)
    RETURN WYCIECZKI_TAB PIPELINED IS

    BEGIN
      FOR i IN (SELECT *
                FROM dostepne_wycieczki2 dw
                WHERE (dw.data BETWEEN pv_data_od AND pv_data_do)
                  AND dw.kraj = pv_kraj)
      LOOP
        PIPE ROW (i);
      END LOOP;
    END;

END;

