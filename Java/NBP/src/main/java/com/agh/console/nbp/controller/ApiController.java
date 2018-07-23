package com.agh.console.nbp.controller;

import com.agh.console.nbp.domain.CurrencyRate;
import com.agh.console.nbp.domain.CurrencyTable;
import com.agh.console.nbp.domain.GoldRate;
import com.agh.console.nbp.domain.enums.Item;
import com.agh.console.nbp.network.NbpService;
import com.agh.console.utils.ApiUtils;
import com.agh.console.utils.DateUtils;
import com.agh.console.utils.MathUtil;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import retrofit2.Call;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

import static com.agh.console.utils.ApiUtils.DEBUG_ENABLED;

/**
 * NBP API controller class
 */
public class ApiController implements IApiController {

    /**
     * Wypisuje obowiązującą cenę złota oraz cenę podanej waluty (tabela A) w podanym dniu
     *
     * @param code kod waluty
     * @param date data w formacie YYYY-MM-DD
     */
    public void printGoldAndCurrencyRateForDate(String code, String date) {

        if (!DateUtils.isValidDate(date, Item.GOLD)) {
            System.err.println("Dane archiwalne dla cen złota dostępne są wyłącznie dla okresu poźniejszego od 2 stycznia 2013");
            return;
        }

        System.out.println("1. Cena złota oraz " + code + " w dniu " + date + " :");

        Gson gson = new GsonBuilder().setPrettyPrinting().create();

        NbpService nbpService = ApiUtils.getNbpService();
        Call<List<GoldRate>> call = nbpService.getGoldPriceForDate(date);
        List<GoldRate> goldRateList = null;
        try {
            goldRateList = call.execute().body();
            if (DEBUG_ENABLED) System.out.println(gson.toJson(goldRateList));

            if (goldRateList == null ) {
                System.err.println("Error: API returned empty list for gold rate table");
                return;
            }

            //if (DEBUG_ENABLED) System.out.println(gson.toJson(goldRateList));

            System.out.println("GOLD : " + goldRateList.get(0).getCena());
        } catch (IOException e) {
            e.printStackTrace();
        }

        //**************************************************************************************************************/

        if (!DateUtils.isValidDate(date, Item.CURRENCY)) {
            System.err.println("Dane archiwalne dla kursów walut dostępne są wyłącznie dla okresu poźniejszego od 2 stycznia 2002");
            return;
        }

        Call<CurrencyTable> call2 = ApiUtils.getNbpService().getCurrencyPriceForDate(code, date);
        CurrencyTable currency = null;
        try {
            currency = call2.execute().body();

            if (currency == null) {
                System.err.println("Error: API returned empty currency object");
                return;
            }

            if (DEBUG_ENABLED)System.out.println(gson.toJson(currency));
            System.out.println(code + " : " + currency.getCurrencyRates().get(0).getMid());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Oblicza średnią cenę złota za podany okres
     *
     * @param startDate data początkowa w formacie YYYY-MM-DD
     * @param endDate data końcowa w formacie YYYY-MM-DD
     */
    public void printAvgPriceOfGoldForPeriod(String startDate, String endDate) {
        if (!DateUtils.isValidDate(startDate, Item.GOLD)) {
            System.err.println("2. Dane archiwalne dla cen złota dostępne są wyłącznie dla okresu poźniejszego od " + DateUtils.GOLD_RATE_MIN_DATE);
            return;
        }
/*        else if (!DateUtils.isValidGoldPeriod(startDate, endDate)) {
            System.err.println("Przekroczony limit " + DateUtils.GOLD_MAX_PERIOD + " dni");
            return;
        }*/

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        List<GoldRate> goldRateList = new ArrayList<GoldRate>();

        String startPeriod = startDate;
        String endPeriod = endDate;
        Calendar start = null;
        Calendar end = null;
        Calendar now = null;
        Calendar finalEndDate = null;

        try {
            now = Calendar.getInstance();
            now.setTime(new Date());
            DateUtils.resetTime(now);

            start = Calendar.getInstance();
            start.setTime(sdf.parse(startPeriod));
            DateUtils.resetTime(start);

            end = Calendar.getInstance();
            end.setTime(sdf.parse(startPeriod));
            // NBP API allows only 367-days period, so end date = startDate + 367
            end.add(Calendar.DATE, DateUtils.GOLD_MAX_PERIOD);
            DateUtils.resetTime(end);

            finalEndDate = Calendar.getInstance();
            finalEndDate.setTime(sdf.parse(endDate));
            DateUtils.resetTime(finalEndDate);


            // if end date exceed max period (367 days), set end date to current date
            if (end.after(finalEndDate)) {
                endPeriod = sdf.format(finalEndDate.getTime());
                end.setTime(sdf.parse(endDate));
            } else {
                // NBP API allows only 367-days period, so end date = startDate + 367
                endPeriod = sdf.format(end.getTime());
                //end.add(Calendar.DATE, DateUtils.GOLD_MAX_PERIOD);  // number of days to add
            }
            //endPeriod = end.before(now) ? sdf.format(end.getTime()) : sdf.format(now.getTime());


        } catch (ParseException e) {
            e.printStackTrace();
        }

        while (start.compareTo(finalEndDate) <= 0 && end.compareTo(finalEndDate) <= 0) {
            Gson gson = new GsonBuilder().setPrettyPrinting().create();

            NbpService nbpService = ApiUtils.getNbpService();
            Call<List<GoldRate>> call = nbpService.getGoldPriceForPeriod(startPeriod, endPeriod);
            try {
                List<GoldRate> tempGoldRateList = call.execute().body();

                if (DEBUG_ENABLED) System.out.println(gson.toJson(tempGoldRateList));

                if (tempGoldRateList == null ) {
                    System.err.println("Error: API returned empty list for gold rate table");
                    return;
                }

                goldRateList.addAll(tempGoldRateList);


                // add CURRENCY_MAX_PERIOD_RATES (367 days) to start/end date
                start.add(Calendar.DATE, DateUtils.GOLD_MAX_PERIOD+1);
                end.add(Calendar.DATE, DateUtils.GOLD_MAX_PERIOD+1);

                // if end date exceed max period (367 days), set end date to current date
                if (end.after(finalEndDate)) {
                    endPeriod = sdf.format(finalEndDate.getTime());
                    end.setTime(sdf.parse(endDate));
                } else {
                    // NBP API allows only 367-days period, so end date = startDate + 367
                    endPeriod = sdf.format(end.getTime());
                    //end.add(Calendar.DATE, DateUtils.GOLD_MAX_PERIOD);  // number of days to add
                }

                // initialize startPeriod/endPeriod to next period
                startPeriod = start.compareTo(finalEndDate) <= 0 ? sdf.format(start.getTime()) : startPeriod;
                //endPeriod = end.compareTo(finalEndDate) <= 0 ? sdf.format(end.getTime()) : endPeriod;

            } catch (IOException e) {
                e.printStackTrace();
            } catch (ParseException e) {
                e.printStackTrace();
            }
        }

        if(DEBUG_ENABLED)System.out.println(goldRateList.toString());

        System.out.println("2. Srednia cena złota za okres " + startDate + " ~ " + endDate + " : " + calulateAvgGoldPrice(goldRateList));
    }

    /**
     * Odszukuje walutę (tabela A), której kurs, począwszy od podanego dnia, uległ największym wahaniom
     * (waluta, której amplituda zmian kursu jest największa)
     *
     * @param startDate data w formacie YYYY-MM-DD
     */
    public void printCurrencyWithLargestAmplitude(String startDate) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); //For declaring values in new date objects. use same date format when creating dates

        if (!DateUtils.isValidDate(startDate, Item.CURRENCY)) {
            System.err.println("Dane archiwalne dla kursów walut dostępne są wyłącznie dla okresu poźniejszego od 2 stycznia 2002");
            return;
        }
        String startPeriod = startDate;
        String endPeriod = startDate;
        Calendar start = null;
        Calendar end = null;
        Calendar now = null;
        boolean fin = false;
        try {
            now = Calendar.getInstance();
            now.setTime(new Date());
            DateUtils.resetTime(now);

            start = Calendar.getInstance();
            start.setTime(sdf.parse(startPeriod));
            DateUtils.resetTime(start);

            end = Calendar.getInstance();
            end.setTime(sdf.parse(startPeriod));
            DateUtils.resetTime(end);

            // NBP API allows only 93-days period, so end date = startDate + 93
            end.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_TABLES);  // number of days to add

            if(now.before(end)) {
                end.setTime(now.getTime());
                fin = true;
            }
            // if end date exceed max period (93 days), set end date to current date
            endPeriod = end.before(now) ? sdf.format(end.getTime()) : sdf.format(now.getTime());

        } catch (ParseException e) {
            e.printStackTrace();
        }

