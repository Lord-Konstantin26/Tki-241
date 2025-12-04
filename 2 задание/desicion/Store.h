#pragma once
#include <string>
#include <vector>
#include "Product.h"

using namespace std;

namespace bakery {

    class Store {
    private:
        string id;
        string name;
        vector<pair<Product*, int>> orders;

    public:
        Store(const string& id, const string& name);

        void addOrder(Product* product, int quantity);
        const vector<pair<Product*, int>>& getOrders() const;
        string getOrderedProducts() const;
        const string& getName() const;
        const string& getId() const;
        int getTotalOrderedItems() const;
    };

} // namespace bakery