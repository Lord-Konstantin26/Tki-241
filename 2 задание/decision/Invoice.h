#pragma once
#include <string>
#include <vector>
#include "Product.h"

using namespace std;

namespace bakery {

    // Предварительное объявление для избежания циклических зависимостей
    class Client;

    class Invoice {
    private:
        string id;
        string date;
        Client* client;
        double totalAmount;
        vector<pair<Product*, int>> soldItems;

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

}