#include "Store.h"

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