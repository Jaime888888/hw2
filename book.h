#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "util.h"
#include <set>
#include <string>

class Book : public Product {
public:
    Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author);

    /**
     * Returns a set of keywords associated with this book.
     */
    std::set<std::string> keywords() const override;

    /**
     * Displays the book's information.
     */
    std::string displayString() const override;

    /**
     * Outputs the book info in the database format.
     */
    void dump(std::ostream& os) const override;

private:
    std::string isbn_;
    std::string author_;
};

#endif
