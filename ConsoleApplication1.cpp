#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Burger
{
private:
	string bun;
	int countBun = 0;
	string patty;
	int countPatty = 0;
	string cheese;
	int countCheese = 0;
	string veggies;
	int countVeggies = 0;
	string sauce;
	int countSauce = 0;
	string drink;
	int countDrink = 0;
public:
	void setBun(const string& bun)
	{
		countBun++;
		this->bun = bun;
	}
	void setPatty(const string& patty)
	{
		countPatty++;
		this->patty = patty;
	}
	void setCheese(const string& cheese)
	{
		countCheese++;
		this->cheese = cheese;
	}
	void setVeggies(const string& veggies)
	{
		countVeggies++;
		this->veggies = veggies;
	}
	void setSauce(const string& sauce)
	{
		countSauce++;
		this->sauce = sauce;
	}
	void setDrink(const string& drink)
	{
		countDrink++;
		this->drink = drink;
	}

	void showOrder() const
	{
		cout << "Состав вашего заказа: " << endl;
		cout << "\t- Булка: x" << countBun << " " << bun << endl;
		cout << "\t- Котлета: x" << countPatty << " " << patty << endl;
		cout << "\t- Сыр: x" << countCheese << " " << cheese << endl;
		cout << "\t- Овощи: x" << countVeggies << " " << veggies << endl;
		cout << "\t- Соус: x" << countSauce << " " << sauce << endl;
		cout << "\t- Напиток: x" << countDrink << " " << drink << endl;
	}
};

class burgerBuilder     //Builder удобен за гибкость, т.к. не нужно создавать по несколько конструкторов для каждой комбинации, его легче читать и тяжелее путать порядок параметров
{
protected:
	Burger* burger = nullptr;
public:
	virtual ~burgerBuilder() {}
	void createBurger() { if (burger == nullptr) burger = new Burger(); }
	Burger* getBurger() { return burger; }

	virtual void buildBun() = 0;
	virtual void buildPatty() = 0;
	virtual void buildCheese() = 0;
	virtual void buildVeggies() = 0;
	virtual void buildSauce() = 0;
	virtual void buildDrink() = 0;
};

class classicBurger : public burgerBuilder
{
public:
	void buildBun() override { burger->setBun("Классическая кунжутная"); }
	void buildPatty() override { burger->setPatty("Говяжья котлета"); }
	void buildCheese() override { burger->setCheese("Чеддер"); }
	void buildVeggies() override { burger->setVeggies("Рукола, Лук, Помидор"); }
	void buildSauce() override { burger->setSauce("Кетчуп, Майонез, Острый перец, Пикули"); }
	void buildDrink() override { burger->setDrink("Кола классическая"); }
};

class veggieBurger : public burgerBuilder
{
public:
	void buildBun() override { burger->setBun("Цельнозерновая булка"); }
	void buildPatty() override { burger->setPatty("Котлета из сладкого картофеля"); }
	void buildCheese() override { burger->setCheese("Веганский сыр"); }
	void buildVeggies() override { burger->setVeggies("Помидоры, Лук, Рукола"); }
	void buildSauce() override { burger->setSauce("Веганский майонез, Кетчуп, Дижонская горчица, Пикули, Паприка и Сухой Лук/Чеснок"); }
	void buildDrink() override { burger->setDrink("Зеленый чай"); }
};

class spicyBurger : public burgerBuilder
{
public:
	void buildBun() override { burger->setBun("Булка без кунжута"); }
	void buildPatty() override { burger->setPatty("Котлета из креветок"); }
	void buildCheese() override { burger->setCheese("Чеддер"); }
	void buildVeggies() override { burger->setVeggies("Лук, Салат"); }
	void buildSauce() override { burger->setSauce("Острый соус 1000 островов"); }
	void buildDrink() override { burger->setDrink("Острый лимонад"); }
};


class Cashier
{
private:
	burgerBuilder* builder;
	bool extraVeggies;
public:
	void setBurger(burgerBuilder* builder) { this->builder = builder; }
	Burger* assemble(bool extraVeggies)
	{
		builder->createBurger();
		builder->buildBun();
		builder->buildPatty();
		builder->buildCheese();
		builder->buildVeggies();
		if (extraVeggies = true)
		{
			builder->buildVeggies();
		}
		builder->buildSauce();
		builder->buildDrink();
		return builder->getBurger();
	}
};

int main()
{
	setlocale(0, "");

	Cashier cashier;

	classicBurger classicBurger;
	cashier.setBurger(&classicBurger);
	Burger* classicBuilder = cashier.assemble(false);
	classicBuilder->showOrder();

	veggieBurger veganBurger;
	cashier.setBurger(&veganBurger);
	Burger* veganBuilder = cashier.assemble(true);
	veganBuilder->showOrder();

	spicyBurger spicyBurger;
	cashier.setBurger(&spicyBurger);
	Burger* spiceBuilder = cashier.assemble(true);
	spiceBuilder->showOrder();

	delete classicBuilder, veganBuilder, spiceBuilder;
}