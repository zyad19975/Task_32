#include <iostream>
#include <string>
#include <DataBase.h>
using namespace std;

enum Shipment_Method
{
    SHIP,
    AIRPLANE
};

struct Shipment_constructor
{
    int EnterCost;
    int CheckCost;
    string type;
    float CostPerTime;
    Shipment_Method ShipmentMethod;
};
/*
this function takes two data and return one
it takes the constructor which contains all the properties of the shipment
check it's type (ship or airplane)
then calculate the Cost
*/
float calculateTotalWaitingCost(const Shipment_constructor *Shipment, int WaitingDays)
{
    if (Shipment->ShipmentMethod) // Airplane
    {
        return ((WaitingDays * 24) * (Shipment->CostPerTime));
    }
    else //Ship
    {
        switch (Shipment->type)
        {
        case "Container Ships":
            return (WaitingDays * 5000);
            break;
        case "Bulk Carrier":
            return (WaitingDays * 10000);
            break;
        case "Tanker Ships":
            return (WaitingDays * 15000);
            break;
        default:
            cout << "Ship Type isn't recognized !!" << endl;
            break;
        }
    }
    return -1;
}

float calculateTotalTripCost(const Shipment_constructor *Shipment, int WaitingDays)
{
    if (Shipment->ShipmentMethod) // Airplane
    {
        return (Shipment->EnterCost + calculateTotalWaitingCost(Shipment, WaitingDays) + Shipment->CheckCost);
    }
    else //Ship
    {
        return (Shipment->EnterCost + calculateTotalWaitingCost(Shipment, WaitingDays));
    }
    return -1;
}

int main()
{
    //connect to the data base
    Connect_DB();

    //struct variable contains all the properties of the shipments
    struct Shipment_constructor Shipment;
    do
    {
        //excute the query
        //get the data from ship table
        if (SQL_SUCCESS != SQLExecDirect(sqlstatementhandle, (SQLCHAR *)"select * from Ship", SQL_NTS))
        {
            //show the errors if happend
            show_error(SQL_HANDLE_STMT, sqlstatementhandle);
            break;
        }
        else
        {
            // no errors fetch data
            //this loop will fetch all the rows that returns but we assume that only one row returns
            while (SQLFetch(sqlstatementhandle) == SQL_SUCCESS)
            {
                Shipment_Method ShipmentMethod;
                int EnterCost;
                string type;
                //get data from colum 1
                SQLGetData(sqlstatementhandle, 1, SQL_C_ULONG, &CostPerTime, 0, NULL);
                //get data from colum 2
                SQLGetData(sqlstatementhandle, 2, SQL_C_CHAR, &type, 64, NULL);
                //get data from colum 3
                SQLGetData(sqlstatementhandle, 3, SQL_C_CHAR, &EnterCost, 64, NULL);
                //assign the return values to the struct variable
                Shipment->ShipmentMethod = SHIP;
                Shipment->EnterCost = EnterCost;
                Shipment->type = type;
            }
        }
    } while (FALSE);
    // call the function
    float cost = calculateTotalWaitingCost(Shipment, 5);
    cout << cost << endl;
    Disconnect_DB();
    return 0;
}