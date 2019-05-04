
from ExchangeClient import ExchangeClient
from BankServer import BankServer
from proto_out.exchange_pb2 import *


def main():
    native_currency = PLN
    supported_currencies = [PLN, USD, EUR, GBP, CHF, JPY]
    exchange_client = ExchangeClient("localhost", 5060, native_currency, supported_currencies)
    bank_server = BankServer("localhost", 10000, "db.json", native_currency, supported_currencies, exchange_client)
    exchange_client.run()


if __name__ == '__main__':
        main()
