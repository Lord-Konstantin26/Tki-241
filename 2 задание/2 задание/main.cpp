#include <iostream>
#include <vector>
#include <memory>
#include "../decision/Client.h"
#include "../decision/Product.h"
#include "../decision/Store.h"
#include "../decision/Warehouse.h"
#include "../decision/Invoice.h"

using namespace std;
using namespace bakery;

enum class MenuOption {
    SHOW_ASSORTMENT = 1,
    SHOW_ORDERS,
    SHOW_SALES,
    SHOW_DISCOUNT_CLIENTS,
    SHOW_STATISTICS,
    EXIT
};

void showSalesForPeriod(const vector<Invoice>& invoices,
    const string& startDate,
    const string& endDate) {
    cout << "\n════════════════════════════════════\n";
    cout << "ПРОДАЖИ ЗА ПЕРИОД:\n";
    cout << "с " << startDate << " по " << endDate << "\n";
    cout << "════════════════════════════════════\n";

    bool foundSales = false;
    double totalRevenue = 0;
    int totalInvoices = 0;

    for (const auto& invoice : invoices) {
        if (invoice.isInPeriod(startDate, endDate)) {
            cout << invoice.toString() << endl;
            foundSales = true;
            totalRevenue += invoice.getTotalAmount();
            totalInvoices++;
        }
    }

    if (foundSales) {
        cout << "════════════════════════════════════\n";
        cout << "СТАТИСТИКА ЗА ПЕРИОД:\n";
        cout << "Количество накладных: " << totalInvoices << "\n";
        cout << "Общая выручка: " << totalRevenue << " руб.\n";
        cout << "════════════════════════════════════\n";
    }
    else {
        cout << "Продаж за указанный период не найдено.\n";
        cout << "════════════════════════════════════\n";
    }
}

void showClientsWithDiscount(const vector<shared_ptr<Client>>& clients) {
    cout << "\n════════════════════════════════════\n";
    cout << "КЛИЕНТЫ СО СКИДКОЙ:\n";
    cout << "════════════════════════════════════\n";

    bool foundClients = false;
    for (const auto& client : clients) {
        if (client->hasDiscountStatus()) {
            cout << "  • " << client->toString() << endl;
            foundClients = true;
        }
    }

    if (!foundClients) {
        cout << "Клиентов со скидкой не найдено.\n";
    }
    cout << "════════════════════════════════════\n";
}

void displayMenu() {
    cout << "\n════════════════════════════════════\n";
    cout << "ГЛАВНОЕ МЕНЮ\n";
    cout << "════════════════════════════════════\n";
    cout << "1. Показать ассортимент на складе\n";
    cout << "2. Показать заказы магазинов\n";
    cout << "3. Показать продажи за период\n";
    cout << "4. Показать клиентов со скидкой\n";
    cout << "5. Показать общую статистику\n";
    cout << "6. Выход\n";
    cout << "════════════════════════════════════\n";
    cout << "Выберите пункт меню: ";
}

