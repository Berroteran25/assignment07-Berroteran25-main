#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "code.h"
#include <iostream>
#include <sstream>

// // // enum and struct tests
// /*
// TEST_CASE("Enums and structs", "[10 points]") 
// {
//     // MenuItemNames
//     {
//     INFO("Check if MenuItemNames is an enum");
//         STATIC_REQUIRE(std::is_enum<MenuItemNames>::value);
//     }    
//     {
//     INFO("Check if MenuItemNames is an enum class and not a plain enum");
//         STATIC_REQUIRE(!std::is_convertible<MenuItemNames, int>::value);
//     }
//     INFO("Check if MenuItemNames enum has the correct number of elements.");
//         CHECK(static_cast<int>(MenuItemNames::Num_Items) == 7);
//     // MenuItem
//     {
//     INFO("Check if MenuItem is a class/struct type");
//         STATIC_REQUIRE(std::is_class<MenuItem>::value);
//     }
//     {
//     INFO("Check if MenuItem has correct element names and default initialization");
//         MenuItem menu_item;
//         CHECK(menu_item.prep_time == 0);
//         CHECK(menu_item.price == 0);
//     }
//     {
//     INFO("Check the number of elements in MenuItem");
//         struct TestMenuItem {
//             int prep_time {};
//             double price {};
//         } test_menu_item;
//         MenuItem menu_item;
//         CHECK(sizeof(test_menu_item) == sizeof(menu_item));
//     }

    // BaristaNames
    //{
//     INFO("Check if BaristaNames is an enum");
//         STATIC_REQUIRE(std::is_enum<BaristaNames>::value);
//     }    
//     {
//     INFO("Check if BaristaNames is an enum class and not a plain enum");
//         STATIC_REQUIRE(!std::is_convertible<BaristaNames, int>::value);
//     }
//     INFO("Check if BaristaNames enum has the correct number of  elements.");
//         CHECK(static_cast<int>(BaristaNames::Num_Baristas) == 5);
//     // Barista
//     {
//     INFO("Check if Barista is a class/struct type");
//         STATIC_REQUIRE(std::is_class<Barista>::value);
//     }
//     {
//     INFO("Check if Barista has correct element names and default initialization");
//         Barista barista;
//         CHECK(barista.name == "missing");
//         CHECK(barista.is_manager == false);
//         CHECK(barista.speed_factor == 1.0);
//         CHECK(barista.num_orders_handled == 0);
//         CHECK(barista.busy_until == 0);
//     }
//     {
//     INFO("Check the number of elements in Barista");
//         struct TestBarista{
//             std::string name = "missing";
//             bool is_manager = false;
//             double speed_factor = 1.0;
//             int num_orders_handled {};
//             int busy_until {};
//         } test_barista;
//         Barista barista;
//         CHECK(sizeof(test_barista) == sizeof(barista));
//     }
//     // OrderStatus
//     {
//     INFO("Check if OrderStatus is an enum");
//         STATIC_REQUIRE(std::is_enum<OrderStatus>::value);
//     }    
//     {
//     INFO("Check if OrderStatus is an enum class and not a plain enum");
//         STATIC_REQUIRE(!std::is_convertible<OrderStatus, int>::value);
//     }
//     INFO("Check if OrderStatus enum has the correct number of elements.");
//         CHECK(static_cast<int>(OrderStatus::Num_statuses) == 4);
//     // Order
//     {
//     INFO("Check if Order is a class/struct type");
//         STATIC_REQUIRE(std::is_class<Order>::value);
//     }
//     {
//     INFO("Check if Order has correct element names and default initialization");
//         Order order;
//         CHECK(order.id == 0);
//         CHECK(order.menu_item_name == MenuItemNames::Num_Items);
//         CHECK(order.barista_name == "missing");
//         CHECK(order.quantity == 0);
//         CHECK(order.status == OrderStatus::Num_statuses);
//         CHECK(order.customer_arrival_time == 0);
//         CHECK(order.start_time == 0);
//         CHECK(order.end_time == 0);
//     }
//     {
//     INFO("Check the number of elements in Order");
//         struct TestOrder {
//             int id {};
//             MenuItemNames menu_item_name= MenuItemNames::Num_Items;
//             std::string barista_name = "missing";
//             int quantity {};
//             OrderStatus status = OrderStatus::Num_statuses;

