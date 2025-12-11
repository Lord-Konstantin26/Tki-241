#include "CppUnitTest.h"
#include <memory>
#include <string>
#include <vector>
#include "../decision/Client.h"
#include "../decision/Product.h"
#include "../decision/Store.h"
#include "../decision/Warehouse.h"
#include "../decision/Invoice.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace bakery;
using namespace std;

namespace WarehouseSystemTests
{
    TEST_CLASS(ProductTest)
    {
    public:

        TEST_METHOD(BasicProductCreation)
        {
            // Создаем базовый товар
            Product product("PRD001", "Хлеб Бородинский", 50.0, 100);

            Assert::AreEqual(string("PRD001"), product.getId().c_str());
            Assert::AreEqual(string("Хлеб Бородинский"), product.getName().c_str());
            Assert::AreEqual(50.0, product.getPrice());
            Assert::AreEqual(100, product.getQuantity());
        }

        TEST_METHOD(TestProductSell)
        {
            Product product("PRD001", "Молоко", 80.0, 10);

            // Продаем один товар
            product.removeQuantity(1);
            Assert::AreEqual(9, product.getQuantity());

            // Продаем еще три товара
            product.removeQuantity(3);
            Assert::AreEqual(6, product.getQuantity());

            // Пытаемся продать больше, чем есть
            product.removeQuantity(10);
            Assert::AreEqual(6, product.getQuantity()); // Количество не должно измениться
        }

        TEST_METHOD(TestAddToStock)
        {
            Product product("PRD001", "Сыр", 300.0, 5);

            product.addQuantity(10);
            Assert::AreEqual(15, product.getQuantity());
        }

        TEST_METHOD(TestSetQuantity)
        {
            Product product("PRD001", "Масло", 150.0, 8);

            product.setQuantity(20);
            Assert::AreEqual(20, product.getQuantity());
        }

        TEST_METHOD(TestProductToString)
        {
            Product product("PRD001", "Тестовый товар", 123.45, 50);

            string info = product.toString();
            Assert::IsTrue(info.find("PRD001") != string::npos);
            Assert::IsTrue(info.find("Тестовый товар") != string::npos);
            Assert::IsTrue(info.find("123.45") != string::npos);
            Assert::IsTrue(info.find("50") != string::npos);
        }

        TEST_METHOD(TestProductAvailability)
        {
            Product product1("PRD001", "Товар 1", 100.0, 10);
            Product product2("PRD002", "Товар 2", 200.0, 0);

            Assert::IsTrue(product1.getQuantity() > 0);
            Assert::IsFalse(product2.getQuantity() > 0);
        }
    };

    TEST_CLASS(ClientTest)
    {
    public:

        TEST_METHOD(TestClientCreation)
        {
            Client client("CL001", "ИП Петров", 5.0);

            Assert::AreEqual(string("CL001"), client.getId().c_str());
            Assert::AreEqual(string("ИП Петров"), client.getName().c_str());
            Assert::AreEqual(5.0, client.getDiscount());
            Assert::IsTrue(client.hasDiscountStatus());
        }

        TEST_METHOD(TestClientWithoutDiscount)
        {
            Client client("CL002", "Магазин У дома", 0.0);

            Assert::AreEqual(0.0, client.getDiscount());
            Assert::IsFalse(client.hasDiscountStatus());
        }

        TEST_METHOD(TestSetDiscount)
        {
            Client client("CL003", "Кафе Бриз", 0.0);

            client.setDiscount(15.0);
            Assert::AreEqual(15.0, client.getDiscount());
            Assert::IsTrue(client.hasDiscountStatus());

            client.setDiscount(0.0);
            Assert::IsFalse(client.hasDiscountStatus());
        }

        TEST_METHOD(TestClientToString)
        {
            Client client("CL001", "ИП Иванов", 10.0);

            string info = client.toString();
            Assert::IsTrue(info.find("CL001") != string::npos);
            Assert::IsTrue(info.find("ИП Иванов") != string::npos);
            Assert::IsTrue(info.find("10") != string::npos);
        }

        TEST_METHOD(TestClientDiscountEdgeCases)
        {
            Client client1("CL001", "Клиент 1", 0.1);
            Client client2("CL002", "Клиент 2", 100.0);
            Client client3("CL003", "Клиент 3", -5.0);

            Assert::IsTrue(client1.hasDiscountStatus());
            Assert::IsTrue(client2.hasDiscountStatus());
            Assert::IsFalse(client3.hasDiscountStatus());
        }
    };

