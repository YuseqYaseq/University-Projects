
import grpc

from proto_out.exchange_pb2_grpc import CurrencyExchangeStub
from proto_out.exchange_pb2 import *
import Bank

class ExchangeClient(object):

    def get_exchange_rate(self):
        return self.exchange_rate

    def run(self):
        with grpc.insecure_channel(
                target=self.address + ':' + str(self.port),
                options=[('grpc.lb_policy_name', 'pick_first'),
                         ('grpc.enable_retries', 0), ('grpc.keepalive_timeout_ms',
                                                      10000)]) as channel:
            stub = CurrencyExchangeStub(channel)
            try:
                response = stub.GetValue(CurrencyArguments(ReferenceCurrency=self.native_currency,
                                                           Currencies=self.available_currencies))
                for resp in response:
                    for currency in resp.Results:
                        self.exchange_rate[Bank.Currency.valueOf(currency.Type)] = currency.Value
            except grpc.RpcError as e:
                print(e)

    def __init__(self, host, port, native_currency, available_currencies):
        self.exchange_rate = {}
        self.address = host
        self.port = port
        self.native_currency = native_currency
        self.available_currencies = available_currencies