//             int customer_arrival_time {};      
//             int start_time {};
//             int end_time {};
//         } test_order;
//         Order order;
//         CHECK(sizeof(test_order) == sizeof(order));
//     }
// // Date
//     {
//     INFO("Check if Date is a class/struct type");
//         STATIC_REQUIRE(std::is_class<Date>::value);
//     }
//     {
//     INFO("Check if Date has correct element names and default initialization");
//         Date date;
//         CHECK(date.month == 0);
//         CHECK(date.day == 0);
//         CHECK(date.year == 0);
//     }
//     {
//     INFO("Check the number of elements in Date");
//         struct TestDate {
//             int month {};
//             int day {};
//             int year {};
//         } test_date;
//         Date date;
//         CHECK(sizeof(test_date) == sizeof(date));
//     }
//     // DailyStatistics
//     {
//     INFO("Check if DailyStatistics is a class/struct type");
//         STATIC_REQUIRE(std::is_class<DailyStatistics>::value);
//     }
//     {
//     INFO("Check if DailyStatistics has correct element names and default initialization");
//         DailyStatistics stats;
//         CHECK((stats.date.month == 0 && stats.date.year == 0 && stats.date.day == 0));
//         CHECK(stats.staff_on_duty.empty());
//         CHECK(stats.orders.empty());
//         CHECK(stats.next_in_line_index == 0);
//         CHECK(stats.count_completed == 0);
//         CHECK(stats.count_abandoned == 0);
//         CHECK(stats.count_pending == 0);
//         CHECK(stats.revenue == 0);
//     }
//     {
//     INFO("Check the number of elements in DailyStatistics");
//         struct TestDailyStatistics {
//             Date date {};
//             std::vector <Barista> staff_on_duty {};
//             std::vector<Order> orders {};
//             int next_in_line_index = 0;
//             int count_completed = 0;
//             int count_abandoned = 0;
//             int count_pending = 0;
//             double revenue {}; 
//         } test_stats;
//         DailyStatistics stats;
//         CHECK(sizeof(test_stats) == sizeof(stats));
//     }
//     // Cafe
//     {
//     INFO("Check if Cafe is a class/struct type");
//         STATIC_REQUIRE(std::is_class<Cafe>::value);
//     }
//     {
//     INFO("Check if Cafe has correct element names and default initialization");
//         Cafe cafe;
//         CHECK(cafe.name == "missing");
//         CHECK(cafe.menu.empty());
//         CHECK(cafe.staff.empty());
//         CHECK(cafe.stats.empty());
//     }
//     {
//     INFO("Check the number of elements in Cafe");
//         struct TestCafe {
//             std::string name;
//             std::vector<MenuItem> menu;
//             std::vector <Barista> staff;
//             std::vector<DailyStatistics> stats {};
//         } test_cafe;
//         Cafe cafe;
//         CHECK(sizeof(test_cafe) == sizeof(cafe));
//     }
//     // Parameters
//     {
//     INFO("Check if Parameters is a class/struct type");
//         STATIC_REQUIRE(std::is_class<Parameters>::value);
//     }
//     {
//     INFO("Check if Parameters has correct element names and default initialization");
//         Parameters params;
//         CHECK(params.max_waiting_time == 0);
//         CHECK(params.closing_time == 0);
//         CHECK(params.p == 0);
//         CHECK(params.lambda == 0);
//     }
//     {
//     INFO("Check the number of elements in Parameters");
//         struct TestParameters {
//             int max_waiting_time {};
//             int closing_time {};
//             double p {};
//             double lambda {};
//         } test_params;
//         Parameters params;
//         CHECK(sizeof(test_params) == sizeof(params));
//     }
// }
// */
// // // random number generation tests
// /*
// TEST_CASE("Random number generation tests", "[5 points]") 
// {
//     {
//     INFO("drawBernoulli() function with invalid parameter.");
//         int seed = 0;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK_THROWS_AS(drawBernoulli(1.01, rng), std::runtime_error);
//         CHECK_THROWS_AS(drawBernoulli(-0.01, rng), std::runtime_error);
//     }
//     int seed = 0;
//     std::mt19937 rng = initializeRng(seed); 
//     {
//     INFO("drawBernoulli() function with p = 0. Always false.");
//         double p = 0;
//         int sample_size = 100;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK(true_cases == 0);
//     }
//     {
//     INFO("drawBernoulli() function with p = 1. Always true.");
//         double p = 1;
//         int sample_size = 100;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK(true_cases == sample_size);
//     }
//     seed = 0;
//     rng = initializeRng(seed); 
//     {
//     INFO("drawBernoulli() function with p = 0.25.");
//         double p = 0.25;
//         int sample_size = 10'000;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK_THAT(true_cases/double(sample_size), Catch::Matchers::WithinAbs(0.25, 0.1));
//     }
//     {
//     INFO("drawBernoulli() function with p = 0.5.");
//         double p = 0.5;
//         int sample_size = 10'000;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK_THAT(true_cases/double(sample_size), Catch::Matchers::WithinAbs(0.5, 0.1));
//     }
//     {
//     INFO("drawBernoulli() function with p = 0.75.");
//         double p = 0.75;
//         int sample_size = 10'000;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK_THAT(true_cases/double(sample_size), Catch::Matchers::WithinAbs(0.75, 0.1));
//     }
//     {
//     INFO("drawBernoulli() function with seed = 0.");
//         double p = 0.25;
//         int seed = 0;
//         std::mt19937 rng = initializeRng(seed); 
//         int sample_size = 100;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK(true_cases == 19);
//     }
//     {
//     INFO("drawBernoulli() function with seed = 3.");
//         double p = 0.25;
//         int seed = 3;
//         std::mt19937 rng = initializeRng(seed); 
//         int sample_size = 100;
//         int true_cases = 0;
//         for(int i = 0; i < sample_size; i++) {
//             if (drawBernoulli(p, rng)) ++true_cases;
//         }
//         CHECK(true_cases == 21);
//     }
//     seed = 0;
//     rng = initializeRng(seed); 
//     {
//     INFO("drawUniformInt() function with invalid range.");
//         CHECK_THROWS_AS(drawUniformInt(6, 5, rng), std::runtime_error);
//         CHECK_THROWS_AS(drawUniformInt(-5, -6, rng), std::runtime_error);
//     }
//     seed = 0;
//     rng = initializeRng(seed); 
//     {
//     INFO("drawUniformInt() function with min=max.");
//         int min = 5;
//         int max = 5;
//         int sample_size = 100;
//         double sum = 0;
//         for(int i = 0; i < sample_size; i++) {
//             sum += drawUniformInt(min, max, rng);
//         }
//         REQUIRE(sum/sample_size == 5);
//     }
//     seed = 0;
//     rng = initializeRng(seed); 
//     {
//     INFO("drawUniformInt() function with min = 1, max = 6.");
//         int min = 1;
//         int max = 6;
//         int sample_size = 10'000;
//         double sum = 0;
//         for(int i = 0; i < sample_size; i++) {
//             sum += drawUniformInt(min, max, rng);
//         }
//         CHECK_THAT(sum/sample_size, Catch::Matchers::WithinAbs(3.5, 0.1));
//     }
//     {
//     INFO("drawUniformInt() function with min = 0, max = 3.");
//         int min = 0;
//         int max = 3;
//         int sample_size = 10'000;
//         double sum = 0;
//         for(int i = 0; i < sample_size; i++) {
//             sum += drawUniformInt(min, max, rng);
//         }
//         CHECK_THAT(sum/sample_size, Catch::Matchers::WithinAbs(1.5, 0.1));
//     }
//     {
//     INFO("drawUniformInt() function with min = -3, max = 3.");
//         int min = -3;
//         int max = 3;
//         int sample_size = 10'000;
//         double sum = 0;
//         for(int i = 0; i < sample_size; i++) {
//             sum += drawUniformInt(min, max, rng);
//         }
//         CHECK_THAT(sum/sample_size, Catch::Matchers::WithinAbs(0, 0.1));
//     }
//     {
//     INFO("drawUniformInt() function with seed = 0.");
//         int min = 1;
//         int max = 6;
//         int seed = 0;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK(drawUniformInt(min, max, rng) == 4);
//     }
//     {
//     INFO("drawUniformInt() function with seed = 1.");
//         int min = 1;
//         int max = 6;
//         int seed = 2;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK(drawUniformInt(min, max, rng) == 3);
//     }
//     {
//     INFO("drawUniformInt() function with seed = 4.");
//         int min = 1;
//         int max = 6;
//         int seed = 4;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK(drawUniformInt(min, max, rng) == 6);
//     }
//     seed = 0;
//     rng = initializeRng(seed); 
//     {
//     INFO("drawUniformReal() function with random seed.");
//         int sample_size = 10'000;
//         double sum = 0;
//         for(int i = 0; i < sample_size; i++) {
//             sum += drawUniformReal(rng);
//         }
//         CHECK_THAT(sum/sample_size, Catch::Matchers::WithinAbs(0.5, 0.1));
//     }
//     {
//     INFO("drawUniformReal() function with seed = 0.");
//         int seed = 0;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK_THAT(drawUniformReal(rng) , Catch::Matchers::WithinAbs(0.59, 0.01));
//     }
//     {
//     INFO("drawUniformReal() function with seed = 1.");
//         int seed = 1;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK_THAT(drawUniformReal(rng) , Catch::Matchers::WithinAbs(0.99, 0.01));
//     }
//     {
//     INFO("drawUniformReal() function with seed = 5.");
//         int seed = 5;
//         std::mt19937 rng = initializeRng(seed); 
//         CHECK_THAT(drawUniformReal(rng) , Catch::Matchers::WithinAbs(0.05, 0.01));
//     }
// }
// */
// // // getStaff tests
// /*
// TEST_CASE("getStaff() function", "[5 points]") 
// {
//     {
//     INFO("getStaff function with a single barista in the team");
//         std::vector<MenuItem> menu;
//         Barista emma = {"Emma", true, 2};
//         std::vector<Barista> staff = {emma};
//         Cafe cafe {"Morning Grind", menu, staff};
       
//         int seed = 0;
//         std::mt19937 rng = initializeRng(seed); 
//         std::vector<Barista> staff_on_duty = getStaff(cafe, 0.5, rng);
//         CHECK(staff_on_duty.size() == 1);
//         CHECK(staff_on_duty[0].name == "Emma");
//     }

//     {
//     INFO("getStaff function with multiple barista in the team, seed = 0");
//         std::vector<MenuItem> menu;
//         Barista alan = {"Alan", false, 1, 0};
//         Barista bella = {"Bella", false, 1.2};
//         Barista carlos = {"Carlos", false, 1.7};
//         Barista daisy = {"Daisy", false, 1.5};
//         Barista emma = {"Emma", true, 2};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};
//         Cafe cafe {"Morning Grind", menu, staff};

//         int seed = 0;
//         std::mt19937 rng = initializeRng(seed); 
//         std::vector<Barista> staff_on_duty = getStaff(cafe, 0.5, rng);
//         CHECK(staff_on_duty.size() == 1);
//         CHECK(staff_on_duty[0].name == "Emma");
//     }

//     {
//     INFO("getStaff function with multiple barista in the team, seed = 1");
//         std::vector<MenuItem> menu;
//         Barista alan = {"Alan", false, 1, 0};
//         Barista bella = {"Bella", false, 1.2};
//         Barista carlos = {"Carlos", false, 1.7};
//         Barista daisy = {"Daisy", false, 1.5};
//         Barista emma = {"Emma", true, 2};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};
//         Cafe cafe {"Morning Grind", menu, staff};

