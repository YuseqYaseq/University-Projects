package exchange;

import exchange.proto_out.Currency;
import exchange.proto_out.CurrencyArguments;
import exchange.proto_out.CurrencyExchangeGrpc.CurrencyExchangeImplBase;
import exchange.proto_out.CurrencyResult;
import exchange.proto_out.CurrencyType;
import io.grpc.stub.StreamObserver;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.logging.Logger;

public class CurrencyExchangeImpl extends CurrencyExchangeImplBase {

    private static final int NUM_OF_CURRENCIES = 6;
    private static final int NUM_OF_ITERATIONS = 1000;
    private static final int CHANGE_INVERVAL = 2000;
    private static final int SEND_INVERVAL = 2000;

    private Random random = new Random();
    private Logger logger = Logger.getLogger(CurrencyExchangeImpl.class.getName());
    private double[][] currencyValues;

    public CurrencyExchangeImpl() {
        initCurrenciesValues();
        startCurrencyFluctuation();
    }

    private void initCurrenciesValues() {
        currencyValues = new double[NUM_OF_CURRENCIES][NUM_OF_CURRENCIES];
        for(int i = 0; i < NUM_OF_CURRENCIES; ++i) {
            for(int j = 0; j < NUM_OF_CURRENCIES; ++j) {
                if(i == j) {
                    currencyValues[i][j] = 1;
                } else {
                    currencyValues[i][j] = Math.random();
                    currencyValues[j][i] = 1 / currencyValues[i][j];
                }
            }
        }
    }

    private void startCurrencyFluctuation() {
        new Thread(() -> {
            try {
                while(true) {
                    Thread.sleep(CHANGE_INVERVAL);
                    int currency = Math.abs(random.nextInt()) % NUM_OF_CURRENCIES;
                    double value = (random.nextDouble() - 0.5) / 10;
                    for (int i = 0; i < NUM_OF_CURRENCIES; ++i) {
                        if (i != currency) {
                            currencyValues[i][currency] += value;
                            currencyValues[currency][i] = 1 / currencyValues[i][currency];
                        }
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                logger.warning(e.toString());
            }
        }).start();
    }

    @Override
    public void getValue(CurrencyArguments request, StreamObserver<CurrencyResult> responseObserver) {
        logger.info("Info requested for " + request.getReferenceCurrency());
        for(int its = 0; its < NUM_OF_ITERATIONS; ++its) {
            List<Currency> currencyInfo = new ArrayList<>();
            for (int i = 0; i < request.getCurrenciesCount(); ++i) {
                int currency_index = request.getCurrenciesValue(i);
                currencyInfo.add(Currency.newBuilder()
                        .setType(CurrencyType.forNumber(currency_index))
                        .setValue(currencyValues[request.getReferenceCurrency().getNumber()][currency_index])
                        .build());
            }
            CurrencyResult result = CurrencyResult.newBuilder()
                    .addAllResults(currencyInfo)
                    .build();
            responseObserver.onNext(result);
            try {
                Thread.sleep(SEND_INVERVAL);
            } catch (Exception e) {
                e.printStackTrace();
                logger.warning(e.toString());
            }
        }
        responseObserver.onCompleted();
    }

}
