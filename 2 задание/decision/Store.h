#pragma once
#include <string>
#include <vector>
#include "Product.h"

using namespace std;

namespace bakery {

    // Предварительные объявления
    class Invoice;
    class Client;

    class Store {
    private:
        string id;
        string name;
        vector<pair<Product*, int>> orders;  // Вектор заказов товаров
        vector<Invoice*> storeInvoices;      // Вектор накладных магазина
        vector<Client*> storeClients;        // Вектор клиентов магазина

    public:
        Store(const string& id, const string& name);

        // Методы для работы с заказами товаров
        void addOrder(Product* product, int quantity);
        const vector<pair<Product*, int>>& getOrders() const;
        string getOrderedProducts() const;

        // Методы для работы с накладными
        void addInvoice(Invoice* invoice);
        const vector<Invoice*>& getInvoices() const;
        int getInvoiceCount() const;

        // Методы для работы с клиентами
        void addClient(Client* client);
        const vector<Client*>& getClients() const;
        int getClientCount() const;

        // Геттеры
        const string& getName() const;
        const string& getId() const;
        int getTotalOrderedItems() const;

        // Статистика
        double getTotalSales() const;
        string getStoreStats() const;
        string getBriefInfo() const;
    };

}