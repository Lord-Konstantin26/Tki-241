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

// Enum для главного меню
enum class MainMenuOption {
    SHOW_ASSORTMENT = 1,
    SHOW_ORDERS,
    SHOW_SALES,
    SHOW_DISCOUNT_CLIENTS,
    SHOW_STATISTICS,
    MANAGE_CLIENTS,
    MANAGE_PRODUCTS,
    EXIT
};

// Enum для меню продаж
enum class SalesMenuOption {
    PERIOD_JANUARY = 1,
    PERIOD_RECENT,
    CUSTOM_PERIOD,
    BACK
};

// Enum для меню управления клиентами
enum class ClientMenuOption {
    SHOW_ALL_CLIENTS = 1,
    ADD_CLIENT,
    MODIFY_DISCOUNT,
    SHOW_CLIENT_HISTORY,
    BACK
};

// Enum для меню управления продуктами
enum class ProductMenuOption {
    SHOW_ALL_PRODUCTS = 1,
    ADD_PRODUCT,
    UPDATE_STOCK,
    SHOW_LOW_STOCK,
    BACK
};

// Функции для работы с меню
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

// Функция для отображения меню продаж
void showSalesMenu(vector<Invoice>& invoices) {
    bool inSalesMenu = true;

    while (inSalesMenu) {
        cout << "\n════════════════════════════════════\n";
        cout << "МЕНЮ ПРОДАЖ:\n";
        cout << "════════════════════════════════════\n";
        cout << "1. Продажи за январь 2024 (01-31)\n";
        cout << "2. Последние продажи (20-31 января)\n";
        cout << "3. Задать произвольный период\n";
        cout << "4. Вернуться в главное меню\n";
        cout << "════════════════════════════════════\n";
        cout << "Выберите пункт меню: ";

        int choice;
        cin >> choice;

        SalesMenuOption option = static_cast<SalesMenuOption>(choice);

        switch (option) {
        case SalesMenuOption::PERIOD_JANUARY:
            showSalesForPeriod(invoices, "2024-01-01", "2024-01-31");
            break;

        case SalesMenuOption::PERIOD_RECENT:
            showSalesForPeriod(invoices, "2024-01-20", "2024-01-31");
            break;

        case SalesMenuOption::CUSTOM_PERIOD: {
            string startDate, endDate;
            cout << "Введите начальную дату (ГГГГ-ММ-ДД): ";
            cin >> startDate;
            cout << "Введите конечную дату (ГГГГ-ММ-ДД): ";
            cin >> endDate;
            showSalesForPeriod(invoices, startDate, endDate);
            break;
        }

        case SalesMenuOption::BACK:
            inSalesMenu = false;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }

        if (inSalesMenu && option != SalesMenuOption::BACK) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    }
}

