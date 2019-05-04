from threading import Thread

import Ice
from AccountImpl import AccountImpl
from FactoryImpl import FactoryImpl

_default_account_servant_name = "Account"
_default_factory_servant_name = "Factory"


class BankServer(object):

    def add_account_servant(self, account_identifier=_default_account_servant_name):
        account = AccountImpl(self.db_name, self.supported_currencies, self.exchange_client)
        self.adapter.add(account, self.communicator.stringToIdentity(account_identifier))
        return account


    def _start_service(self, name, port):
        self.communicator = Ice.initialize()
        self.adapter = self.communicator.createObjectAdapterWithEndpoints(name, "default -p " + str(port))
        self.adapter.add(FactoryImpl(self.db_name, self.supported_currencies, self),
                         self.communicator.stringToIdentity(_default_factory_servant_name))
        self.adapter.activate()
        self.communicator.waitForShutdown()

    def __init__(self, name, port, db_name, native_currency, supported_currencies, exchange_client):
        self.db_name = db_name
        self.native_currency = native_currency
        self.supported_currencies = supported_currencies
        self.exchange_client = exchange_client
        thread = Thread(target=self._start_service, args=(name, port))
        thread.start()
