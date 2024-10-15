#include<iostream>
#include<string>
using namespace std;

class Product {
	int id;
	string name;
	string description;
	float price;
	int discount;

public:
	static int static_id;
	Product(string name, string description, float price, int discount) {
		static_id++;
		this->id = static_id;
		this->name = name;
		this->description = description;
		this->price = price;
		this->discount = discount;
	}

	int GetId()const {
		return id;
	}

	void SetID(int id)
	{
		this->id = id;
	}

	string GetName()const {
		return name;
	}

	void SetName(string name)
	{
		if (name.length() < 3)
		{
			cout << "Wrong name!!!";
		}
		else
		{
			this->name = name;
		}
	}

	string GetDescription()const {
		return description;
	}

	void SetDescription(string description)
	{
		if (description.length() < 10)
		{
			cout << "Wrong description!!!";
		}
		else
		{
			this->description = description;
		}
	}

	float GetPrice()const {
		return price;
	}

	void SetPrice(float price)
	{
		if (price < 0)
		{
			cout << "Wrong price!!!";
		}
		else
		{
			this->price = price;
		}
	}

	int GetDiscount()const {
		return discount;
	}

	void SetDiscount(int discount)
	{
		if (discount < 10 && discount > 100)
		{
			cout << "Wrong discount!!!";
		}
		else
		{
			this->discount = discount;
		}
	}

	void ShowProduct() {
		cout << "No:" << this->id << "  ";
		cout << "Name: " << this->name << "  ";
		cout << "Description: " << this->description << "  ";
		cout << "Price: " << this->price << "  ";
		cout << "Discount: " << this->discount << "  ";
	}

	int GetPriceWithDiscount() {
		int new_price = this->price - ((this->price * this->discount) / 100);
		this->price = new_price;
		return new_price;
	}

};

class Stock {
	char* address;
    Product** products;
	int count;

public:
	
	Stock() {
		this->address = new char[20] {};
		this->products = new Product * [count] {};
		this->count = 0;
	}

	Stock(char* address,Product** products,int count) :Stock() {
		this->address = address;
		this->count = count;
	    this->products = new Product * [count];
		for (int i = 0; i < count; i++) 
		{
			this->products[i] = products[i]; 
		}
	}


	Stock(const Stock& object) {
		this->address = new char[20] {*object.address};
		this->count = object.count;
		this->products = new Product * [count] {};
		for (int i = 0; i < count; i++)
		{
			this->products[i] = object.products[i];
		}
	}

	Stock& operator=(const Stock& object) {
		this->address = new char[20] {*object.address};
		this->count = object.count;
		this->products = new Product * [count] {};
		for (int i = 0; i < count; i++)
		{
			this->products[i] = object.products[i];
		}
		return *this;
	}

	void ShowStock() {
		cout << "Address: " << GetAddress() << endl;
		cout << "Products: " << endl;
		for (size_t i = 0; i < count; i++)
		{
			products[i]->ShowProduct();
			cout << endl;
		}
	}

	void ChangeProductDiscount(int new_discount, int product_id) {
		bool found = false;
		for (size_t i = 0; i < count; i++)
		{
			if (products[i]->GetId() == product_id) {
				if (new_discount >= 0 && new_discount <= 100) {
					products[i]->SetDiscount(new_discount);
				}
				else {
					cout << "Wrong discount" << endl;
				}
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "Not found product " << endl;
		}

	}

	void CreateProduct() {
		string new_name;
		cout << "Enter new name: ";
		cin.ignore();
		getline(cin, new_name);
		string new_description;
		cout << "Enter new description: ";
		cin.ignore();
		getline(cin, new_description);
		float new_price;
		cout << "Enter new price: ";
		cin >> new_price;
		int new_discount;
		cout << "Enter new discount: ";
		cin >> new_discount;

		Product* new_product = new Product(new_name, new_description, new_price, new_discount);
		Product** new_products = new Product * [count + 1];
		for (size_t i = 0; i < count; i++)
		{
			new_products[i] = products[i];
		}

		new_products[count] = new_product;

		delete[]products;

		products = new_products;

		count++;
	
	}

	void SearchProduct() {
		bool result = false;
		int search_id;
		cout << "Enter id: ";
		cin >> search_id;
		for (size_t i = 0; i < count; i++)
		{
			if (products[i]->GetId() == search_id) {
				cout << endl;
				products[i]->ShowProduct();
				cout << endl;
				result = true;
				break;
			}
		}
		if (!result) {
			cout << "Not Found" << endl;
		}
	}

	void DeleteProduct() {
		int delete_id;
		cout << "Enter id: ";
		cin >> delete_id;

		bool result = false;
		int index = -1;
		for (size_t i = 0; i < count; i++)
		{
			if (products[i]->GetId() == delete_id) {
				index = i;
				result = true;
				break;
			}
		}
		if (result) {
			delete products[index];
			Product** new_products = new Product * [count - 1] {};
			int k = 0;
			for (int i = 0; i < count; i++)
			{
				if (i != index) {
					new_products[k++] = products[i];
				}
			}
			delete[] products;
			products = new_products;
			count--;

			for (int i = 0; i < count; i++)
		    { 
				products[i]->SetID(i + 1);
		    }
		}
		else {
			cout << "Not Found" << endl;
		}

	}

	char* GetAddress() const {
		return address;
	}

	void SetAddress(char* address) {
		if (strlen(address) < 4) {
			cout << "Wrong address" << endl;
		}
		else {
			this->address = address;
		}
	}

	Product** GetProducts() const {
		return products;
	}

	void SetProduct(Product** products, int count) {
		if (products==0 && count<1) {
			cout << "Wrong product" << endl;
		}
		else {
			this->products = products;
		}
	}

	int GetCount()  const {
		return count;
	}
	
	void SetCount(int count) {
		if (strlen(address) < 1) {
			cout << "Wrong count" << endl;
		}
		else {
			this->count = count;
		}
	}

	~Stock() {
		delete[] address; 

		for (int i = 0; i < count; i++) 
		{
			delete products[i];
		}
		delete[] products;
	}
};

int Product::static_id = 0;


void main() {
	int size = 2;
	Product* product1 = new Product("Product1", "Description1", 10.5f, 10);
	Product* product2 = new Product("Product2", "Description2", 20.6f, 15);


	Product** products = new Product * [size] {product1, product2};
	
	//cout << product1->GetPriceWithDiscount() << endl;

	char* address = new char[20] {"Baki"};
	Stock* stock = new Stock(address, products, size);

	//stock->ShowStock();

	//stock->CreateProduct();
	//stock->ShowStock();

	//stock->SearchProduct();
	 
	//stock->DeleteProduct();
	//stock->ShowStock();

	//stock->ChangeProductDiscount(50, 2);
	//stock->ShowStock();

}