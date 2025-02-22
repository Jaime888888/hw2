#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    MyDataStore ds; // Use the derived data store class

    // Instantiate the individual section and product parsers
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        if(ss >> cmd) {
            cmd = convToLower(cmd); // Make case-insensitive

            if(cmd == "and" || cmd == "or") {
                vector<string> terms;
                string term;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, cmd == "and" ? 0 : 1);
                displayProducts(hits);
            }
            else if (cmd == "add") {
                string username;
                int index;
                if(ss >> username >> index) {
                    if (index > 0 && index <= (int)hits.size()) {
                        ds.addToCart(username, hits[index - 1]);
                    } else {
                        cout << "Invalid request" << endl;
                    }
                } else {
                    cout << "Invalid request" << endl;
                }
            }
            else if (cmd == "viewcart") {
                string username;
                if(ss >> username) {
                    ds.viewCart(username);
                } else {
                    cout << "Invalid username" << endl;
                }
            }
            else if (cmd == "buycart") {
                string username;
                if(ss >> username) {
                    ds.buyCart(username);
                } else {
                    cout << "Invalid username" << endl;
                }
            }
            else if (cmd == "quit") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.empty()) {
        cout << "No results found!" << endl;
        return;
    }
    sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
