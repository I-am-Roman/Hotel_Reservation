
#include "Client.h"
/*****************************************************************/
/*				M A K E   R E S E R V A T I O N 				* /
/*****************************************************************/
void Client::Make_Reservation( Metropol& hotel,const int& num_room)
{
    // true - free, false - occupied
    string name = first_name + " " + last_name;
    hotel.Check_Number_Reservation(num_room, name, day_of_arrival, day_of_departure);

}
/*****************************************************************/
/*				C A N A L   R E S E R V A T I O N 				* /
/*****************************************************************/
void Client::Canal_Reservation( Metropol& hotel,const int& num_room)
{
    string name = first_name + " " + last_name;
    hotel.Annul_Reservation(num_room, name);
}
/*****************************************************************/
/*				        C H E C K   D A T A        				* /
/*****************************************************************/
void Client::Check_Data()
{
    if (day_of_arrival.month - day_of_departure.month > 0)
    {
        throw runtime_error
        ("The arrival date cannot be later than the departure date.(Wrong month!)");
    }
    if (day_of_arrival.month == day_of_departure.month)
    {
        if (day_of_arrival.day - day_of_departure.day > 0)
        {
            throw runtime_error
            ("The arrival date cannot be later than the departure date.(Wrong day!)");
        }
    }
    if (first_name.empty())
    {
        throw runtime_error
        ("The First name cannot be empty!");
    }
    if (last_name.empty())
    {
        throw runtime_error
        ("The First name cannot be empty!");
    }
    if (day_of_arrival.day < 1)
    {
        throw runtime_error
        ("The day cannot less than 1!");
    }
    if (day_of_departure.day < 1)
    {
        throw runtime_error
        ("The day cannot less than 1!");
    }
    if (day_of_arrival.month < 1)
    {
        throw runtime_error
        ("The month cannot less than 1!");
    }
    if (day_of_departure.month < 1)
    {
        throw runtime_error
        ("The month cannot less than 1!");
    }

    //---------------------------
    if (day_of_arrival.day > 31)
    {
        throw runtime_error
        ("The day cannot more than 31!");
    }
    if (day_of_departure.day > 31)
    {
        throw runtime_error
        ("The day cannot more than 31!");
    }
    if (day_of_arrival.month > 12)
    {
        throw runtime_error
        ("The day cannot more than 12!");
    }
    if (day_of_departure.month > 12)
    {
        throw runtime_error
        ("The day cannot more than 12!");
    }
}