//         int seed = 1;
//         std::mt19937 rng = initializeRng(seed); 
//         std::vector<Barista> staff_on_duty = getStaff(cafe, 0.5, rng);
//         CHECK(staff_on_duty.size() == 2);
//         CHECK(staff_on_duty[0].name == "Carlos");
//         CHECK(staff_on_duty[1].name == "Emma");
//     }

//     {
//     INFO("getStaff function with multiple barista in the team, seed = 2");
//         std::vector<MenuItem> menu;
//         Barista alan = {"Alan", false, 1, 0};
//         Barista bella = {"Bella", false, 1.2};
//         Barista carlos = {"Carlos", false, 1.7};
//         Barista daisy = {"Daisy", false, 1.5};
//         Barista emma = {"Emma", true, 2};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};
//         Cafe cafe {"Morning Grind", menu, staff};

//         int seed = 2;
//         std::mt19937 rng = initializeRng(seed); 
//         std::vector<Barista> staff_on_duty = getStaff(cafe, 0.5, rng);
//         CHECK(staff_on_duty.size() == 3);
//         CHECK(staff_on_duty[0].name == "Alan");
//         CHECK(staff_on_duty[1].name == "Daisy");
//         CHECK(staff_on_duty[2].name == "Emma");
//     }
// }
// */
// // // displayOpeningNote tests
// /*
// TEST_CASE("displayOpeningNote() function", "[4 points]") {
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     auto buildCafe = []() -> Cafe {
//         std::vector<MenuItem> menu;

//         Barista alan   = {"Alan",   false, 1.0, 0, 0};
//         Barista bella  = {"Bella",  false, 1.2, 0, 0};
//         Barista carlos = {"Carlos", false, 1.7, 0, 0};
//         Barista daisy  = {"Daisy",  false, 1.5, 0, 0};
//         Barista emma   = {"Emma",   true,  2.0, 0, 0};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};

//     return Cafe{"Morning Grind", menu, staff};
//     };
//     {
//         INFO("Only Emma is on duty; the output should say \"Your barista today is …\"");
//         Cafe cafe = buildCafe();

//         // Build a DailyStatistics that contains **only** Emma
//         Date todayDate = {3, 10, 2026};
//         std::vector<Barista> onlyEmma = { cafe.staff.back() };   // Emma is the last element
//         DailyStatistics stats{ todayDate, onlyEmma };

//         std::string out = captureOutput([&](){ displayOpeningNote(cafe, stats); });

//         // Expected exact lines (including the blank line after the greeting)
//         const std::string expectedHeader =
//             "Welcome to Morning Grind!\n\n"
//             "Today is 3/10/2026.\n";

//         const std::string expectedBaristaLine = "Your barista today is Emma.\n\n";

//         CHECK(out.find(expectedHeader) != std::string::npos);
//         CHECK(out.find(expectedBaristaLine) != std::string::npos);
//     }
//     {
//         INFO("All five staff members are on duty; the output should list them with commas and \"and\"");
//         Cafe cafe = buildCafe();

//         // Use the full staff vector that was created in buildStandardCafe()
//         Date todayDate = {3, 10, 2026};
//         DailyStatistics stats{ todayDate, cafe.staff };

//         std::string out = captureOutput([&](){ displayOpeningNote(cafe, stats); });

//         // Header part (identical to the previous test)
//         const std::string expectedHeader =
//             "Welcome to Morning Grind!\n\n"
//             "Today is 3/10/2026.\n";

//         // The barista list should be: Alan, Bella, Carlos, Daisy and Emma.
//         const std::string expectedBaristaLine = "Your baristas today are Alan, Bella, Carlos, Daisy and Emma.\n\n";

//         CHECK(out.find(expectedHeader) != std::string::npos);
//         CHECK(out.find(expectedBaristaLine) != std::string::npos);
//     }
// }
// */
// // // generateArrivalTimes tests
// /*
// TEST_CASE("generateArrivalTimes() function", "[5 points]")
// {
//     {
//     INFO("generateArrivalTimes() function with invalid range.");
//         std::mt19937 rng = initializeRng(0);
//         double lambda = 0;
//         int    closing_time = 5;
//         CHECK_THROWS_AS(generateArrivalTimes(lambda, closing_time, rng), std::runtime_error);
//         lambda = -0.5;
//         CHECK_THROWS_AS(generateArrivalTimes(lambda, closing_time, rng), std::runtime_error);
//         lambda = 0.5;
//         closing_time = 0;
//         CHECK_THROWS_AS(generateArrivalTimes(lambda, closing_time, rng), std::runtime_error);
//         closing_time = -10;
//         CHECK_THROWS_AS(generateArrivalTimes(lambda, closing_time, rng), std::runtime_error);
//     }
//     {
//     INFO("closing_time = 5, moderate lambda = 0.5, seed = 0");
//         std::mt19937 rng = initializeRng(0);
//         double lambda = 0.5;
//         int    closing_time = 5;

//         std::vector<int> arrivals = generateArrivalTimes(lambda, closing_time, rng);
//         CHECK(arrivals.size() == 7);
//         CHECK(arrivals[0] >= 0);
//         CHECK(arrivals[0] <= closing_time);
//         for (std::size_t i = 1; i < arrivals.size(); ++i) {
//             CHECK(arrivals[i] >= 0);
//             CHECK(arrivals[i] <= closing_time);
//             CHECK(arrivals[i] >= arrivals[i - 1]);
//         }
//         CHECK(arrivals[0] == 1);
//         CHECK(arrivals[1] == 1);
//         CHECK(arrivals[2] == 1);
//         CHECK(arrivals[3] == 1);
//         CHECK(arrivals[4] == 1);
//         CHECK(arrivals[5] == 2);
//         CHECK(arrivals[6] == 4);
//     }


//     {
//     INFO("closing_time = 60, lamnba = 0.2, seed = 0");
//         std::mt19937 rng = initializeRng(0);
//         double lambda = 0.2;
//         int    closing_time = 60;

//         std::vector<int> arrivals = generateArrivalTimes(lambda, closing_time, rng);

//         CHECK(arrivals.size() == 18);
//         CHECK(arrivals[0] >= 0);
//         CHECK(arrivals[0] <= closing_time);
//         for (std::size_t i = 1; i < arrivals.size(); ++i) {
//             CHECK(arrivals[i] >= 0);
//             CHECK(arrivals[i] <= closing_time);
//             CHECK(arrivals[i] >= arrivals[i - 1]);
//         }
//         CHECK(arrivals[0] == 2);
//         CHECK(arrivals[1] == 2);
//         CHECK(arrivals[2] == 2);
//         CHECK(arrivals[7] == 28);
//         CHECK(arrivals[17] == 56);
//     }

//     {
//         INFO("closing_time = 60, lamnba = 0.2, seed = 1");
//             std::mt19937 rng = initializeRng(1);
//             double lambda = 0.2;
//             int    closing_time = 60;

//             std::vector<int> arrivals = generateArrivalTimes(lambda, closing_time, rng);

//             CHECK(arrivals.size() == 22);
//             CHECK(arrivals[0] == 0);
//             CHECK(arrivals[1] == 0);
//             CHECK(arrivals[2] == 10);
//             CHECK(arrivals[7] == 27);
//             CHECK(arrivals[17] == 56);
//     }

//     {
//         INFO("Edge case, lambda close to 0, closing_time = 10, seed = 3");
//             std::mt19937 rng = initializeRng(3);
//             double lambda = 0.001;   // almost no arrivals during the day
//             int    closing_time = 10;

//             std::vector<int> arrivals = generateArrivalTimes(lambda, closing_time, rng);

//             CHECK(arrivals.size() == 0);
//     }
// }
// */
// // // completeOrder tests
// /*
// TEST_CASE("completeOrder() function", "[5 points]")
// {
//     //  Helper: build a minimal Cafe with a known menu and an empty stats
//     auto buildCafe = []() -> Cafe {
//         // --- menu (same values as in main.cpp) ---------------------------------
//         MenuItem espresso = {2, 3.50};
//         MenuItem doppio = {2, 5.0};
//         MenuItem latte = {3, 7.50};
//         MenuItem cappuccino = {3, 8.25};
//         MenuItem americano = {2, 6.00};
//         MenuItem mocha = {4, 10.25};
//         MenuItem macchiato = {3, 8.50};
//         std::vector<MenuItem> menu = {espresso, doppio, latte, cappuccino, americano, mocha, macchiato};

//         // --- staff (not used by completeOrder, but required for a valid Cafe) --
//         Barista alan  = {"Alan",  false, 1.0};
//         Barista bella = {"Bella", false, 1.2};
//         Barista emma  = {"Emma",  true,  2.0};
//         std::vector<Barista> staff = {alan, bella, emma};

//         // --- create the Cafe ----------------------------------------------------
//         Cafe cafe {"Morning Grind", menu, staff};

//         // --- push an empty DailyStatistics entry so that cafe.stats.back() is valid
//         Date today_date = {3, 10, 2026};
//         cafe.stats.push_back({today_date, staff});   
//         return cafe;
//     };


//     {
//     INFO("Complete a single Espresso order (quantity = 2)");
//         Cafe cafe = buildCafe();
//         // Build the order manually
//         Order order;
//         order.id                = 1;
//         order.menu_item_name    = MenuItemNames::Espresso;  
//         order.quantity          = 2;
//         order.status            = OrderStatus::Pending;     
//         order.customer_arrival_time = 0;                     

//         completeOrder(cafe, order);              

//         CHECK(order.status == OrderStatus::Completed);
//         const DailyStatistics& today = cafe.stats.back();
//         CHECK(today.count_completed == 1);
//         // revenue must be quantity × price = 2 × 3.50 = 7.00
//         double expected = 2 * cafe.menu[static_cast<int>(MenuItemNames::Espresso)].price;
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(expected, 0.01));
//     }

