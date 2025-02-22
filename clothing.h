#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "util.h"
#include <set>
#include <string>

class Clothing : public Product {
public:
    Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string& brand);

    /**
     * Returns a set of keywords associated with this clothing item.
     */
    std::set<std::string> keywords() const override;

    /**
     * Displays the clothing's information.
     */
    std::string displayString() const override;

    /**
     * Outputs the clothing info in the database format.
     */
    void dump(std::ostream& os) const override;

private:
    std::string size_;
    std::string brand_;
};

#endif