        List<CurrencyTable> currencyList = new ArrayList<CurrencyTable>();
        //invoke api request for period between startDate AND TODAY()
        while (end.compareTo(now) <= 0) {
            Call<List<CurrencyTable>> call = ApiUtils.getNbpService().getCurrenciesPriceForPeriod(startPeriod, endPeriod);

            try {
                List<CurrencyTable> tmpCurrencyList = call.execute().body();
                currencyList.addAll(tmpCurrencyList);
                if (DEBUG_ENABLED)
                    System.out.println(new GsonBuilder().setPrettyPrinting().create().toJson(currencyList));

            } catch (IOException e) {
                e.printStackTrace();
            }

            if(fin) break;

            // add CURRENCY_MAX_PERIOD_RATES (367 days) to start/end date
            start.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_TABLES + 1);
            end.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_TABLES + 1);


            if (end.after(now))
            {
                end = now;
                fin = true;
            }
            startPeriod = sdf.format(start.getTime());
            endPeriod = sdf.format(end.getTime());
        }
        System.out.println("3. Waluta o największym wachaniu od dnia " + startDate + ": " + findCodeOfCurrencyWithGreatestDifference(currencyList));
    }

    public String findCodeOfCurrencyWithGreatestDifference(List<CurrencyTable> currencyList)
    {
        //int numOfCurrencies = currencyList.get(0).getCurrencyRates().size();
        Map<String, Double> MinVal = new HashMap<String, Double>();
        Map<String, Double> MaxVal = new HashMap<String, Double>();

        for(int i = 0; i < currencyList.size(); i++)
        {
            List<CurrencyRate> currencyRateList = currencyList.get(i).getCurrencyRates();
            for(int j = 0; j < currencyRateList.size(); ++j)
            {
                String key = currencyRateList.get(j).getCode();
                double val = currencyRateList.get(j).getMid();

                if(!MinVal.containsKey(key))
                {
                    MinVal.put(key, val);
                    MaxVal.put(key, val);
                }
                else
                {
                    if(MinVal.get(key) > val)MinVal.replace(key, val);
                    if(MaxVal.get(key) < val)MaxVal.replace(key, val);
                }
            }
        }
        double maxDiff = 0;
        String foundKey = "";
        for(String key : MinVal.keySet())
        {
            double dif = MaxVal.get(key) - MinVal.get(key);
            if(maxDiff <= dif)
            {
                maxDiff = dif;
                foundKey = key;
            }
        }
        return foundKey;
        /*int numOfCurrencies = currencyList.get(0).getCurrencyRates().size();
        String[] arrayOfCurrenciesCode = new String[numOfCurrencies];
        double[] arrayOfDifferences = new double[numOfCurrencies];
        double[][] arrayOfRates = new double[numOfCurrencies][currencyList.size()];

        for (int i = 0; i < currencyList.size(); i++) {
            System.out.println("1");
            List<CurrencyRate> currencyRateList = currencyList.get(i).getCurrencyRates();
            System.out.println("2");
            for (int j = 0; j < numOfCurrencies; j++) {

                if (i == 0) {
                    try {
                        arrayOfCurrenciesCode[j] = currencyRateList.get(j).getCode();
                    }
                    catch(Exception e){
                        System.out.println("ehhh" + e);}
                }
                System.out.println("3 " + i);
                double val = currencyRateList.get(j).getMid();
                System.out.println("4 " + j);
                arrayOfRates[j][i] = val;
            }
        }

        for (double[] arrayOfRate : arrayOfRates) {
            //System.out.println(Arrays.toString(arrayOfRate));
        }

        for (int i = 0; i < arrayOfRates.length; i++) {
            double maxDiffrence = BigDecimal.valueOf(MathUtil.findMaxDifference(arrayOfRates[i])).setScale(8, RoundingMode.HALF_UP).doubleValue();
            arrayOfDifferences[i] = maxDiffrence;
            //System.out.printf("Max diff for " + arrayOfCurrencies[i] + " :  %.8f", maxDiffrence);
            //System.out.println();
        }

        int indexOfLargestValue = MathUtil.getIndexOfLargestValue(arrayOfDifferences);
        return arrayOfCurrenciesCode[indexOfLargestValue];
        */
    }

    /**
     * Odszukuje walutę (tabela C), której kurs kupna był najmniejszy w podanym dniu
     *
     * @param date data w formacie YYYY-MM-DD
     */
    public void printCurrencyWithSmallestBuyPriceForDate(String date) {

        if (!DateUtils.isValidDate(date, Item.CURRENCY)) {
            System.err.println("Dane archiwalne dla kursów walut dostępne są wyłącznie dla okresu poźniejszego od 2 stycznia 2002");
            return;
        }

        Call<List<CurrencyTable>> call = ApiUtils.getNbpService().getCurrenciesBySellPriceForDate(date);
        List<CurrencyTable> currencyTables = null;
        try {
            currencyTables = call.execute().body();

            if (DEBUG_ENABLED) System.out.println(new GsonBuilder().setPrettyPrinting().create().toJson(currencyTables));

            System.out.println("4. Waluta, której kurs był najmniejszy w dniu " + date + " : " + findCurrencyWithSmallestBuyPrice(currencyTables));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String findCurrencyWithSmallestBuyPrice(List<CurrencyTable> currencyTables) {
        int numOfCurrencies = currencyTables.get(0).getCurrencyRates().size();
        String[] arrayOfCurrenciesCode = new String[numOfCurrencies];
        double[] arrayOfBuyPrices = new double[numOfCurrencies];

        List<CurrencyRate> currencyRateList = currencyTables.get(0).getCurrencyRates();

        for (int j = 0; j < currencyRateList.size(); j++) {

            arrayOfCurrenciesCode[j] = currencyRateList.get(j).getCode();

            double val = currencyRateList.get(j).getBid();
            arrayOfBuyPrices[j] = val;
        }

        int currencyIndex = MathUtil.getIndexOfSmallestValue(arrayOfBuyPrices);
        return arrayOfCurrenciesCode[currencyIndex];
    }

    /**
     * Wypisuje N walut (tabela C), posortowanych względem różnicy pomiędzy ceną sprzedaży a ceną kupna, w podanym dniu
     *
     * @param date data w formacie YYYY-MM-DD
     * @param N liczba walut do wyswietlenia
     */
    public void printSortedCurrenciesForDate(String date, String N) {

        if (!DateUtils.isValidDate(date, Item.CURRENCY)) {
            System.err.println("Dane archiwalne dla kursów walut dostępne są wyłącznie dla okresu poźniejszego od 2 stycznia 2002");
            return;
        }

        Call<List<CurrencyTable>> call = ApiUtils.getNbpService().getCurrenciesBySellPriceForDate(date);
        List<CurrencyTable> currencyTables = null;
        try {
            currencyTables = call.execute().body();
            if (DEBUG_ENABLED) System.out.println(new GsonBuilder().setPrettyPrinting().create().toJson(currencyTables));

            getSortedListOfCurrencies(currencyTables);

            System.out.println("5. Lista pierwszych " + N + " walut, posortowana względem różnicy pomiędzy ceną sprzedaży a ceną kupna dniu " + date);

            //for (CurrencyRate rate : currencyTables.get(0).getCurrencyRates()) {
            //    System.out.print(rate.getCode() + " ");
            //}
            for(int i = 0; i < Integer.parseInt(N); ++i)
            {
                CurrencyRate rate = currencyTables.get(0).getCurrencyRates().get(i);
                System.out.print(rate.getCode() + " ");
            }
            System.out.println();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    /**
     * Dla podanej waluty (tabela A) wypisuje informację kiedy dana waluta była najtańsza, a kiedy najdroższa
     *
     * @param code kod waluty
     */
    public void printHiLowDatesForCurrency(String code)
    {
        printHiLowDatesForCurrency(code, DateUtils.CURRENCY_MIN_DATE);
    }

    public void printHiLowDatesForCurrency(String code, String from) {

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); //For declaring values in new date objects. use same date format when creating dates

        String startPeriod = from;
        String endPeriod = from;
        Calendar start = null;
        Calendar end = null;
        Calendar now = null;

        try {
            now = Calendar.getInstance();
            now.setTime(new Date());
            DateUtils.resetTime(now);

            start = Calendar.getInstance();
            start.setTime(sdf.parse(startPeriod));
            DateUtils.resetTime(start);

            end = Calendar.getInstance();
            end.setTime(sdf.parse(DateUtils.CURRENCY_MIN_DATE));
            DateUtils.resetTime(end);

            // NBP API allows only 93-days period, so end date = startDate + 93
            end.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_RATES);  // number of days to add

            // if end date exceed max period (93 days), set end date to current date
            endPeriod = end.before(now) ? sdf.format(end.getTime()) : sdf.format(now.getTime());

        } catch (ParseException e) {
            e.printStackTrace();
        }

        List<CurrencyRate> currencyTables = new ArrayList<CurrencyRate>();

        //invoke api request for period between DateUtils.CURRENCY_MIN_DATE AND TODAY()
        while (!startPeriod.equals(endPeriod)) {

            Call<CurrencyTable> call = ApiUtils.getNbpService().getCurrencyPriceForPeriod(code, startPeriod, endPeriod);
            try {
                CurrencyTable tempCurrencyTables = call.execute().body();

                if (DEBUG_ENABLED) System.out.println(new GsonBuilder().setPrettyPrinting().create().toJson(tempCurrencyTables));

                if (tempCurrencyTables != null) {
                    currencyTables.addAll(tempCurrencyTables.getCurrencyRates());
                }

            } catch (IOException e) {
                e.printStackTrace();
            }

            // add CURRENCY_MAX_PERIOD_RATES (367 days) to start/end date
            start.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_RATES+1);
            end.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_RATES+1);

            // initialize startPeriod/endPeriod to next period
            startPeriod = start.compareTo(now) < 0 ? sdf.format(start.getTime()) : sdf.format(now.getTime());
            endPeriod = end.compareTo(now) < 0 ? sdf.format(end.getTime()) : sdf.format(now.getTime());
        }

        System.out.println("6. [" + code + "] Najniższy kurs : " + findDateForMinRate(currencyTables) + ", najwyższy kurs : " + findDateForMaxRate(currencyTables));
    }


    /**
     * Rysuje (w trybie tekstowym) wspólny (dla wszystkich tygodni) wykres zmian ceny podanej waluty (tabela A) w
     * układzie tygodniowym
     *
     *
     */
    public void printChartOfPriceChanges(String code, String date1, String date2) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); //For declaring values in new date objects. use same date format when creating dates

        if (!DateUtils.isValidDate(date1, Item.CURRENCY) || !DateUtils.isValidDate(date2, Item.CURRENCY)) {
            System.err.println("Dane archiwalne dla kursów walut dostępne są wyłącznie dla okresu poźniejszego od 2 stycznia 2002");
            return;
        }
        String startPeriod = date1;
        String endPeriod = date1;
        Calendar start = null;
        Calendar end = null;
        Calendar now = null;
        boolean fin = false;

        try {
            now = Calendar.getInstance();
            now.setTime(sdf.parse(date2));
            DateUtils.resetTime(now);

            start = Calendar.getInstance();
            start.setTime(sdf.parse(startPeriod));
            DateUtils.resetTime(start);

            end = Calendar.getInstance();
            end.setTime(sdf.parse(startPeriod));
            DateUtils.resetTime(end);

            //Set start date to  Monday and end date to Friday
            start.add(Calendar.DATE, 2 - start.get(Calendar.DAY_OF_WEEK));
            now.add(Calendar.DATE, 6 - now.get(Calendar.DAY_OF_WEEK));
            startPeriod = sdf.format(start.getTime());
            ////////////////

            // NBP API allows only 93-days period, so end date = startDate + 93
            end.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_TABLES);  // number of days to add

            if(now.before(end))
            {
                end.setTime(now.getTime());
                fin = true;
            }

            // if end date exceed max period (93 days), set end date to current date
            endPeriod = end.before(now) ? sdf.format(end.getTime()) : sdf.format(now.getTime());

        } catch (ParseException e) {
            e.printStackTrace();
        }

        List<CurrencyRate> currencyList = new ArrayList<CurrencyRate>();
        //invoke api request for period between startDate AND TODAY()
        while (end.compareTo(now) <= 0) {
            Call<CurrencyTable> call = ApiUtils.getNbpService().getCurrencyPriceForPeriod(code, startPeriod, endPeriod);

            try {
                CurrencyTable tmpCurrencyList = call.execute().body();
                currencyList.addAll(tmpCurrencyList.getCurrencyRates());
                //currencyList.addAll(tmpCurrencyList);
                if (DEBUG_ENABLED)
                    System.out.println(new GsonBuilder().setPrettyPrinting().create().toJson(currencyList));

            } catch (IOException e) {
                e.printStackTrace();
            }

            if(fin)break;

            // add CURRENCY_MAX_PERIOD_RATES (367 days) to start/end date
            start.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_TABLES + 1);
            end.add(Calendar.DATE, DateUtils.CURRENCY_MAX_PERIOD_TABLES + 1);


            if (end.after(now))
            {
                end = now;
                fin = true;
            }
            startPeriod = sdf.format(start.getTime());
            endPeriod = sdf.format(end.getTime());
        }
        System.out.println("7. Wykres waluty [" + code + "] dla tygodni od " + date1 + " do " + date2 + ": ");
        PrintChart(currencyList);
    }

    public void PrintChart(List<CurrencyRate> l)
    {
        for(int currentDay = 2; currentDay < 7; currentDay++) {
            int no = 0;
            for (CurrencyRate cr : l) {

                try {
                    SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                    Calendar c = Calendar.getInstance();
                    c.setTime(sdf.parse(cr.getEffectiveDate()));
                    if (c.get(Calendar.DAY_OF_WEEK) == currentDay)
                    {
                        no++;
                        switch(currentDay)
                        {
                            case 2: System.out.print("Pon"+no+" "); break;
                            case 3: System.out.print("Wto"+no+" "); break;
                            case 4: System.out.print("Sro"+no+" "); break;
                            case 5: System.out.print("Czw"+no+" "); break;
                            case 6: System.out.print("Pia"+no+" "); break;
                        }
                        for(int howMany = 0; howMany < (int)Math.round(cr.getMid()*20); howMany++)
                        {
                            System.out.print((char)3);
                        }
                        System.out.println(" " + cr.getMid());
                    }
                } catch (Exception e) {
                    System.out.println("The date is incorrect!");
                }
            }
        }
    }
    /****************
     * Helper methods
     ***************/

    private Long calulateAvgGoldPrice(List<GoldRate> goldRateList) {
        long avgPrice = 0;

        for (GoldRate goldRate : goldRateList) {
            avgPrice += goldRate.getCena();
        }

        return avgPrice / goldRateList.size();
    }

    public void getSortedListOfCurrencies(List<CurrencyTable> currencyTables) {
        Collections.sort(currencyTables.get(0).getCurrencyRates());
    }

    private String findDateForMaxRate(List<CurrencyRate> currencyTables) {
        int minIdx = 0;
        for (int i = 1; i < currencyTables.size(); i++) {
            if ( currencyTables.get(i).getMid() > currencyTables.get(minIdx).getMid() ) minIdx = i;
        }

        return currencyTables.get(minIdx).getEffectiveDate();
    }

    private String findDateForMinRate(List<CurrencyRate> currencyTables) {
        int maxIdx = 0;
        for (int i = 1; i < currencyTables.size(); i++) {
            if ( currencyTables.get(i).getMid() < currencyTables.get(maxIdx).getMid() ) maxIdx = i;
        }

        return currencyTables.get(maxIdx).getEffectiveDate();
    }
}
