package com.agh.console.nbp.network;

import com.agh.console.nbp.domain.CurrencyTable;
import com.agh.console.nbp.domain.GoldRate;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Headers;
import retrofit2.http.Path;

import java.util.List;

public interface NbpService {

    //*********************  API dla notowań kursu złota  ************************/

    /**
     * Cena złota opublikowana w dniu 2013-01-02
     *
     * @param date Data notowania
     */
    @Headers("Accept: application/json")
    @GET("cenyzlota/{date}")
    Call<List<GoldRate>> getGoldPriceForDate(@Path("date") String date);


    /**
     * Seria cen złota opublikowanych w zakresie dat począwszy od 2013-01-02
     *
     * @param startdate data początkowa okresu
     * @param enddate data końcowa okresu
     */
    @Headers("Accept: application/json")
    @GET("cenyzlota/{startdate}/{enddate}")
    Call<List<GoldRate>> getGoldPriceForPeriod(@Path("startdate") String startdate, @Path("enddate") String enddate);

    //*********************  API dla notowań kursu walut  ************************/

    /**
     * Wypisuje obowiązującą cenę podanej waluty (tabela A) w podanym dniu
     *
     * @param currency kod waluty
     * @param date data, dla której wyliczony ma zostać kurs
     */
    @Headers("Accept: application/json")
    @GET("exchangerates/rates/a/{code}/{date}")
    Call<CurrencyTable> getCurrencyPriceForDate(@Path("code") String currency, @Path("date") String date);


    /**
     * Seria tabel typu A z przedziału dat od 2012-01-01 do 2012-01-31
     *
     * @param startdate data początkowa okresu
     * @param enddate data końcowa okresu
     */
    @Headers("Accept: application/json")
    @GET("exchangerates/tables/a/{startdate}/{enddate}/")
    Call<List<CurrencyTable>> getCurrenciesPriceForPeriod(@Path("startdate") String startdate, @Path("enddate") String enddate);


    /**
     * Notowanie kursu kupna i sprzedaży w podanym dniu
     *
     * @param date data, dla której ma zostać wyświetlona tabela kursów
     */
    @Headers("Accept: application/json")
    @GET("exchangerates/tables/c/{date}/")
    Call<List<CurrencyTable>> getCurrenciesBySellPriceForDate(@Path("date") String date);


    /**
     * Seria kursów średnich waluty z przedziału dat od 2012-01-01 do dziś
     *
     * @param code kod waluty
     * @param startdate data początkowa okresu
     * @param enddate data końcowa okresu
     */
    @Headers("Accept: application/json")
    @GET("exchangerates/rates/a/{code}/{startdate}/{enddate}/")
    Call<CurrencyTable> getCurrencyPriceForPeriod(@Path("code") String code, @Path("startdate") String startdate, @Path("enddate") String enddate);
}
