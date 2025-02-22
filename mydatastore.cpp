#include "mydatastore.h"
#include <iostream>

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    // Free allocated memory
    for (Product* p : products_) {
        delete p;
    }
    for (User* u : users_) {
        delete u;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    // Extract keywords and store in keywordMap_
    std::set<std::string> keywords = p->keywords();
    for (const std::string& keyword : keywords) {
        keywordMap_[convToLower(keyword)].insert(p);  // Store keywords in lowercase
    }
}

void MyDataStore::addUser(User* u)
{
    users_.push_back(u);
    carts_[u->getName()] = {};  // Initialize an empty cart for the user
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::set<Product*> resultSet;

    if (terms.empty()) {
        return std::vector<Product*>();
    }

    // Convert search terms to lowercase
    for (std::string& term : terms) {
        term = convToLower(term);
    }

    if (type == 0) { // AND search
        if (keywordMap_.find(terms[0]) != keywordMap_.end()) {
            resultSet = keywordMap_[terms[0]];
        } else {
            return std::vector<Product*>(); // If first term isn't found, return empty
        }

        for (size_t i = 1; i < terms.size(); i++) {
            if (keywordMap_.find(terms[i]) != keywordMap_.end()) {
                resultSet = setIntersection(resultSet, keywordMap_[terms[i]]);
            } else {
                return std::vector<Product*>(); // No results if any term is missing
            }
        }
    } else { // OR search
        for (const std::string& term : terms) {
            if (keywordMap_.find(term) != keywordMap_.end()) {
                resultSet = setUnion(resultSet, keywordMap_[term]);
            }
        }
    }

    return std::vector<Product*>(resultSet.begin(), resultSet.end());
}

void MyDataStore::addToCart(std::string username, Product* p)
{
    auto it = carts_.find(username);
    if (it != carts_.end()) {
        it->second.push_back(p); // Add product to user's cart (FIFO order)
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::viewCart(std::string username)
{
    auto it = carts_.find(username);
    if (it != carts_.end()) {
        if (it->second.empty()) {
            std::cout << "Cart is empty" << std::endl;
            return;
        }
        int itemNum = 1;
        for (Product* p : it->second) {
            std::cout << "Item " << itemNum << std::endl;
            std::cout << p->displayString() << std::endl;
            std::cout << std::endl;
            itemNum++;
        }
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::buyCart(std::string username)
{
    auto it = carts_.find(username);
    if (it != carts_.end()) {
        std::vector<Product*>& cart = it->second;
        std::vector<Product*> remainingItems;
        User* user = nullptr;

        // Find the user in the user list
        for (User* u : users_) {
            if (u->getName() == username) {
                user = u;
                break;
            }
        }

        if (!user) {
            std::cout << "Invalid username" << std::endl;
            return;
        }

        for (Product* p : cart) {
            if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
                user->deductAmount(p->getPrice());
                p->subtractQty(1);
            } else {
                remainingItems.push_back(p); // Keep item in cart if purchase fails
            }
        }

        // Update the cart with remaining items
        carts_[username] = remainingItems;
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>\n";
    for (Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>\n";

    ofile << "<users>\n";
    for (User* u : users_) {
        u->dump(ofile);
    }
    ofile << "</users>\n";
}
