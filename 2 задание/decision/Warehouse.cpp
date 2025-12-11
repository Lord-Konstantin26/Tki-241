#include "Warehouse.h"

using namespace bakery;

void Warehouse::addProduct(Product* product) {
    products.push_back(product);
}

string Warehouse::getCurrentAssortment() const {
    string result = "════════════════════════════════════\n";
    result += "ТЕКУЩИЙ АССОРТИМЕНТ НА СКЛАДЕ:\n";
    result += "════════════════════════════════════\n";

    bool hasProducts = false;
    int totalItems = 0;
    double totalValue = 0;

    for (const auto& product : products) {
        result += "  • " + product->toString() + "\n";
        hasProducts = true;
        totalItems += product->getQuantity();
        totalValue += product->getQuantity() * product->getPrice();
    }

    if (!hasProducts) {
        result += "Склад пуст.\n";
    }
    else {
        result += "════════════════════════════════════\n";
        result += "Всего товаров на складе: " + to_string(totalItems) + " шт.\n";
        result += "Общая стоимость товаров: " + to_string(totalValue) + " руб.\n";
        result += "Количество позиций: " + to_string(products.size()) + "\n";
    }

    result += "════════════════════════════════════\n";
    return result;
}

const vector<Product*>& Warehouse::getAllProducts() const {
    return products;
}

Product* Warehouse::findProductById(const string& id) {
    for (auto& product : products) {
        if (product->getId() == id) {
            return product;
        }
    }
    return nullptr;
}

bool Warehouse::hasProduct(const string& productId, int requiredQuantity) {
    for (const auto& product : products) {
        if (product->getId() == productId &&
            product->getQuantity() >= requiredQuantity) {
            return true;
        }
    }
    return false;
}

int Warehouse::getProductCount() const {
    return products.size();
}

int Warehouse::getTotalItemsCount() const {
    int total = 0;
    for (const auto& product : products) {
        total += product->getQuantity();
    }
    return total;
}

vector<Product*> Warehouse::getAvailableProducts() const {
    vector<Product*> available;
    for (const auto& product : products) {
        if (product->getQuantity() > 0) {
            available.push_back(product);
        }
    }
    return available;
}