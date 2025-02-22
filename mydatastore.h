#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <vector>
#include <map>
#include <set>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store.
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store.
     */
    void addUser(User* u) override;

    /**
     * Searches for products matching the given terms.
     * type 0 = AND search (intersection)
     * type 1 = OR search (union)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Saves the current database state.
     */
    void dump(std::ostream& ofile) override;

    /**
     * Adds a product to the user's cart.
     */
    void addToCart(std::string username, Product* p);

    /**
     * Displays the user's cart.
     */
    void viewCart(std::string username);

    /**
     * Processes purchases from the user's cart.
     */
    void buyCart(std::string username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::set<Product*>> keywordMap_;
    
    // Maps usernames to their shopping carts (FIFO order)
    std::map<std::string, std::vector<Product*>> carts_;
};

#endif
