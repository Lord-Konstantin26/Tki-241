#include "Client.h"

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