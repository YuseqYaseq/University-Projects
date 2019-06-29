
from AccountImpl import map_currency_to_int
from ExchangeClient import ExchangeClient
from BankServer import BankServer
from proto_out.exchange_pb2 import *
import Bank


def main():
    native_currency = map_currency_to_int(sys.argv[1])
    supported_currencies = list(map(map_currency_to_int, sys.argv[2].split(",")))
    exchange_port = int(sys.argv[3])
    client_port = int(sys.argv[4])
    exchange_client = ExchangeClient("localhost", exchange_port, native_currency, supported_currencies)
    bank_server = BankServer("localhost", client_port, "db.json", native_currency, supported_currencies, exchange_client)
    exchange_client.run()


if __name__ == '__main__':
        main()
