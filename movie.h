#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"
#include <set>
#include <string>

class Movie : public Product {
public:
    Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating);

    /**
     * Returns a set of keywords associated with this movie.
     */
    std::set<std::string> keywords() const override;

    /**
     * Displays the movie's information.
     */
    std::string displayString() const override;

    /**
     * Outputs the movie info in the database format.
     */
    void dump(std::ostream& os) const override;

private:
    std::string genre_;
    std::string rating_;
};

#endif