//     {
//         INFO("Complete a Latte order (quantity = 1)");
//         Cafe cafe = buildCafe();

//         Order order;
//         order.id             = 42;
//         order.menu_item_name = MenuItemNames::Latte;   // price $7.50
//         order.quantity       = 1;
//         order.status         = OrderStatus::Pending;

//         completeOrder(cafe, order);

//         CHECK(order.status == OrderStatus::Completed);
//         const DailyStatistics& today = cafe.stats.back();
//         CHECK(today.count_completed == 1);
//         double expected = 1 * cafe.menu[static_cast<int>(MenuItemNames::Latte)].price;
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(expected, 0.01));
//     }

//     {
//         INFO("Complete three orders in succession and verify cumulative stats");
//         Cafe cafe = buildCafe();

//         // Order A: Espresso × 3  = $10.50
//         Order a;
//         a.id             = 1;
//         a.menu_item_name = MenuItemNames::Espresso;
//         a.quantity       = 3;
//         a.status         = OrderStatus::Pending;
//         completeOrder(cafe, a);

//         // Order B: Latte × 2    = $15.00
//         Order b;
//         b.id             = 2;
//         b.menu_item_name = MenuItemNames::Latte;
//         b.quantity       = 2;
//         b.status         = OrderStatus::Pending;
//         completeOrder(cafe, b);

//         // Order C: Cappuccino × 1 = $8.25
//         Order c;
//         c.id             = 3;
//         c.menu_item_name = MenuItemNames::Cappuccino;
//         c.quantity       = 1;
//         c.status         = OrderStatus::Pending;
//         completeOrder(cafe, c);

//         const DailyStatistics& today = cafe.stats.back();
//         CHECK(today.count_completed == 3);

//         // Revenue = 3*3.50 + 2*7.50 + 1*8.25 = 10.50 + 15.00 + 8.25 = 33.75
//         double expected = 3 * cafe.menu[static_cast<int>(MenuItemNames::Espresso)].price
//                         + 2 * cafe.menu[static_cast<int>(MenuItemNames::Latte)].price
//                         + 1 * cafe.menu[static_cast<int>(MenuItemNames::Cappuccino)].price;
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(expected, 0.01));
//     }
// }
// */
// // // displayOrderCompleted tests
// /*
// TEST_CASE("displayOrderCompleted() function", "[4 points]")
// {
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };

//     {
//         INFO("Order completed at time = 0 (noon)");
//         Order o;
//         o.id       = 1;
//         o.end_time = 0;               

//         std::string out = captureOutput([&](){ displayOrderCompleted(o); });
//         CHECK(out == "[Order 1] is completed at 12:00 p.m.\n");
//     }

//     {
//         INFO("Order completed at time = 5 (12:05 p.m.)");
//         Order o;
//         o.id       = 42;
//         o.end_time = 5;               

//         std::string out = captureOutput([&](){ displayOrderCompleted(o); });
//         CHECK(out == "[Order 42] is completed at 12:05 p.m.\n");
//     }

//     {
//         INFO("Order completed at time = 60 (1:00 p.m.)");
//         Order o;
//         o.id       = 13;
//         o.end_time = 60;             

//         std::string out = captureOutput([&](){ displayOrderCompleted(o); });
//         CHECK(out == "[Order 13] is completed at 1:00 p.m.\n");
//     }

//     {
//         INFO("Order completed at time = 720 (12:00 a.m.)");
//         Order o;
//         o.id       = 23;
//         o.end_time = 720;             

//         std::string out = captureOutput([&](){ displayOrderCompleted(o); });
//         CHECK(out == "[Order 23] is completed at 12:00 a.m.\n");
//     }
// }
// */
// // // generateOrder tests
// /*
// TEST_CASE("generateOrder() function", "[5 points]")
// {
//     // Helper to reset the static id counter before each independent test
//     auto resetIdCounter = []() { Order::next_id = 1; };

//     {
//         INFO("First order, seed = 0, current_time = 7");
//         resetIdCounter();
//         std::mt19937 rng = initializeRng(0);   
//         const int current_minute = 7;

//         Order o = generateOrder(current_minute, rng);
//         CHECK(o.id == 1);        
//         CHECK(o.next_id == 2);                                   
//         CHECK(o.customer_arrival_time == current_minute);   
//         CHECK(o.status == OrderStatus::Pending);             
//         // With seed 0 the first two uniform‑int draws are known:
//         CHECK(o.menu_item_name == MenuItemNames::Cappuccino);
//         CHECK(o.quantity == 2);
//     }
//     {
//         INFO("Second order from the same RNG (seed 0)");
//         resetIdCounter();
//         std::mt19937 rng = initializeRng(0);
//         // Consume the first order so the RNG is in the same state as after call #1
//         (void)generateOrder(0, rng);
//         const int current_minute = 12;

//         // Now generate the second order
//         Order second = generateOrder(current_minute, rng);
//         CHECK(second.id == 2);
//         CHECK(second.next_id == 3);      
//         CHECK(second.customer_arrival_time == current_minute);
//         CHECK(second.status == OrderStatus::Pending);
//         CHECK(second.menu_item_name == MenuItemNames::Mocha);
//         CHECK(second.quantity == 3);
//     }
//     {
//         INFO("Order with a different seed (seed = 42)");
//         resetIdCounter();

//         std::mt19937 rng = initializeRng(42);
//         const int current_minute = 0;
//         Order o = generateOrder(current_minute, rng);

