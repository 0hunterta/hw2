#include "mydatastore.h"
#include "user.h"
#include "product.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for(Product* p : products_) {
        delete p;
    }
    for(auto const& uPair : users_) {
        delete uPair.second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    if(!p) return;
    products_.push_back(p);
    std::set<std::string> keys = p->keywords();
    for(const std::string& kw : keys) {
        std::string lowerKW = convToLower(kw);
        keywordMap_[lowerKW].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    if(!u) return;
    std::string uname = convToLower(u->getName());
    users_[uname] = u;
    carts_[uname] = std::vector<Product*>();
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    if(terms.empty()) {
        return std::vector<Product*>();
    }

    std::set<Product*> result;
    std::string lowerTerm = convToLower(terms[0]);
    if(keywordMap_.find(lowerTerm) != keywordMap_.end()) {
        result = keywordMap_[lowerTerm];
    }
    for(size_t i = 1; i < terms.size(); i++) {
        std::string t = convToLower(terms[i]);
        std::set<Product*> temp;
        if(keywordMap_.find(t) != keywordMap_.end()) {
            temp = keywordMap_[t];
        }
        if(type == 0) {
            result = setIntersection(result, temp);
        }
        else {
            result = setUnion(result, temp);
        }
    }
    //std::vector<Product*> finalResult(result.begin(), result.end());
    std::vector<Product*> finalResult;
    for(Product* p : products_) {
        if(result.find(p) != result.end()) {
            finalResult.push_back(p);
        }
    }
    return finalResult;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for(Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for(auto const& uPair : users_) {
        User* u = uPair.second;
        ofile << u->getName() << " "
              << u->getBalance() << " "
              << u->getType() << endl;
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(const std::string& username, Product* p)
{
    std::string uname = convToLower(username);
    if(users_.find(uname) == users_.end()) {
        cout << "Invalid request" << endl;
        return;
    }
    carts_[uname].push_back(p);
}

void MyDataStore::viewCart(const std::string& username)
{
    std::string uname = convToLower(username);
    if(users_.find(uname) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    std::vector<Product*>& cart = carts_[uname];
    for(size_t i = 0; i < cart.size(); i++) {
        Product* p = cart[i];
        cout << i+1 << ": " << p->displayString() << endl << endl;
    }
}
void MyDataStore::buyCart(const std::string& username)
{
    std::string uname = convToLower(username);
    if(users_.find(uname) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    User* u = users_[uname];
    std::vector<Product*>& cart = carts_[uname];

    std::vector<Product*> newCart;

    for(Product* p : cart) {
        if((p->getQty() > 0) && (u->getBalance() >= p->getPrice())) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            newCart.push_back(p);
        }
    }

    cart = newCart;
}
