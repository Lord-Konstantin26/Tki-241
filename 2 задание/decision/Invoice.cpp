#include "Invoice.h"
#include "Client.h"

using namespace bakery;

Invoice::Invoice(const string& id, const string& date, Client* client)
    : id(id), date(date), client(client), totalAmount(0.0) {
}

void Invoice::addItem(Product* product, int quantity, double price) {
    soldItems.push_back(make_pair(product, quantity));

    // Расчет суммы с учетом скидки клиента
    double discountMultiplier = 1.0 - (client->getDiscount() / 100.0);
    totalAmount += quantity * price * discountMultiplier;

    // Уменьшаем количество товара на складе
    product->removeQuantity(quantity);
}

const string& Invoice::getId() const {
    return id;
}

const string& Invoice::getDate() const {
    return date;
}

double Invoice::getTotalAmount() const {
    return totalAmount;
}

Client* Invoice::getClient() const {
    return client;
}

const vector<pair<Product*, int>>& Invoice::getSoldItems() const {
    return soldItems;
}

int Invoice::getItemCount() const {
    return soldItems.size();
}

int Invoice::getTotalItemsSold() const {
    int total = 0;
    for (const auto& item : soldItems) {
        total += item.second;
    }
    return total;
}

string Invoice::toString() const {
    string result = "════════════════════════════════════\n";
    result += "НАКЛАДНАЯ #" + id + "\n";
    result += "Дата: " + date + "\n";
    result += "Клиент: " + client->getName();

    if (client->hasDiscountStatus()) {
        result += " (скидка " + to_string(client->getDiscount()) + "%)";
    }

    result += "\n════════════════════════════════════\n";
    result += "ПРОДАННЫЕ ТОВАРЫ:\n";

    for (const auto& item : soldItems) {
        double itemPrice = item.first->getPrice();
        double itemTotal = item.second * itemPrice;
        double discount = client->getDiscount();
        double discountedTotal = itemTotal * (1.0 - discount / 100.0);

        result += "  • " + item.first->getName() +
            " - " + to_string(item.second) + " шт. x " +
            to_string(itemPrice) + " руб. = " +
            to_string(itemTotal) + " руб.";

        if (discount > 0) {
            result += " (со скидкой: " + to_string(discountedTotal) + " руб.)";
        }

        result += "\n";
    }

    result += "════════════════════════════════════\n";
    result += "ИТОГО: " + to_string(totalAmount) + " руб.\n";
    result += "════════════════════════════════════\n";

    return result;
}

string Invoice::getBriefInfo() const {
    return "Накладная #" + id + " от " + date +
        " - " + client->getName() +
        " - " + to_string(totalAmount) + " руб.";
}

bool Invoice::isInPeriod(const string& startDate, const string& endDate) const {
    return date >= startDate && date <= endDate;
}