#include "book.h"
#include "util.h"
#include <sstream>
using namespace std;

Book::Book(const std::string &name, double price, int qty, const std::string &isbn, const std::string &author) : Product("book", name, price, qty), isbn_(isbn), author_(author)
{
}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys = parseStringToWords(getName());
    std::set<std::string> authKeys = parseStringToWords(author_);
    keys.insert(authKeys.begin(), authKeys.end());
    keys.insert(isbn_);
    return keys;
}

std::string Book::displayString() const {
    std::ostringstream oss;
    oss << getName() << "\n"
        << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << getPrice() << " " << getQty() << " left.";
    return oss.str();
}

void Book::dump(std::ostream &os) const {
    os << "book" << "\n"
       << getName() << "\n"
       << getPrice() << "\n"
       << getQty() << "\n"
       << isbn_ << "\n"
       << author_ << "\n";
}