//         CHECK(o.id == 1);
//         CHECK(o.id == 1);        
//         CHECK(o.next_id == 2);                                   
//         CHECK(o.customer_arrival_time == current_minute);   
//         CHECK(o.status == OrderStatus::Pending);             
//         // With seed 0 the first two uniform‑int draws are known:
//         CHECK(o.menu_item_name == MenuItemNames::Latte);
//         CHECK(o.quantity == 3);
//     }
//     {
//         INFO("Generate three orders in a row, same RNG");
//         resetIdCounter();

//         std::mt19937 rng = initializeRng(1);
//         Order a = generateOrder(3, rng);
//         Order b = generateOrder(5, rng);
//         Order c = generateOrder(8, rng);

//         CHECK(a.id == 1);
//         CHECK(b.id == 2);
//         CHECK(c.id == 3);

//         // All three orders must be Pending and have the correct arrival times
//         CHECK(a.status == OrderStatus::Pending);
//         CHECK(b.status == OrderStatus::Pending);
//         CHECK(c.status == OrderStatus::Pending);
//         CHECK(a.customer_arrival_time == 3);
//         CHECK(b.customer_arrival_time == 5);
//         CHECK(c.customer_arrival_time == 8);
//     }
// }
// */
// // // displayCustomerArrival tests
// /*
// TEST_CASE("displayCustomerArrival() function", "[4 points]")
// {
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     {
//         INFO("Customer arrives at noon and orders 1 Espresso");
//         Order o;
//         o.id                     = 1;
//         o.menu_item_name         = MenuItemNames::Espresso;   // “Espresso”
//         o.quantity               = 1;
//         o.customer_arrival_time  = 0;                         // 12:00 p.m.

//         std::string out = captureOutput([&](){ displayCustomerArrival(o); });
//         CHECK(out == "[Order 1] A new customer arrived at 12:00 p.m. and ordered 1 Espresso(s)\n");
//     }
//     {
//         INFO("Customer arrives at 12:05 p.m. and orders 3 Latte");
//         Order o;
//         o.id                     = 42;
//         o.menu_item_name         = MenuItemNames::Latte;   
//         o.quantity               = 3;
//         o.customer_arrival_time  = 5;                     // 12:05 p.m.

//         std::string out = captureOutput([&](){ displayCustomerArrival(o); });
//         CHECK(out == "[Order 42] A new customer arrived at 12:05 p.m. and ordered 3 Latte(s)\n");
//     }
// }
// */
// // // anyBaristaAvailable tests
// /*
// TEST_CASE("anyBaristaAvailable() function", "[5 points]")
// {
//     // Helper to create a fresh DailyStatistics entry and attach it to a cafe
//     auto buildCafeWithStats = [&](const std::vector<Barista>& staff_on_duty) -> Cafe {
//         MenuItem dummy = {0, 0.0};
//         std::vector<MenuItem> menu = { dummy };
//         Cafe cafe { "TestCafe", menu, staff_on_duty };
//         Date today_date = { 1, 1, 2026 };
//         cafe.stats.push_back({ today_date, staff_on_duty });
//         return cafe;
//     };
//     {
//         INFO("Empty staff list, no barista can be available");
//         std::vector<Barista> empty_staff;              
//         Cafe cafe = buildCafeWithStats(empty_staff);
//         CHECK(anyBaristaAvailable(cafe, 0) == false);
//         CHECK(anyBaristaAvailable(cafe, 100) == false);
//     }
//     {
//         INFO("One barista whose busy_until is 0 (free at time 0)");
//         Barista b = { "Alan", false, 1.0, 0, 0 };       
//         Cafe cafe = buildCafeWithStats({b});

//         CHECK(anyBaristaAvailable(cafe, 0) == true);   // exactly equal 
//         CHECK(anyBaristaAvailable(cafe, 5) == true);   // later time 
//     }
//     {
//         INFO("One barista busy until minute 20, query at minute 10");
//         Barista b = { "Bella", false, 1.2, 0, 20 };     
//         Cafe cafe = buildCafeWithStats({b});

//         CHECK(anyBaristaAvailable(cafe, 10) == false);
//         CHECK(anyBaristaAvailable(cafe, 20) == true);
//     }
//     {
//         INFO("Three baristas: two busy, one free");
//         Barista a = { "Alan",   false, 1.0, 0, 15 };   // busy_until 15
//         Barista b = { "Bella",  false, 1.2, 0, 30 };   // busy_until 30
//         Barista c = { "Carlos", false, 1.7, 0, 0  };   // free now
//         Cafe cafe = buildCafeWithStats({a, b, c});

//         // At time 5 only Carlos is free ⇒ true
//         CHECK(anyBaristaAvailable(cafe, 5) == true);
//         // At time 20 Alan is now free, Bella still busy ⇒ true
//         CHECK(anyBaristaAvailable(cafe, 20) == true);
//         // At time 31 all are free ⇒ true
//         CHECK(anyBaristaAvailable(cafe, 31) == true);
//     }
//     {
//         INFO("All three baristas are still busy at the queried minute");
//         Barista a = { "Alan",   false, 1.0, 0, 12 };
//         Barista b = { "Bella",  false, 1.2, 0, 12 };
//         Barista c = { "Carlos", false, 1.7, 0, 12 };
//         Cafe cafe = buildCafeWithStats({a, b, c});

//         // Query before any of them have finished
//         CHECK(anyBaristaAvailable(cafe, 5) == false);
//         // Query exactly at 12 – they become free, so it should be true
//         CHECK(anyBaristaAvailable(cafe, 12) == true);
//     }
// }
// */
// // // abandonOrder tests
// /*
// TEST_CASE("abandonOrder() function", "[5 points]")
// {
//     auto buildCafeWithStats = [&](const std::vector<Barista>& staff_on_duty) -> Cafe {
//         MenuItem dummy = {0, 0.0};
//         std::vector<MenuItem> menu = { dummy };
//         Cafe cafe { "TestCafe", menu, staff_on_duty };
//         Date today_date = { 1, 1, 2026 };
//         cafe.stats.push_back({ today_date, staff_on_duty });
//         return cafe;
//     };

//     {
//         INFO("Abandon a pending order at minute 17");
//         Cafe cafe = buildCafeWithStats({});  
//         Order o;
//         o.id                     = 1;
//         o.status                 = OrderStatus::In_progress;
//         o.end_time               = 25;      
//         o.customer_arrival_time  = 0;

//         abandonOrder(cafe, 17, o);          
//         CHECK(o.status == OrderStatus::Abandoned);  
//         CHECK(o.end_time == 17);                     
//         const DailyStatistics& today = cafe.stats.back();
//         CHECK(today.count_abandoned == 1);           // counter incremented
//         CHECK(today.count_completed == 0);           // completed counter untouched
//     }
//     {
//         INFO("Two orders abandoned sequentially");
//         Cafe cafe = buildCafeWithStats({});
//         Order first;
//         first.id     = 10;
//         first.status = OrderStatus::In_progress;
//         first.end_time = -1;
//         abandonOrder(cafe, 4, first);
//         CHECK(cafe.stats.back().count_abandoned == 1);

//         Order second;
//         second.id     = 11;
//         second.status = OrderStatus::In_progress;
//         second.end_time = -1;
//         abandonOrder(cafe, 12, second);
//         CHECK(cafe.stats.back().count_abandoned == 2);   // counter now 2
//     }
//     {
//         INFO("Abandon an order while some orders have already been completed");
//         Cafe cafe = buildCafeWithStats({});
//         cafe.stats.back().count_completed = 3;   // simulate prior work

//         Order o;
//         o.id     = 99;
//         o.status = OrderStatus::In_progress;
//         o.end_time = -1;

//         abandonOrder(cafe, 25, o);

//         const DailyStatistics& today = cafe.stats.back();
//         CHECK(today.count_abandoned == 1);
//         CHECK(today.count_completed == 3);   // unchanged
//     }
// }
// */
// // // displayOrderAbandoned tests
// /*
// TEST_CASE("displayOrderAbandoned() function", "[4 points]")
// {
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     {
//         INFO("Order abandoned at 12:05 p.m.");
//         Order o;
//         o.id      = 42;
//         o.end_time = 5;                      

//         std::string out = captureOutput([&](){ displayOrderAbandoned(o); });
//         CHECK(out == "[Order 42] is abandoned at 12:05 p.m.\n");
//     }
//     {
//         INFO("Order object remains unchanged after displayOrderAbandoned");
//         Order o;
//         o.id      = 5;
//         o.end_time = 30;                      
//         int saved_id      = o.id;
//         int saved_endtime = o.end_time;

//         captureOutput([&](){ displayOrderAbandoned(o); });
//         CHECK(o.id      == saved_id);
//         CHECK(o.end_time == saved_endtime);
//     }
// }
// */
// // // findAvailableBarista tests
// /*
// TEST_CASE("findAvailableBarista() function", "[5 points]")
// {
//     // Helper to create a fresh DailyStatistics entry and attach it to a cafe
//     auto buildCafeWithStats = [&](const std::vector<Barista>& staff_on_duty) -> Cafe {
//         MenuItem dummy = {0, 0.0};
//         std::vector<MenuItem> menu = { dummy };
//         Cafe cafe { "TestCafe", menu, staff_on_duty };
//         Date today_date = { 1, 1, 2026 };
//         cafe.stats.push_back({ today_date, staff_on_duty });
//         return cafe;
//     };
//     {
//         INFO("Single free barista (Alan) at time 0  should be returned");
//         Barista alan  = {"Alan",  false, 1.0, 0, 0};   // busy_until == 0 (free)
//         Barista bella = {"Bella", false, 1.2, 0, 10};  // busy
//         Barista emma  = {"Emma",  true,  2.0, 0, 20};  // busy
//         Cafe cafe = buildCafeWithStats({alan, bella, emma});

//         std::mt19937 rng = initializeRng(0);          // deterministic seed
//         Barista& chosen = findAvailableBarista(cafe, 0, rng);
//         CHECK(chosen.name == "Alan");                 // the only free barista
//     }
//     {
//         INFO("Three free baristas, seed 0");
//         Barista a = {"Alan",   false, 1.0, 0, 0};   // free
//         Barista b = {"Bella",  false, 1.2, 0, 0};   // free
//         Barista c = {"Carlos", false, 1.7, 0, 5};   // busy
//         Barista d = {"Daisy",  false, 1.5, 0, 0};   // free
//         Barista e = {"Emma",   true,  2.0, 0, 10};  // busy

//         Cafe cafe = buildCafeWithStats({a, b, c, d, e});

//         std::mt19937 rng = initializeRng(0);
//         Barista& chosen = findAvailableBarista(cafe, 0, rng);
//         CHECK(chosen.name == "Bella");
//     }
//     {
//         INFO("Same free set as above, but seed 1 should select a different barista");
//         Barista a = {"Alan",   false, 1.0, 0, 0};
//         Barista b = {"Bella",  false, 1.2, 0, 0};
//         Barista d = {"Daisy",  false, 1.5, 0, 0};

//         // All three are free; we reuse the same staff vector.
//         Cafe cafe = buildCafeWithStats({a, b, d});
//         std::mt19937 rng = initializeRng(5);
//         Barista& chosen = findAvailableBarista(cafe, 0, rng);
//         CHECK(chosen.name == "Alan");
//     }
//     {
//         INFO("Free baristas are at positions 2 and 4; seed 0 should pick index 2");
//         Barista a = {"Alan",   false, 1.0, 0, 10};   // busy
//         Barista b = {"Bella",  false, 1.2, 0, 12};   // busy
//         Barista c = {"Carlos", false, 1.7, 0, 0};    // free
//         Barista d = {"Daisy",  false, 1.5, 0, 20};   // busy
//         Barista e = {"Emma",   true,  2.0, 0, 0};    // free

//         Cafe cafe = buildCafeWithStats({a, b, c, d, e});

//         std::mt19937 rng = initializeRng(5);          // draws 0 
//         Barista& chosen = findAvailableBarista(cafe, 0, rng);
//         CHECK(chosen.name == "Carlos");               // index 2 is the first free one
//     }
// }
// */
// // // calcPrepTime tests
// /*
// TEST_CASE("calcPrepTime() function", "[5 points]")
// {
//     auto buildCafe = []() -> Cafe {
//         MenuItem espresso   = {5, 3.50};
//         MenuItem doppio     = {6, 5.00};
//         MenuItem latte      = {9, 7.50};
//         MenuItem cappuccino = {8, 8.25};
//         MenuItem americano  = {7, 6.00};
//         MenuItem mocha      = {9,10.25};
//         MenuItem macchiato  = {7, 8.50};

//         std::vector<MenuItem> menu = {espresso, doppio, latte,
//                                       cappuccino, americano, mocha,
//                                       macchiato};
//         std::vector<Barista> staff;
//         return Cafe{"TestCafe", menu, staff};
//     };
//     {
//         INFO("Espresso (5 min) * 2, barista speed=1 -> 10 min");
//         Cafe cafe = buildCafe();

//         Order order;
//         order.menu_item_name = MenuItemNames::Espresso;   // base time = 5
//         order.quantity       = 2;

//         Barista barista;
//         barista.speed_factor = 1.0;                       

//         int prep = calcPrepTime(cafe, order, barista);
//         CHECK(prep == 10);   // 5*2/1 = 10, 
//     }
//     {
//         INFO("Latte (9 min) * 2, barista speed = 1.5 → ceil(9*2/1.5)=12");
//         Cafe cafe = buildCafe();

//         Order order;
//         order.menu_item_name = MenuItemNames::Latte;   
//         order.quantity       = 2;

//         Barista barista;
//         barista.speed_factor = 1.5;                   

//         int prep = calcPrepTime(cafe, order, barista);
//         // 9*2/1.5 = 12.0 → ceil = 12
//         CHECK(prep == 12);
//     }
//     {
//         INFO("Cappuccino (8 min) * 1, barista speed = 1.3 → ceil(8/1.3)=7");
//         Cafe cafe = buildCafe();

//         Order order;
//         order.menu_item_name = MenuItemNames::Cappuccino; 
//         order.quantity       = 1;

//         Barista barista;
//         barista.speed_factor = 1.3;

//         int prep = calcPrepTime(cafe, order, barista);
//         // 8/1.3 ≈ 6.1538 → ceil = 7
//         CHECK(prep == 7);
//     }
//     {
//         INFO("Barista with speed factor <= 0 must trigger exception");
//         Cafe cafe = buildCafe();

//         Order order;
//         order.menu_item_name = MenuItemNames::Americano;
//         order.quantity       = 1;

//         Barista barista;
//         barista.speed_factor = 0.0;   // illegal

//         CHECK_THROWS_AS(calcPrepTime(cafe, order, barista), std::runtime_error);
//     }
//     {
//         INFO("Menu item with non positive prep_time triggers exception");
//         MenuItem broken = {0, 1.00};               // invalid prep time
//         std::vector<MenuItem> menu = {broken};

//         Cafe cafe{"BrokenCafe", menu, {}};

//         Order order;
//         order.menu_item_name = MenuItemNames::Espresso; 
//         order.quantity       = 1;

//         Barista barista;
//         barista.speed_factor = 1.0;

//         CHECK_THROWS_AS(calcPrepTime(cafe, order, barista), std::runtime_error);
//     }
// }
// */
// // assignOrderToBarista tests

TEST_CASE("assignOrderToBarista() function", "[5 points]")
{
    auto buildCafe = []() -> Cafe {
        MenuItem espresso   = {5,  3.50};
        MenuItem doppio     = {6,  5.00};
        MenuItem latte      = {9,  7.50};
        MenuItem cappuccino = {8,  8.25};
        MenuItem americano  = {7,  6.00};
        MenuItem mocha      = {9, 10.25};
        MenuItem macchiato  = {7,  8.50};

        std::vector<MenuItem> menu = {espresso, doppio, latte,
                                      cappuccino, americano, mocha,
                                      macchiato};
        std::vector<Barista> staff;
        return Cafe{"TestCafe", menu, staff};
    };
    {
        INFO("Assign a 2-Espresso order to a barista with speed=1.0");
        Cafe cafe = buildCafe();

        Order order;
        order.menu_item_name = MenuItemNames::Espresso; 
        order.quantity       = 2;                     
        order.id             = 1;                     

        Barista barista;
        barista.name          = "Alan";
        barista.speed_factor  = 1.0;   
        barista.num_orders_handled = 0;
        barista.busy_until   = 0;

        int current_time = 10;        

        assignOrderToBarista(cafe, current_time, order, barista);   

        CHECK(order.status == OrderStatus::In_progress);
        CHECK(order.start_time == current_time);
        CHECK(order.barista_name == "Alan");
        int expected_end = current_time + 10;
        CHECK(order.end_time == expected_end);
        CHECK(barista.num_orders_handled == 1);
        CHECK(barista.busy_until == expected_end);
    }
    {
        INFO("Zero quantity order must trigger a runtime_error");
        Cafe cafe = buildCafe();

        Order order;
        order.menu_item_name = MenuItemNames::Mocha;
        order.quantity       = 0;      // illegal
        order.id             = 3;

        Barista barista;
        barista.name          = "Carlos";
        barista.speed_factor  = 1.5;

        int current_time = 12;

        CHECK_THROWS_AS(assignOrderToBarista(cafe, current_time, order, barista), std::runtime_error);
    }
    {
        INFO("Barista with non positive speed_factor must trigger a runtime_error");
        Cafe cafe = buildCafe();

        Order order;
        order.menu_item_name = MenuItemNames::Cappuccino;
        order.quantity       = 1;
        order.id             = 4;

        Barista barista;
        barista.name          = "Daisy";
        barista.speed_factor  = 0.0;   // illegal

        int current_time = 22;

        CHECK_THROWS_AS(assignOrderToBarista(cafe, current_time, order, barista), std::runtime_error);
    }
}

// // // displayOrderStarted tests
// /*
// TEST_CASE("displayOrderStarted() function", "[4 points]")
// {
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     {
//         INFO("Order started at 12:05 p.m.");
//         Order o;
//         o.id          = 42;
//         o.barista_name = "Bella";
//         o.start_time   = 5;          // 5 minutes → 12:05 p.m.

//         std::string out = captureOutput([&](){ displayOrderStarted(o); });

//         CHECK(out == "[Order 42] Bella started preparing the order at 12:05 p.m.\n");
//     }
//     {
//         INFO("After calling displayOrderStarted, the Order fields stay unchanged");
//         Order o;
//         o.id          = 5;
//         o.barista_name = "Emma";
//         o.start_time   = 30;        
//         int saved_id          = o.id;
//         std::string saved_name = o.barista_name;
//         int saved_start       = o.start_time;

//         captureOutput([&](){ displayOrderStarted(o); });

//         CHECK(o.id          == saved_id);
//         CHECK(o.barista_name == saved_name);
//         CHECK(o.start_time   == saved_start);
//     }
// }
// */
//  // // simulateDailyOperation tests
// /*
// TEST_CASE("simulateDailyOperation() function", "[10 points]"){
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     auto buildCafe = []() -> Cafe {
//         MenuItem espresso = {2, 3.50};
//         MenuItem doppio = {2, 5.0};
//         MenuItem latte = {3, 7.50};
//         MenuItem cappuccino = {3, 8.25};
//         MenuItem americano = {2, 6.00};
//         MenuItem mocha = {4, 10.25};
//         MenuItem macchiato = {3, 8.50};
//         std::vector<MenuItem> menu = {espresso, doppio, latte, cappuccino, americano, mocha, macchiato};

//         Barista alan   = {"Alan",   false, 1.0, 0, 0};
//         Barista bella  = {"Bella",  false, 1.2, 0, 0};
//         Barista carlos = {"Carlos", false, 1.7, 0, 0};
//         Barista daisy  = {"Daisy",  false, 1.5, 0, 0};
//         Barista emma   = {"Emma",   true,  2.0, 0, 0};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};

//     return Cafe{"Morning Grind", menu, staff};
//     };
//     {
//         INFO("Low lambda = 0.001, seed = 0 -> no orders enter the system");
//         Cafe cafe = buildCafe();

//         Date date = {3, 10, 2026};
//         Parameters params;
//         params.max_waiting_time = 10;   
//         params.closing_time      = 600;
//         params.p                 = 0.5; 
//         params.lambda            = 0.001; // extremely low arrival rate

//         std::string out = captureOutput([&](){ simulateDailyOperation(cafe, date, params, 0); });
//         CHECK(cafe.stats.size() == 1);
//         const DailyStatistics& today = cafe.stats.back();

//         CHECK(today.orders.empty());               // no orders were created
//         CHECK(today.next_in_line_index == 0);
//         CHECK(today.count_completed == 0);
//         CHECK(today.count_abandoned == 0);
//         CHECK(today.count_pending == 0);
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(0, 0.01));
//     }
//     {
//         INFO("High lambda; seed = 0, too many orders, high abandonment");
//         Cafe cafe = buildCafe();

//         Date date = {3, 10, 2026};
//         Parameters params;
//         params.max_waiting_time = 10;   
//         params.closing_time      = 600; 
//         params.p                 = 0.5;
//         params.lambda            = 2.0;  // high arrival rate

//         std::string out = captureOutput([&](){ simulateDailyOperation(cafe, date, params, 0); });

//         CHECK(cafe.stats.size() == 1);
//         const DailyStatistics& today = cafe.stats.back();

//         CHECK(today.orders.size() == 3848);
//         CHECK(today.next_in_line_index == 3775);
//         CHECK(today.count_completed == 219);
//         CHECK(today.count_abandoned == 3556);
//         CHECK(today.count_pending == 0);
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(2901.5, 0.01));
//     }
//     {
//         INFO("Moderate lambda; standard closing time, seed = 0");
//         Cafe cafe = buildCafe();

//         Date date = {3, 10, 2026};
//         Parameters params;
//         params.max_waiting_time = 10;   
//         params.closing_time      = 600; 
//         params.p                 = 0.5;
//         params.lambda            = 0.2;

//         std::string out = captureOutput([&](){ simulateDailyOperation(cafe, date, params, 0); });

//         CHECK(cafe.stats.size() == 1);
//         const DailyStatistics& today = cafe.stats.back();

//         CHECK(today.orders.size() == 146);
//         CHECK(today.next_in_line_index == 145);
//         CHECK(today.count_completed == 141);
//         CHECK(today.count_abandoned == 4);
//         CHECK(today.count_pending == 0);
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(1875.75, 0.01));
//     }
//     {
//         INFO("Moderate lambda; standard closing time, seed = 5");
//         Cafe cafe = buildCafe();

//         Date date = {3, 10, 2026};
//         Parameters params;
//         params.max_waiting_time = 10;   
//         params.closing_time      = 600; 
//         params.p                 = 0.5;
//         params.lambda            = 0.2;

//         std::string out = captureOutput([&](){ simulateDailyOperation(cafe, date, params, 5); });

//         CHECK(cafe.stats.size() == 1);
//         const DailyStatistics& today = cafe.stats.back();

//         CHECK(today.orders.size() == 145);
//         CHECK(today.next_in_line_index == 145);
//         CHECK(today.count_completed == 145);
//         CHECK(today.count_abandoned == 0);
//         CHECK(today.count_pending == 0);
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(2209.5, 0.01));
//     }
//     {
//         INFO("Closing time = 2, but preparation takes longer; the order must finish after the loop");
//         Cafe cafe = buildCafe();

