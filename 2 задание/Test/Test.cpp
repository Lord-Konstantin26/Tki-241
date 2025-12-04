#include "CppUnitTest.h"
#include <memory>
#include "../desicion/Client.h"
#include "../desicion/Product.h"
#include "../desicion/Store.h"
#include "../desicion/Warehouse.h"
#include "../desicion/Invoice.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace bakery;
using namespace std;

namespace WarehouseSystemTests
{
    TEST_CLASS(WarehouseTests)
    {
    public:

        TEST_METHOD(TestEmptyWarehouse)
        {
            Warehouse warehouse;

            auto assortment = warehouse.getCurrentAssortment();
            // Проверяем, что строка содержит информацию о пустом складе
            Assert::IsTrue(assortment.find("Склад пуст") != string::npos ||
                assortment.find("Товаров: 0") != string::npos);
            Assert::AreEqual(0, warehouse.getProductCount());
        }

        TEST_METHOD(TestAddProductToWarehouse)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 50);
            warehouse.addProduct(product.get());

            auto assortment = warehouse.getCurrentAssortment();
            Assert::IsTrue(assortment.find("Test Product") != string::npos);
            Assert::AreEqual(50, product->getQuantity());
        }

        TEST_METHOD(TestFindProductById)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 50);
            warehouse.addProduct(product.get());

            auto found = warehouse.findProductById("TEST001");
            Assert::IsNotNull(found);
            Assert::AreEqual(string("Test Product"), found->getName());

            auto notFound = warehouse.findProductById("NONEXISTENT");
            Assert::IsNull(notFound);
        }

        TEST_METHOD(TestHasProduct)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 50);
            warehouse.addProduct(product.get());

            bool hasEnough = warehouse.hasProduct("TEST001", 30);
            Assert::IsTrue(hasEnough);

            bool notEnough = warehouse.hasProduct("TEST001", 100);
            Assert::IsFalse(notEnough);

            bool notExist = warehouse.hasProduct("NONEXISTENT", 10);
            Assert::IsFalse(notExist);
        }
    };

    TEST_CLASS(ProductTests)
    {
    public:

        TEST_METHOD(TestProductCreation)
        {
            Product product("TEST001", "Test Product", 150.0, 30);

            Assert::AreEqual(string("TEST001"), product.getId());
            Assert::AreEqual(string("Test Product"), product.getName());
            Assert::AreEqual(150.0, product.getPrice());
            Assert::AreEqual(30, product.getQuantity());
        }

        TEST_METHOD(TestProductQuantityOperations)
        {
            Product product("TEST001", "Test Product", 100.0, 50);

            product.addQuantity(20);
            Assert::AreEqual(70, product.getQuantity());

            product.removeQuantity(30);
            Assert::AreEqual(40, product.getQuantity());

            // Пытаемся удалить больше, чем есть
            product.removeQuantity(100);
            Assert::AreEqual(40, product.getQuantity()); // Количество не должно измениться
        }

        TEST_METHOD(TestProductToString)
        {
            Product product("TEST001", "Test Product", 150.0, 25);

            auto str = product.toString();
            Assert::IsTrue(str.find("TEST001") != string::npos);
            Assert::IsTrue(str.find("Test Product") != string::npos);
            Assert::IsTrue(str.find("150.0") != string::npos);
            Assert::IsTrue(str.find("25") != string::npos);
        }
    };

    TEST_CLASS(ClientTests)
    {
    public:

        TEST_METHOD(TestClientCreation)
        {
            Client client("CL001", "Test Client", 10.0);

            Assert::AreEqual(string("CL001"), client.getId());
            Assert::AreEqual(string("Test Client"), client.getName());
            Assert::AreEqual(10.0, client.getDiscount());
            Assert::IsTrue(client.hasDiscountStatus());
        }

        TEST_METHOD(TestClientWithoutDiscount)
        {
            Client client("CL002", "Client No Discount", 0.0);

            Assert::AreEqual(0.0, client.getDiscount());
            Assert::IsFalse(client.hasDiscountStatus());
        }

        TEST_METHOD(TestSetDiscount)
        {
            Client client("CL003", "Test Client", 0.0);

            client.setDiscount(15.0);
            Assert::AreEqual(15.0, client.getDiscount());
            Assert::IsTrue(client.hasDiscountStatus());

            client.setDiscount(0.0);
            Assert::IsFalse(client.hasDiscountStatus());
        }
    };

    TEST_CLASS(StoreTests)
    {
    public:

        TEST_METHOD(TestEmptyStoreOrders)
        {
            Store store("ST001", "Test Store");

            auto ordersInfo = store.getOrderedProducts();
            Assert::IsTrue(ordersInfo.find("Test Store") != string::npos);
            Assert::IsTrue(ordersInfo.find("Всего товаров: 0") != string::npos);
        }

        TEST_METHOD(TestAddOrderToStore)
        {
            Store store("ST001", "Test Store");
            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 50);

            store.addOrder(product.get(), 10);

            auto orders = store.getOrders();
            Assert::AreEqual(1, (int)orders.size());
            Assert::AreEqual(10, orders[0].second); // Количество товара
        }

        TEST_METHOD(TestStoreTotalOrderedItems)
        {
            Store store("ST001", "Test Store");
            auto product1 = make_shared<Product>("TEST001", "Product 1", 100.0, 50);
            auto product2 = make_shared<Product>("TEST002", "Product 2", 200.0, 30);

            store.addOrder(product1.get(), 5);
            store.addOrder(product2.get(), 3);
            store.addOrder(product1.get(), 2); // Еще 2 первого товара

            // 5 + 3 + 2 = 10 товаров всего
            Assert::AreEqual(3, (int)store.getOrders().size()); // 3 записи в заказах
        }
    };

    TEST_CLASS(InvoiceTests)
    {
    public:

        TEST_METHOD(TestInvoiceCreation)
        {
            auto client = make_shared<Client>("CL001", "Test Client", 10.0);
            Invoice invoice("INV001", "2024-01-15", client.get());

            Assert::AreEqual(string("INV001"), invoice.getId());
            Assert::AreEqual(string("2024-01-15"), invoice.getDate());
            Assert::AreEqual(client.get(), invoice.getClient());
            Assert::AreEqual(0.0, invoice.getTotalAmount());
        }

        TEST_METHOD(TestAddItemToInvoice)
        {
            auto client = make_shared<Client>("CL001", "Test Client", 10.0);
            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 50);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product.get(), 5, product->getPrice());

            // 5 товаров по 100 руб = 500 руб, со скидкой 10% = 450 руб
            Assert::AreEqual(450.0, invoice.getTotalAmount());
            Assert::AreEqual(1, invoice.getItemCount());

            // Количество товара должно уменьшиться
            Assert::AreEqual(45, product->getQuantity()); // 50 - 5 = 45
        }

        TEST_METHOD(TestInvoiceIsInPeriod)
        {
            auto client = make_shared<Client>("CL001", "Test Client", 10.0);
            Invoice invoice("INV001", "2024-01-15", client.get());

            Assert::IsTrue(invoice.isInPeriod("2024-01-01", "2024-01-31"));
            Assert::IsTrue(invoice.isInPeriod("2024-01-15", "2024-01-15")); // В тот же день
            Assert::IsFalse(invoice.isInPeriod("2024-02-01", "2024-02-28"));
            Assert::IsFalse(invoice.isInPeriod("2023-12-01", "2023-12-31"));
        }

        TEST_METHOD(TestInvoiceWithMultipleItems)
        {
            auto client = make_shared<Client>("CL001", "Test Client", 10.0);
            auto product1 = make_shared<Product>("TEST001", "Product 1", 100.0, 100);
            auto product2 = make_shared<Product>("TEST002", "Product 2", 200.0, 50);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product1.get(), 2, product1->getPrice()); // 200 руб
            invoice.addItem(product2.get(), 1, product2->getPrice()); // 200 руб
            // Итого: 400 руб, со скидкой 10% = 360 руб

            Assert::AreEqual(360.0, invoice.getTotalAmount());
            Assert::AreEqual(2, invoice.getItemCount());
            Assert::AreEqual(98, product1->getQuantity()); // 100 - 2 = 98
            Assert::AreEqual(49, product2->getQuantity()); // 50 - 1 = 49
        }

        TEST_METHOD(TestInvoiceWithNoDiscount)
        {
            auto client = make_shared<Client>("CL002", "Client No Discount", 0.0);
            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 100);

            Invoice invoice("INV002", "2024-01-16", client.get());
            invoice.addItem(product.get(), 3, product->getPrice());

            // 3 товара по 100 руб = 300 руб, без скидки
            Assert::AreEqual(300.0, invoice.getTotalAmount());
        }
    };

    TEST_CLASS(IntegrationTests)
    {
    public:

        TEST_METHOD(TestCompleteWorkflow)
        {
            // Создаем склад
            Warehouse warehouse;

            // Создаем товары
            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 50);

            warehouse.addProduct(bread.get());
            warehouse.addProduct(milk.get());

            // Проверяем начальный ассортимент
            Assert::AreEqual(2, warehouse.getProductCount());

            // Создаем магазин и добавляем заказ
            Store store("STR001", "Тестовый магазин");
            store.addOrder(bread.get(), 20);
            store.addOrder(milk.get(), 10);

            // Проверяем заказы
            Assert::AreEqual(2, (int)store.getOrders().size());

            // Создаем клиента
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 5.0);

            // Создаем накладную и добавляем продажи
            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(bread.get(), 10, bread->getPrice());  // 500 руб со скидкой 5% = 475 руб
            invoice.addItem(milk.get(), 5, milk->getPrice());     // 400 руб со скидкой 5% = 380 руб

            // Проверяем итоговую сумму
            // 10 хлеба по 50 = 500, 5 молока по 80 = 400, всего 900, скидка 5% = 855
            Assert::AreEqual(855.0, invoice.getTotalAmount());

            // Проверяем остатки на складе
            Assert::AreEqual(90, bread->getQuantity());  // 100 - 10 = 90
            Assert::AreEqual(45, milk->getQuantity());   // 50 - 5 = 45

            // Проверяем период
            Assert::IsTrue(invoice.isInPeriod("2024-01-01", "2024-01-31"));
        }

        TEST_METHOD(TestSalesPeriodStatistics)
        {
            // Создаем несколько накладных за разные периоды
            auto client = make_shared<Client>("CL001", "Test Client", 10.0);
            auto product = make_shared<Product>("TEST001", "Test Product", 100.0, 1000);

            vector<Invoice> invoices;

            Invoice inv1("INV001", "2024-01-10", client.get());
            inv1.addItem(product.get(), 10, product->getPrice());
            invoices.push_back(inv1);

            Invoice inv2("INV002", "2024-01-20", client.get());
            inv2.addItem(product.get(), 20, product->getPrice());
            invoices.push_back(inv2);

            Invoice inv3("INV003", "2024-02-05", client.get());
            inv3.addItem(product.get(), 15, product->getPrice());
            invoices.push_back(inv3);

            // Считаем продажи за январь
            double januaryRevenue = 0;
            int januaryInvoices = 0;
            for (const auto& inv : invoices) {
                if (inv.isInPeriod("2024-01-01", "2024-01-31")) {
                    januaryRevenue += inv.getTotalAmount();
                    januaryInvoices++;
                }
            }

            // 10 товаров по 100 = 1000, скидка 10% = 900
            // 20 товаров по 100 = 2000, скидка 10% = 1800
            // Итого за январь: 900 + 1800 = 2700
            Assert::AreEqual(2700.0, januaryRevenue);
            Assert::AreEqual(2, januaryInvoices);

            // Считаем продажи за февраль
            double februaryRevenue = 0;
            int februaryInvoices = 0;
            for (const auto& inv : invoices) {
                if (inv.isInPeriod("2024-02-01", "2024-02-28")) {
                    februaryRevenue += inv.getTotalAmount();
                    februaryInvoices++;
                }
            }

            // 15 товаров по 100 = 1500, скидка 10% = 1350
            Assert::AreEqual(1350.0, februaryRevenue);
            Assert::AreEqual(1, februaryInvoices);
        }
    };
}