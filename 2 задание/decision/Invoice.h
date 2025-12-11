#pragma once
#include <string>
#include <vector>
#include "Product.h"
#include "Client.h"

using namespace std;

namespace bakery {

    class Invoice {
    private:
        string id;
        string date;
        Client* client;
        vector<pair<Product*, int>> soldItems;
        double totalAmount;

    public:
        Invoice(const string& id, const string& date, Client* client);

        void addItem(Product* product, int quantity, double price);
        const string& getId() const;
        const string& getDate() const;
        double getTotalAmount() const;
        Client* getClient() const;
        const vector<pair<Product*, int>>& getSoldItems() const;
        int getItemCount() const;
        int getTotalItemsSold() const;

        string toString() const;
        string getBriefInfo() const;
        bool isInPeriod(const string& startDate, const string& endDate) const;
    };

} // namespace bakery