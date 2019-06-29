import random
import string

import Ice

import Bank
from tinydb import TinyDB, Query

_premium_account_threshold = 1000


class FactoryImpl(Bank.Factory):

    def __init__(self, db_name, supported_currencies, bank_server):
        self.db = TinyDB(db_name)
        self.users = self.db.table('users')
        self.supported_currencies = supported_currencies
        self.bank_server = bank_server

    def login(self, id, context=None):
        user = Query()
        user = self.users.search(user.id == id)
        if user == []:
            raise Bank.IncorrectCredentials()
        if user[0]['key'] != context.ctx['key']:
            raise Bank.IncorrectCredentials()

        self.bank_server.add_account_servant(str(id))

    def logout(self, context=None):
        identity = Ice.stringToIdentity(context.ctx['id'])
        self.bank_server.remove_account_servant(identity)

    def createAccount(self, name, surname, threshold, id, context=None):
        if self.user_already_exists(id):
            raise Bank.UserAlreadyExists()

        if threshold > _premium_account_threshold:
            is_premium = True
        else:
            is_premium = False
        key = self.generate_random_string()
        new_user_info = {'id': id,
                         'name': name,
                         'surname': surname,
                         'is_premium': is_premium,
                         'has_loan': False,
                         'loan_return_native': 0.0,
                         'loan_return_foregin': 0.0,
                         'key': key,
                         'funds': {}}
        for currency in self.supported_currencies:
            new_user_info['funds'][str(Bank.Currency.valueOf(currency))] = 0

        self.users.insert(new_user_info)
        registration_info = Bank.RegistrationInfo()
        self.bank_server.add_account_servant(str(id))
        registration_info.key = key
        registration_info.isPremium = is_premium
        return registration_info

    def user_already_exists(self, id):
        user = Query()
        if self.users.search(user.id == id) == []:
            return False
        return True

    @staticmethod
    def generate_random_string(length=10):
        letters = string.ascii_lowercase
        return ''.join(random.choice(letters) for _ in range(length))
