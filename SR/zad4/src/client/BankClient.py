from threading import Thread

import Bank
import Ice


_default_account_servant_name = "Account"
_default_factory_servant_name = "Factory"


class BankClient(object):

    def __init__(self, factory_servant_name=_default_factory_servant_name, port=10000):
        try:
            self.port = port
            self.communicator = Ice.initialize()
            self.base = self.communicator.stringToProxy(factory_servant_name + ":default -p " + str(port))
            self.factory = Bank.FactoryPrx.checkedCast(self.base)
            self.account = None
            self.key = None
            self.id = None
            self.failed = False
            if not self.factory:
                print("Failed to connect to factory servant!")
            thread = Thread(target=self._start_service)
            thread.start()
        except Exception:
            print("Failed to connect to bank service! Try again later.")
            self.communicator.destroy()
            self.failed = True

    def _start_service(self):
        self.communicator.waitForShutdown()

    def register(self, name, surname, threshold, id):
        try:
            registration_info = self.factory.createAccount(name, surname, threshold, id)
            self.id = id
            self.key = registration_info.key
            is_premium = registration_info.isPremium
            self.base = self.communicator.stringToProxy(str(id) + ":default -p " + str(self.port))
            self.account = Bank.AccountPrx.checkedCast(self.base)

            if is_premium:
                type = "PREMIUM"
            else:
                type = "STANDARD"
            print("You created a new %s account" % type)
            print("Your assigned key is: " + str(self.key))

        except Bank.UserAlreadyExists:
            print("Unfortunately user with this id is already registered!")

    def request_loan(self, currency, amount, num_of_months):
        if not self.account:
            print("You have to log in first!")
            return
        try:
            loan_info = self.account.requestLoan(currency, amount, num_of_months,
                                                 context={'id': str(self.id), 'key': self.key})
            print("You received a loan. It will cost {0} in native currency and {1} in {2}.".format(
                  loan_info.amountInNativeCurrency,
                  loan_info.amountInForeignCurrency,
                  str(currency)))
        except Bank.IncorrectCredentials:
            print("Incorrect credentials!")
        except Bank.LoanNotAllowed:
            print("You either have standard account or have already received a loan!")

    def insert_money(self, funds):
        if not self.account:
            print("You have to log in first!")

        try:
            self.account.insertMoney(funds, context={'id': str(self.id), 'key': self.key})
            print("ok")
        except Bank.IncorrectCredentials:
            print("Incorrect credentials!")

    def withdraw_money(self, funds):
        if not self.account:
            print("You have to log in first!")
            return
        try:
            self.account.withdrawMoney(funds, context={'id': str(self.id), 'key': self.key})
            print("ok")
        except Bank.IncorrectCredentials:
            print("Incorrect credentials!")
        except Bank.InsufficientFunds:
            print("Insufficient funds!")

    def get_info(self):
        if not self.account:
            print("You have to log in first!")
            return
        try:
            account_info = self.account.getAccountInfo(context={'id': str(self.id), 'key': self.key})
            print(str(account_info))  # TODO
        except Bank.IncorrectCredentials:
            print("Incorrect credentials!")

    def login(self, id, key):
        try:
            self.factory.login(id, context={'key': key})
            self.id = id
            self.key = key
            self.base = self.communicator.stringToProxy(str(id) + ":default -p " + str(self.port))
            self.account = Bank.AccountPrx.checkedCast(self.base)
            print("Login successful")
        except Bank.IncorrectCredentials:
            print("Incorrect credentials!")

    def logout(self):
        if self.account:
            self.factory.logout(context={'id': str(self.id)})
            self.account = None
            self.key = None
            self.id = None
