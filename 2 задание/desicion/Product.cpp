#include "Product.h"
#include <algorithm>

using namespace bakery;

Product::Product(const string& id, const string& name, double price, int quantity)
    : id(id), name(name), price(price), quantity(quantity) {
}

const string& Product::getId() const { return id; }
const string& Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::setQuantity(int qty) {
    quantity = qty;
}

void Product::addQuantity(int qty) {
    quantity += qty;
}

void Product::removeQuantity(int qty) {
    if (qty <= quantity) {
        quantity -= qty;
    }
}

string Product::toString() const {
    return "ID: " + id + ", Название: " + name +
        ", Цена: " + to_string(price) + " руб." +
        ", Количество: " + to_string(quantity) + " шт.";
}