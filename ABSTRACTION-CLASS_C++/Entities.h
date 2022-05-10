#pragma once
#include<iostream>
#include<assert.h>
#include<Windows.h>
using namespace std;

void mysetcolor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

class Ingredient {
	string name;
	double fats;
	double protein;
	double carbohydrates;
	int kcal;
	int id;
public:
	static int ing_id;
	Ingredient() :name(" "), fats(0), protein(0), carbohydrates(0), kcal(0) {}

	Ingredient(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal)
	{
		SetId(++ing_id);
		SetName(name);
		SetFats(fats);
		SetProtein(protein);
		SetCarbohydrates(carbohydrates);
		SetKcal(kcal);
	}

#pragma region IngredientGetters
	string GetName()const {
		return name;
	}

	double GetFats()const {
		return fats;
	}

	double GetProtein() {
		return protein;
	}

	double GetCarbohydrates()const {
		return carbohydrates;
	}

	int GetKcal()const {
		return kcal;
	}

	int GetId()const {
		return id;
	}
#pragma endregion

#pragma region IngredientSetters

	void SetName(const string& name) {
		assert(name.length() >= 2 && "Ingredient name should include more than 2 letters");
		this->name = name;
	}

	void SetFats(const double& fats) {
		assert(fats >= 0 && "Fat Value cannot be less than 0 !!!");
		this->fats = fats;
	}

	void SetProtein(const double& protein) {
		assert(protein >= 0 && "Protein Value cannot be less than 0 !!!");
		this->protein = protein;
	}

	void SetCarbohydrates(const double& carbohydrates) {
		assert(carbohydrates >= 0 && "Carbohydrates Value cannot be less than 0 !!!");
		this->carbohydrates = carbohydrates;
	}

	void SetKcal(const int& kcal) {
		assert(kcal >= 0 && "Kcal Value cannot be less than 0 !!!");
		this->kcal = kcal;
	}

	void SetId(const int& id) {
		this->id = id;
	}


#pragma endregion

	virtual ~Ingredient() = 0
	{

	}
};

int Ingredient::ing_id = 0;

class Mushroom :public Ingredient {
public:
	Mushroom(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal) :
		Ingredient(name, fats, protein, carbohydrates, kcal) {}


};

class Meat :public Ingredient {
public:
	Meat(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal) :
		Ingredient(name, fats, protein, carbohydrates, kcal)
	{

	}

};


class Spices :public Ingredient {
public:
	Spices(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal) :
		Ingredient(name, fats, protein, carbohydrates, kcal) {}
};


class Cheese :public Ingredient {
public:
	Cheese(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal) :
		Ingredient(name, fats, protein, carbohydrates, kcal)
	{

	}
};

class Rice :public Ingredient {
public:
	Rice(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal) :
		Ingredient(name, fats, protein, carbohydrates, kcal)
	{

	}
};


class Tomatoes :public Ingredient {
public:
	Tomatoes(const string& name, const double& fats, const double& protein,
		const double& carbohydrates, const int& kcal) :
		Ingredient(name, fats, protein, carbohydrates, kcal)
	{

	}
};


struct RecipeItem {
	Ingredient* ingredient;// 2 dene ingredient

	int amount = 0;// neche dene
};


//Yemek DISH

class Dish {
	RecipeItem** items;
	int count;
	string name;
	double price;
	int id;
	int GetIngredientIndexById(int ing_id)const {
		for (size_t i = 0; i < count; i++)
		{
			if (items[i]->ingredient->GetId() == ing_id) {
				return i;
			}
		}
		return -1;
	}
public:
	static int dish_id;
	Dish(RecipeItem** items, const int& count, const string& name, const double& price)
	{
		SetId(dish_id++);
		this->price = price;
		this->items = items;
		this->count = count;
		this->name = name;
	}


	void AddIngredient(RecipeItem* item) {
		auto newitems = new RecipeItem * [count + 1]{};

		for (size_t i = 0; i < count; i++)
		{
			newitems[i] = items[i];
		}

		newitems[count] = item;
		items = newitems;
		newitems = nullptr;
		count++;
	}

	void DeleteIngredient(int id) {
		auto newitems = new RecipeItem * [count - 1]{};
		auto index = GetIngredientIndexById(id);
		for (size_t i = 0; i < index; i++)
		{
			newitems[i] = items[i];
		}

		for (size_t i = index, i2 = index + 1; i < count - 1; i++, i2++)
		{
			newitems[i] = items[i2];
		}

		items = newitems;
		newitems = nullptr;
		count--;
	}

	string GetName()const {
		return name;
	}

	int GetCount()const {
		return count;
	}

	double GetPrice()const {
		return price;
	}

	int GetId() {
		return id;
	}

	RecipeItem** GetItems()const {
		return items;
	}

	void SetId(const int& id) {
		this->id = id;
	}
	virtual void Taste() {
		cout << "I do not know what is this ? " << endl;
	}

