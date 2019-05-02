
import grpc

from proto_out.exchange_pb2_grpc import CurrencyExchangeStub
from proto_out.exchange_pb2 import *


class ExchangeClient(object):

    def run(self):
        with grpc.insecure_channel(
                target='localhost:50051',
                options=[('grpc.lb_policy_name', 'pick_first'),
                         ('grpc.enable_retries', 0), ('grpc.keepalive_timeout_ms',
                                                      10000)]) as channel:
            stub = CurrencyExchangeStub(channel)
            try:
                response = stub.GetValue(CurrencyArguments(ReferenceCurrency=PLN, Currencies=[PLN, CHF, USD, JPY]))
                for resp in response:
                    print(resp)
            except grpc.RpcError as e:
                print(e)
