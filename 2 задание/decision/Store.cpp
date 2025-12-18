#include "Store.h"
#include "Invoice.h"
#include "Client.h"

using namespace bakery;

Store::Store(const string& id, const string& name)
    : id(id), name(name) {
}

void Store::addOrder(Product* product, int quantity) {
    orders.push_back(make_pair(product, quantity));
}

const vector<pair<Product*, int>>& Store::getOrders() const {
    return orders;
}

string Store::getOrderedProducts() const {
    string result = "════════════════════════════════════\n";
    result += "Магазин: " + name + " (ID: " + id + ")\n";
    result += "Заказанные товары:\n";

    int totalItems = 0;
    double totalCost = 0;
    for (const auto& order : orders) {
        result += "  • " + order.first->getName() +
            " - " + to_string(order.second) + " шт.\n";
        totalItems += order.second;
        totalCost += order.second * order.first->getPrice();
    }

    result += "════════════════════════════════════\n";
    result += "Всего товаров: " + to_string(totalItems) + " шт.\n";
    result += "Общая стоимость: " + to_string(totalCost) + " руб.\n";

    result += "════════════════════════════════════\n";
    result += "СТАТИСТИКА МАГАЗИНА:\n";
    result += "• Количество накладных: " + to_string(storeInvoices.size()) + "\n";
    result += "• Количество клиентов: " + to_string(storeClients.size()) + "\n";
    result += "• Общая сумма продаж: " + to_string(getTotalSales()) + " руб.\n";

    result += "════════════════════════════════════\n";
    return result;
}

const string& Store::getName() const {
    return name;
}

const string& Store::getId() const {
    return id;
}

int Store::getTotalOrderedItems() const {
    int total = 0;
    for (const auto& order : orders) {
        total += order.second;
    }
    return total;
}


void Store::addInvoice(Invoice* invoice) {
    storeInvoices.push_back(invoice);
}

const vector<Invoice*>& Store::getInvoices() const {
    return storeInvoices;
}

int Store::getInvoiceCount() const {
    return storeInvoices.size();
}

void Store::addClient(Client* client) {
    storeClients.push_back(client);
}

const vector<Client*>& Store::getClients() const {
    return storeClients;
}

int Store::getClientCount() const {
    return storeClients.size();
}

double Store::getTotalSales() const {
    double total = 0.0;
    for (const auto& invoice : storeInvoices) {
        total += invoice->getTotalAmount();
    }
    return total;
}

string Store::getStoreStats() const {
    string result = "════════════════════════════════════\n";
    result += "СТАТИСТИКА МАГАЗИНА: " + name + "\n";
    result += "════════════════════════════════════\n";
    result += "• ID магазина: " + id + "\n";
    result += "• Заказано товаров: " + to_string(getTotalOrderedItems()) + " шт.\n";
    result += "• Количество позиций в заказах: " + to_string(orders.size()) + "\n";
    result += "• Количество накладных: " + to_string(storeInvoices.size()) + "\n";
    result += "• Количество клиентов: " + to_string(storeClients.size()) + "\n";
    result += "• Общая сумма продаж: " + to_string(getTotalSales()) + " руб.\n";

    // Статистика по клиентам со скидкой
    int discountClients = 0;
    for (const auto& client : storeClients) {
        if (client->hasDiscountStatus()) {
            discountClients++;
        }
    }
    result += "• Клиентов со скидкой: " + to_string(discountClients) + "\n";

    // Статистика по активным накладным
    double averageInvoice = storeInvoices.empty() ? 0.0 : getTotalSales() / storeInvoices.size();
    result += "• Средний чек: " + to_string(averageInvoice) + " руб.\n";

    result += "════════════════════════════════════\n";
    return result;
}

// Метод для получения краткой информации о магазине
string Store::getBriefInfo() const {
    return "[" + id + "] " + name + " (" + to_string(getInvoiceCount()) + " продаж)";
}