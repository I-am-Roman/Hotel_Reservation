#pragma once
#include <string>
using namespace std;

struct Date
{
    int day;
    int month;
};

struct Information_about_user
{
    string user_name;
    Date user_day_of_arrival;
    Date user_day_of_departure;
};