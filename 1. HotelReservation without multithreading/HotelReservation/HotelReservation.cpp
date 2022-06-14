#include "Metropol.h"
#include "Client.h"
#include "test_runner.h"

using namespace std;
/*****************************************************************/
/*		                        T E S T S                  		* /
/*****************************************************************/
// the rooms don't overlap
void SimpleTest()
{
    try
    {
        Metropol hotel;
        hotel.Record_Database();

        Client cl1("Ivan", "Bush",      { 24,6  }, { 28,6 });
        Client cl2("Elena", "Bush",     { 25,07 }, { 28,07 });
        Client cl3("George", "Odincov", { 23,07 }, { 27,07 });


        cl1.Make_Reservation(hotel, 5);
        cl2.Make_Reservation(hotel, 10);
        cl3.Make_Reservation(hotel, 15);

        ostringstream res_output;
        hotel.Show_Reservation(res_output);

        const string result = res_output.str();
        const string true_result =
            "Number of room: 5\tGuest name: Ivan Bush\t\tArrival/departure date: 24 - 6 / 28 - 6\n"
            "Number of room: 10\tGuest name: Elena Bush\t\tArrival/departure date: 25 - 7 / 28 - 7\n"
            "Number of room: 15\tGuest name: George Odincov\tArrival/departure date: 23 - 7 / 27 - 7\n\n";
        ASSERT_EQUAL(true_result, result);
    }
    catch (exception& ex)
    {
        cout << "Exceprion happens: " << ex.what();
    }

}

//dates intersect with two of sides, there are more client
void MiddleTest()
{
    try {
        Metropol hotel;
        hotel.Record_Database();

        Client cl1("Ivan", "Bush", { 24,06 }, { 28,06 });
        Client cl2("Elena", "Bush", { 24,07 }, { 28,07 });
        Client cl3("George", "Odincov", { 23,07 }, { 27,07 });
        Client cl4("Rinata", "Odincova", { 23,07 }, { 27,07 });
        Client cl5("Oleg", "Ulanov", { 29,06 }, { 02,07 });
        Client cl6("Olga", "Mira", { 2,8 }, { 2,9 });
        Client cl7("Greg", "Ural", { 24,5 }, { 23,6 });
        Client cl8("Kate", "Ural", { 29,7 }, { 28,8 });
        Client cl9("Samir", "Ural", { 23,8 }, { 29,8 });
        Client cl10("Andre", "Tenoskin", { 23,8 }, { 29,8 });
        Client cl11("Funa", "Tenoshkin", { 2,10 }, { 30,10 });
        Client cl12("Rem", "Tenoshkin", { 2,10 }, { 30,10 });

        cl1.Make_Reservation(hotel, 1);
        cl2.Make_Reservation(hotel, 2);
        cl3.Make_Reservation(hotel, 9);
        cl4.Make_Reservation(hotel, 10);
        cl5.Make_Reservation(hotel, 35);
        cl6.Make_Reservation(hotel, 36);

        cl7.Make_Reservation(hotel, 1);
        cl8.Make_Reservation(hotel, 2);

        cl9.Make_Reservation(hotel, 9);
        cl10.Make_Reservation(hotel, 10);

        cl11.Make_Reservation(hotel, 36);
        cl12.Make_Reservation(hotel, 37);

        ostringstream res_output;
        hotel.Show_Reservation(res_output);

        const string result = res_output.str();
        const string true_result =
            "Number of room: 1\tGuest name: Ivan Bush\t\tArrival/departure date: 24 - 6 / 28 - 6\n"
            "Number of room: 1\tGuest name: Greg Ural\t\tArrival/departure date: 24 - 5 / 23 - 6\n"
            "Number of room: 2\tGuest name: Elena Bush\t\tArrival/departure date: 24 - 7 / 28 - 7\n"
            "Number of room: 2\tGuest name: Kate Ural\t\tArrival/departure date: 29 - 7 / 28 - 8\n"
            "Number of room: 9\tGuest name: George Odincov\tArrival/departure date: 23 - 7 / 27 - 7\n"
            "Number of room: 9\tGuest name: Samir Ural\t\tArrival/departure date: 23 - 8 / 29 - 8\n"
            "Number of room: 10\tGuest name: Rinata Odincova\tArrival/departure date: 23 - 7 / 27 - 7\n"
            "Number of room: 10\tGuest name: Andre Tenoskin\tArrival/departure date: 23 - 8 / 29 - 8\n"
            "Number of room: 35\tGuest name: Oleg Ulanov\t\tArrival/departure date: 29 - 6 / 2 - 7\n"
            "Number of room: 36\tGuest name: Olga Mira\t\tArrival/departure date: 2 - 8 / 2 - 9\n"
            "Number of room: 36\tGuest name: Funa Tenoshkin\tArrival/departure date: 2 - 10 / 30 - 10\n"
            "Number of room: 37\tGuest name: Rem Tenoshkin\tArrival/departure date: 2 - 10 / 30 - 10\n\n";
        
        ASSERT_EQUAL(true_result, result);
    }
    catch (exception& ex)
    {
        cout << "Exceprion happens: " << ex.what();
    }


}