	virtual void PrintRecipe() {
		double sum_fat = 0;
		double sum_protein = 0;
		double sum_carbohydrate = 0;
		int sum_kcal = 0;
		double fats = 0;
		double proteins = 0;
		double carbohydrates = 0;
		int kcals = 0;
		mysetcolor(15, 0);
		cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		cout << "M E A L  N A M E : ";
		mysetcolor(4, 0);
		cout << GetName() << endl;;
		mysetcolor(15, 0);
		cout << "\nM E A L   I D : " << GetId() << endl;
		mysetcolor(15, 0);
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		mysetcolor(7, 0);
		for (size_t i = 0; i < GetCount(); i++)
		{
			mysetcolor(6, 0);
			cout << "I n g r e d i e n t   n u m b e r  " << i + 1 << endl;;
			mysetcolor(7, 0);
			cout << "\nIngredient ID: " << GetItems()[i]->ingredient->GetId() << endl;
			cout << "Name: " << GetItems()[i]->ingredient->GetName() << " - " << GetItems()[i]->amount << endl;
			cout << "Ingredient Fat: " << GetItems()[i]->ingredient->GetFats() << endl;
			cout << "Ingredient Protein: " << GetItems()[i]->ingredient->GetProtein() << endl;
			cout << "Ingredient Carbohydrate: " << GetItems()[i]->ingredient->GetCarbohydrates() << endl;
			cout << "Ingredient Kcal: " << GetItems()[i]->ingredient->GetKcal() << endl;
			fats = GetItems()[i]->amount * GetItems()[i]->ingredient->GetFats();
			proteins = GetItems()[i]->amount * GetItems()[i]->ingredient->GetProtein();
			carbohydrates = GetItems()[i]->amount * GetItems()[i]->ingredient->GetCarbohydrates();
			kcals = GetItems()[i]->amount * GetItems()[i]->ingredient->GetKcal();
			sum_kcal += kcals;
			sum_fat += fats;
			sum_carbohydrate += carbohydrates;
			sum_protein += proteins;
			cout << "======================================" << endl;
		}cout << endl;
		mysetcolor(11, 0);
		cout << "Total Protein : " << sum_protein << endl;
		cout << "Total Fat : " << sum_fat << endl;
		cout << "Total Carbohydrate : " << sum_carbohydrate << endl;
		cout << "Total Kcal : " << sum_kcal << endl;
		mysetcolor(7, 0);
	};


	virtual ~Dish() = 0 { //pure vitual destructor

	}

};

int Dish::dish_id = 1;

class Pizza :public Dish {

public:
	Pizza() = delete;

	Pizza(RecipeItem** items, const int& count, const string& name, const double& price) :
		Dish(items, count, name, price) {}

	void Taste()override {
		cout << "Taste : Very Good" << endl;
	}

	void PrintRecipe()override {
		Dish::PrintRecipe();
	}

};


class Kabab :public Dish {
public:
	Kabab() = delete;

	Kabab(RecipeItem** items, const int& count, const string& name, const double& price) :
		Dish(items, count, name, price) {}

	void Taste()override {
		cout << "Taste : Perfect, Soft and Delicious" << endl;
	}

	void PrintRecipe()override {
		Dish::PrintRecipe();
	}
};



class Dolma :public Dish {
public:
	Dolma() = delete;

	Dolma(RecipeItem** items, const int& count, const string& name, const double& price) :
		Dish(items, count, name, price) {}
	void Taste()override {
		cout << "Taste : Nice, Very Tasty" << endl;
	}

	void PrintRecipe()override {
		Dish::PrintRecipe();
	}
};


class CookingDevice {
protected:
	Dish* dish;
	bool hasCooked;
	int second;
public:
	CookingDevice(Dish* dish, const bool& hasCooked, const int& second) :dish(dish), hasCooked(hasCooked),
		second(second) {}
	virtual void Cook() = 0 {
	};

	virtual int GetSecond()const = 0;

	virtual Dish* GetDish()const = 0;

	virtual bool GetHasCooked() const = 0;

	virtual void SetHasCooked(const bool& hasCooked) = 0;

};


class Oven :public CookingDevice {
public:
	Oven(Dish* dish, const bool& hasCooked, const int& second) :CookingDevice(dish, hasCooked, second) {}


	// Inherited via CookingDevice
	virtual void Cook() override {
		if (hasCooked == 1) {
			cout << dish->GetName() << " in the  O V E N  is already cooked ---> READY !!! " << endl;
		}
		else {
			cout << dish->GetName() << " in the  O V E N  is not cooked yet ---> NOT READY !!! " << endl;
		}
	};
	int GetSecond()const override {
		return second;
	}

	Dish* GetDish()const override {
		return dish;
	}

	bool GetHasCooked() const override {
		return hasCooked;
	}

	void SetHasCooked(const bool& hasCooked)override {
		this->hasCooked = hasCooked;
	}
};


class Brazzier :public CookingDevice {
public:
	Brazzier(Dish* dish, const bool& hasCooked, const int& second) :CookingDevice(dish, hasCooked, second) {}


	// Inherited via CookingDevice
	virtual void Cook() override {
		if (hasCooked == 1) {
			cout << dish->GetName() << " in the   B R A Z Z I E R  is already cooked ---> READY !!!" << endl;
		}
		else
			cout << dish->GetName() << " in the  B R A Z Z I E R  is not cooked yet ---> NOT READY !!! " << endl;
	};

	int GetSecond()const override {
		return second;
	}

	Dish* GetDish()const override {
		return dish;
	}


	bool GetHasCooked()const override {
		return hasCooked;
	}
	void SetHasCooked(const bool& hasCooked)override {
		this->hasCooked = hasCooked;
	}
};



class Pot :public CookingDevice {
public:
	Pot(Dish* dish, const bool& hasCooked, const int& second) :CookingDevice(dish, hasCooked, second) {}

	// Inherited via CookingDevice
	virtual void Cook() override {
		if (hasCooked == 1) {
			cout << dish->GetName() << " in the  P O T  is already cooked ---> READY !!!" << endl;
		}
		cout << dish->GetName() << " in the  P O T  is not cooked yet ---> NOT READY !!! " << endl;
	};

	int GetSecond()const override {
		return second;
	}

	Dish* GetDish()const override {
		return dish;
	}


	bool GetHasCooked() const override {
		return hasCooked;
	}

	void SetHasCooked(const bool& hasCooked)override {
		this->hasCooked = hasCooked;
	}

};

#pragma once