    TEST_CLASS(StoreTest)
    {
    public:

        TEST_METHOD(TestStoreCreation)
        {
            Store store("STR001", "Супермаркет Продукты");

            Assert::AreEqual(string("STR001"), store.getId().c_str());
            Assert::AreEqual(string("Супермаркет Продукты"), store.getName().c_str());
            Assert::IsTrue(store.getOrders().empty());
        }

        TEST_METHOD(TestAddOrderToStore)
        {
            Store store("STR001", "Тестовый магазин");

            auto product = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            store.addOrder(product.get(), 20);

            auto orders = store.getOrders();
            Assert::AreEqual(1, (int)orders.size());
            Assert::AreEqual(20, orders[0].second);
            Assert::AreEqual(string("Хлеб"), orders[0].first->getName().c_str());
        }

        TEST_METHOD(TestStoreWithMultipleOrders)
        {
            Store store("STR001", "Тестовый магазин");

            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 50);

            store.addOrder(bread.get(), 10);
            store.addOrder(milk.get(), 5);
            store.addOrder(bread.get(), 5); // Еще 5 хлеба

            Assert::AreEqual(3, (int)store.getOrders().size());
        }

        TEST_METHOD(TestStoreOrderedProductsInfo)
        {
            Store store("STR001", "Тестовый магазин");

            auto product = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            store.addOrder(product.get(), 25);

            string info = store.getOrderedProducts();
            Assert::IsTrue(info.find("Тестовый магазин") != string::npos);
            Assert::IsTrue(info.find("Хлеб") != string::npos);
            Assert::IsTrue(info.find("25") != string::npos);
            Assert::IsTrue(info.find("50.0") != string::npos);
        }

        TEST_METHOD(TestStoreTotalOrderedItems)
        {
            Store store("STR001", "Тестовый магазин");

            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 50);

            store.addOrder(bread.get(), 10);
            store.addOrder(milk.get(), 5);
            store.addOrder(bread.get(), 3);

