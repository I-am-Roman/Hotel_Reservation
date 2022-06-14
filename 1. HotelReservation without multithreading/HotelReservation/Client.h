#pragma once

#include <iostream>
#include "Date.h"
#include "Metropol.h"

using namespace std;
/*****************************************************************/
/*					        C L I E N T             			* /
/*****************************************************************/
class Client
{
private:
    string first_name;
    string last_name;
    Date day_of_arrival;
    Date day_of_departure;

public:
    Client() = default;
    Client(const string& f_n, const string& l_n,
        const Date& d_o_a, const Date& d_o_d) :
        first_name(f_n), last_name(l_n),
        day_of_arrival(d_o_a), day_of_departure(d_o_d)
    {   
        Check_Data();
    }

    void Make_Reservation( Metropol& hotel,const int& num_room);
    void Canal_Reservation( Metropol& hotel, const int& num_room);
    void Check_Data();
};
