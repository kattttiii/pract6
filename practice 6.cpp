#include <iostream>
#include <stdexcept>
using namespace std;
// банковский счет
class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;
public:
    // конструктор
    BankAccount(int accNumber, double initialBalance) {
        this->accountNumber = accNumber;
        this->balance = initialBalance;
        this->interestRate = 0.0;
    }
    //внесение денег
    void deposit(double amount) {
        if (amount < 0) {
            throw   invalid_argument("Сумма не может быть отрицательной");
        }
        this->balance += amount;
    }
    // снятие денег
    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма не может быть отрицательной");
        }
        if (amount > this->balance) {
            throw runtime_error("Недостаточно средств на балансе");
        }
        this->balance -= amount;
    }
    //получение баланса
    double getBalance() const {
        return this->balance;
    }
    //расчет процента
    double getInterest() const {
        return this->balance * this->interestRate / 1.12;
    }
    //процентная ставка
    void setInterestRate(double rate) {
        this->interestRate = rate;
    }
    int getAccountNumber() const {
        return this->accountNumber;
    }
    //перевод денег с одного счета на другой
    static bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
        try {
            fromAccount.withdraw(amount);
            toAccount.deposit(amount);
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }
};

void printMenu() {
    std::cout << "1. Внести депозит на счет 1" << std::endl;
    std::cout << "2. Снять средства со счета" << std::endl;
    std::cout << "3. Перевести средства между счетами" << std::endl;
    std::cout << "4. Внести депозит на счет 2" << std::endl;
    std::cout << "5. Выход из программы" << std::endl;
    std::cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    BankAccount account1(800000, 0.0);
    BankAccount account2(800000, 0.0);
    int choice;
    double amount;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите сумму для внесения депозита на счет 1: ";
            std::cin >> amount;
            try {
                account1.deposit(amount);
                std::cout << "Остаток средств на счету 1 после внесения депозита: " << account1.getBalance() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        case 2:
            std::cout << "Введите сумму для снятия со счета 1: ";
            std::cin >> amount;
            try {
                account1.withdraw(amount);
                std::cout << "Остаток средств на счету 1 после снятия: " << account1.getBalance() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        case 3:
            std::cout << "Введите сумму для перевода со счета 2 на счет 1: ";
            std::cin >> amount;
            BankAccount::transfer(account2, account1, amount);
            std::cout << "Остаток на счету 1 после перевода: " << account1.getBalance() << std::endl;
            std::cout << "Остаток на счету 2 после перевода: " << account2.getBalance() << std::endl;
            break;
        case 4:
            std::cout << "Введите сумму для внесения депозита на счет 2: ";
            std::cin >> amount;
            try {
                account2.deposit(amount);
                std::cout << "Остаток средств на счету 2 после внесения депозита: " << account2.getBalance() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        case 5:
            std::cout << "Выход из меню" << std::endl;
            break;
        default:
            std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            break;
        }
    } while (choice != 5);

    return 0;
}