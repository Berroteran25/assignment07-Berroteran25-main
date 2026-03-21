
#include "code.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>

using namespace std;

// Helper to create the generator once
std::mt19937 initializeRng(int seed) {
    return std::mt19937(static_cast<std::mt19937::result_type>(seed));
}

// Helper to print MenuItemNames
static std::ostream& operator<<(std::ostream& os, const MenuItemNames& name) {
    switch (name) {
        case MenuItemNames::Espresso:
            os << "Espresso";
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
        case MenuItemNames::Americano:
            os << "Americano";
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

static DailyStatistics& currentStats(Cafe& cafe) {
    if (cafe.stats.empty()) {
        throw runtime_error("Negative value not allowed");
    }
    return cafe.stats.back();
}

static const DailyStatistics& currentStats(const Cafe& cafe) {
    if (cafe.stats.empty()) {
        throw runtime_error("Negative value not allowed");
    }
    return cafe.stats.back();
}

static bool sameDate(const Date& a, const Date& b) {
    return a.month == b.month && a.day == b.day && a.year == b.year;
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

static string formatTime(int minutes_after_open) {
    if (minutes_after_open < 0) {
        throw runtime_error("Negative value not allowed");
    }

    int total_minutes = 12 * 60 + minutes_after_open;
    int hour24 = total_minutes / 60;
    int minute = total_minutes % 60;

    string suffix = "p.m.";
    int hour12 = hour24;

    if (hour24 == 0) {
        hour12 = 12;
        suffix = "a.m.";
    } else if (hour24 < 12) {
        suffix = "a.m.";
    } else if (hour24 == 12) {
        suffix = "p.m.";
    }else if (hour24 < 24) {
        hour12 = hour24 - 12;
        suffix = "p.m.";
    } else {
        hour12 = 12;
        suffix = "a.m.";
    }

    ostringstream out;
    out << hour12 << ":" << setw(2) << setfill('0') << minute << " " << suffix;
    return out.str();
}

static bool hasInProgressOrders(const Cafe& cafe) {
    if (cafe.stats.empty()) {
        return false;
    }

    for (const Order& order : currentStats(cafe).orders) {
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
    if (p < 0.0 || p > 1.0 || cafe.staff.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    vector<Barista> on_duty;

    for (const Barista& barista : cafe.staff) {
        if (barista.speed_factor <= 0.0) {
            throw runtime_error("Negative value not allowed");
        }

        bool shows_up = drawBernoulli(p, rng);   // consume RNG for every barista

        if (barista.is_manager || shows_up) {
            Barista copy = barista;
            copy.num_orders_handled = 0;
            copy.busy_until = 0;
            on_duty.push_back(copy);
        }
    }

    return on_duty;
}

void displayOpeningNote(const Cafe& cafe, const DailyStatistics& today) {
    if (cafe.name == "missing" || !validDate(today.date) || today.staff_on_duty.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "Welcome to " << cafe.name << "!" << "\n\n";
    cout << "Today is " << today.date.month << "/" << today.date.day << "/" << today.date.year << "." << "\n";

    size_t n = today.staff_on_duty.size();

    if (n == 1) {
        cout << "Your barista today is " << today.staff_on_duty[0].name << "." << "\n\n";
        return;
    }

    cout << "Your baristas today are ";
    for (size_t i = 0; i < n; i++) {
        cout << today.staff_on_duty[i].name;
        if (i < n - 2) {
            cout << ", ";
        } else if (i == n - 2) {
            cout << " and ";
        }
    }
    cout << "." << "\n\n";
}

vector<int> generateArrivalTimes(double lambda, int closing_time, std::mt19937& rng) {
    if (lambda <= 0.0 || closing_time <= 0) {
        throw runtime_error("Negative value not allowed");
    }

    vector<int> arrivals;
    int current_time = 0;

    while (lambda > 0.001) {
        double u = drawUniformReal(rng);
        int inter_arrival_time = static_cast<int>(floor(-log(u) / lambda));
        current_time += inter_arrival_time;

        if (current_time >= closing_time) {
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
    order.quantity = drawUniformInt(1, 3, rng);
    order.status = OrderStatus::Pending;
    order.customer_arrival_time = current_time;
    order.barista_name = "missing";
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

    const DailyStatistics& today = currentStats(cafe);

    for (const Barista& barista : today.staff_on_duty) {
        if (barista.busy_until <= current_time) {
            return true;
        }
    }

    return false;
}

void abandonOrder(Cafe& cafe, int current_time, Order& order) {
    if (current_time < 0 || order.id <= 0) {
        throw runtime_error("Negative value not allowed");
    }

    order.status = OrderStatus::Abandoned;
    order.end_time = current_time;

    if (!cafe.stats.empty()) {
        DailyStatistics& today = currentStats(cafe);
        today.count_abandoned++;
        if (today.count_pending > 0) {
            today.count_pending--;
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

    DailyStatistics& today = currentStats(cafe);
    vector<int> available_indices;

    for (int i = 0; i < static_cast<int>(today.staff_on_duty.size()); i++) {
        if (today.staff_on_duty[i].busy_until <= current_time) {
            available_indices.push_back(i);
        }
    }

    if (available_indices.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    if (available_indices.size() == 1) {
        return today.staff_on_duty[available_indices[0]];
    }

    int chosen = drawUniformInt(0, static_cast<int>(available_indices.size()) - 1, rng);
    return today.staff_on_duty[available_indices[chosen]];
}

int calcPrepTime(const Cafe& cafe, const Order& order, const Barista& barista) {
    if (order.quantity <= 0 || barista.speed_factor <= 0.0) {
        throw runtime_error("Negative value not allowed");
    }

    int item_index = static_cast<int>(order.menu_item_name);
    if (item_index < 0 || item_index >= static_cast<int>(cafe.menu.size())) {
        throw runtime_error("Negative value not allowed");
    }

    if (cafe.menu[item_index].prep_time <= 0) {
        throw runtime_error("Negative value not allowed");
    }

    double base_time = static_cast<double>(cafe.menu[item_index].prep_time) * order.quantity;
    return static_cast<int>(ceil(base_time / barista.speed_factor));
}

void assignOrderToBarista(Cafe& cafe, int current_time, Order& order, Barista& barista) {
    if (current_time < 0 || order.id <= 0 || order.quantity <= 0 || barista.speed_factor <= 0.0) {
        throw runtime_error("Negative value not allowed");
    }

    int prep_time = calcPrepTime(cafe, order, barista);

    order.status = OrderStatus::In_progress;
    order.barista_name = barista.name;
    order.start_time = current_time;
    order.end_time = current_time + prep_time;

    barista.busy_until = order.end_time;
    barista.num_orders_handled++;

    if (!cafe.stats.empty()) {
        DailyStatistics& today = currentStats(cafe);
        if (today.count_pending > 0) {
            today.count_pending--;
        }
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
    if (order.id <= 0 || order.quantity <= 0) {
        throw runtime_error("Negative value not allowed");
    }

    int item_index = static_cast<int>(order.menu_item_name);

    if (order.status == OrderStatus::Completed || order.status == OrderStatus::Abandoned) {
        throw runtime_error("Negative value not allowed");
    }

    order.status = OrderStatus::Completed;

    if (!cafe.stats.empty()) {
        DailyStatistics& today = currentStats(cafe);
        today.count_completed++;
        today.revenue += cafe.menu[item_index].price * order.quantity;
    }
}

void displayOrderCompleted(const Order& order) {
    if (order.id <= 0 || order.end_time < 0) {
        throw runtime_error("Negative value not allowed");
    }

    cout << "[Order " << order.id << "] is completed at "
         << formatTime(order.end_time) << "\n";
}

void simulateDailyOperation(Cafe& cafe, Date& date, const Parameters& params, int seed) {
    if (!validDate(date) || params.max_waiting_time < 0 || params.closing_time <= 0 ||
        params.p < 0.0 || params.p > 1.0 || params.lambda <= 0.0) {
        throw runtime_error("Negative value not allowed");
    }

    if (cafe.name == "missing" || cafe.menu.empty() || cafe.staff.empty()) {
        throw runtime_error("Negative value not allowed");
    }

    Order::next_id = 1;

    DailyStatistics today;
    today.date = date;

    mt19937 rng = initializeRng(seed);
    today.staff_on_duty = getStaff(cafe, params.p, rng);
    cafe.stats.push_back(today);

    displayOpeningNote(cafe, currentStats(cafe));

    vector<int> arrivals = generateArrivalTimes(params.lambda, params.closing_time, rng);
    int arrival_index = 0;

    for (int current_time = 0; current_time < params.closing_time; current_time++) {
        DailyStatistics& active = currentStats(cafe);

        // Complete orders finishing now
        for (Order& order : active.orders) {
            if (order.status == OrderStatus::In_progress && order.end_time == current_time) {
                completeOrder(cafe, order);
                displayOrderCompleted(order);
            }
        }

        // Add arrivals at this minute
        while (arrival_index < static_cast<int>(arrivals.size()) &&
               arrivals[arrival_index] == current_time) {
            Order order = generateOrder(current_time, rng);
            active.orders.push_back(order);
            active.count_pending++;
            displayCustomerArrival(active.orders.back());
            arrival_index++;
        }

        // Abandon orders that have waited too long
        for (int i = active.next_in_line_index; i < static_cast<int>(active.orders.size()); i++) {
            if (active.orders[i].status == OrderStatus::Pending &&
                current_time - active.orders[i].customer_arrival_time > params.max_waiting_time) {
                abandonOrder(cafe, current_time, active.orders[i]);
                displayOrderAbandoned(active.orders[i]);
            }
        }

        // Move queue pointer forward past any non-pending orders
        while (active.next_in_line_index < static_cast<int>(active.orders.size()) &&
               active.orders[active.next_in_line_index].status != OrderStatus::Pending) {
            active.next_in_line_index++;
        }

        // Assign oldest pending orders while baristas are available
        while (anyBaristaAvailable(cafe, current_time)) {
            while (active.next_in_line_index < static_cast<int>(active.orders.size()) &&
                   active.orders[active.next_in_line_index].status != OrderStatus::Pending) {
                active.next_in_line_index++;
            }

            if (active.next_in_line_index >= static_cast<int>(active.orders.size())) {
                break;
            }

            Barista& barista = findAvailableBarista(cafe, current_time, rng);
            assignOrderToBarista(cafe, current_time, active.orders[active.next_in_line_index], barista);
            displayOrderStarted(active.orders[active.next_in_line_index]);

            active.next_in_line_index++;

            while (active.next_in_line_index < static_cast<int>(active.orders.size()) &&
                   active.orders[active.next_in_line_index].status != OrderStatus::Pending) {
                active.next_in_line_index++;
            }
        }
    }

    // After closing, only finish orders already in progress
    int current_time = params.closing_time;
    while (hasInProgressOrders(cafe)) {
        DailyStatistics& active = currentStats(cafe);

        for (Order& order : active.orders) {
            if (order.status == OrderStatus::In_progress && order.end_time == current_time) {
                completeOrder(cafe, order);
                displayOrderCompleted(order);
            }
        }

        current_time++;
    }

    // Final queue position: first not-yet-assigned pending order, or orders.size()
    DailyStatistics& active = currentStats(cafe);
    while (active.next_in_line_index < static_cast<int>(active.orders.size()) &&
           active.orders[active.next_in_line_index].status != OrderStatus::Pending) {
        active.next_in_line_index++;
    }
}

void displayDailyStats(const Cafe& cafe, const Date& date) {
    for (const DailyStatistics& today : cafe.stats) {
        if (today.date.month == date.month &&
            today.date.day == date.day &&
            today.date.year == date.year) {

            cout << "\n=== Daily Summary for "
                 << today.date.month << "/" << today.date.day << "/" << today.date.year
                 << " ===\n";

            cout << fixed << setprecision(2);
            cout << "Revenue: $" << today.revenue << "\n";
            cout << "Orders completed: " << today.count_completed << "\n";
            cout << "Orders abandoned: " << today.count_abandoned << "\n";

            cout << "Barista performance:\n";
            cout << "---------------------------\n";
            cout << left << setw(12) << "Name" << setw(10) << "Orders" << "\n";
            cout << "---------------------------\n";

            for (const Barista& barista : today.staff_on_duty) {
                cout << left << setw(12) << barista.name
                     << setw(10) << barista.num_orders_handled << "\n";
            }

            cout << "---------------------------\n";
            return;
        }
    }

    cout << ">>> No statistics available for "
         << date.month << "/" << date.day << "/" << date.year << ".\n";
}