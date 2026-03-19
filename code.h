#pragma once

#include <string>
#include <vector>
#include <random>
#include <chrono>

enum class MenuItemNames {
    Espresso,
    Doppio,
    Latte,
    Cappuccino,
    Americano,
    Mocha,
    Macchiato,
    Num_Items,
};

struct MenuItem {
    int prep_time = 0;
    double price = 0.0;
};

enum class BaristaNames {
    Alan,
    Bella,
    Carlos,
    Daisy,
    Emma,
    Num_Baristas,
};

struct Barista {
    std::string name = "missing";
    bool is_manager = false;
    double speed_factor = 1.0;
    int num_orders_handled = 0;
    int busy_until = 0;
};

enum class OrderStatus {
    Pending,
    In_progress,
    Completed,
    Abandoned,
    Num_statuses,
};

struct Order {
    int id = 0;
    MenuItemNames menu_item_name = MenuItemNames::Num_Items;
    std::string barista_name = "missing";
    int quantity = 0;
    OrderStatus status = OrderStatus::Num_statuses;
    int customer_arrival_time = 0;
    int start_time = 0;
    int end_time = 0;
    static int next_id;
};

struct Customer {
    std::string name = "missing";
    int arrival_time = 0;
    int patience_sec = 0;
    Order order;
};

struct Date {
    int month = 0;
    int day = 0;
    int year = 0;
};

struct DailyStatistics {
    Date date;
    std::vector<Barista> staff_on_duty;
    std::vector<Order> orders;
    int next_in_line_index = 0;
    int count_completed = 0;
    int count_abandoned = 0;
    int count_pending = 0;
    double revenue = 0.0;
};

struct Cafe {
    std::string name = "missing";
    std::vector<MenuItem> menu;
    std::vector<Barista> staff;
    DailyStatistics stats;
};

struct Parameters {
    int max_waiting_time = 0;
    int closing_time = 0;
    double show_up_probability = 0.0;
    double lambda = 0.0;
};

std::mt19937 initializeRng(int seed);
bool drawBernoulli(double p, std::mt19937& rng);
int drawUniformInt(int min, int max, std::mt19937& rng);
double drawUniformReal(std::mt19937& rng);
std::vector<Barista> getStaff(const Cafe& cafe, double p, std::mt19937& rng);
void displayOpeningNote(const Cafe& cafe, const DailyStatistics& today);
std::vector<int> generateArrivalTimes(double lambda, int closing_time, std::mt19937& rng);
Order generateOrder(int current_time, std::mt19937& rng);
void displayCustomerArrival(const Order& order);
bool anyBaristaAvailable(const Cafe& cafe, int current_time);
void abandonOrder(Cafe& cafe, int current_time, Order& order);
void displayOrderAbandoned(const Order& order);
Barista& findAvailableBarista(Cafe& cafe, int current_time, std::mt19937& rng);
int calcPrepTime(const Cafe& cafe, const Order& order, const Barista& barista);
void assignOrderToBarista(Cafe& cafe, int current_time, Order& order, Barista& barista);
void displayOrderStarted(const Order& order);
void completeOrder(Cafe& cafe, Order& order);
void displayOrderCompleted(const Order& order);
void simulateDailyOperation(Cafe& cafe, Date& date, const Parameters& params, int seed);
void displayDailyStats(const Cafe& cafe, const Date& date);