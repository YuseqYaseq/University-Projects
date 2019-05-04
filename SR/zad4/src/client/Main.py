from BankClient import BankClient
import Bank


def main():
    client = BankClient()
    while True:
        print(">>", end='')
        command = str(input())
        if command == "register":
            print("Insert name")
            name = str(input())
            print("Insert surname")
            surname = str(input())
            print("Insert threshold")
            threshold = int(input())
            print("Insert id")
            login = int(input())
            client.register(name, surname, threshold, login)
        elif command == "login":
            print("Insert login")
            login = int(input())
            print("Insert key")
            key = str(input())
            client.login(login, key)
        elif command == "logout":
            client.logout()
        elif command == "info":
            client.get_info()
        elif command == "insert":
            client.insert_money({Bank.Currency.PLN: 150})
            client.insert_money({Bank.Currency.USD: 150})
        elif command == "loan":
            print("Choose amount")
            amount = int(input())
            print("Choose duration in months")
            duration = int(input())
            client.request_loan(Bank.Currency.EUR, amount, duration)
        elif command == "exit":
            client.logout()
            break
        else:
            print("Unknown command")
        # client.login(1250, "jlgyrxarzl")


if __name__ == '__main__':
    main()
