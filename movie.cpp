#include "movie.h"
#include "util.h"
#include <sstream>
using namespace std;

Movie::Movie(const std::string &name, double price, int qty, const std::string &genre, const std::string &rating) : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keys = parseStringToWords(getName());
    keys.insert(genre_);
    return keys;
}

std::string Movie::displayString() const {
    std::ostringstream oss;
    oss << getName() << "\n"
        << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
        << getPrice() << " " << getQty() << " left.";
    return oss.str();
}

void Movie::dump(std::ostream &os) const {
    os << "movie" << "\n"
       << getName() << "\n"
       << getPrice() << "\n"
       << getQty() << "\n"
       << genre_ << "\n"
       << rating_ << "\n";
}