void HardTest()
{
    try {
        Metropol hotel;
        hotel.Record_Database();

        // These clients are settled in empty rooms
        Client cl1("Ivan", "Bush", { 24,06 }, { 28,06 });
        Client cl2("Elena", "Bush", { 24,07 }, { 28,07 });
        Client cl3("George", "Odincov", { 23,8 }, { 27,8 });
        Client cl4("Rinata", "Odincova", { 23,8 }, { 30,8 });
        Client cl5("Oleg", "Ulanov", { 29,06 }, { 02,07 });

        // These clients arrive earlier
        Client cl6("Olga", "Mira", { 18,6 }, { 22,6 });
        Client cl7("Greg", "Ural", { 14,6 }, { 17,6 });
        Client cl8("Kate", "Ural", { 20,5 }, { 20,7 });
        Client cl9("Samir", "Ural", { 20,7 }, { 22,7 });
        Client cl10("Andre", "Tenoskin", { 20,7 }, { 23,7 });
        Client cl11("Funa", "Tenoshkin", { 13,12 }, { 17,12 });
        Client cl12("Rem", "Tenoshkin", { 2,6 }, { 27,6 });

        // These clients arrive later
        Client cl13("Clark", "Bush", { 11,06 }, { 13,06 });
        Client cl14("Lusia", "Bush", { 30,06 }, { 03,07 });
        Client cl15("Theoretic", "Odincov", { 29,07 }, { 24,8 });
        Client cl16("Mule", "Odincova", { 28,8 }, { 30,8 });
        Client cl17("Frank", "Ulanov", { 1,9 }, { 7,9 });
        Client cl18("Jimmy", "Mira", { 1,1 }, { 3,1 });
        Client cl19("Alfonc", "Ural", { 03,07 }, { 14,7 });


        cl1.Make_Reservation(hotel, 5);
        cl2.Make_Reservation(hotel, 6);
        cl3.Make_Reservation(hotel, 7);
        cl4.Make_Reservation(hotel, 8);
        cl5.Make_Reservation(hotel, 9);

        cl6.Make_Reservation(hotel, 5);
        cl7.Make_Reservation(hotel, 5);
        cl8.Make_Reservation(hotel, 6);
        cl9.Make_Reservation(hotel, 7);
        cl10.Make_Reservation(hotel, 8);
        cl11.Make_Reservation(hotel, 10);
        cl12.Make_Reservation(hotel, 9);

        cl13.Make_Reservation(hotel, 5);
        cl14.Make_Reservation(hotel, 5);
        cl15.Make_Reservation(hotel, 6);
        cl16.Make_Reservation(hotel, 7);
        cl17.Make_Reservation(hotel, 8);
        cl18.Make_Reservation(hotel, 10);
        cl19.Make_Reservation(hotel, 9);

        ostringstream res_output;
        hotel.Show_Reservation(res_output);
        const string result = res_output.str();
        const string true_result =
            "Number of room: 5\tGuest name: Ivan Bush\t\tArrival/departure date: 24 - 6 / 28 - 6\n"
            "Number of room: 5\tGuest name: Olga Mira\t\tArrival/departure date: 18 - 6 / 22 - 6\n"
            "Number of room: 5\tGuest name: Greg Ural\t\tArrival/departure date: 14 - 6 / 17 - 6\n"
            "Number of room: 5\tGuest name: Clark Bush\t\tArrival/departure date: 11 - 6 / 13 - 6\n"
            "Number of room: 5\tGuest name: Lusia Bush\t\tArrival/departure date: 30 - 6 / 3 - 7\n"
            "Number of room: 6\tGuest name: Elena Bush\t\tArrival/departure date: 24 - 7 / 28 - 7\n"
            "Number of room: 6\tGuest name: Kate Ural\t\tArrival/departure date: 20 - 5 / 20 - 7\n"
            "Number of room: 6\tGuest name: Theoretic Odincov\tArrival/departure date: 29 - 7 / 24 - 8\n"
            "Number of room: 7\tGuest name: George Odincov\tArrival/departure date: 23 - 8 / 27 - 8\n"
            "Number of room: 7\tGuest name: Samir Ural\t\tArrival/departure date: 20 - 7 / 22 - 7\n"
            "Number of room: 7\tGuest name: Mule Odincova\tArrival/departure date: 28 - 8 / 30 - 8\n"
            "Number of room: 8\tGuest name: Rinata Odincova\tArrival/departure date: 23 - 8 / 30 - 8\n"
            "Number of room: 8\tGuest name: Andre Tenoskin\tArrival/departure date: 20 - 7 / 23 - 7\n"
            "Number of room: 8\tGuest name: Frank Ulanov\tArrival/departure date: 1 - 9 / 7 - 9\n"
            "Number of room: 9\tGuest name: Oleg Ulanov\t\tArrival/departure date: 29 - 6 / 2 - 7\n"
            "Number of room: 9\tGuest name: Rem Tenoshkin\tArrival/departure date: 2 - 6 / 27 - 6\n"
            "Number of room: 9\tGuest name: Alfonc Ural\t\tArrival/departure date: 3 - 7 / 14 - 7\n"
            "Number of room: 10\tGuest name: Funa Tenoshkin\tArrival/departure date: 13 - 12 / 17 - 12\n"
            "Number of room: 10\tGuest name: Jimmy Mira\t\tArrival/departure date: 1 - 1 / 3 - 1\n\n";

        ASSERT_EQUAL(true_result, result);
        ////---------------------------------------------------------
        //// These clients arrive earlier
        
        cl13.Canal_Reservation(hotel, 5);
        cl14.Canal_Reservation(hotel, 5);
        cl15.Canal_Reservation(hotel, 6);
        cl16.Canal_Reservation(hotel, 7);
        cl17.Canal_Reservation(hotel, 8);
        cl18.Canal_Reservation(hotel, 10);
        cl19.Canal_Reservation(hotel, 9);

        ostringstream res_output_2;
        hotel.Show_Reservation(res_output_2);
        const string result_2 = res_output_2.str();
        const string true_result_2 =
            "Number of room: 5\tGuest name: Ivan Bush\t\tArrival/departure date: 24 - 6 / 28 - 6\n"
            "Number of room: 5\tGuest name: Olga Mira\t\tArrival/departure date: 18 - 6 / 22 - 6\n"
            "Number of room: 5\tGuest name: Greg Ural\t\tArrival/departure date: 14 - 6 / 17 - 6\n"
            "Number of room: 6\tGuest name: Elena Bush\t\tArrival/departure date: 24 - 7 / 28 - 7\n"
            "Number of room: 6\tGuest name: Kate Ural\t\tArrival/departure date: 20 - 5 / 20 - 7\n"
            "Number of room: 7\tGuest name: George Odincov\tArrival/departure date: 23 - 8 / 27 - 8\n"
            "Number of room: 7\tGuest name: Samir Ural\t\tArrival/departure date: 20 - 7 / 22 - 7\n"
            "Number of room: 8\tGuest name: Rinata Odincova\tArrival/departure date: 23 - 8 / 30 - 8\n"
            "Number of room: 8\tGuest name: Andre Tenoskin\tArrival/departure date: 20 - 7 / 23 - 7\n"
            "Number of room: 9\tGuest name: Oleg Ulanov\t\tArrival/departure date: 29 - 6 / 2 - 7\n"
            "Number of room: 9\tGuest name: Rem Tenoshkin\tArrival/departure date: 2 - 6 / 27 - 6\n"
            "Number of room: 10\tGuest name: Funa Tenoshkin\tArrival/departure date: 13 - 12 / 17 - 12\n\n";

        ASSERT_EQUAL(true_result_2, result_2);
    }
    catch (exception& ex)
    {
        cout << "Exceprion happens: " << ex.what();
    }
}

/*****************************************************************/
/*		                        M A I N                 		* /
/*****************************************************************/
int main()
{
    TestRunner tr; 
    RUN_TEST(tr, SimpleTest);
    RUN_TEST(tr, MiddleTest);
    RUN_TEST(tr, HardTest);
    
}
