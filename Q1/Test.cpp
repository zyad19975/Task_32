/*This file is to test the functions only*/

#include <iostream>
#include <string>
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

float calculateTotalWaitingCost(const Shipment_constructor *Shipment, int WaitingDays)
{
    if (Shipment->ShipmentMethod) // Airplane
    {
        return ((WaitingDays * 24) * Shipment->CostPerTime);
    }
    else //Ship
    {
        if ((Shipment->type) == "Container Ships")
        {
            return (WaitingDays * 5000);
        }
        else if ((Shipment->type) == "Bulk Carrier")
        {
            return (WaitingDays * 10000);
        }
        else if ((Shipment->type) == "Tanker Ships")
        {
            return (WaitingDays * 15000);
        }
        else
        {
            cout << "Ship Type isn't recognized !!" << endl;
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
    struct Shipment_constructor *Shipment = new Shipment_constructor;
    Shipment->ShipmentMethod = SHIP;
    Shipment->EnterCost = 1500;
    Shipment->type = "Bulk Carrier";
    float cost = calculateTotalWaitingCost(Shipment, 5);
    float tripcost = calculateTotalTripCost(Shipment, 5);
    cout << cost << endl;
    cout << tripcost << endl;
    return 0;
}