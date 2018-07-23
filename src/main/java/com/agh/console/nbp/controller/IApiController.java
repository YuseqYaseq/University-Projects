package com.agh.console.nbp.controller;

public interface IApiController {

    void printGoldAndCurrencyRateForDate(String code, String date);

    void printAvgPriceOfGoldForPeriod(String startDate, String endDate);

    void printCurrencyWithLargestAmplitude(String date);

    void printCurrencyWithSmallestBuyPriceForDate(String date);

    void printSortedCurrenciesForDate(String date, String N);

    void printHiLowDatesForCurrency(String code);

    void printChartOfPriceChanges(String code, String date1, String date2);

}
