#include "code.h"
#include <iostream>
#include <iomanip>   // std::setw, std::setprecision
#include <stdexcept>
#include <cmath>
#include <sstream>

using namespace std;


// Helper to create the generator once
std::mt19937 initializeRng(int seed) {
    return std::mt19937(static_cast<std::mt19937::result_type>(seed));
}

// Helper to std::out MenuItemNames
static std::ostream& operator<<(std::ostream& os, const MenuItemNames& name) {
    switch (name) {
    case MenuItemNames::Americano:
        os << "Americano";
        break;
    case MenuItemNames::Doppio:
        os << "Doppio";
        break;
    case MenuItemNames::Latte:
        os << "Latte";
        break;
    case MenuItemNames::Cappuccino:
        os << "Cappuccino";
        break;
    case MenuItemNames::Espresso:
        os << "Espresso";
        break;
    case MenuItemNames::Mocha:
        os << "Mocha";
        break;
    case MenuItemNames::Macchiato:
        os << "Macchiato";
        break;
    default:
        os << "<unknown>";
        break;
    }
    return os;
}

int Order::next_id = 1;

// ============================================================
// Internal helpers
// ============================================================

static string formatTime(int minutes_after_open) {
    if (minutes_after_open < 0) {
        throw runtime_error("Negative value not allowed");
    }

    int total_minutes = 12 * 60 + minutes_after_open;
    int hour24 = total_minutes / 60;
    int minute = total_minutes % 60;

    string suffix = (hour24 < 12) ? "a.m." : "p.m.";
    int hour12 = hour24 % 12;
    if (hour12 == 0) {
        hour12 = 12;
    }

    ostringstream out;
    out << hour12 << ":" << setw(2) << setfill('0') << minute << " " << suffix;
    return out.str();
}

static bool validDate(const Date& date) {
    if (date.month <= 0 || date.day <= 0 || date.year <= 0) {
        return false;
    }
    if (date.month > 12) {
        return false;
    }

    int days_in_month = 31;
    if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
        days_in_month = 30;
    } else if (date.month == 2) {
        bool leap = (date.year % 400 == 0) || (date.year % 4 == 0 && date.year % 100 != 0);
        days_in_month = leap ? 29 : 28;
    }

    return date.day <= days_in_month;
}

static bool hasInProgressOrders(const Cafe& cafe) {
    for (const Order& order : cafe.stats.orders) {
        if (order.status == OrderStatus::In_progress) {
            return true;
        }
    }
    return false;
}

// ============================================================
// Required functions
// ============================================================

bool drawBernoulli(double p, std::mt19937& rng) {
    if (p < 0.0 || p > 1.0) {
        throw runtime_error("Negative value not allowed");
    }

    bernoulli_distribution dist(p);
    return dist(rng);
}

int drawUniformInt(int min, int max, std::mt19937& rng) {
    if (min < 0 || max < 0) {
        throw runtime_error("Negative value not allowed");
    }
    if (min > max) {
        throw runtime_error("Negative value not allowed");
    }
    if (min == max) {
        return min;
    }

    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

double drawUniformReal(std::mt19937& rng) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    double value = dist(rng);

    while (value <= 0.0 || value >= 1.0) {
        value = dist(rng);
    }

    return value;
}

