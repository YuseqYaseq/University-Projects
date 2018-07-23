package com.agh.console.utils;

import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

import static com.agh.console.utils.ApiUtils.DEBUG_ENABLED;

public class RetrofitClient {

    private static Retrofit retrofit;

    private RetrofitClient() {}

    public static Retrofit getClient(String url) {
        if (retrofit == null) {
            OkHttpClient.Builder builder = new OkHttpClient().newBuilder();

            if (DEBUG_ENABLED) {
                HttpLoggingInterceptor interceptor = new HttpLoggingInterceptor();
                interceptor.setLevel(HttpLoggingInterceptor.Level.BASIC);
                builder.addInterceptor(interceptor);
            }

            OkHttpClient client = builder.build();
            retrofit = new Retrofit.Builder()
                    .baseUrl(url)
                    .client(client)
                    .addConverterFactory(GsonConverterFactory.create())
                    .build();
        }
        return retrofit;
    }

}
