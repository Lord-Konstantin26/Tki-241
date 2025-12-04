#pragma once
#include <vector>
#include <string>
#include "Product.h"

using namespace std;

namespace bakery {

    class Warehouse {
    private:
        vector<Product*> products;

    public:
        void addProduct(Product* product);
        string getCurrentAssortment() const;
        const vector<Product*>& getAllProducts() const;
        Product* findProductById(const string& id);
        bool hasProduct(const string& productId, int requiredQuantity);
        int getProductCount() const;
        int getTotalItemsCount() const;
        vector<Product*> getAvailableProducts() const;
    };

} // namespace bakery