// Функция для отображения меню управления клиентами
void showClientMenu(vector<shared_ptr<Client>>& clients, vector<Invoice>& invoices) {
    bool inClientMenu = true;

    while (inClientMenu) {
        cout << "\n════════════════════════════════════\n";
        cout << "УПРАВЛЕНИЕ КЛИЕНТАМИ:\n";
        cout << "════════════════════════════════════\n";
        cout << "1. Показать всех клиентов\n";
        cout << "2. Добавить нового клиента\n";
        cout << "3. Изменить скидку клиента\n";
        cout << "4. Показать историю покупок клиента\n";
        cout << "5. Вернуться в главное меню\n";
        cout << "════════════════════════════════════\n";
        cout << "Выберите пункт меню: ";

        int choice;
        cin >> choice;

        ClientMenuOption option = static_cast<ClientMenuOption>(choice);

        switch (option) {
        case ClientMenuOption::SHOW_ALL_CLIENTS: {
            cout << "\n════════════════════════════════════\n";
            cout << "ВСЕ КЛИЕНТЫ:\n";
            cout << "════════════════════════════════════\n";
            for (const auto& client : clients) {
                cout << "  • " << client->getBriefInfo() << endl;
            }
            cout << "════════════════════════════════════\n";
            break;
        }

        case ClientMenuOption::ADD_CLIENT: {
            string id, name;
            double discount;
            cout << "Введите ID клиента: ";
            cin >> id;
            cout << "Введите имя клиента: ";
            cin.ignore();
            getline(cin, name);
            cout << "Введите скидку (%): ";
            cin >> discount;
            clients.push_back(make_shared<Client>(id, name, discount));
            cout << "Клиент успешно добавлен!\n";
            break;
        }

        case ClientMenuOption::MODIFY_DISCOUNT: {
            string id;
            double newDiscount;
            cout << "Введите ID клиента: ";
            cin >> id;
            cout << "Введите новую скидку (%): ";
            cin >> newDiscount;

            bool found = false;
            for (auto& client : clients) {
                if (client->getId() == id) {
                    client->setDiscount(newDiscount);
                    cout << "Скидка обновлена!\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Клиент с ID " << id << " не найден.\n";
            }
            break;
        }

        case ClientMenuOption::SHOW_CLIENT_HISTORY: {
            string clientId;
            cout << "Введите ID клиента: ";
            cin >> clientId;

            bool found = false;
            for (const auto& client : clients) {
                if (client->getId() == clientId) {
                    cout << client->getClientStats() << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Клиент с ID " << clientId << " не найден.\n";
            }
            break;
        }

        case ClientMenuOption::BACK:
            inClientMenu = false;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }

        if (inClientMenu && option != ClientMenuOption::BACK) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    }
}

// Функция для отображения меню управления продуктами
void showProductMenu(Warehouse& warehouse) {
    bool inProductMenu = true;

    while (inProductMenu) {
        cout << "\n════════════════════════════════════\n";
        cout << "УПРАВЛЕНИЕ ПРОДУКТАМИ:\n";
        cout << "════════════════════════════════════\n";
        cout << "1. Показать все продукты\n";
        cout << "2. Добавить новый продукт\n";
        cout << "3. Обновить количество на складе\n";
        cout << "4. Показать товары с низким запасом\n";
        cout << "5. Вернуться в главное меню\n";
        cout << "════════════════════════════════════\n";
        cout << "Выберите пункт меню: ";

        int choice;
        cin >> choice;

        ProductMenuOption option = static_cast<ProductMenuOption>(choice);

        switch (option) {
        case ProductMenuOption::SHOW_ALL_PRODUCTS:
            cout << warehouse.getCurrentAssortment() << endl;
            break;

        case ProductMenuOption::ADD_PRODUCT: {
            string id, name;
            double price;
            int quantity;
            cout << "Введите ID продукта: ";
            cin >> id;
            cout << "Введите название продукта: ";
            cin.ignore();
            getline(cin, name);
            cout << "Введите цену: ";
            cin >> price;
            cout << "Введите количество: ";
            cin >> quantity;

            auto newProduct = make_shared<Product>(id, name, price, quantity);
            warehouse.addProduct(newProduct.get());
            cout << "Продукт успешно добавлен!\n";
            break;
        }

        case ProductMenuOption::UPDATE_STOCK: {
            string id;
            int quantity;
            cout << "Введите ID продукта: ";
            cin >> id;
            cout << "Введите новое количество: ";
            cin >> quantity;

            Product* product = warehouse.findProductById(id);
            if (product) {
                product->setQuantity(quantity);
                cout << "Количество обновлено!\n";
            }
            else {
                cout << "Продукт с ID " << id << " не найден.\n";
            }
            break;
        }

        case ProductMenuOption::SHOW_LOW_STOCK: {
            cout << "\n════════════════════════════════════\n";
            cout << "ТОВАРЫ С НИЗКИМ ЗАПАСОМ (<10 шт.):\n";
            cout << "════════════════════════════════════\n";

            const auto& products = warehouse.getAllProducts();
            bool hasLowStock = false;

            for (const auto& product : products) {
                if (product->getQuantity() < 10) {
                    cout << "  • " << product->toString() << endl;
                    hasLowStock = true;
                }
            }

            if (!hasLowStock) {
                cout << "Нет товаров с низким запасом.\n";
            }
            cout << "════════════════════════════════════\n";
            break;
        }

        case ProductMenuOption::BACK:
            inProductMenu = false;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }

        if (inProductMenu && option != ProductMenuOption::BACK) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    }
}

// Обновленная функция отображения главного меню
void displayMainMenu() {
    cout << "\n════════════════════════════════════\n";
    cout << "ГЛАВНОЕ МЕНЮ\n";
    cout << "════════════════════════════════════\n";
    cout << "1. Показать ассортимент на складе\n";
    cout << "2. Показать заказы магазинов\n";
    cout << "3. Показать продажи за период\n";
    cout << "4. Показать клиентов со скидкой\n";
    cout << "5. Показать общую статистику\n";
    cout << "6. Управление клиентами\n";
    cout << "7. Управление продуктами\n";
    cout << "8. Выход\n";
    cout << "════════════════════════════════════\n";
    cout << "Выберите пункт меню: ";
}

// ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ
int main() {
    cout << "════════════════════════════════════════════════════════════\n";
    cout << "           СИСТЕМА СКЛАДСКОГО УЧЕТА\n";
    cout << "════════════════════════════════════════════════════════════\n\n";

    // Инициализация данных
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

    // Добавляем клиентов в магазины
    for (auto& client : clients) {
        supermarket->addClient(client.get());
        minimarket->addClient(client.get());
    }

    vector<Invoice> invoices;

    Invoice inv1("INV001", "2024-01-15", clients[0].get());
    inv1.addItem(bread.get(), 10, bread->getPrice());
    inv1.addItem(milk.get(), 5, milk->getPrice());
    invoices.push_back(inv1);

    // Добавляем накладные в клиентов и магазины
    clients[0]->addInvoice(&invoices.back());
    supermarket->addInvoice(&invoices.back());

    Invoice inv2("INV002", "2024-01-20", clients[1].get());
    inv2.addItem(cheese.get(), 8, cheese->getPrice());
    inv2.addItem(butter.get(), 3, butter->getPrice());
    invoices.push_back(inv2);

    clients[1]->addInvoice(&invoices.back());
    supermarket->addInvoice(&invoices.back());

    Invoice inv3("INV003", "2024-01-25", clients[2].get());
    inv3.addItem(bread.get(), 5, bread->getPrice());
    inv3.addItem(milk.get(), 4, milk->getPrice());
    invoices.push_back(inv3);

    clients[2]->addInvoice(&invoices.back());
    minimarket->addInvoice(&invoices.back());

    bool running = true;

    while (running) {
        displayMainMenu();

        int choice;
        cin >> choice;

        MainMenuOption option = static_cast<MainMenuOption>(choice);

        switch (option) {
        case MainMenuOption::SHOW_ASSORTMENT:
            cout << "\n════════════════════════════════════\n";
            cout << "АССОРТИМЕНТ НА СКЛАДЕ:\n";
            cout << "════════════════════════════════════\n";
            cout << warehouse.getCurrentAssortment() << endl;
            break;

        case MainMenuOption::SHOW_ORDERS:
            cout << "\n════════════════════════════════════\n";
            cout << "ЗАКАЗЫ МАГАЗИНОВ:\n";
            cout << "════════════════════════════════════\n";
            cout << supermarket->getOrderedProducts() << endl;
            cout << minimarket->getOrderedProducts() << endl;
            break;

        case MainMenuOption::SHOW_SALES:
            showSalesMenu(invoices);
            break;

        case MainMenuOption::SHOW_DISCOUNT_CLIENTS:
            showClientsWithDiscount(clients);
            break;

        case MainMenuOption::SHOW_STATISTICS:
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

            // Статистика магазинов
            cout << "════════════════════════════════════\n";
            cout << "СТАТИСТИКА МАГАЗИНОВ:\n";
            cout << "════════════════════════════════════\n";
            cout << "1. " << supermarket->getBriefInfo() << "\n";
            cout << "   Продаж: " << supermarket->getInvoiceCount() << ", Клиентов: "
                << supermarket->getClientCount() << ", Сумма: "
                << supermarket->getTotalSales() << " руб.\n";
            cout << "2. " << minimarket->getBriefInfo() << "\n";
            cout << "   Продаж: " << minimarket->getInvoiceCount() << ", Клиентов: "
                << minimarket->getClientCount() << ", Сумма: "
                << minimarket->getTotalSales() << " руб.\n";
            cout << "════════════════════════════════════\n";

            // Статистика клиентов
            cout << "СТАТИСТИКА КЛИЕНТОВ:\n";
            cout << "════════════════════════════════════\n";
            for (const auto& client : clients) {
                cout << "• " << client->getBriefInfo() << "\n";
                cout << "  Покупок: " << client->getInvoiceCount()
                    << ", Сумма: " << client->getTotalPurchases() << " руб.\n";
            }
            cout << "════════════════════════════════════\n";
            break;

        case MainMenuOption::MANAGE_CLIENTS:
            showClientMenu(clients, invoices);
            break;

        case MainMenuOption::MANAGE_PRODUCTS:
            showProductMenu(warehouse);
            break;

        case MainMenuOption::EXIT:
            cout << "\n════════════════════════════════════\n";
            cout << "Спасибо за использование системы!\n";
            cout << "════════════════════════════════════\n";
            running = false;
            break;

        default:
            cout << "\nНеверный выбор. Попробуйте снова.\n";
        }

        if (running && option != MainMenuOption::MANAGE_CLIENTS &&
            option != MainMenuOption::MANAGE_PRODUCTS &&
            option != MainMenuOption::SHOW_SALES) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}