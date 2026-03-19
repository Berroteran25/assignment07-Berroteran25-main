#include "code.h"
#include <iostream>

int main() {
    MenuItem espresso = {2, 3.50};
    MenuItem doppio = {2, 5.0};
    MenuItem latte = {3, 7.50};
    MenuItem cappuccino = {3, 8.25};
    MenuItem americano = {2, 6.00};
    MenuItem mocha = {4, 10.25};
    MenuItem macchiato = {3, 8.50};
    std::vector<MenuItem> menu = {espresso, doppio, latte, cappuccino, americano, mocha, macchiato};

    Barista alan = {"Alan", false, 1, 0};
    Barista bella = {"Bella", false, 1.2};
    Barista carlos = {"Carlos", false, 1.7};
    Barista daisy = {"Daisy", false, 1.5};
    Barista emma = {"Emma", true, 2};
    std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};

    Cafe cafe;
    cafe.name = "Morning Grind";
    cafe.menu = menu;
    cafe.staff = staff;

    Date date = {3, 10, 2026};

    Parameters params;
    params.max_waiting_time = 10;
    params.closing_time = 600;
    params.p = 0.5;
    params.lambda = 0.2;

    int seed = 0;
    simulateDailyOperation(cafe, date, params, seed);
    displayDailyStats(cafe, date);

    return 0;
}