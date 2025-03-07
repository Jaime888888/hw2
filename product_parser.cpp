#include <iostream>
#include <sstream>
#include "product_parser.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"

using namespace std;

ProductParser::ProductParser()
{
}

ProductParser::~ProductParser()
{
}

Product* ProductParser::parse(string category,
                              istream& is,
                              bool& error,
                              string& errorMsg,
                              int& lineno)
{
    parseCommonProduct(is, error, errorMsg, lineno);
    if(error) return NULL;
    return parseSpecificProduct(category, is, error, errorMsg, lineno);
}

void ProductParser::parseCommonProduct(std::istream& is,
                                       bool& error,
                                       string& errorMsg,
                                       int& lineno)
{
    string myline;
    getline(is, myline);
    myline = trim(myline);
    if(myline.size() == 0) {
        error = true;
        errorMsg = "Unable to find a product name";
        return;
    }
    prodName_ = myline;

    lineno++;
    getline(is, myline);
    if(is.fail()) {
        error = true;
        errorMsg = "Expected another line with the price";
        return;
    }
    stringstream ss1(myline);
    ss1 >> price_;
    if( ss1.fail() ) {
        error = true;
        errorMsg = "Unable to read price";
        return;
    }

    lineno++;
    getline(is, myline);
    if(is.fail()) {
        error = true;
        errorMsg = "Expected another line with the quantity";
        return;
    }
    stringstream ss2(myline);
    ss2 >> qty_;
    if( ss2.fail() ) {
        error = true;
        errorMsg = "Unable to read quantity";
        return;
    }
    lineno++;
}

/*************** Book Parser Implementation ***************/
ProductBookParser::ProductBookParser() : ProductParser()
{
}

Product* ProductBookParser::parseSpecificProduct(std::string category,
        std::istream& is,
        bool& error,
        std::string& errorMsg,
        int& lineno)
{
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> isbn_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read ISBN";
        return NULL;
    }

    lineno++;
    getline(is, author_);
    if(is.fail()) {
        error = true;
        errorMsg = "Unable to read author";
        return NULL;
    }

    lineno++;
    if(error) {
        return NULL;
    }
    return makeProduct();
}

std::string ProductBookParser::categoryID()
{
    return "book";
}

Product* ProductBookParser::makeProduct()
{
    return new Book(prodName_, price_, qty_, isbn_, author_);
}

/*************** Clothing Parser Implementation ***************/
ProductClothingParser::ProductClothingParser()
{
}

Product* ProductClothingParser::parseSpecificProduct(std::string category,
        std::istream& is,
        bool& error,
        std::string& errorMsg,
        int& lineno)
{
    string myline;
    getline(is, myline);
    size_ = myline; // Read size

    lineno++;
    getline(is, brand_);
    if(is.fail() || (brand_.size() == 0)) {
        error = true;
        errorMsg = "Unable to read brand";
        return NULL;
    }

    lineno++;
    if(error) {
        return NULL;
    }
    return makeProduct();
}

std::string ProductClothingParser::categoryID()
{
    return "clothing";
}

Product* ProductClothingParser::makeProduct()
{
    return new Clothing(prodName_, price_, qty_, size_, brand_);
}

/*************** Movie Parser Implementation ***************/
ProductMovieParser::ProductMovieParser()
{
}

Product* ProductMovieParser::parseSpecificProduct(std::string category,
        std::istream& is,
        bool& error,
        std::string& errorMsg,
        int& lineno)
{
    string myline;
    getline(is, genre_); // Read genre
    lineno++;
    
    getline(is, rating_); // Read rating
    if(is.fail()) {
        error = true;
        errorMsg = "Unable to read rating";
        return NULL;
    }

    lineno++;
    if(error) {
        return NULL;
    }
    return makeProduct();
}

std::string ProductMovieParser::categoryID()
{
    return "movie";
}

Product* ProductMovieParser::makeProduct()
{
    return new Movie(prodName_, price_, qty_, genre_, rating_);
}
