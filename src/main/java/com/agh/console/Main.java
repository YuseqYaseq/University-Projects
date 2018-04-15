package com.agh.console;

import com.agh.console.nbp.controller.ApiController;
import gnu.getopt.Getopt;

import java.io.IOException;

public final class Main {

    public static void main(String[] args) throws IOException {
        Getopt g = new Getopt("Main", args, "1:2:3:4:5:6:7:");
        ApiController apiController = new ApiController();
        int c;
        boolean noarg = true;
        String s1, s2, s3;
        while ((c = g.getopt()) != -1) {
            noarg = false;
            s1 = g.getOptarg();
            switch (c) {
                case 49/*1*/:
                    g.getopt();
                    s2 = g.getOptarg();
                    apiController.printGoldAndCurrencyRateForDate(s1, s2);
                    break;
                case 50/*2*/:
                    g.getopt();
                    s2 = g.getOptarg();
                    apiController.printAvgPriceOfGoldForPeriod(s1, s2);
                    break;
                case 51/*3*/:
                    apiController.printCurrencyWithLargestAmplitude(s1);
                    break;
                case 52/*4*/:
                    apiController.printCurrencyWithSmallestBuyPriceForDate(s1);
                    break;
                case 53/*5*/:
                    g.getopt();
                    s2 = g.getOptarg();
                    apiController.printSortedCurrenciesForDate(s1, s2);
                    break;
                case 54/*6*/:
                    apiController.printHiLowDatesForCurrency(s1);
                    break;
                case 55/*7*/:
                    g.getopt();
                    s2 = g.getOptarg();
                    g.getopt();
                    s3 = g.getOptarg();
                    apiController.printChartOfPriceChanges(s1, s2, s3);
                    break;
            }
        }
        if (noarg) {
            System.out.println("System do analizy kursow walut i zlota.");
            System.out.println("Stworzony przez: Jozef Jasek 2018");
            System.out.println("Uzycie z linii komend:");
            System.out.println("-1 arg1 -1 arg2 : Wypisuje dla podanego dnia obowiazujaca cene zlota oraz cene podanej waluty. arg1 - kod waluty; arg2 - data");
            System.out.println("-2 arg1 -2 arg2 : Oblicza srednia cene zlota za podany okres. arg1 - data poczatkowa; arg2 - data końcowa");
            System.out.println("-3 arg1 : Odszukuje walute, ktorej kurs, poczawszy od podanego dnia, ulegl najwiekszym wahaniom. arg1 - data, od ktorej rozpoczynamy liczenie");
            System.out.println("-4 arg1 : Odszukuje walute, ktorej kurs kupna byl najmniejszy w podanym dniu. arg1 - data");
            System.out.println("-5 arg1 -5 N : Wypisuje N walut posortowanych wzgledem roznicy pomiedzy cena sprzedazy a cena kupna w podanym dniu. arg1 - data; N - liczba walut");
            System.out.println("-6 arg1 : Dla podanej waluty wypisuje informacje kiedy dana waluta byla najtańsza a kiedy najdrozsza. arg1 - kod waluty");
            System.out.println("-7 arg1 -7 arg2 -7 arg3 : Rysuje wykres zmian ceny podanej waluty w ukladzie tygodniowym. arg1 - kod waluty; arg2 - data poczatkowa; arg3 - data końcowa");
            System.out.println("Daty podawane wylacznie w formacie YYYY-MM-DD");
            System.out.println("Przykladowe uzycie: java -jar AGH.jar -1 \"EUR\" -1 \"2013-10-05\" -3 \"2015-04-04\" -7 \"EUR\" -7 \"2010-01-01\" -7 \"2010-01-03\"");
            System.out.println("(Jednokrotne wywolanie funkcji pierwszej, trzeciej, siodmej)");
        }
    }
}