int main() {
    cout << "════════════════════════════════════════════════════════════\n";
    cout << "           СИСТЕМА СКЛАДСКОГО УЧЕТА\n";
    cout << "════════════════════════════════════════════════════════════\n\n";

    Warehouse warehouse;

    auto bread = make_shared<Product>("PRD001", "Хлеб Бородинский", 50.0, 100);
    auto milk = make_shared<Product>("PRD002", "Молоко 3.2%", 80.0, 80);
    auto cheese = make_shared<Product>("PRD003", "Сыр Российский", 300.0, 40);
    auto butter = make_shared<Product>("PRD004", "Масло сливочное", 150.0, 30);

    warehouse.addProduct(bread.get());
    warehouse.addProduct(milk.get());
    warehouse.addProduct(cheese.get());
    warehouse.addProduct(butter.get());

    auto supermarket = make_shared<Store>("STR001", "Супермаркет 'Продукты'");
    auto minimarket = make_shared<Store>("STR002", "Минимаркет 'У дома'");

    supermarket->addOrder(bread.get(), 20);
    supermarket->addOrder(milk.get(), 15);
    supermarket->addOrder(cheese.get(), 10);

    minimarket->addOrder(bread.get(), 10);
    minimarket->addOrder(butter.get(), 5);
    minimarket->addOrder(milk.get(), 8);

    vector<shared_ptr<Client>> clients;
    clients.push_back(make_shared<Client>("CL001", "ИП Петров", 5.0));    
    clients.push_back(make_shared<Client>("CL002", "ООО 'Вектор'", 10.0)); 
    clients.push_back(make_shared<Client>("CL003", "Кафе 'Бриз'", 0.0));   

    vector<Invoice> invoices;

    Invoice inv1("INV001", "2024-01-15", clients[0].get());
    inv1.addItem(bread.get(), 10, bread->getPrice());
    inv1.addItem(milk.get(), 5, milk->getPrice());
    invoices.push_back(inv1);

    Invoice inv2("INV002", "2024-01-20", clients[1].get());
    inv2.addItem(cheese.get(), 8, cheese->getPrice());
    inv2.addItem(butter.get(), 3, butter->getPrice());
    invoices.push_back(inv2);

    Invoice inv3("INV003", "2024-01-25", clients[2].get());
    inv3.addItem(bread.get(), 5, bread->getPrice());
    inv3.addItem(milk.get(), 4, milk->getPrice());
    invoices.push_back(inv3);

    bool running = true;

    while (running) {
        displayMenu();

        int choice;
        cin >> choice;

        MenuOption option = static_cast<MenuOption>(choice);

        switch (option) {
        case MenuOption::SHOW_ASSORTMENT:
            cout << "\n════════════════════════════════════\n";
            cout << "АССОРТИМЕНТ НА СКЛАДЕ:\n";
            cout << "════════════════════════════════════\n";
            cout << warehouse.getCurrentAssortment() << endl;
            break;

        case MenuOption::SHOW_ORDERS:
            cout << "\n════════════════════════════════════\n";
            cout << "ЗАКАЗЫ МАГАЗИНОВ:\n";
            cout << "════════════════════════════════════\n";
            cout << supermarket->getOrderedProducts() << endl;
            cout << minimarket->getOrderedProducts() << endl;
            break;

        case MenuOption::SHOW_SALES:
            cout << "\n════════════════════════════════════\n";
            cout << "ВЫБОР ПЕРИОДА ПРОДАЖ:\n";
            cout << "════════════════════════════════════\n";

            int periodChoice;
            cout << "1. Январь 2024 (01-31)\n";
            cout << "2. Последние продажи\n";
            cout << "Выберите период: ";
            cin >> periodChoice;

            switch (periodChoice) {
            case 1:
                showSalesForPeriod(invoices, "2024-01-01", "2024-01-31");
                break;
            case 2:
                showSalesForPeriod(invoices, "2024-01-20", "2024-01-31");
                break;
            default:
                cout << "Неверный выбор!\n";
            }
            break;

        case MenuOption::SHOW_DISCOUNT_CLIENTS:
            showClientsWithDiscount(clients);
            break;

        case MenuOption::SHOW_STATISTICS:
            cout << "\n════════════════════════════════════\n";
            cout << "ОБЩАЯ СТАТИСТИКА СИСТЕМЫ:\n";
            cout << "════════════════════════════════════\n";
            cout << "• Количество клиентов: " << clients.size() << "\n";
            cout << "• Количество магазинов: 2\n";
            cout << "• Количество товарных позиций: " << warehouse.getProductCount() << "\n";
            cout << "• Количество накладных: " << invoices.size() << "\n";
            cout << "• Всего товаров на складе: " << warehouse.getTotalItemsCount() << " шт.\n";

            double totalRevenue = 0;
            for (const auto& invoice : invoices) {
                totalRevenue += invoice.getTotalAmount();
            }
            cout << "• Общая выручка: " << totalRevenue << " руб.\n";
            cout << "════════════════════════════════════\n";
            break;

        case MenuOption::EXIT:
            cout << "\n════════════════════════════════════\n";
            cout << "Спасибо за использование системы!\n";
            cout << "════════════════════════════════════\n";
            running = false;
            break;

        default:
            cout << "\nНеверный выбор. Попробуйте снова.\n";
        }

        if (running) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}