#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <string>
#include <vector>
#include <map>
#include <set>

class Product;
class User;

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    void addToCart(const std::string& username, Product* p);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif
