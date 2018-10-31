

  CREATE OR REPLACE TRIGGER sprawdz_dodanie_rezerwacji_i_zaloguj
    BEFORE INSERT
    ON rezerwacje
    FOR EACH ROW
    DECLARE
      check1                      NUMBER; --1 GDY, TAKA WYCIECZKA ISTNIEJE, JESZCZE SIE NIE ODBYLA
      -- ORAZ SA JESZCZE WOLNE MIEJSCA
      check2                      NUMBER; --1 GDY TAKA OSOBA ISTNIEJE
      v_exc_niepoprawna_wycieczka VARCHAR2(4000) := 'Exception: wycieczka jest niepoprawna';
      v_exc_brak_osoby            VARCHAR2(4000) := 'Exception: osoba o tym id nie istnieje';

    BEGIN
      SELECT count(*)
          INTO check1
      FROM wycieczki_miejsca w
      WHERE w.id_wycieczki = :new.id_wycieczki
        AND w.data > TRUNC(SYSDATE)
        AND w.liczba_wolnych_miejsc > 0;

      IF check1 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20001, v_exc_niepoprawna_wycieczka);
      END IF;

      SELECT count(*)
          INTO check2 FROM osoby o WHERE o.id_osoby = :new.id_osoby;

      IF check2 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20002, v_exc_brak_osoby);
      END IF;

      INSERT INTO rezerwacje_log (nr_rezerwacji, data, status) VALUES (:new.nr_rezerwacji, SYSDATE, 'N');
    END;

  CREATE TRIGGER sprawdz_zmiane_statusu_i_zaloguj
    BEFORE UPDATE
    ON rezerwacje
    FOR EACH ROW
    DECLARE
      check1                         NUMBER; --czy istnieje podana rezerwacja?
      check2                         NUMBER; --czy wycieczka sie juz odbyla?
      check3                         NUMBER; --czy mozna zmienic na dany stan
      v_exc_brak_wycieczki           VARCHAR(4000) := 'Exception: wycieczka o tym id nie istnieje';
      v_exc_wycieczka_juz_sie_odbyla VARCHAR(4000) := 'Exception: wycieczka juz sie odbyla';
      v_exc_rezerwacja_zle_przejscie VARCHAR(4000) := 'Exception: nie mozna zmienic rezerwacji na ten status';
    BEGIN
      SELECT COUNT(*)
          INTO check1 FROM rezerwacje r WHERE r.nr_rezerwacji = :new.nr_rezerwacji;

      IF check1 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20004, v_exc_brak_wycieczki);
      END IF;

      SELECT COUNT(*)
          INTO check2
      FROM rezerwacje r
             JOIN wycieczki w ON w.id_wycieczki = r.id_wycieczki
      WHERE w.data > TRUNC(SYSDATE)
        AND r.nr_rezerwacji = :new.nr_rezerwacji;

      IF check2 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20005, v_exc_wycieczka_juz_sie_odbyla);
      END IF;

      IF (:old.status = 'N' AND :new.status IN ('P', 'Z', 'A'))
         OR (:old.status = 'P' AND :new.status IN ('Z', 'A'))
         OR (:old.status = 'Z' AND :new.status = 'A')
      THEN
        SELECT 1
            INTO check3 FROM dual;
      ELSE
        SELECT 0
            INTO check3 FROM dual;
      END IF;

      IF check3 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20006, v_exc_rezerwacja_zle_przejscie);
      END IF;

      INSERT INTO rezerwacje_log (nr_rezerwacji, data, status) VALUES (:new.nr_rezerwacji, SYSDATE, :new.status);
    END;

  CREATE

  CREATE TRIGGER zabron_usuwac_rezerwacje
    BEFORE DELETE
    ON rezerwacje

    BEGIN
      RAISE_APPLICATION_ERROR(-20010, 'Exception: nie mozna usuwac rezerwacji');
    END;

  CREATE TRIGGER zaktualizuj_liczbe_wolnych_miejsc2
    AFTER INSERT
    ON rezerwacje
    FOR EACH ROW
    BEGIN
      IF :new.status != 'A'
      THEN
        UPDATE wycieczki2 w
        SET liczba_wolnych_miejsc = liczba_wolnych_miejsc - 1
        WHERE w.id_wycieczki = :new.id_wycieczki;
      END IF;
    END;

  CREATE TRIGGER zaktualizuj_liczbe_wolnych_miejsc2_dla_zmiany_statusu
    AFTER UPDATE
    ON rezerwacje
    FOR EACH ROW
    BEGIN
      IF :new.status = 'A' AND :old.status != 'A'
      THEN
        UPDATE wycieczki2 w
        SET liczba_wolnych_miejsc = liczba_wolnych_miejsc + 1
        WHERE w.id_wycieczki = :new.id_wycieczki;
      END IF;
    END;

  CREATE TRIGGER sprawdz_i_popraw_liczbe_miejsc_w_wycieczce
    BEFORE INSERT OR UPDATE
    ON wycieczki2
    FOR EACH ROW
    DECLARE
      check1                      NUMBER; --czy wycieczka o podanym ID istnieje?
      check2                      NUMBER; --czy zapisalo sie na wycieczke mniej osob, niz nasz nowy limit miejsc?
      v_exc_niepoprawna_wycieczka VARCHAR2(4000) := 'Exception: wycieczka jest niepoprawna';
      v_exc_za_duzo_miejsc        VARCHAR2(4000) := 'Exception: zarezerwowano za duzo miejsc';
    BEGIN
      SELECT COUNT(*)
          INTO check1 FROM wycieczki2 w WHERE w.id_wycieczki = :new.id_wycieczki;

      IF check1 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20001, v_exc_niepoprawna_wycieczka);
      END IF;

      SELECT COUNT(*)
          INTO check2
      FROM wycieczki_miejsca2 wm
      WHERE wm.id_wycieczki = :new.id_wycieczki
        AND wm.liczba_miejsc - wm.liczba_wolnych_miejsc < :new.id_wycieczki;

      IF check2 = 0
      THEN
        RAISE_APPLICATION_ERROR(-20003, v_exc_za_duzo_miejsc);
      END IF;

      UPDATE wycieczki2 SET liczba_wolnych_miejsc = liczba_wolnych_miejsc + (:new.liczba_miejsc - liczba_miejsc)
      WHERE :new.id_wycieczki = id_wycieczki;
    END;


