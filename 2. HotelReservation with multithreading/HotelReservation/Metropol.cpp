#include "Metropol.h"

using namespace std; 
/*****************************************************************/
/*					R E C O R D    D A T A B A S E				* /
/*****************************************************************/
void Metropol::Record_Database()
{
	ifstream input("database.txt");
	if (!input)
	{
		cout << "File not found!\n";
		input.close();
		return;
	}//if

	if (!input.good())
	{
		cout << "File is empty\n";
		input.close();
		return;
	}//if

	string type_room;
	string type_room2;
	int number_room;
	bool status_room;
	string line;

	for (string line; getline(input, line); )
	{
		istringstream is(line);

		is >> type_room;
		is >> number_room;
		is >> status_room;

		holel_database.insert({ number_room, make_pair(type_room, status_room) });
	}

	input.close();

}//Record_Database
/*****************************************************************/
/*					S H O W   D A T A B A S E					* /
/*****************************************************************/
void Metropol::Show_Database()
{
	if (holel_database.empty())
	{
		cout << "Database is empty!" << endl;
		return;
	}
	for (auto it = holel_database.begin(); it != holel_database.end(); ++it)
	{
		cout << it->first << " "
			<< it->second.first << " " << boolalpha <<it->second.second << endl;
	}
	cout << endl;
}//Show_Database
/*****************************************************************/
/*		C H E C K   N U M B E R   R E S E R V A T I O N			* /
/*****************************************************************/
void Metropol::  Check_Number_Reservation
(const int& number, string& name, Date& day_of_arrival, Date& day_of_departure)
{
	
	auto iterator_hotel = holel_database.find(number);
	if (iterator_hotel == holel_database.end())
	{
		cerr << "You enter wrong number! Please, try again!" << endl;
		return;
	}

	Information_about_user client; 
	client.user_name = name;
	client.user_day_of_arrival = day_of_arrival;
	client.user_day_of_departure = day_of_departure;

	//	map <int, set<Information_about_user>> reservation;
	//The room may be occupied, but the guest may leave by 
	//the time of the arrival of the other

	auto iterator_reservation = reservation.find(number);
	bool flag = false;

	// the room is not reserved
	{
		lock_guard<mutex> g(m);
		flag = iterator_reservation == reservation.end();
	}

	if (flag)
	{
		iterator_hotel->second.second = false;
		//cout << "The booking was successful!" << endl;
		reservation[number].push_back(client);
		return;
	}
	

	bool client_arrival_earlier = true;
	bool client_arrival_later = true;

	{
		lock_guard<mutex> g(m);
		for (auto& it : reservation[number])
		{
			client_arrival_earlier = Earlier(client.user_day_of_departure, it.user_day_of_arrival);

			client_arrival_later = Later(client.user_day_of_arrival, it.user_day_of_departure);

			if ((client_arrival_earlier | client_arrival_later) == 0)
			{
				cerr << client.user_name << ", the room is occupied!" << endl;
				return;
			}
		}// for it 
	}

	reservation[number].push_back(client);
	return;

}
/*****************************************************************/
/*					S H O W   R E S E R V A T I O N				* /
/*****************************************************************/
void Metropol :: Show_Reservation()
{
	if (reservation.empty())
	{
		cout << "Database is empty!" << endl;
		return;
	}
	for (auto& show: reservation)
	{
		//cout <<"Number of room: " << show.first << "\t";
		for (auto& s : show.second)
		{
			cout << "Number of room: " << show.first << "\t";
			cout << "Guest name: " << s.user_name << "\t";
			if (s.user_name.size() < 12)
			{
				cout << "\t";
			}
			cout << "Arrival/departure date: "
				<< s.user_day_of_arrival.day
				<< " - " << s.user_day_of_arrival.month
				<< " / " << s.user_day_of_departure.day << " - "
				<< s.user_day_of_departure.month;
			cout << endl;
		}
	}
	cout << endl;
}
/*****************************************************************/
/*					A N N U L   R E S E R V A T I O N			* /
/*****************************************************************/
void Metropol::Annul_Reservation(const int& number, string& name)
{
	auto iterator_hotel = holel_database.find(number);
	if (iterator_hotel == holel_database.end())
	{
		cerr << "You enter wrong number! Please, try again!" << endl;
		return;
	}

	auto iterator_reservation = reservation.find(number);
	// the room is not reserved
	if (iterator_reservation == reservation.end())
	{
		cerr << "This number is already available!" << endl;
		return;
	}

	auto res = find_if(begin(reservation[number]), end(reservation[number]),
		[&name](Information_about_user& name_res) {return name_res.user_name == name; });
	reservation[number].erase(res);
	
	if ((reservation[number].empty()))
	{
		holel_database[number].second = true;
		reservation.erase(number);
	}
}
/*****************************************************************/
/*					H E L P E R   F U N C T I O N				* /
/*****************************************************************/
bool Metropol::Earlier(const Date& lhs_departure, const Date& rhs_arrival)
{
	return  tie(lhs_departure.month, lhs_departure.day) < 
			tie(rhs_arrival.month, rhs_arrival.day);
}

bool Metropol::Later(const Date& lhs_arrival,const Date& rhs_departure)
{
	return  tie(lhs_arrival.month, lhs_arrival.day) >
		tie(rhs_departure.month, rhs_departure.day);
}

void Metropol::Show_Reservation(ostringstream& res_output) const
{

	if (reservation.empty())
	{
		res_output << "Database is empty!" << endl;
		return;
	}
	for (auto& show : reservation)
	{
		//cout <<"Number of room: " << show.first << "\t";
		for (auto& s : show.second)
		{
			res_output << "Number of room: " << show.first << "\t";
			res_output << "Guest name: " << s.user_name << "\t";
			if (s.user_name.size() < 12)
			{
				res_output << "\t";
			}
			res_output << "Arrival/departure date: "
				<< s.user_day_of_arrival.day
				<< " - " << s.user_day_of_arrival.month
				<< " / " << s.user_day_of_departure.day << " - "
				<< s.user_day_of_departure.month;
			res_output << endl;
		}
	}
	res_output << endl;
}