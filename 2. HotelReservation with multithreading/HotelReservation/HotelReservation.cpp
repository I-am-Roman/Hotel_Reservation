#include "Metropol.h"
#include "Client.h"
#include "test_runner.h"
#include <thread>
#include "profile.h"

using namespace std;
/*****************************************************************/
/*                          T H R E A D                 		* /
/*****************************************************************/
void Thread_Make_Reservation(vector<pair<Client,int>> vec_cl, Metropol& hotel)
{
    //cout << this_thread::get_id() << endl;
    for (size_t i = 0; i < vec_cl.size(); i++)
    {
        vec_cl[i].first.Make_Reservation(hotel, vec_cl[i].second);
    }
}

void Thread_Canal_Reservation(vector<pair<Client, int>> vec_cl, Metropol& hotel)
{
    //cout << this_thread::get_id() << endl;
    for (size_t i = 0; i < vec_cl.size(); i++)
    {
        vec_cl[i].first.Canal_Reservation(hotel, vec_cl[i].second);
    }
}
/*****************************************************************/
/*		                    T E S T S                     		* /
/*****************************************************************/
// the rooms don't overlap
void SimpleTest()
{    
    // push in vector Client and number of room 
    vector<pair<Client, int>> vec_clients_1;
    vec_clients_1.reserve(100);

    vector<pair<Client, int>> vec_clients_2;
    vec_clients_1.reserve(100);

    Metropol hotel;
    hotel.Record_Database();

    Client cl1("Ivan", "Bush", { 22,6 }, { 29,6 });
    Client cl2("Elena", "Bush", { 24,07 }, { 28,07 });
    Client cl3("George", "Odincov", { 23,07 }, { 27,07 });
    Client cl4("Rinata", "Odincova", { 23,9 }, { 27,9 });

    vec_clients_1.push_back({ cl1,9 });
    vec_clients_1.push_back({ cl2,9 });
    vec_clients_1.push_back({ cl3,9 });
    vec_clients_1.push_back({ cl4,9 });


    Client cl7("Greg", "Ural", { 21,7 }, { 30,7 });
    Client cl8("Kate", "Ural", { 22,7 }, { 29,7 });
    Client cl9("Samir", "Ural", { 22,7 }, { 29,7 });
    Client cl10("Andre", "Tenoskin", { 24,7 }, { 25,7 });
    Client cl11("Funa", "Tenoshkin", { 22,7 }, { 29,7 });
    Client cl12("Rem", "Tenoshkin", { 22,7 }, { 29,7 });

    vec_clients_2.push_back({ cl7,9 });
    vec_clients_2.push_back({ cl8,9 });
    vec_clients_2.push_back({ cl9,9 });
    vec_clients_2.push_back({ cl10,9 });
    vec_clients_2.push_back({ cl11,9 });
    vec_clients_2.push_back({ cl12,9 });

    thread th1(Thread_Make_Reservation, ref(vec_clients_1), ref(hotel));
    thread th2(Thread_Make_Reservation, ref(vec_clients_2), ref(hotel));

    Client cl13("Gre", "Ura", { 22,7 }, { 29,7 });
    Client cl14("Kat", "Ura", { 22,7 }, { 29,7 });
    Client cl15("Sami", "Ura", { 22,7 }, { 29,7 });
    Client cl16("And", "Teno", { 23,8 }, { 29,8 });
    Client cl17("Funa", "Teno", { 22,7 }, { 29,7 });
    Client cl18("Rem", "Teno", { 22,7 }, { 29,7 });

    cl13.Make_Reservation(hotel, 9);
    cl14.Make_Reservation(hotel, 9);
    cl15.Make_Reservation(hotel, 9);
    cl16.Make_Reservation(hotel, 9);
    cl17.Make_Reservation(hotel, 9);
    cl18.Make_Reservation(hotel, 9);
    th1.join();
    th2.join();

    ostringstream res_output;
    hotel.Show_Reservation(res_output);
    cout << endl;
    const string result = res_output.str();
    const string true_result =
        "Number of room: 9\tGuest name: Gre Ura\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 9\tGuest name: And Teno\t\tArrival/departure date: 23 - 8 / 29 - 8\n"
        "Number of room: 9\tGuest name: Ivan Bush\t\tArrival/departure date: 22 - 6 / 29 - 6\n"
        "Number of room: 9\tGuest name: Rinata Odincova\tArrival/departure date: 23 - 9 / 27 - 9\n\n";
        
    ASSERT_EQUAL(true_result, result);

}

