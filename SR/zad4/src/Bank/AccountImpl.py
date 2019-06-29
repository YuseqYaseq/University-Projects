import Bank
from tinydb import TinyDB, Query
from tinydb.operations import set


def map_currency(str):
    if str == 'PLN':
        return Bank.Currency.PLN
    if str == 'EUR':
        return Bank.Currency.EUR
    if str == 'USD':
        return Bank.Currency.USD
    if str == 'GBP':
        return Bank.Currency.GBP
    if str == 'CHF':
        return Bank.Currency.CHF
    if str == 'JPY':
        return Bank.Currency.JPY
    raise NotImplementedError(str)


def map_currency_to_int(str):
    if str == 'PLN':
        return 0
    if str == 'EUR':
        return 1
    if str == 'USD':
        return 2
    if str == 'GBP':
        return 3
    if str == 'CHF':
        return 4
    if str == 'JPY':
        return 5
    raise NotImplementedError(str)


class AccountImpl(Bank.Account):

    def __init__(self, db_name, supported_currencies, exchange_client):
        self.db = TinyDB(db_name)
        self.users = self.db.table('users')
        self.supported_currencies = supported_currencies
        self.exchange_client = exchange_client

    def requestLoan(self, currency, amount, num_of_months, context=None):
        if not self.ok_credentials(context.ctx['id'], context.ctx['key']):
            raise Bank.IncorrectCredentials()

        if not self.user[0]['is_premium'] or self.user[0]['has_loan']:
            raise Bank.LoanNotAllowed()
        rates = self.exchange_client.get_exchange_rate()
        return_amount = amount * 1.3
        return_amount_in_native = return_amount / rates[currency]

        self.user[0]['has_loan'] = True
        self.user[0]['loan_return_native'] = return_amount_in_native
        self.user[0]['loan_return_foreign'] = return_amount

        loan_info = Bank.LoanInfo()
        loan_info.amountInNativeCurrency = return_amount_in_native
        loan_info.amountInForeignCurrency = return_amount
        return loan_info

    def getAccountInfo(self, context=None):
        if not self.ok_credentials(context.ctx['id'], context.ctx['key']):
            raise Bank.IncorrectCredentials()
        account_info = Bank.AccountInfo()
        account_info.isPremium = bool(self.user[0]['is_premium'])
        account_info.hasLoan = False
        # account_info.loanInfo =
        account_info.funds = {}
        funds = self.user[0]['funds']
        for (k, v) in funds.items():
            new_key = map_currency(k)
            account_info.funds[new_key] = v
        return account_info

    def insertMoney(self, funds, context=None):
        if not self.ok_credentials(context.ctx['id'], context.ctx['key']):
            raise Bank.IncorrectCredentials()

        user_funds = self.user[0]['funds']
        for (k, v) in funds.items():
            user_funds[str(k)] += v
        self.db.update(set('funds', user_funds), self.user)

    def withdrawMoney(self, funds, context=None):
        if not self.ok_credentials(context.ctx['id'], context.ctx['key']):
            raise Bank.IncorrectCredentials()

        raise NotImplementedError

    def ok_credentials(self, id, key):
        self.user = Query()
        self.user = self.users.search(self.user.id == int(id))
        if self.user == []:
            return False
        if self.user[0]['key'] != key:
            return False
        return True