//         Date date = {3, 10, 2026};
//         Parameters params;
//         params.max_waiting_time = 10;
//         params.closing_time      = 2;      // very short day
//         params.p                 = 0.5;
//         params.lambda            = 2.0;   // guarantees an arrival at t = 0

//         std::string out = captureOutput([&](){ simulateDailyOperation(cafe, date, params, 0); });

//         REQUIRE(cafe.stats.size() == 1);
//         const DailyStatistics& today = cafe.stats.back();

//         const Order& order = today.orders.front();
//         CHECK(order.status == OrderStatus::Completed);
//         CHECK(order.end_time > params.closing_time);   // finished after closing
//         CHECK(today.count_completed == 1);
//         // No abandonment and revenue equal to price × quantity
//         CHECK(today.count_abandoned == 0);
//         double expectedRev = order.quantity * cafe.menu[static_cast<int>(order.menu_item_name)].price;
//         CHECK_THAT(today.revenue, Catch::Matchers::WithinAbs(expectedRev, 0.01));
//     }

// }

// TEST_CASE("simulateDailyOperation() creates a separate stats record for each day", "[5 points]")
// {
//     // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     auto buildCafe = []() -> Cafe {
//         MenuItem espresso = {2, 3.50};
//         MenuItem doppio = {2, 5.0};
//         MenuItem latte = {3, 7.50};
//         MenuItem cappuccino = {3, 8.25};
//         MenuItem americano = {2, 6.00};
//         MenuItem mocha = {4, 10.25};
//         MenuItem macchiato = {3, 8.50};
//         std::vector<MenuItem> menu = {espresso, doppio, latte, cappuccino, americano, mocha, macchiato};

