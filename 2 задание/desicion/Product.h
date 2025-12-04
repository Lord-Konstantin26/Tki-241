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

        const string& getId() const;
        const string& getName() const;
        double getPrice() const;
        int getQuantity() const;

        void setQuantity(int qty);
        void addQuantity(int qty);
        void removeQuantity(int qty);

        string toString() const;
    };

} // namespace bakery