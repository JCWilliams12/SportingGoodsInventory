#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>
#include <iomanip>

// Base Class
class Item {
protected:
    double price;

public:
    std::string department;
    std::string section;
    std::string itemName;
    int quantity;
    double discount;

    Item(std::string dept, std::string sect, std::string name, int qty, double p);
    virtual ~Item() {}

    double getPrice() const;
    void setPrice(double newPrice);
    double getDiscountedPrice() const;

    // display item details in terminal
    virtual std::string getDetails() const;
};

// --=-=-=-=--Child Classes-=-=-=-=-=-

class VolleyballItem : public Item {
public:
    std::string trainingType;
    VolleyballItem(std::string name, int qty, double p, std::string tType);
    std::string getDetails() const override;
};

class TableTennisItem : public Item {
public:
    std::string style;
    std::string material;
    TableTennisItem(std::string name, int qty, double p, std::string sty, std::string mat);
    std::string getDetails() const override;
};

class CampingItem : public Item {
public:
    std::string weatherRating;
    CampingItem(std::string name, int qty, double p, std::string wx);
    std::string getDetails() const override;
};

class SoccerItem : public Item {
public:
    std::string size;
    SoccerItem(std::string name, int qty, double p, std::string sz);
    std::string getDetails() const override;
};

#endif