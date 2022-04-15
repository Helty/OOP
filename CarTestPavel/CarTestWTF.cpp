#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Car/Car.h"

//������ �������
// void RequireCCarToFail(const CCar& car, const std::function<bool(CCar&)>& action)
//{
//	CCar carCopy(car);
//	REQUIRE(!action(carCopy));
//	REQUIRE(carCopy.GetDirection() == car.GetDirection());
//	// ���������� ��������� ������ ��������
// }
//
// void RequireCCarToSucceed(CCar& car, const std::function<bool(CCar&)>& action, bool expectToBeTurnedOn, int expectedGear, int expectedSpeed)
//{
//	REQUIRE(action(car));
// }

SCENARIO("�������� ������ �����")
{
	//{
	//	CCar car;
	//	car.TurnOnEngine();
	//	car.SetGear(Gear::FIRST);
	//	car.SetSpeed(20);
	//	RequireCCarToFail(car, [](CCar& car) { return car.SetGear(Gear::FIRST); });
	//}

	GIVEN("A moving car with turned on engine at backward gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(15);
		WHEN("Setting speed in range 0-20")
		{
			car.SetSpeed(20);
			THEN("CCar changes its speed")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}
	}
}
//������ �������

SCENARIO("1. �������� ������ TurnOnEngine()")
{
	SECTION("1.1 ���������� true, ���� ��������� ���������")
	{
		CCar car;

		WHEN("��������� ���������")
		{
			bool result = car.TurnOnEngine();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	SECTION("1.2 ���������� true, ���� ��� ��� �������.")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("��������� ����������, �� ���������� ���������")
		{
			bool result = car.TurnOnEngine();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	SECTION("1.3 ����� ��������� ���������, ������ ��������� �� ����������� ��������, � ��������� �����, �������� 0,")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("��������� ����������")
		{
			bool state = car.IsTurnedOn();
			Direction direction = car.GetDirection();
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("��������� ��������� - ��������")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}

			THEN("������ ��������� � ��������� �����")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}

			THEN("������ ��������� �� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("2. �������� ������ TurnOffEngine()")
{

	SECTION("2.1 ��������� ���������, ���� �� ������� � ������� �������� � �����������, � ���������� �����, ��������  ����� ���� - �������� true")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("�������� ���������")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("2.2 ��������� ��������� ���������")
			{
				bool expectedResult = false;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.3 ��������� ���������, ���� �� ��� ��������")
	{
		CCar car;

		WHEN("�������� ���������")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("��������� ��������� ���������")
			{
				bool expectedResult = false;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.4 ��������� ���������, ���� �������� ������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("�������� ���������")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("��������� ��������� ��������")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.5 ��������� ���������, ���� �������� ������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("�������� ���������")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("��������� ��������� ��������")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.6 ��������� ���������, ���� �������� ����������� � �������� ���������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(1);
		car.SetGear(Gear::NEUTRAL);

		WHEN("�������� ���������")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();
			int speed = car.GetSpeed();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("��������� ��������� ��������")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}

			THEN("�������� ����� ��������� ��������")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("3 �������� SetGear() � SetSpeed() - ��� ����������� ���������")
{
	SECTION("3.1 ��� ����������� ��������� ���������� ������ ��������")
	{
		CCar car;

		WHEN("������� ��������")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.2 ��� ����������� ��������� ������ �������� (-1) �� ����������")
	{
		CCar car;

		WHEN("������� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.3 ��� ����������� ��������� ������ �������� �� ����������")
	{
		CCar car;

		WHEN("������� ������ ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.4 ��� ����������� ��������� ������������� �������� �� ������������")
	{
		CCar car;

		WHEN("��������� �������� ������ ����")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� �� ����")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("3.5 ��� ����������� ��������� �������� �� ������������")
	{
		CCar car;

		WHEN("��������� �������� ������ ����")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� �� ����")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("4.1 �������� SetGear() � SetSpeed() - ��� ���������� ��������� - ������ ��������")
{
	SECTION("4.1.1 �� ������ ��� (-1) ����� ������������� �� ������� ��������")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("������� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1.2 ����� ������ �� ����� ����� �������� 0, ����������� ����� stop")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("����� �������� 0")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ����� �� �����")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.3 ����� ������� �������� 1, ����������� ����� back")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("����� �������� 1")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����� 1")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ��������� �����")
			{
				Direction expectedResult = Direction::BACK;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.4 ����� ������� �������� 20, ����������� ����� back")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("����� �������� 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����� 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ��������� �����")
			{
				Direction expectedResult = Direction::BACK;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.5 ��� �������� ����� �� ����������� �������� �� ����������� �������� ������ ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("������� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� ����� 10")
			{
				int expectedResult = 10;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ��������� �����")
			{
				Direction expectedResult = Direction::BACK;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.6 �������������� �� ������ ���� �� ����������� �������� �� ��������� ��������, �������� ����� ���������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("�������� ��������")
		{
			bool result = car.SetSpeed(8);
			int speed = car.GetSpeed();

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����� 8")
			{
				int expectedResult = 8;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1.7 �������������� �� ������ ���� �� ����������� �������� �� ��������� �������� ������������� �� �������� �������� ����� ������ ����� ���������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(0);

		WHEN("������� ������ ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1[���������� �������� 1] ������ ������� �������� ������ 0 ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("����� ������������� ��������")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[���������� �������� 2] ������ ������� �������� ������ 20 ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("����� �������� ������ 20")
		{
			bool result = car.SetSpeed(21);
			int speed = car.GetSpeed();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[���������� �������� 3] �������������� �� ������ ���� �� ����������� �������� �� ��������� �������� ������������� �� �������� ������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(15);
		car.SetGear(Gear::NEUTRAL);

		WHEN("����� ������ ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1[���������� �������� 4] �������������� �� ������ ���� �� ����������� �������� �� ��������� ��������, �������� ������ ���������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("���������� ��������")
		{
			bool result = car.SetSpeed(15);
			int speed = car.GetSpeed();

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� �������� ����������")
			{
				int expectedResult = 10;
				REQUIRE(speed == expectedResult);
			}
		}
	}
	/*
	SECTION("4.1[���������� �������� 5] ������ �������� �������� ������ -1")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(20);

		WHEN("���������� ��������")
		{
			bool result = car.SetGear(-2);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� �����")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}
		}
	}
	*/
}

SCENARIO("4.2 �������� SetGear() � SetSpeed() - ��� ���������� ��������� - ��������")
{
	SECTION("4.2.1 �� �������� ����� ������������� �� ��������")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("������� ��������")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ���������� true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.2.2 ������������� �� �������� � 1� �������� � ������������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(15);

		WHEN("������� �������� � ��������������")
		{
			car.SetGear(Gear::NEUTRAL);
			car.SetSpeed(0);

			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ����� �� �����")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.2.7 ��� ��������� �������� ��� �������� ����� ������ �������� ������ ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(15);
		car.SetGear(Gear::NEUTRAL);

		WHEN("������� ������ ��������")
		{
			car.SetGear(Gear::REVERSE);

			int gear = static_cast<int>(car.GetGear());
			Direction direction = car.GetDirection();

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("������ ��������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}
}

SCENARIO("4.3 �������� SetGear() � SetSpeed() - ��� ���������� ��������� - ������ ��������(1) - �������� 0 � 30")
{
	SECTION("4.3.1 ����� ������ �� ����� ����� �������� 0, ����������� ����� stop")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("����� �������� 0")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ����� �� �����")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.2 ����� ������� �������� 1, ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("����� �������� 1")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 1")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ��������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.3 �� ������� �������� ����� �������� ������ ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("������� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}

			THEN("������ ����� �� �����")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.4 ����� ������� �������� 30")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("����� �������� 30")
		{
			bool result = car.SetSpeed(30);
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 30")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.5 ��� �������� 30 ����� ������������� � 3� �� 1� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.6 ��� �������� 20 ����� ������������� � 2� �� 1� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(20);

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.7 �� �������� ����� ��������� �������� � 30 �� 20")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� �������� �� 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.8 �� �������� ������ ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� �������� �� 25")
		{
			bool result = car.SetSpeed(25);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.9 �� ������ �������� ����� ������������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);

		WHEN("��������������")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ����� �� �����")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.10 �� �������� ��������� �������� �� 40 �� 20 � ������������� �� 1�")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(20);

		WHEN("��������� ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ���������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.11 �� �������� ����� ������������� � �������� �� 1� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::NEUTRAL);

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3[���������� �������� 1] ������ ������� �������� ������ 0")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("������ �������� ������ 0")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("��������� ������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3[���������� �������� 2] ������ ������� �������� ������ ������ 30")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("������ �������� ������ 30")
		{
			bool result = car.SetSpeed(31);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("��������� ������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3[���������� �������� 3] ������ ������������� �� ������ �������� (-1) �� ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(10);

		WHEN("������������� �� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3[���������� �������� 4] ��� �������� 31 ������ ������������� �� 2� �� 1� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(31);

		WHEN("������������� �� 2� �� 1� ��������")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

SCENARIO("4.4 �������� SetGear() � SetSpeed() - ��� ���������� ��������� - ������ �������� (2) - �������� 20 � 50")
{
	SECTION("4.4.1 ��� �������� 20 ����� ������������� � 1� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);

		WHEN("������������� �� 1� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.2 ��� �������� 30 ����� ������������� � 1� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);

		WHEN("������������� �� 1� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.3 ��� �������� 30 ����� ������������� � 3� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("������������� �� 3� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.4 ��� �������� 50 ����� ������������� � 3� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);

		WHEN("������������� �� 3� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.5 ��� �������� 40 ����� ������������� � 4� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);

		WHEN("������������� �� 4� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.6 ��� �������� 50 ����� ������������� � 5� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);

		WHEN("������������� �� 5� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.7 ����� ������������� �� ������ �� ������ ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("������������� �� 2� ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.8 ����� ������� �������� 20 ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("��������� �������� �� 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.4.9 ����� ������� �������� 50 ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("��������� �������� �� 50")
		{
			bool result = car.SetSpeed(50);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.4.10 ����� ������������� �� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("�������� ��������")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.11 ����� ������������� � �������� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetGear(Gear::NEUTRAL);

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.12 �� �������� ����� ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� ��������")
		{
			bool result = car.SetSpeed(25);
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4.13 �� �������� ������ ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� ��������")
		{
			bool result = car.SetSpeed(45);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[���������� �������� 1] ��� ������� �������� � ������� �������� ������ �������� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[���������� �������� 2] �� ������ �������� ������ ������������� �� ������ �������� (-1)")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(25);
		car.SetGear(Gear::SECOND);

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[���������� �������� 3] �� ������ �������� ������ ������� �������� ������ 20")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(25);
		car.SetGear(Gear::SECOND);

		WHEN("��������� �������� �� 19")
		{
			bool result = car.SetSpeed(19);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[���������� �������� 4] �� ������ �������� ������ ������� �������� ������ 50")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(25);
		car.SetGear(Gear::SECOND);

		WHEN("��������� �������� �� 51")
		{
			bool result = car.SetSpeed(51);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[���������� �������� 5] ��� �������� 19 ������ ������������� � 1� �� 2� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(19);

		WHEN("����������� �������� �� ������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[���������� �������� 6] ��� �������� 51 ������ ������������� � 3� �� 2� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(51);

		WHEN("����������� �������� �� ������")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ������ ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

SCENARIO("4.5 �������� SetGear() � SetSpeed() - ��� ���������� ��������� - ������ �������� (3) - �������� 30 � 60")
{
	SECTION("4.5.1 ��� �������� 30 ����� ������������� � 1� �� 3� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);

		WHEN("������������� �� 1� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.3 ��� �������� 50 �� 2� �������� ����� ������������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);

		WHEN("������������� �� 2� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.4 ��� �������� 40 � 4� �������� ����� ������������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);

		WHEN("������������� � 4� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.5 ��� �������� 60 � 4� �������� ����� ������������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(60);

		WHEN("������������� � 4� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.6 ��� �������� 50 �� 5� �������� ����� ������������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);

		WHEN("������������� � 5� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.7 ��� �������� 60 �� 5� �������� ����� ������������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);
		car.SetSpeed(60);

		WHEN("������������� � 5� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.8 �� 3� �������� ����� ������������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("������������� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.9 ����� ������� �������� 30 ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);

		WHEN("��������� ��������")
		{
			bool result = car.SetSpeed(30);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 30")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.5.10 ����� ������� �������� 60 ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);

		WHEN("��������� ��������")
		{
			bool result = car.SetSpeed(60);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.5.11 ����� ������������� �� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);

		WHEN("������������� �� ��������")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 45")
			{
				int expectedResult = 45;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.12 ����� ������������� � �������� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);
		car.SetGear(Gear::NEUTRAL);

		WHEN("������������� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 45")
			{
				int expectedResult = 45;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.13 �� �������� ����� ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� ��������")
		{
			bool result = car.SetSpeed(40);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.14 �� �������� ������ ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� ��������")
		{
			bool result = car.SetSpeed(50);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 45")
			{
				int expectedResult = 45;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.15 �� �������� ��������� �������� �� 70 �� 50 � ������������� �� 3�")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);
		car.SetSpeed(70);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� ��������  � �������� 3� ��������")
		{
			car.SetSpeed(50);
			car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("�������� 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 1] ��� ������� �������� � ������� �������� ������ �������� 3� ��������")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("������������� �� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 2] �� 3� �������� ������ ������������� �� ������ �������� (-1)")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("������������� �� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 3] ��� �������� 29 ������ ������������� � 2� �� 3� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(29);
		car.SetGear(Gear::SECOND);

		WHEN("�������� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 2� ��������")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 4] ��� �������� 61 ������ ������������� � 4� �� 3� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(61);

		WHEN("�������� 3� ��������")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 7] ������ ������� ������������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::THIRD);

		WHEN("������ ������������� ��������")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 8] ������ ������� �������� 29")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::THIRD);

		WHEN("������ �������� 29")
		{
			bool result = car.SetSpeed(29);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5 [���������� �������� 9] ������ ������� �������� 61")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::THIRD);

		WHEN("������ �������� 61")
		{
			bool result = car.SetSpeed(61);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("4.6 �������� SetGear() � SetSpeed() - ��� ���������� ��������� - ��������� �������� (4) - �������� 40 � 90")
{
	SECTION("4.6.1 ��� �������� 40 �� 2� �������� ����� ������������� �� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.2 ��� �������� 40 � 3� �������� ����� ������������� �� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(40);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.3 ��� �������� 60 � 3� �������� ����� ������������� �� 4� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.4 ��� �������� 50 � 5� �������� ����� ������������� �� 4� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.5 ��� �������� 60 � 5� �������� ����� ������������� �� 4� �������� ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FIFTH);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.7 � 4� �������� ����� ������������� �� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.8 ����� ������� �������� 40 ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("������ �������� 40")
		{
			bool result = car.SetSpeed(40);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ��������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.6.9 ����� ������� �������� 90 ����������� ����� forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("������ �������� 90")
		{
			bool result = car.SetSpeed(90);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 40")
			{
				int expectedResult = 90;
				REQUIRE(speed == expectedResult);
			}

			THEN("������ ��������� ������")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.6.11 ����� ������������� � �������� �� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::NEUTRAL);

		WHEN("������������� �� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.13 �� �������� ����� ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(90);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� �������� �� 50")
		{
			bool result = car.SetSpeed(50);
			int speed = car.GetSpeed();

			THEN("����� ������ true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ��������� �� 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6.14 �� �������� ������ ��������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(80);
		car.SetGear(Gear::NEUTRAL);

		WHEN("��������� �������� �� 5")
		{
			bool result = car.SetSpeed(85);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� �������� �������")
			{
				int expectedResult = 80;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 1] ��� ������� �������� � ������� �������� ������ �������� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("�������� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 2] � 4� �������� ������ ������������� �� ������ �������� (-1)")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("�������� ������ ��������")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 4� ��������")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 3] ��� �������� 39 ������ ������������� � 3� �� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(39);

		WHEN("�������� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 3� ��������")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 4] ��� �������� 91 ������ ������������� � 5� �� 4� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FIFTH);
		car.SetSpeed(91);

		WHEN("�������� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 5� ��������")
			{
				int expectedResult = 5;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 5] �� �������� ��������� �������� �� 39 � ������������� �� 4�")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(39);

		WHEN("�������� 4� ��������")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� ����������� ��������")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 7] ������ ������� ������������� ��������")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FOURTH);

		WHEN("������ ������������� ��������")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 8] ������ ������� �������� 39")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FOURTH);

		WHEN("������ �������� 39")
		{
			bool result = car.SetSpeed(39);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6 [���������� �������� 9] ������ ������� �������� 91")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FOURTH);

		WHEN("������ �������� 91")
		{
			bool result = car.SetSpeed(91);
			int speed = car.GetSpeed();

			THEN("����� ������ false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("�������� 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}
