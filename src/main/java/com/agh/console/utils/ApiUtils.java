package com.agh.console.utils;

import com.agh.console.krs.network.KrsService;
import com.agh.console.nbp.network.NbpService;

public class ApiUtils {

    public static final String NBP_BASE_URL = "http://api.nbp.pl/api/";
    public static final String KRS_BASE_URL = "https://mojepanstwo.pl/api/krs/";

    public static final String CURRENCY_MAX_PERIOD = "2002-01-2";
    public static final String GOLD_RATE_MAX_PERIOD = "2013-01-2";
    public static final int MAX_PERIOD = 93;

    public static final boolean DEBUG_ENABLED = false;

    public static NbpService getNbpService() {
        return RetrofitClient.getClient(NBP_BASE_URL).create(NbpService.class);
    }

    /**
     * Example of usage another service e.g. KRS
     */
    public static KrsService getKrsService() {
        return RetrofitClient.getClient(KRS_BASE_URL).create(KrsService.class);
    }
}
