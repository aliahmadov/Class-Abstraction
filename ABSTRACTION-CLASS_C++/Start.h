#pragma once
#pragma once
#include<iostream>
#include "Entities.h"
#include "Functions.h"
#include<string>
#include<string.h>
using namespace std;




void Start() {

	AddDish(pizza);
	AddDish(kabab);
	AddDish(dolma);

	while (true) {
		MainMenu();
		int select = 0;
		cout << "Enter the option: ";
		cin >> select;


		if (select == 1) {
			AdminMenu();

			int option = 0;
			cout << "Enter the option: ";
			cin >> option;
			system("cls");
			if (option == 1) {
				//Add Ingredient
				ShowDishes();
				int dish_id = 0;
				cout << "Choose the dish type for which you would like to add ingredient (BY ID) : ";
				cin >> dish_id;

				system("cls");
				auto dish = GetDishById(dish_id);
				dish->PrintRecipe();
				ShowIngredients();
				int ing_id = 0;
				cout << "Enter ingredient ID : ";
				cin >> ing_id;

				int amount = 0;
				cout << "Enter the amount : ";
				cin >> amount;

				auto ingredient = GetIngredientById(ing_id);

				auto item = new RecipeItem{ ingredient,amount };

				dish->AddIngredient(item);
				cout << "Success - - - > ";
				cout << amount << " " << ingredient->GetName() << " successfully added to the " << dish->GetName() << endl;
			}
			else if (option == 2) {
				//Add Dish to the Menu
				ShowDishes();
				int dish_id = 0;
				cout << "Choose the dish type (BY ID): ";
				cin >> dish_id;
				Sleep(400);
				system("cls");

				ShowIngredients();

				int number = 0;
				cout << "The number of ingredients to be added: ";
				cin >> number;

				RecipeItem** items = new RecipeItem * [number] {};

				for (size_t i = 0; i < number; i++)
				{
					system("cls");
					ShowIngredients();
					int ing_id = 0;
					cout << "Choose ingredient (BY ID) : ";
					cin >> ing_id;

					int ing_number = 0;
					cout << "Enter amount: ";
					cin >> ing_number;
					auto ingredient = GetIngredientById(ing_id);
					RecipeItem* item = new RecipeItem{ ingredient,ing_number };
					items[i] = item;
				}

				cin.ignore();
				cin.clear();
				string dish_name;
				cout << "Enter the dish name: ";
				getline(cin, dish_name);

				double price = 0;
				cout << "Enter the price: ";
				cin >> price;

				auto dish = GetDishById(dish_id);
				auto new_dish = DefineNewDishType(dish, items, price, number, dish_name);

				AddDish(new_dish);
				cout << "\nSuccess - - - > ";
				cout << new_dish->GetName() << " successfully added to the Menu" << endl;
			}
			else if (option == 3) {
				//Delete Ingredient
				for (size_t i = 0; i < dish_count; i++)
				{
					dishes[i]->PrintRecipe();
				}

				int dish_id = 0;
				cout << "Choose the dish type for which you would like to delete ingredient (BY ID) : ";
				cin >> dish_id;

				int ing_id = 0;
				cout << "Enter Ingredient (BY ID): ";
				cin >> ing_id;

				auto dish = GetDishById(dish_id);

				dish->DeleteIngredient(ing_id);

				cout << "\nSuccess - - - > ";
				cout << "Ingredient with ID " << ing_id << " successfully deleted from ";
				mysetcolor(4, 0);
				cout << dish->GetName();
				mysetcolor(7, 0);
				cout << "  recipe !!!" << endl;
			}

			else if (option == 4) {
				//Delete Dish

				ShowDishes();

				int id = 0;
				cout << "Enter the dish ID: ";
				cin >> id;

				DeleteDishByID(id);
				cout << "\nSuccess - - - > ";
				cout << "Dish with ID " << id << " successfully deleted from Menu" << endl;;
			}


		}

		else if (select == 2) {
			CustomerMenu();
			int select = 0;
			cout << "Enter the option: ";
			cin >> select;
			system("cls");
			if (select == 1) {
				//Show Food Menu to Customer
				ShowDishes();
			}
			else if (select == 2) {
				ShowDishes();

				int id = 0;
				cout << "Enter Id: ";
				cin >> id;

				for (size_t i = 0; i < dish_count; i++)
				{
					if (dishes[i]->GetId() == id) {
						dishes[i]->PrintRecipe();
						break;
					}
				}
			}

			else if (select == 3) {
				//Order Food
				ShowDishes();

				int id = 0;
				cout << "Enter ID: ";
				cin >> id;

				auto dish = GetDishById(id);

				ShowCookingDevices();
				int number = 0;
				cout << "Select Cooking Method" << endl;
				cin >> number;

				if (number == 1) {
					cout << " O V E N " << endl;
					CookingDevice* oven = new Oven(dish, 0, 20);
					FoodCookingProcess(oven);
				}
				else if (number == 2) {
					cout << "\nB R A Z Z I E R " << endl;
					CookingDevice* brazzier = new Brazzier(dish, 0, 15);
					FoodCookingProcess(brazzier);
				}
				else if (number == 3) {
					cout << " P O T " << endl;
					CookingDevice* pot = new Pot(dish, 0, 18);
					FoodCookingProcess(pot);
				}
				else {
					cout << "Invalid Input !!!" << endl;
				}

				cout << "\nPayment: " << dish->GetPrice() << " AZN" << endl;
				const string date = __DATE__;
				cout << "Date: " << date << endl;
			}

		}


	}

}