//         Barista alan   = {"Alan",   false, 1.0, 0, 0};
//         Barista bella  = {"Bella",  false, 1.2, 0, 0};
//         Barista carlos = {"Carlos", false, 1.7, 0, 0};
//         Barista daisy  = {"Daisy",  false, 1.5, 0, 0};
//         Barista emma   = {"Emma",   true,  2.0, 0, 0};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};

//     return Cafe{"Morning Grind", menu, staff};
//     };
//     Cafe cafe = buildCafe();

//     Parameters params;
//     params.max_waiting_time = 10;
//     params.closing_time      = 60;
//     params.p                 = 0.5;
//     params.lambda            = 0.2;

//     // Day 1
//     Date day1 = {3, 10, 2026};
//     int seed_day1 = 1;      
//     std::string out_day1 = captureOutput([&](){ simulateDailyOperation(cafe, day1, params, seed_day1); });               

//     // Day 2 – a different calendar date
//     Date day2 = {3, 11, 2026};
//     int seed_day2 = 2;                     // a different seed to vary the RNG sequence
//     std::string out_day2 = captureOutput([&](){ simulateDailyOperation(cafe, day2, params, seed_day2); });      


//     REQUIRE(cafe.stats.size() == 2);      // exactly two days recorded

//     const DailyStatistics& stats_day1 = cafe.stats[0];
//     const DailyStatistics& stats_day2 = cafe.stats[1];