void MiddleTest()
{
    // push in vector Client and number of room 
    vector<pair<Client, int>> vec_clients_1;
    vec_clients_1.reserve(100);

    vector<pair<Client, int>> vec_clients_2;
    vec_clients_1.reserve(100);

    Metropol hotel;
    hotel.Record_Database();

    Client cl1("Ivan", "Bush", { 22,6 }, { 29,6 });
    Client cl2("Elena", "Bush", { 24,07 }, { 28,07 });
    Client cl3("George", "Odincov", { 23,07 }, { 27,07 });
    Client cl4("Rinata", "Odincova", { 23,9 }, { 27,9 });

    vec_clients_1.push_back({ cl1,1 });
    vec_clients_1.push_back({ cl2,2 });
    vec_clients_1.push_back({ cl3,3 });
    vec_clients_1.push_back({ cl4,4 });


    Client cl7("Greg", "Ural", { 21,7 }, { 30,7 });
    Client cl8("Kate", "Ural", { 22,7 }, { 29,7 });
    Client cl9("Samir", "Ural", { 22,7 }, { 29,7 });
    Client cl10("Andre", "Tenoskin", { 24,7 }, { 25,7 });
    Client cl11("Funa", "Tenoshkin", { 22,7 }, { 29,7 });
    Client cl12("Rem", "Tenoshkin", { 22,7 }, { 29,7 });

    vec_clients_2.push_back({ cl7,5 });
    vec_clients_2.push_back({ cl8,6 });
    vec_clients_2.push_back({ cl9,7 });
    vec_clients_2.push_back({ cl10,8 });
    vec_clients_2.push_back({ cl11,9 });
    vec_clients_2.push_back({ cl12,10 });

    thread th1(Thread_Make_Reservation, ref(vec_clients_1), ref(hotel));
    thread th2(Thread_Make_Reservation, ref(vec_clients_2), ref(hotel));

    Client cl13("Gre", "Ura", { 22,7 }, { 29,7 });
    Client cl14("Kat", "Ura", { 22,7 }, { 29,7 });
    Client cl15("Sami", "Ura", { 22,7 }, { 29,7 });
    Client cl16("And", "Teno", { 23,8 }, { 29,8 });
    Client cl17("Funa", "Teno", { 22,7 }, { 29,7 });
    Client cl18("Rem", "Teno", { 22,7 }, { 29,7 });

    cl13.Make_Reservation(hotel, 11);
    cl14.Make_Reservation(hotel, 12);
    cl15.Make_Reservation(hotel, 13);
    cl16.Make_Reservation(hotel, 14);
    cl17.Make_Reservation(hotel, 15);
    cl18.Make_Reservation(hotel, 16);
    th1.join();
    th2.join();

    ostringstream res_output;
    hotel.Show_Reservation(res_output);

    const string result = res_output.str();
    const string true_result =
        "Number of room: 1\tGuest name: Ivan Bush\t\tArrival/departure date: 22 - 6 / 29 - 6\n"
        "Number of room: 2\tGuest name: Elena Bush\t\tArrival/departure date: 24 - 7 / 28 - 7\n"
        "Number of room: 3\tGuest name: George Odincov\tArrival/departure date: 23 - 7 / 27 - 7\n"
        "Number of room: 4\tGuest name: Rinata Odincova\tArrival/departure date: 23 - 9 / 27 - 9\n"
        "Number of room: 5\tGuest name: Greg Ural\t\tArrival/departure date: 21 - 7 / 30 - 7\n"
        "Number of room: 6\tGuest name: Kate Ural\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 7\tGuest name: Samir Ural\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 8\tGuest name: Andre Tenoskin\tArrival/departure date: 24 - 7 / 25 - 7\n"
        "Number of room: 9\tGuest name: Funa Tenoshkin\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 10\tGuest name: Rem Tenoshkin\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 11\tGuest name: Gre Ura\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 12\tGuest name: Kat Ura\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 13\tGuest name: Sami Ura\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 14\tGuest name: And Teno\t\tArrival/departure date: 23 - 8 / 29 - 8\n"
        "Number of room: 15\tGuest name: Funa Teno\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 16\tGuest name: Rem Teno\t\tArrival/departure date: 22 - 7 / 29 - 7\n\n";

    ASSERT_EQUAL(true_result, result);

    thread th3(Thread_Canal_Reservation, ref(vec_clients_1), ref(hotel));
    thread th4(Thread_Canal_Reservation, ref(vec_clients_2), ref(hotel));

    cl13.Canal_Reservation(hotel, 11);
    cl14.Canal_Reservation(hotel, 12);
    cl15.Canal_Reservation(hotel, 13);
    cl16.Canal_Reservation(hotel, 14);
    th3.join();
    th4.join();

    ostringstream res_output2;
    hotel.Show_Reservation(res_output2);

    const string result2 = res_output2.str();
    const string true_result2 = 
        "Number of room: 15\tGuest name: Funa Teno\t\tArrival/departure date: 22 - 7 / 29 - 7\n"
        "Number of room: 16\tGuest name: Rem Teno\t\tArrival/departure date: 22 - 7 / 29 - 7\n\n";

    ASSERT_EQUAL(true_result2, result2);

}

/*****************************************************************/
/*		                        M A I N                 		* /
/*****************************************************************/
int main()
{
    //cout << "The number of concurrent threads is " << std::thread::hardware_concurrency() << "\n";

    TestRunner tr; 
    RUN_TEST(tr, SimpleTest);
    RUN_TEST(tr, MiddleTest);   
    return 0;
}
