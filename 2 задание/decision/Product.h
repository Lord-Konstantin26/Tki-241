#pragma once
#include <string>
#include <vector>

using namespace std;

namespace bakery {

    class Product {
    private:
        string id;
        string name;
        double price;
        int quantity;

    public:
        Product(const string& id, const string& name, double price, int quantity = 0);

        // Геттеры
        const string& getId() const;
        const string& getName() const;
        double getPrice() const;
        int getQuantity() const;

        // Сеттеры
        void setQuantity(int qty);
        void addQuantity(int qty);
        void removeQuantity(int qty);

        // Вспомогательные методы
        string toString() const;
        bool isAvailable() const;
    };

} 