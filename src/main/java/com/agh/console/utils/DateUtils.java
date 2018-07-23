package com.agh.console.utils;

import com.agh.console.nbp.domain.enums.Item;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class DateUtils {

    public static final String CURRENCY_MIN_DATE = "2002-01-02";
    public static final String GOLD_RATE_MIN_DATE = "2013-01-02";
    public static final int GOLD_MAX_PERIOD = 367;
    public static final int CURRENCY_MAX_PERIOD_RATES = 367;
    public static final int CURRENCY_MAX_PERIOD_TABLES = 93;

    public static boolean isValidDate(String stringDate, Item item) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); //For declaring values in new date objects. use same date format when creating dates

        try {
            Date date = sdf.parse(stringDate);
            Date maxPeriod = item == Item.CURRENCY ? sdf.parse(CURRENCY_MIN_DATE) : sdf.parse(GOLD_RATE_MIN_DATE);

            // check if given stringDate is earlier than maxPeriod
            return date.after(maxPeriod) || (date.compareTo(maxPeriod) == 0);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static boolean isValidGoldPeriod(String startDate, String endDate) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); //For declaring values in new date objects. use same date format when creating dates

        try {
            Date date1 = sdf.parse(startDate);
            Date date2 = sdf.parse(endDate);

            long difference = date2.getTime() - date1.getTime();
            float daysBetween = (difference / (1000*60*60*24));

            return daysBetween < GOLD_MAX_PERIOD;
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static String addCurrencyMaxPeriod(String date, int maxPeriod) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); //For declaring values in new date objects. use same date format when creating dates

        try {
            Calendar c = Calendar.getInstance();
            c.setTime(sdf.parse(date));
            c.add(Calendar.DATE, maxPeriod);  // number of days to add
            String newDate =  sdf.format(c.getTime());  // return new date
            //System.out.println("Max period: " + newDate);
            return newDate;  // return new date
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return sdf.format(new Date());
    }

    public static void resetTime(Calendar date) {
        date.set(Calendar.HOUR_OF_DAY, 0);
        date.set(Calendar.MINUTE, 0);
        date.set(Calendar.SECOND, 0);
        date.set(Calendar.MILLISECOND, 0);
    }
}
