#pragma once
#include <string>

using namespace std;

namespace bakery {

    class Client {
    private:
        string id;
        string name;
        double discount;
        bool hasDiscount;

    public:
        Client(const string& id, const string& name, double discount = 0.0);

        const string& getId() const;
        const string& getName() const;
        double getDiscount() const;
        bool hasDiscountStatus() const;

        void setDiscount(double newDiscount);
        string toString() const;
    };

} // namespace bakery