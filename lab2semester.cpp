#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define SIZE 3

// HouseholdAppliance

class HouseholdAppliance {
protected:
	bool state; // включен/ выключен
	float powerConsumption; // потребляемая мощность
	float width, height, depth, weight; // ширина, высота, глубина и вес
	string color; // цвет
public:
	HouseholdAppliance() { state = false; cin >> *this; }
	~HouseholdAppliance() {} // операций по освобождению памяти не производит, поскольку класс не содержит полей, для которых динамически выделялась память
	void turnOn(void) { state = true; }
	void switchOff(void) { state = false; }
	bool checkState(void) { return state; }
	friend istream& operator >>(istream& stream, HouseholdAppliance& object);
	friend ostream& operator <<(ostream& stream, HouseholdAppliance& object);
};

istream& operator >>(istream& stream, HouseholdAppliance& object) {
	cout << "Введите ширину устройства: "; stream >> object.width;
	cout << "Введите высоту устройства: "; stream >> object.height;
	cout << "Введите глубину устройства: "; stream >> object.depth;
	cout << "Введите вес устройства: "; stream >> object.weight;
	cout << "Введите потребляемую мощность устройства: "; stream >> object.powerConsumption;
	cout << "Введите цвет устройства: "; stream >> object.color;
	return stream;
}

ostream& operator <<(ostream& stream, HouseholdAppliance& object) {
	stream << "Ширина/Высота/Глубина/Вес: " << object.width << "/" << object.height << "/" << object.depth << "/" << object.weight << "\n" <<
		"Потребляемая мощность: " << object.powerConsumption << "\n" <<
		"Цвет устройства: " << object.color << "\n" <<
		"Состояние: " << (object.state ? "включен" : "выключен") << "\n";
	return stream;
}

// ComputingDevice

class ComputingDevice {
protected:
	string processorModel; // модель процессора
	unsigned int memory; // объем памяти
	float processorFrequency; // частота процессора
public:
	ComputingDevice() { cin >> *this; }
	~ComputingDevice() {} // операций по освобождению памяти не производит, поскольку класс не содержит полей, для которых динамически выделялась память
	void changeFrequency(float processorFrequency) { this->processorFrequency = processorFrequency; }
	string getCPU(void) { return processorModel; }
	friend istream& operator >>(istream& stream, ComputingDevice& object);
	friend ostream& operator <<(ostream& stream, ComputingDevice& object);
};

istream& operator >>(istream& stream, ComputingDevice& object) {
	cout << "Введите модель процессора: "; stream >> object.processorModel;
	cout << "Введите частоту процессора: "; stream >> object.processorFrequency;
	cout << "Введите объем памяти устройства: "; stream >> object.memory;
	return stream;
}

ostream& operator <<(ostream& stream, ComputingDevice& object) {
	stream << "Модель процессора: " << object.processorModel << "\n" <<
		"Частота процессора: " << object.processorFrequency << "\n" <<
		"Объем памяти устройства: " << object.memory << "\n";
	return stream;
}

// Laptop

class Laptop : public ComputingDevice, public HouseholdAppliance {
private:
	static int count; // статическая переменная, определяющая количество созданных объектов класса Laptop
	string laptopModel, operatingSystem; // модель ноутбука и ОС
	unsigned int batteryCapacity; // емкость аккумулятора
public:
	Laptop() : ComputingDevice(), HouseholdAppliance() { cin >> *this; ++count; cout << "\n\n"; }
	~Laptop() { --count; } // операций по освобождению памяти не производит, поскольку класс не содержит полей, для которых динамически выделялась память
	string getLaptopModel(void) { return laptopModel; }
	string getOS(void) { return operatingSystem; }
	friend istream& operator >>(istream& stream, Laptop& object);
	friend ostream& operator <<(ostream& stream, Laptop& object);
	static int getCount(void) { return count; }
};

int Laptop::count;

istream& operator >>(istream& stream, Laptop& object) {
	cout << "Введите модель ноутбука: "; stream >> object.laptopModel;
	cout << "Введите название операционной системы: "; stream >> object.operatingSystem;
	cout << "Введите емкость аккумулятора: "; stream >> object.batteryCapacity;
	return stream;
}

ostream& operator <<(ostream& stream, Laptop& object) {
	stream << "Модель ноутбука: " << object.laptopModel << "\n" <<
		"Операционная система: " << object.operatingSystem << "\n" <<
		"Емкость аккумулятора: " << object.batteryCapacity << "\n";
	stream << (ComputingDevice&)object;
	stream << (HouseholdAppliance&)object;
	stream << "\n\n";
	return stream;
}

// main

int main(void) {
	setlocale(LC_ALL, "Russian");
	vector<Laptop*> computers;
	for (unsigned int i = 0; i < SIZE; ++i) computers.push_back(new Laptop());
	cout << "Число экземпляров класса Laptop: " << Laptop::getCount() << "\n\n"; // число объектов класса Laptop
	computers[0]->turnOn(); // работа метода из HouseholdAppliance
	computers[0]->changeFrequency(99999999.9f); // работа метода из ComputingDevice
	for (unsigned int i = 0; i < SIZE; ++i) cout << *(computers[i]);
	for (unsigned int i = 0; i < SIZE; ++i) delete computers[i];
	cout << "Число экземпляров класса Laptop: " << Laptop::getCount() << "\n\n"; // число объектов класса Laptop
	system("pause");
	return 0;
}