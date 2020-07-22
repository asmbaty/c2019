#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#elif defined __linux__
#include <unistd.h>
#endif

/* Uncomment below line to enable debug logs */
/* #define DEBUG */

std::string _stateToStrCourier[] = {"Received", "VerifyReachbility", "AssignPerson",
									"DispatchPackage", "GetDeliveryConfirmation", "Complete"};
std::string _stateToStrVendor[] = {"Received", "VerifyInventory", "GetItemFromWareHouse",
								   "PackItem", "ContactCourier", "Complete"};
std::string _stateToStrOrderTeam[] = {"Received", "VerifyPayment", "ContactVendor", "Complete"};

void mySleep(unsigned int millisecs)
{
#ifdef _WIN32
	Sleep(millisecs);
#elif defined __linux__
	usleep(1000 * millisecs);
#endif
}

class Courier
{
public:
	void submitRequestToCourier()
	{
		_state = 0;
	}
	bool checkStatus()
	{
#ifdef DEBUG
		std::cout << "Courier: Current State: " << _stateToStrCourier[_state] << std::endl;
#endif
		mySleep(500); /* Do some useful work here */

		_state++;
		if (_state == Complete)
			return 1;
		return 0;
	}

private:
	enum States
	{
		Received,
		VerifyReachbility,
		AssignPerson,
		DispatchPackage,
		GetDeliveryConfirmation,
		Complete
	};
	int _state;
};

class Vendor
{
public:
	void submitRequestToVendor()
	{
		_state = 0;
	}
	bool checkStatus()
	{
#ifdef DEBUG
		std::cout << "Vendor: Current State: " << _stateToStrVendor[_state] << std::endl;
#endif
		mySleep(500); /* Do some useful work here */

		_state++;
		if (_state == Complete)
			return 1;
		return 0;
	}

private:
	enum States
	{
		Received,
		VerifyInventory,
		GetItemFromWareHouse,
		PackItem,
		ContactCourier,
		Complete
	};
	int _state;
};

class OrderingTeam
{
public:
	void submitRequestToOrderTeam()
	{
		_state = 0;
	}
	bool checkStatus()
	{
#ifdef DEBUG
		std::cout << "OrderingTeam: Current State: " << _stateToStrOrderTeam[_state] << std::endl;
#endif
		mySleep(500); /* Do some useful work here */
		_state++;
		if (_state == Complete)
			return 1;
		return 0;
	}

private:
	enum States
	{
		Received,
		VerifyPayment,
		ContactVendor,
		Complete
	};
	int _state;
};

class OnlineShoppingFacade
{
public:
	OnlineShoppingFacade()
	{
		_count = 0;
	}
	void submitRequest()
	{
		_state = 0;
	}
	bool checkStatus()
	{
		/* Item request has just been received */
		switch (_state)
		{
		case Received:
			_state++;
			/* Forward the job request to the ordering team */
			_order.submitRequestToOrderTeam();
			std::cout << "submitted to Order Team - " << _count << " followups till now" << std::endl;
			break;
		case SubmittedToOrderTeam:
			/* If order team has completed verification, 
   place the request with vendor */
			if (_order.checkStatus())
			{
				_state++;
				_vendor.submitRequestToVendor();
				std::cout << "submitted to Vendor - " << _count << " followups till now" << std::endl;
			}
			break;
		case SubmittedToVendor:
			/* If vendor has packed the item, forward it to courier */
			if (_vendor.checkStatus())
			{
				_state++;
				_courier.submitRequestToCourier();
				std::cout << "submitted to Courier - " << _count << " followups till now" << std::endl;
			}
			break;
		case SubmittedToCourier:
			/* If package is delivered, order is complete */
			if (_courier.checkStatus())
				return 1;
		default:
			break;
		}

		_count++;

		/* The order is not complete */
		return 0;
	}
	int numFUPs()

	{
		return _count;
	}

private:
	enum States
	{
		Received,
		SubmittedToOrderTeam,
		SubmittedToVendor,
		SubmittedToCourier
	};

	int _state;
	int _count;

	OrderingTeam _order;
	Vendor _vendor;
	Courier _courier;
};

int main()
{
	OnlineShoppingFacade onlinereq;

	onlinereq.submitRequest();

	/* Keep checking until order is complete */
	while (!onlinereq.checkStatus())
		;

	std::cout << "Order completed after " << onlinereq.numFUPs() << " followups" << std::endl;
}