//     // Dates must match the ones we passed in
//     CHECK(stats_day1.date.month == day1.month);
//     CHECK(stats_day1.date.day   == day1.day);
//     CHECK(stats_day1.date.year  == day1.year);

//     CHECK(stats_day2.date.month == day2.month);
//     CHECK(stats_day2.date.day   == day2.day);
//     CHECK(stats_day2.date.year  == day2.year);

//     CHECK(!stats_day1.orders.empty());
//     CHECK(!stats_day2.orders.empty());

//     CHECK(&stats_day1 != &stats_day2);
//     CHECK((stats_day1.count_completed != stats_day2.count_completed ||
//           stats_day1.count_abandoned != stats_day2.count_abandoned));
// }
// */
// // // displayDailyStats tests
// /*
// TEST_CASE("displayDailyStats() function", "[5 points]")
// {
//         // Helper to capture std::cout output
//     auto captureOutput = [](auto&& func) {
//         std::ostringstream oss;
//         std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());  // redirect
//         func();                                                                             // call the function under test
//         std::cout.rdbuf(old_buf);                                                 // restore
//         return oss.str();   
//     };
//     auto buildCafe = []() -> Cafe {
//         MenuItem espresso = {2, 3.50};
//         MenuItem doppio = {2, 5.0};
//         MenuItem latte = {3, 7.50};
//         MenuItem cappuccino = {3, 8.25};
//         MenuItem americano = {2, 6.00};
//         MenuItem mocha = {4, 10.25};
//         MenuItem macchiato = {3, 8.50};
//         std::vector<MenuItem> menu = {espresso, doppio, latte, cappuccino, americano, mocha, macchiato};

//         Barista alan   = {"Alan",   false, 1.0, 0, 0};
//         Barista bella  = {"Bella",  false, 1.2, 0, 0};
//         Barista carlos = {"Carlos", false, 1.7, 0, 0};
//         Barista daisy  = {"Daisy",  false, 1.5, 0, 0};
//         Barista emma   = {"Emma",   true,  2.0, 0, 0};
//         std::vector<Barista> staff = {alan, bella, carlos, daisy, emma};

//     return Cafe{"Morning Grind", menu, staff};
//     };
//     Cafe cafe = buildCafe();
//     Date todayDate = {3, 10, 2026};
//     Barista carlos = {"Carlos", false, 1.7, 0, 0};
//     Barista daisy  = {"Daisy",  false, 1.5, 0, 0};
//     Barista emma   = {"Emma",   true,  2.0, 0, 0};
//     std::vector<Barista> staff_on_duty = {carlos, daisy, emma};
//     cafe.stats.push_back({todayDate, staff_on_duty}); 
//     {
//     INFO("A Cafe with a populated DailyStatistics entry");
//         DailyStatistics& stats = cafe.stats.back();
//         stats.revenue          = 123.45;
//         stats.count_completed  = 7;
//         stats.count_abandoned  = 2;

//         stats.staff_on_duty[0].num_orders_handled = 1; // Carlos
//         stats.staff_on_duty[1].num_orders_handled = 0; // Daisy
//         stats.staff_on_duty[2].num_orders_handled = 4; // Emma

//         std::string out = captureOutput([&](){ displayDailyStats(cafe, stats.date); });

//         CHECK(out.find("\n=== Daily Summary for 3/10/2026 ===\n") != std::string::npos);
//         CHECK(out.find("Revenue: $123.45") != std::string::npos);
//         CHECK(out.find("Orders completed: 7") != std::string::npos);
//         CHECK(out.find("Orders abandoned: 2") != std::string::npos);

//         // ---- Verify the barista table ------------------------------------------
//         CHECK(out.find("Name") != std::string::npos);
//         CHECK(out.find("Orders") != std::string::npos);
//         // Individual rows (name padded to 12 chars, orders to 10 chars)
//         CHECK(out.find("Carlos      1") != std::string::npos);
//         CHECK(out.find("Daisy       0") != std::string::npos);
//         CHECK(out.find("Emma        4") != std::string::npos);
//     }

//     {
//         INFO("A Café with no entry for the requested date");
//         Cafe cafe = buildCafe();
//         Date todayDate = {3, 10, 2026};
//         Barista carlos = {"Carlos", false, 1.7, 0, 0};
//         Barista daisy  = {"Daisy",  false, 1.5, 0, 0};
//         Barista emma   = {"Emma",   true,  2.0, 0, 0};
//         std::vector<Barista> staff_on_duty = {carlos, daisy, emma};
//         cafe.stats.push_back({todayDate, staff_on_duty}); 

//         // Query a date that is NOT stored in cafe.stats
//         Date missingDate = {4, 1, 2026};

//         std::string out = captureOutput([&](){ displayDailyStats(cafe, missingDate); });

//         // The function should emit the specific warning line and then return
//         std::string expected = ">>> No statistics available for 4/1/2026.\n";
//         CHECK(out == expected);
//     }
// }
// */
