#pragma once
#pragma once
#include<iostream>
#include "Start.h"
#include "Entities.h"
using namespace std;


Ingredient* mushroom = new Mushroom("Italian Mushroom", 134.3, 12.6, 125.2, 95);
Ingredient* tomato = new Tomatoes("Khazakh Tomato", 65, 72.3, 98.7, 100);
Ingredient* cheese = new Cheese("Holland Cheese", 77, 87, 102.9, 134);
Ingredient* salt = new Spices("Salt", 12, 0, 72, 12.9);
Ingredient* meat = new Meat("Beef", 105.6, 135.9, 155.2, 200);
Ingredient* pepper = new Spices("Chili Pepper", 0, 0, 9, 40);
Ingredient* rice = new Rice("Tamasha", 5.2, 9.7, 15.3, 20);

int ing_count = 7;
Ingredient** ingredients = new Ingredient * [7]{ mushroom,tomato,cheese,salt,meat,pepper,rice };


RecipeItem* m1 = new RecipeItem{ mushroom,2 };
RecipeItem* t1 = new RecipeItem{ tomato,3 };
RecipeItem* c1 = new RecipeItem{ cheese,4 };
RecipeItem* me1 = new RecipeItem{ meat,1 };
RecipeItem* s1 = new RecipeItem{ salt,2 };

//DOLMA
RecipeItem* r1 = new RecipeItem{ rice,2 };
RecipeItem* t2 = new RecipeItem{ tomato,2 };
RecipeItem* me2 = new RecipeItem{ meat,2 };
RecipeItem* s2 = new RecipeItem{ salt,2 };
RecipeItem* p1 = new RecipeItem{ pepper,2 };

auto items_pizza = new RecipeItem * [4]{ m1,t1,c1,me1 };
auto items_kabab = new RecipeItem * [3]{ s1,me1,t1 };
auto items_dolma = new RecipeItem * [4]{ r1,t2,me2,s2 };

Dish* pizza = new Pizza(items_pizza, 4, "M A R G A R I T T O", 12.70);

Dish* kabab = new Kabab(items_kabab, 3, "T U R K I S H   K A B A B", 10.30);

Dish* dolma = new Dolma(items_dolma, 4, "N A T I O N A L  D O L M A", 9.70);

int dish_count = 0;

Dish** dishes = new Dish * [dish_count] {};



void MainMenu() {
	cout << "\nA D M I N        1" << endl;
	cout << "C U S T O M E R  2" << endl;
}


void CustomerMenu() {
	cout << "\nShow Menu                            1" << endl;
	cout << "Show Detailed Recipe of Any Food     2" << endl;
	cout << "Order Food                           3" << endl;
}

void AdminMenu() {
	cout << "\nAdd Ingredient          1" << endl;
	cout << "Add dish to the Menu    2" << endl;
	cout << "Delete Ingredient       3" << endl;
	cout << "Delete dish from Menu   4" << endl;

}


void AddDish(Dish* dish) {
	auto new_dishes = new Dish * [dish_count] {};

	for (size_t i = 0; i < dish_count; i++)
	{
		new_dishes[i] = dishes[i];
	}

	new_dishes[dish_count] = dish;

	dishes = new_dishes;
	new_dishes = nullptr;
	dish_count++;

}

//auto dishes = new Dish * [dish_count] { pizza, kabab, dolma };

Dish* GetDishById(int id) {

	for (size_t i = 0; i < dish_count; i++)
	{
		if (dishes[i]->GetId() == id) {
			return dishes[i];
		}
	}
	return nullptr;
}


int GetDishIndexByID(int id) {

	for (size_t i = 0; i < dish_count; i++)
	{
		if (dishes[i]->GetId() == id) {
			return i;
		}
	}
	return -1;
}

void DeleteDishByID(int id) {
	int dish_index = GetDishIndexByID(id);
	auto new_dishes = new Dish * [dish_count - 1]{};
	for (size_t i = 0; i < dish_index; i++)
	{
		new_dishes[i] = dishes[i];
	}

	for (size_t i = dish_index, i2 = dish_index + 1; i < dish_count - 1; i++, i2++)
	{
		new_dishes[i] = dishes[i2];
	}
	dishes = new_dishes;
	new_dishes = nullptr;
	dish_count--;
}

Ingredient* GetIngredientById(int id) {

	for (size_t i = 0; i < ing_count; i++)
	{
		if (ingredients[i]->GetId() == id) {
			return ingredients[i];
		}
	}

	return nullptr;
}

void ShowDishes() {
	mysetcolor(15, 0);
	cout << "\nR E S T A U R A N T  M E N U" << endl;;
	mysetcolor(7, 0);
	for (size_t i = 0; i < dish_count; i++)
	{
		cout << "\nMeal Name: " << dishes[i]->GetName() << endl;;
		cout << "Price: " << dishes[i]->GetPrice() << " AZN " << endl;
		cout << "Dish ID: " << dishes[i]->GetId() << endl;
		cout << "==============================" << endl;
	}
}

void ShowCookingDevices() {
	cout << " O V E N          1" << endl;
	cout << " B R A Z Z I E R  2" << endl;
	cout << " P O T            3" << endl;
}


void FoodCookingProcess(CookingDevice* device) {

	bool hasCooked = device->GetHasCooked();
	int wait_time = device->GetSecond();
	cout << device->GetDish()->GetName() << " is being cooked - - - > W A I T ....." << endl;
	Sleep(800);
	for (size_t i = 0; i < device->GetSecond(); i++)
	{
		Sleep(600);
		system("cls");
		mysetcolor(4, 0);
		cout << wait_time << " seconds left ...";
		mysetcolor(7, 0);
		wait_time--;
	}
	cout << " M E A L   R E A D Y " << endl;
	system("pause");
	hasCooked = 1;
	device->SetHasCooked(hasCooked);
}



void ShowIngredients() {

	for (size_t i = 0; i < ing_count; i++)
	{
		cout << "\nID: " << ingredients[i]->GetId() << endl;
		cout << "Ingredient Name: " << ingredients[i]->GetName() << endl;
		cout << "===========================" << endl;
	}
}

Dish* DefineNewDishType(Dish* dish, RecipeItem** items, double price, int count, string name) {


	if (dish->GetId() == 1) {
		Dish* new_dish = new Pizza(items, count, name, price);
		return new_dish;
	}
	else if (dish->GetId() == 2) {
		Dish* new_dish = new Kabab(items, count, name, price);
		return new_dish;
	}
	else if (dish->GetId() == 3) {
		Dish* new_dish = new Dolma(items, count, name, price);
		return new_dish;
	}
	else {
		return nullptr;
	}

}