            // 10 + 5 + 3 = 18 товаров всего
            Assert::AreEqual(18, store.getTotalOrderedItems());
        }
    };

    TEST_CLASS(WarehouseTest)
    {
    public:

        TEST_METHOD(TestEmptyWarehouse)
        {
            Warehouse warehouse;

            string assortment = warehouse.getCurrentAssortment();
            Assert::IsTrue(assortment.find("Склад пуст") != string::npos ||
                assortment.find("Товаров: 0") != string::npos);
            Assert::AreEqual(0, warehouse.getProductCount());
            Assert::AreEqual(0, warehouse.getTotalItemsCount());
        }

        TEST_METHOD(TestAddProductToWarehouse)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 50);
            warehouse.addProduct(product.get());

            string assortment = warehouse.getCurrentAssortment();
            Assert::IsTrue(assortment.find("Тестовый товар") != string::npos);
            Assert::AreEqual(1, warehouse.getProductCount());
            Assert::AreEqual(50, warehouse.getTotalItemsCount());
        }

        TEST_METHOD(TestFindProductById)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 50);
            warehouse.addProduct(product.get());

            auto found = warehouse.findProductById("PRD001");
            Assert::IsNotNull(found);
            Assert::AreEqual(string("Тестовый товар"), found->getName().c_str());
            Assert::AreEqual(100.0, found->getPrice());

            auto notFound = warehouse.findProductById("NONEXISTENT");
            Assert::IsNull(notFound);
        }

        TEST_METHOD(TestHasProduct)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 50);
            warehouse.addProduct(product.get());

            bool hasEnough = warehouse.hasProduct("PRD001", 30);
            Assert::IsTrue(hasEnough);

            bool notEnough = warehouse.hasProduct("PRD001", 100);
            Assert::IsFalse(notEnough);

            bool notExist = warehouse.hasProduct("NONEXISTENT", 10);
            Assert::IsFalse(notExist);
        }

        TEST_METHOD(TestGetAvailableProducts)
        {
            Warehouse warehouse;

            auto product1 = make_shared<Product>("PRD001", "Товар 1", 100.0, 50);
            auto product2 = make_shared<Product>("PRD002", "Товар 2", 200.0, 0); // Нет в наличии
            auto product3 = make_shared<Product>("PRD003", "Товар 3", 300.0, 30);

            warehouse.addProduct(product1.get());
            warehouse.addProduct(product2.get());
            warehouse.addProduct(product3.get());

            auto available = warehouse.getAvailableProducts();
            Assert::AreEqual(2, (int)available.size()); // Должно быть 2 доступных товара
            Assert::AreEqual(string("Товар 1"), available[0]->getName().c_str());
            Assert::AreEqual(string("Товар 3"), available[1]->getName().c_str());
        }

        TEST_METHOD(TestWarehouseAssortmentInfo)
        {
            Warehouse warehouse;

            auto product = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            warehouse.addProduct(product.get());

            string info = warehouse.getCurrentAssortment();
            Assert::IsTrue(info.find("Хлеб") != string::npos);
            Assert::IsTrue(info.find("50.0") != string::npos);
            Assert::IsTrue(info.find("100") != string::npos);
        }

        TEST_METHOD(TestWarehouseMultipleProducts)
        {
            Warehouse warehouse;

            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 50);
            auto cheese = make_shared<Product>("PRD003", "Сыр", 300.0, 30);

            warehouse.addProduct(bread.get());
            warehouse.addProduct(milk.get());
            warehouse.addProduct(cheese.get());

            Assert::AreEqual(3, warehouse.getProductCount());
            Assert::AreEqual(180, warehouse.getTotalItemsCount()); // 100 + 50 + 30

            auto allProducts = warehouse.getAllProducts();
            Assert::AreEqual(3, (int)allProducts.size());
        }
    };

    TEST_CLASS(InvoiceTest)
    {
    public:

        TEST_METHOD(TestInvoiceCreation)
        {
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 5.0);
            Invoice invoice("INV001", "2024-01-15", client.get());

            Assert::AreEqual(string("INV001"), invoice.getId().c_str());
            Assert::AreEqual(string("2024-01-15"), invoice.getDate().c_str());
            Assert::AreEqual(client.get(), invoice.getClient());
            Assert::AreEqual(0.0, invoice.getTotalAmount());
            Assert::IsTrue(invoice.getSoldItems().empty());
            Assert::AreEqual(0, invoice.getItemCount());
            Assert::AreEqual(0, invoice.getTotalItemsSold());
        }

        TEST_METHOD(TestAddItemToInvoice)
        {
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 10.0);
            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 100);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product.get(), 5, product->getPrice());

            // 5 товаров по 100 руб = 500 руб, со скидкой 10% = 450 руб
            Assert::AreEqual(450.0, invoice.getTotalAmount());
            Assert::AreEqual(1, invoice.getItemCount());
            Assert::AreEqual(5, invoice.getTotalItemsSold());

            // Количество товара должно уменьшиться
            Assert::AreEqual(95, product->getQuantity()); // 100 - 5 = 95

            // Проверяем список проданных товаров
            auto soldItems = invoice.getSoldItems();
            Assert::AreEqual(1, (int)soldItems.size());
            Assert::AreEqual(5, soldItems[0].second);
        }

        TEST_METHOD(TestInvoiceWithMultipleItems)
        {
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 5.0);
            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 50);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 30);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(bread.get(), 10, bread->getPrice()); // 500 руб
            invoice.addItem(milk.get(), 5, milk->getPrice());    // 400 руб
            // Итого: 900 руб, со скидкой 5% = 855 руб

            Assert::AreEqual(855.0, invoice.getTotalAmount());
            Assert::AreEqual(2, invoice.getItemCount());
            Assert::AreEqual(15, invoice.getTotalItemsSold());
            Assert::AreEqual(40, bread->getQuantity()); // 50 - 10 = 40
            Assert::AreEqual(25, milk->getQuantity());  // 30 - 5 = 25

            auto soldItems = invoice.getSoldItems();
            Assert::AreEqual(2, (int)soldItems.size());
        }

        TEST_METHOD(TestInvoiceWithNoDiscount)
        {
            auto client = make_shared<Client>("CL002", "Клиент без скидки", 0.0);
            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 50);

            Invoice invoice("INV002", "2024-01-16", client.get());
            invoice.addItem(product.get(), 3, product->getPrice());

            // 3 товара по 100 руб = 300 руб, без скидки
            Assert::AreEqual(300.0, invoice.getTotalAmount());
            Assert::AreEqual(47, product->getQuantity()); // 50 - 3 = 47
        }

        TEST_METHOD(TestInvoiceIsInPeriod)
        {
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 5.0);

            Invoice invoice("INV001", "2024-01-15", client.get());

            // Корректные периоды
            Assert::IsTrue(invoice.isInPeriod("2024-01-01", "2024-01-31"));
            Assert::IsTrue(invoice.isInPeriod("2024-01-15", "2024-01-15")); // В тот же день
            Assert::IsTrue(invoice.isInPeriod("2024-01-10", "2024-01-20"));

            // Некорректные периоды
            Assert::IsFalse(invoice.isInPeriod("2024-02-01", "2024-02-28"));
            Assert::IsFalse(invoice.isInPeriod("2023-12-01", "2023-12-31"));
            Assert::IsFalse(invoice.isInPeriod("2024-01-16", "2024-01-31"));
            Assert::IsFalse(invoice.isInPeriod("2024-01-01", "2024-01-14"));
        }

        TEST_METHOD(TestInvoiceToString)
        {
            auto client = make_shared<Client>("CL001", "ИП Петров", 10.0);
            auto product = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product.get(), 5, product->getPrice());

            string info = invoice.toString();

            // Проверяем ключевые элементы накладной
            Assert::IsTrue(info.find("НАКЛАДНАЯ #INV001") != string::npos);
            Assert::IsTrue(info.find("Дата: 2024-01-15") != string::npos);
            Assert::IsTrue(info.find("Клиент: ИП Петров") != string::npos);
            Assert::IsTrue(info.find("Хлеб") != string::npos);
            Assert::IsTrue(info.find("5") != string::npos);
            Assert::IsTrue(info.find("50.0") != string::npos);
            Assert::IsTrue(info.find("скидка") != string::npos);
        }

        TEST_METHOD(TestInvoiceBriefInfo)
        {
            auto client = make_shared<Client>("CL001", "ИП Петров", 10.0);
            auto product = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product.get(), 5, product->getPrice());

            string briefInfo = invoice.getBriefInfo();

            // Краткая информация должна содержать основные данные
            Assert::IsTrue(briefInfo.find("INV001") != string::npos);
            Assert::IsTrue(briefInfo.find("2024-01-15") != string::npos);
            Assert::IsTrue(briefInfo.find("ИП Петров") != string::npos);
            Assert::IsTrue(briefInfo.find("225") != string::npos); // Сумма со скидкой
        }

        TEST_METHOD(TestInvoiceWithLargeQuantity)
        {
            auto client = make_shared<Client>("CL001", "Оптовый покупатель", 15.0);
            auto product = make_shared<Product>("PRD001", "Товар", 10.0, 1000);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product.get(), 100, product->getPrice());

            // 100 товаров по 10 руб = 1000 руб, скидка 15% = 850 руб
            Assert::AreEqual(850.0, invoice.getTotalAmount());
            Assert::AreEqual(900, product->getQuantity()); // 1000 - 100 = 900
        }

        TEST_METHOD(TestInvoiceWithFractionalPrice)
        {
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 7.5);
            auto product = make_shared<Product>("PRD001", "Товар", 49.99, 100);

            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(product.get(), 3, product->getPrice());

            // 3 товара по 49.99 руб = 149.97 руб, скидка 7.5% = 138.72 руб (округление)
            double expected = 149.97 * (1 - 7.5 / 100.0);
            Assert::AreEqual(expected, invoice.getTotalAmount(), 0.01); // Допуск 0.01
        }
    };

    TEST_CLASS(IntegrationTests)
    {
    public:

        TEST_METHOD(TestCompleteWorkflow)
        {
            // 1. Создаем склад
            Warehouse warehouse;

            // 2. Создаем товары
            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 100);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 50);
            auto cheese = make_shared<Product>("PRD003", "Сыр", 300.0, 30);

            // 3. Добавляем товары на склад
            warehouse.addProduct(bread.get());
            warehouse.addProduct(milk.get());
            warehouse.addProduct(cheese.get());

            // 4. Проверяем начальный ассортимент
            Assert::AreEqual(3, warehouse.getProductCount());
            Assert::AreEqual(180, warehouse.getTotalItemsCount()); // 100 + 50 + 30

            // 5. Создаем магазин
            auto store = make_shared<Store>("STR001", "Супермаркет");

            // 6. Добавляем заказы от магазина
            store->addOrder(bread.get(), 20);
            store->addOrder(milk.get(), 10);
            store->addOrder(cheese.get(), 5);

            // 7. Проверяем заказы
            Assert::AreEqual(3, (int)store->getOrders().size());
            Assert::AreEqual(35, store->getTotalOrderedItems()); // 20 + 10 + 5

            // 8. Создаем клиента
            auto client = make_shared<Client>("CL001", "ИП Иванов", 5.0);

            // 9. Создаем накладную
            Invoice invoice("INV001", "2024-01-15", client.get());
            invoice.addItem(bread.get(), 10, bread->getPrice());  // 500 руб
            invoice.addItem(milk.get(), 5, milk->getPrice());     // 400 руб
            invoice.addItem(cheese.get(), 3, cheese->getPrice()); // 900 руб
            // Итого: 1800 руб, скидка 5% = 1710 руб

            // 10. Проверяем итоговую сумму
            Assert::AreEqual(1710.0, invoice.getTotalAmount());
            Assert::AreEqual(18, invoice.getTotalItemsSold()); // 10 + 5 + 3 = 18

            // 11. Проверяем остатки на складе
            Assert::AreEqual(90, bread->getQuantity());   // 100 - 10 = 90
            Assert::AreEqual(45, milk->getQuantity());    // 50 - 5 = 45
            Assert::AreEqual(27, cheese->getQuantity());  // 30 - 3 = 27

            // 12. Проверяем обновленный ассортимент
            Assert::AreEqual(162, warehouse.getTotalItemsCount()); // 90 + 45 + 27 = 162
        }

        TEST_METHOD(TestSalesPeriodStatistics)
        {
            // Создаем клиента
            auto client = make_shared<Client>("CL001", "Тестовый клиент", 10.0);

            // Создаем товар
            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 1000);

            // Создаем накладные за разные периоды
            vector<Invoice> invoices;

            // Январские накладные
            Invoice inv1("INV001", "2024-01-10", client.get());
            inv1.addItem(product.get(), 10, product->getPrice());
            invoices.push_back(inv1);

            Invoice inv2("INV002", "2024-01-20", client.get());
            inv2.addItem(product.get(), 20, product->getPrice());
            invoices.push_back(inv2);

            // Февральская накладная
            Invoice inv3("INV003", "2024-02-05", client.get());
            inv3.addItem(product.get(), 15, product->getPrice());
            invoices.push_back(inv3);

            // Мартовская накладная
            Invoice inv4("INV004", "2024-03-10", client.get());
            inv4.addItem(product.get(), 25, product->getPrice());
            invoices.push_back(inv4);

            // Считаем продажи за январь
            double januaryRevenue = 0;
            int januaryInvoices = 0;
            int januaryItemsSold = 0;

            for (const auto& invoice : invoices) {
                if (invoice.isInPeriod("2024-01-01", "2024-01-31")) {
                    januaryRevenue += invoice.getTotalAmount();
                    januaryInvoices++;
                    januaryItemsSold += invoice.getTotalItemsSold();
                }
            }

            // Январь: 10 + 20 = 30 товаров
            // 10 товаров: 1000 руб - 10% = 900 руб
            // 20 товаров: 2000 руб - 10% = 1800 руб
            // Итого: 900 + 1800 = 2700 руб
            Assert::AreEqual(2700.0, januaryRevenue);
            Assert::AreEqual(2, januaryInvoices);
            Assert::AreEqual(30, januaryItemsSold);

            // Считаем продажи за первый квартал (январь-март)
            double quarterRevenue = 0;
            int quarterInvoices = 0;

            for (const auto& invoice : invoices) {
                if (invoice.isInPeriod("2024-01-01", "2024-03-31")) {
                    quarterRevenue += invoice.getTotalAmount();
                    quarterInvoices++;
                }
            }

            // Квартал: 10 + 20 + 15 + 25 = 70 товаров
            // Январь: 30 товаров = 2700 руб
            // Февраль: 15 товаров = 1500 руб - 10% = 1350 руб
            // Март: 25 товаров = 2500 руб - 10% = 2250 руб
            // Итого: 2700 + 1350 + 2250 = 6300 руб
            Assert::AreEqual(6300.0, quarterRevenue);
            Assert::AreEqual(4, quarterInvoices);
        }

        TEST_METHOD(TestClientDiscountFunctionality)
        {
            // Создаем клиентов с разными скидками
            vector<shared_ptr<Client>> clients;

            clients.push_back(make_shared<Client>("CL001", "ИП Петров", 5.0));
            clients.push_back(make_shared<Client>("CL002", "ООО Вектор", 10.0));
            clients.push_back(make_shared<Client>("CL003", "Магазин У дома", 0.0));
            clients.push_back(make_shared<Client>("CL004", "Столовая №5", 7.0));
            clients.push_back(make_shared<Client>("CL005", "Ресторан Европа", 0.0));
            clients.push_back(make_shared<Client>("CL006", "Кофейня Утро", 12.5));

            // Проверяем клиентов со скидкой
            int clientsWithDiscount = 0;
            for (const auto& client : clients) {
                if (client->hasDiscountStatus()) {
                    clientsWithDiscount++;
                }
            }

            Assert::AreEqual(4, clientsWithDiscount); // 4 клиента со скидкой

            // Создаем товар
            auto product = make_shared<Product>("PRD001", "Тестовый товар", 100.0, 100);

            // Проверяем расчеты с разными скидками
            Invoice inv1("INV001", "2024-01-15", clients[0].get()); // 5% скидка
            inv1.addItem(product.get(), 10, product->getPrice());
            Assert::AreEqual(950.0, inv1.getTotalAmount()); // 1000 - 5% = 950

            Invoice inv2("INV002", "2024-01-16", clients[1].get()); // 10% скидка
            inv2.addItem(product.get(), 10, product->getPrice());
            Assert::AreEqual(900.0, inv2.getTotalAmount()); // 1000 - 10% = 900

            Invoice inv3("INV003", "2024-01-17", clients[2].get()); // без скидки
            inv3.addItem(product.get(), 10, product->getPrice());
            Assert::AreEqual(1000.0, inv3.getTotalAmount()); // 1000 - 0% = 1000

            Invoice inv4("INV004", "2024-01-18", clients[5].get()); // 12.5% скидка
            inv4.addItem(product.get(), 10, product->getPrice());
            Assert::AreEqual(875.0, inv4.getTotalAmount()); // 1000 - 12.5% = 875

            // Проверяем что скидки не влияют на количество товара
            Assert::AreEqual(60, product->getQuantity()); // 100 - 10*4 = 60
        }

        TEST_METHOD(TestMultipleStoresAndClients)
        {
            // Создаем склад
            Warehouse warehouse;

            // Создаем товары
            auto bread = make_shared<Product>("PRD001", "Хлеб", 50.0, 200);
            auto milk = make_shared<Product>("PRD002", "Молоко", 80.0, 150);

            warehouse.addProduct(bread.get());
            warehouse.addProduct(milk.get());

            // Создаем магазины
            auto supermarket = make_shared<Store>("STR001", "Супермаркет");
            auto minimarket = make_shared<Store>("STR002", "Минимаркет");

            // Добавляем заказы
            supermarket->addOrder(bread.get(), 30);
            supermarket->addOrder(milk.get(), 20);

            minimarket->addOrder(bread.get(), 15);
            minimarket->addOrder(milk.get(), 10);

            // Создаем клиентов
            auto client1 = make_shared<Client>("CL001", "ИП Петров", 5.0);
            auto client2 = make_shared<Client>("CL002", "ООО Вектор", 10.0);

            // Создаем накладные для разных клиентов
            vector<Invoice> invoices;

            Invoice inv1("INV001", "2024-01-10", client1.get());
            inv1.addItem(bread.get(), 10, bread->getPrice());
            inv1.addItem(milk.get(), 5, milk->getPrice());
            invoices.push_back(inv1);

            Invoice inv2("INV002", "2024-01-15", client2.get());
            inv2.addItem(bread.get(), 20, bread->getPrice());
            inv2.addItem(milk.get(), 10, milk->getPrice());
            invoices.push_back(inv2);

            // Проверяем общую статистику
            double totalRevenue = 0;
            int totalItemsSold = 0;

            for (const auto& invoice : invoices) {
                totalRevenue += invoice.getTotalAmount();
                totalItemsSold += invoice.getTotalItemsSold();
            }

            // Накладная 1: 10 хлеба (500 руб) + 5 молока (400 руб) = 900 руб - 5% = 855 руб
            // Накладная 2: 20 хлеба (1000 руб) + 10 молока (800 руб) = 1800 руб - 10% = 1620 руб
            // Итого: 855 + 1620 = 2475 руб
            Assert::AreEqual(2475.0, totalRevenue);
            Assert::AreEqual(45, totalItemsSold); // 10+5 + 20+10 = 45

            // Проверяем остатки
            Assert::AreEqual(170, bread->getQuantity()); // 200 - 10 - 20 = 170
            Assert::AreEqual(135, milk->getQuantity());  // 150 - 5 - 10 = 135

            // Проверяем заказы магазинов
            Assert::AreEqual(30 + 15, supermarket->getTotalOrderedItems() + minimarket->getTotalOrderedItems());
        }
    };
}