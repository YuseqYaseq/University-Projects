module Bank {

    enum Currency {
        PLN, EUR, USD, GBP, CHF, JPY
    }

    struct LoanInfo {
        long amountInNativeCurrency;
        long amountInForeignCurrency;
    }

    dictionary <Currency, long> Funds;

    struct AccountInfo {
        bool isPremium;
        bool hasLoan;
        LoanInfo loanInfo;
        Funds funds;
    }

    exception LoanNotAllowed {}
    exception CurrencyNoctSupported {}
    exception IncorrectCredentials {}
    exception UserAlreadyExists {}
    exception InsufficientFunds {}

    interface Account {
        LoanInfo requestLoan(Currency currency, long amount, int numOfMonths) throws
            IncorrectCredentials, LoanNotAllowed;
        idempotent AccountInfo getAccountInfo() throws IncorrectCredentials;
        void insertMoney(Funds funds) throws IncorrectCredentials;
        void withdrawMoney(Funds funds) throws IncorrectCredentials, InsufficientFunds;
    };

    struct RegistrationInfo {
            bool isPremium;
            string key;
        }

    interface Factory {
        RegistrationInfo createAccount(string name, string surname, long threshold, long id) throws UserAlreadyExists;
        void login(long id) throws IncorrectCredentials;
        void logout();
    }
}