vector<Barista> getStaff(const Cafe& cafe, double p, std::mt19937& rng) {
    if (p < 0.0 || p > 1.0) {
        throw runtime_error("Negative value not allowed");
    }
    if (cafe.staff.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    vector<Barista> staff_today;

    for (const Barista& barista : cafe.staff) {
        if (barista.speed_factor <= 0.0) {
            throw runtime_error("Negative value not allowed");
        }

        if (barista.is_manager || drawBernoulli(p, rng)) {
            Barista copy = barista;
            copy.num_orders_handled = 0;
            copy.busy_until = 0;
            staff_today.push_back(copy);
        }
    }

    return staff_today;
}

void displayOpeningNote(const Cafe& cafe, const DailyStatistics& today) {
    if (cafe.name == "missing" || !validDate(today.date)) {
        throw runtime_error("Negative value not allowed");
    }
    if (today.staff_on_duty.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "Welcome to " << cafe.name << "!\n\n";
    cout << "Today is " << today.date.month << "/" << today.date.day << "/" << today.date.year << ".\n";
    cout << "Your baristas today are ";

    for (size_t i = 0; i < today.staff_on_duty.size(); i++) {
        cout << today.staff_on_duty[i].name;
        if (i + 2 < today.staff_on_duty.size()) {
            cout << ", ";
        } else if (i + 1 < today.staff_on_duty.size()) {
            cout << " and ";
        }
    }

    cout << ".\n";
}

vector<int> generateArrivalTimes(double lambda, int closing_time, std::mt19937& rng) {
    if (lambda <= 0.0 || closing_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    vector<int> arrivals;
    int current_time = 0;

    while (true) {
        double u = drawUniformReal(rng);
        int inter_arrival_time = static_cast<int>(floor(-log(u) / lambda));
        current_time += inter_arrival_time;

        if (current_time > closing_time) {
            break;
        }

        arrivals.push_back(current_time);
    }

    return arrivals;
}

Order generateOrder(int current_time, std::mt19937& rng) {
    if (current_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    Order order;
    order.id = Order::next_id++;
    order.menu_item_name = static_cast<MenuItemNames>(
        drawUniformInt(0, static_cast<int>(MenuItemNames::Num_Items) - 1, rng)
    );
    order.barista_name = "missing";
    order.quantity = drawUniformInt(1, 3, rng);
    order.status = OrderStatus::Pending;
    order.customer_arrival_time = current_time;
    order.start_time = 0;
    order.end_time = 0;

    return order;
}

void displayCustomerArrival(const Order& order) {
    if (order.id <= 0 || order.quantity <= 0 || order.customer_arrival_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "[Order " << order.id << "] A new customer arrived at "
         << formatTime(order.customer_arrival_time)
         << " and ordered " << order.quantity << " "
         << order.menu_item_name << "(s)\n";
}

bool anyBaristaAvailable(const Cafe& cafe, int current_time) {
    if (current_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    for (const Barista& barista : cafe.stats.staff_on_duty) {
        if (barista.busy_until <= current_time) {
            return true;
        }
    }

    return false;
}

void abandonOrder(Cafe& cafe, int current_time, Order& order) {
    if (current_time < 0) {
        throw runtime_error("Negative value not allowed");
    }
    if (order.id <= 0) {
        throw runtime_error("Negative value not allowed");
    }

    if (order.status == OrderStatus::Pending) {
        order.status = OrderStatus::Abandoned;
        order.end_time = current_time;
        cafe.stats.count_abandoned++;
        if (cafe.stats.count_pending > 0) {
            cafe.stats.count_pending--;
        }
    }
}

void displayOrderAbandoned(const Order& order) {
    if (order.id <= 0 || order.end_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "[Order " << order.id << "] is abandoned at "
         << formatTime(order.end_time) << "\n";
}

Barista& findAvailableBarista(Cafe& cafe, int current_time, std::mt19937& rng) {
    if (current_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    vector<int> available_indices;

    for (int i = 0; i < static_cast<int>(cafe.stats.staff_on_duty.size()); i++) {
        if (cafe.stats.staff_on_duty[i].busy_until <= current_time) {
            available_indices.push_back(i);
        }
    }

    if (available_indices.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    int chosen_pos = drawUniformInt(0, static_cast<int>(available_indices.size()) - 1, rng);
    return cafe.stats.staff_on_duty[available_indices[chosen_pos]];
}

int calcPrepTime(const Cafe& cafe, const Order& order, const Barista& barista) {
    if (order.quantity <= 0 || barista.speed_factor <= 0.0) {
        throw runtime_error("Negative value not allowed");
    }

    int menu_index = static_cast<int>(order.menu_item_name);
    if (menu_index < 0 || menu_index >= static_cast<int>(cafe.menu.size())) {
        throw runtime_error("Negative value not allowed");
    }

    double total_base_time = cafe.menu[menu_index].prep_time * order.quantity;
    return static_cast<int>(ceil(total_base_time / barista.speed_factor));
}

void assignOrderToBarista(Cafe& cafe, int current_time, Order& order, Barista& barista) {
    if (current_time < 0) {
        throw runtime_error("Negative value not allowed");
    }
    if (order.status != OrderStatus::Pending) {
        throw runtime_error("Negative value not allowed");
    }

    int prep_time = calcPrepTime(cafe, order, barista);

    order.status = OrderStatus::In_progress;
    order.barista_name = barista.name;
    order.start_time = current_time;
    order.end_time = current_time + prep_time;

    barista.busy_until = order.end_time;
    barista.num_orders_handled++;

    if (cafe.stats.count_pending > 0) {
        cafe.stats.count_pending--;
    }
}

void displayOrderStarted(const Order& order) {
    if (order.id <= 0 || order.start_time < 0 || order.barista_name == "missing") {
        throw runtime_error("Negative value not allowed");
    }

    cout << "[Order " << order.id << "] "
         << order.barista_name
         << " started preparing the order at "
         << formatTime(order.start_time) << "\n";
}

void completeOrder(Cafe& cafe, Order& order) {
    if (order.status != OrderStatus::In_progress) {
        throw runtime_error("Negative value not allowed");
    }

    int menu_index = static_cast<int>(order.menu_item_name);
    if (menu_index < 0 || menu_index >= static_cast<int>(cafe.menu.size())) {
        throw runtime_error("Negative value not allowed");
    }

    order.status = OrderStatus::Completed;
    cafe.stats.count_completed++;
    cafe.stats.revenue += cafe.menu[menu_index].price * order.quantity;
}

void displayOrderCompleted(const Order& order) {
    if (order.id <= 0 || order.end_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "[Order " << order.id << "] is completed at "
         << formatTime(order.end_time) << "\n";
}

void simulateDailyOperation(Cafe& cafe, Date& date, const Parameters& params, int seed) {
    if (params.max_waiting_time < 0 || params.closing_time < 0 || seed < 0) {
        throw runtime_error("Negative value not allowed");
    }
    if (params.lambda <= 0.0) {
        throw runtime_error("Negative value not allowed");
    }
    if (!validDate(date)) {
        throw runtime_error("Negative value not allowed");
    }

    Order::next_id = 1;

    cafe.stats = DailyStatistics{};
    cafe.stats.date = date;

    mt19937 rng = initializeRng(seed);

    // Change this field name here if your code.h uses a different one.
    cafe.stats.staff_on_duty = getStaff(cafe, params.show_up_probability, rng);

    displayOpeningNote(cafe, cafe.stats);
    cout << "\n";

    vector<int> arrival_times = generateArrivalTimes(params.lambda, params.closing_time, rng);
    int arrival_index = 0;

    for (int current_time = 0; current_time <= params.closing_time; current_time++) {
        // 1. Complete orders finishing now
        for (Order& order : cafe.stats.orders) {
            if (order.status == OrderStatus::In_progress && order.end_time == current_time) {
                completeOrder(cafe, order);
                displayOrderCompleted(order);
            }
        }

        // 2. Add arriving customers
        while (arrival_index < static_cast<int>(arrival_times.size()) &&
               arrival_times[arrival_index] == current_time) {
            Order new_order = generateOrder(current_time, rng);
            cafe.stats.orders.push_back(new_order);
            cafe.stats.count_pending++;
            displayCustomerArrival(cafe.stats.orders.back());
            arrival_index++;
        }

        // 3. Abandon orders waiting too long
        for (Order& order : cafe.stats.orders) {
            if (order.status == OrderStatus::Pending &&
                current_time - order.customer_arrival_time > params.max_waiting_time) {
                abandonOrder(cafe, current_time, order);
                displayOrderAbandoned(order);
            }
        }

        // 4. Assign free baristas to oldest pending orders
        while (anyBaristaAvailable(cafe, current_time)) {
            int next_pending_index = -1;

            for (int i = cafe.stats.next_in_line_index; i < static_cast<int>(cafe.stats.orders.size()); i++) {
                if (cafe.stats.orders[i].status == OrderStatus::Pending) {
                    next_pending_index = i;
                    break;
                }
            }

            if (next_pending_index == -1) {
                break;
            }

            Barista& chosen = findAvailableBarista(cafe, current_time, rng);
            assignOrderToBarista(cafe, current_time, cafe.stats.orders[next_pending_index], chosen);
            displayOrderStarted(cafe.stats.orders[next_pending_index]);

            cafe.stats.next_in_line_index = next_pending_index + 1;
        }
    }

    // After closing, only finish orders already in progress
    int current_time = params.closing_time + 1;
    while (hasInProgressOrders(cafe)) {
        for (Order& order : cafe.stats.orders) {
            if (order.status == OrderStatus::In_progress && order.end_time == current_time) {
                completeOrder(cafe, order);
                displayOrderCompleted(order);
            }
        }
        current_time++;
    }
}

void displayDailyStats(const Cafe& cafe, const Date& date) {
    if (!validDate(date)) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "\n=== Daily Summary for "
         << date.month << "/" << date.day << "/" << date.year << " ===\n\n";

    cout << fixed << setprecision(2);
    cout << "Revenue: $" << cafe.stats.revenue << "\n";
    cout << "Orders completed: " << cafe.stats.count_completed << "\n";
    cout << "Orders abandoned: " << cafe.stats.count_abandoned << "\n\n";

    cout << "Barista performance:\n";
    cout << "---------------------------\n";
    cout << left << setw(12) << "Name" << setw(10) << "Orders" << "\n";
    cout << "---------------------------\n";

    for (const Barista& barista : cafe.stats.staff_on_duty) {
        cout << left << setw(12) << barista.name << setw(10) << barista.num_orders_handled << "\n";
    }

    cout << "---------------------------\n";
}