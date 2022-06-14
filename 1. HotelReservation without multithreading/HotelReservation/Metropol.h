#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream> 
#include <sstream>
#include <iostream>
#include <tuple>
#include <list>
#include <iomanip>
#include "Date.h"

using  namespace std;
/*****************************************************************/
/*						M E T R O P O L							* /
/*****************************************************************/
// Our Hotel
class Metropol
{
private:
	const uint8_t number_of_room = 40u;
	//the database includes the room type, room numberand status(free / occupied)    
	map <int, pair<string, bool>> holel_database;
	map <int, list<Information_about_user>> reservation;

public:
	Metropol() {}
	void Record_Database();
	void Show_Database();
	void Check_Number_Reservation
	(const int& number,string& name, Date& day_of_arrival,Date& day_of_departure);

	void Show_Reservation();
	void Annul_Reservation(const int& number, string& name);
	bool Earlier(const Date& lhs_departure, const Date& rhs_arrival);
	bool Later(const Date& lhs_arrival, const Date& rhs_departure);
	void Show_Reservation(ostringstream& res_output) const;
};