#pragma once
#include <string>
#include <vector>

using namespace std;

namespace bakery {

    // Предварительное объявление для избежания циклических зависимостей
    class Invoice;

    class Client {
    private:
        string id;
        string name;
        double discount;
        bool hasDiscount;
        vector<Invoice*> clientInvoices;  // Вектор накладных клиента

    public:
        Client(const string& id, const string& name, double discount = 0.0);

        // Геттеры
        const string& getId() const;
        const string& getName() const;
        double getDiscount() const;
        bool hasDiscountStatus() const;

        // Сеттер
        void setDiscount(double newDiscount);

        // Методы для работы с накладными
        void addInvoice(Invoice* invoice);
        const vector<Invoice*>& getInvoices() const;
        int getInvoiceCount() const;
        double getTotalPurchases() const;

        // Статистика
        string getClientStats() const;
        string getBriefInfo() const;

        string toString() const;
    };

}