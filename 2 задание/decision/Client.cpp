#include "Client.h"
#include "Invoice.h"

using namespace bakery;

Client::Client(const string& id, const string& name, double discount)
    : id(id), name(name), discount(discount), hasDiscount(discount > 0.0) {
}

const string& Client::getId() const {
    return id;
}

const string& Client::getName() const {
    return name;
}

double Client::getDiscount() const {
    return discount;
}

bool Client::hasDiscountStatus() const {
    return hasDiscount;
}

void Client::setDiscount(double newDiscount) {
    discount = newDiscount;
    hasDiscount = (discount > 0.0);
}

string Client::toString() const {
    string discountText = hasDiscount ?
        " (скидка " + to_string(discount) + "%)" : " (без скидки)";
    return "ID: " + id + ", " + name + discountText;
}

// Новые методы для работы с накладными
void Client::addInvoice(Invoice* invoice) {
    clientInvoices.push_back(invoice);
}

const vector<Invoice*>& Client::getInvoices() const {
    return clientInvoices;
}

int Client::getInvoiceCount() const {
    return clientInvoices.size();
}

// Метод для расчета общей суммы покупок
double Client::getTotalPurchases() const {
    double total = 0.0;
    for (const auto& invoice : clientInvoices) {
        total += invoice->getTotalAmount();
    }
    return total;
}

// Метод для получения полной статистики клиента
string Client::getClientStats() const {
    string result = "════════════════════════════════════\n";
    result += "СТАТИСТИКА КЛИЕНТА:\n";
    result += "════════════════════════════════════\n";
    result += "• ID клиента: " + id + "\n";
    result += "• Имя: " + name + "\n";
    result += "• Скидка: " + to_string(discount) + "%\n";
    result += "• Количество накладных: " + to_string(getInvoiceCount()) + "\n";
    result += "• Общая сумма покупок: " + to_string(getTotalPurchases()) + " руб.\n";

    // Статистика по среднему чеку
    double averagePurchase = clientInvoices.empty() ? 0.0 : getTotalPurchases() / clientInvoices.size();
    result += "• Средний чек: " + to_string(averagePurchase) + " руб.\n";

    // Подробная информация по накладным
    if (!clientInvoices.empty()) {
        result += "════════════════════════════════════\n";
        result += "ПОСЛЕДНИЕ НАКЛАДНЫЕ:\n";

        int count = 0;
        for (const auto& invoice : clientInvoices) {
            if (count < 5) { // Показываем только последние 5 накладных
                result += "  • " + invoice->getBriefInfo() + "\n";
                count++;
            }
            else {
                result += "  • ... и еще " + to_string(clientInvoices.size() - 5) + " накладных\n";
                break;
            }
        }
    }

    // Анализ активности клиента
    if (clientInvoices.size() >= 10) {
        result += "• Статус: Постоянный клиент\n";
    }
    else if (clientInvoices.size() >= 3) {
        result += "• Статус: Регулярный клиент\n";
    }
    else if (clientInvoices.size() == 0) {
        result += "• Статус: Новый клиент\n";
    }
    else {
        result += "• Статус: Клиент\n";
    }

    result += "════════════════════════════════════\n";
    return result;
}

// Дополнительный метод для получения краткой информации о клиенте
string Client::getBriefInfo() const {
    return "[" + id + "] " + name + " (" + to_string(getInvoiceCount()) + " покупок)";
}