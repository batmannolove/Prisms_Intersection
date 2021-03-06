/*
	Michał Piotrak
	numer albumu: 269336
	Przecięcie graniastosłupów
*/

#include "Prism.h"

Prism::Prism()
{}

Prism::Prism(Polygon base)
{
	this->base = base;
}

Prism::Prism(int id, Polygon base)
{
	this->id = id;
	this->base = base;
}

Prism::Prism(int id, Polygon base, pair<double,double> heightRange)
{
	this->id = id;
	this->base = base;
	heightRanges.insert(make_pair(id, heightRange));
}

Prism::Prism(const Prism& otherPrism)
{
	this->id = otherPrism.id;
	this->base = otherPrism.base;
	this->heightRanges = otherPrism.heightRanges;
}

Prism::Prism(int id, Polygon polygon, map<int, pair<double, double>> heightRanges)
{
	this->id = id;
	this->base = polygon;
	this->heightRanges = heightRanges;
}


Prism& Prism::operator=(const Prism& otherPrism)
{
    id = otherPrism.id;
    base = otherPrism.base;
    heightRanges = otherPrism.heightRanges;
    return *this;
}

bool Prism::operator==(const Prism& otherPrism) const
{
	if (base == otherPrism.base && heightRanges == otherPrism.heightRanges && id == otherPrism.id)
	{	
		return true;
	}
    else
        return false;
}

void Prism::addHeightRange(int id, pair<double, double> heightRange)
{
	bool isThisHeightRange = false;
	for (auto r : heightRanges)
	{
		if (r.second == heightRange && r.first == id)
		{
			isThisHeightRange = true;
			break;
		}
	}
	if (!isThisHeightRange)
		heightRanges.insert(make_pair(id, heightRange));
}

void Prism::addHeightRanges(const map<int, pair<double, double>>& ranges)
{
	for (auto r : ranges) 
	{
		addHeightRange(r.first, r.second);
	}
}


int Prism::getId() const
{
    return id;
}

Polygon Prism::getBase() const
{
    return base;
}

map<int, pair<double, double>> Prism::getHeightRanges() const
{
    return heightRanges;
}

void Prism::printPrism() const
{
	for (auto i : heightRanges) 
	{
		cout << i.first <<  " " << i.second.first << " " << i.second.second << endl;
	}
	cout << "Base: ";
    base.printPolygon();
	cout << endl;
}

string Prism::toString() const
{
	stringstream prismsString;
	for (auto i : heightRanges)
	{
		prismsString << i.first << " " << i.second.first << " " << i.second.second << endl;
	}
	prismsString << "Base: " << base.toString() << endl << endl;

	return prismsString.str();
}

Prism::~Prism()
{

}
