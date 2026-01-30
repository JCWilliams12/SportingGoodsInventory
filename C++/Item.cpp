#include "Item.h"

// -=-=-=-=-=Base Class Implementation-=-=-=-=-=-
Item::Item(std::string dept, std::string sect, std::string name, int qty, double p)
    : department(dept), section(sect), itemName(name), quantity(qty), price(p), discount(0.0) {}

double Item::getPrice() const { return price; }

void Item::setPrice(double newPrice) {
    //make sure new price in non-negative
    if (newPrice >= 0.0) {
        price = newPrice;
    } else {
        price = 0.0; 
    }
}

double Item::getDiscountedPrice() const {
    return price * (1.0 - discount);
}

std::string Item::getDetails() const {
    std::stringstream ss;
    ss << std::left << std::setw(15) << itemName 
       << " | Qty: " << std::setw(4) << quantity 
       << " | $" << std::fixed << std::setprecision(2) << std::setw(7) << price
       << " | Disc: " << std::setw(3) << (int)(discount * 100) << "%"
       << " | Tot: $" << std::setw(7) << getDiscountedPrice();
    return ss.str();
}

// --=-=-=-=-Child Classes--=-=-=-=-

VolleyballItem::VolleyballItem(std::string name, int qty, double p, std::string tType)
    : Item("indoor", "volleyball", name, qty, p), trainingType(tType) {}

std::string VolleyballItem::getDetails() const {
    return Item::getDetails() + " | Type: " + trainingType;
}

TableTennisItem::TableTennisItem(std::string name, int qty, double p, std::string sty, std::string mat)
    : Item("indoor", "table_tennis", name, qty, p), style(sty), material(mat) {}

std::string TableTennisItem::getDetails() const {
    return Item::getDetails() + " | Sty: " + style + " | Mat: " + material;
}

CampingItem::CampingItem(std::string name, int qty, double p, std::string wx)
    : Item("outdoor", "camping", name, qty, p), weatherRating(wx) {}

std::string CampingItem::getDetails() const {
    return Item::getDetails() + " | Wx: " + weatherRating;
}

SoccerItem::SoccerItem(std::string name, int qty, double p, std::string sz)
    : Item("outdoor", "soccer", name, qty, p), size(sz) {}

std::string SoccerItem::getDetails() const {
    return Item::getDetails() + " | Size: " + size;
}