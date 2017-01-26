#include "Polygon.h"


Polygon::Polygon()
{

}

Polygon::Polygon(vector<Vertex> verticesList)
{
	for (unsigned int i = 0; i < verticesList.size(); ++i)
	{
		addVertex(verticesList[i]);
	}
}

Polygon::Polygon(const Polygon& otherPolygon)
{
    for(unsigned int i = 0; i < otherPolygon.verticesList.size(); ++i)
        addVertex(otherPolygon.verticesList[i]);

}

Polygon& Polygon::operator=(const Polygon& otherPolygon)
{
    for(unsigned int i = 0; i < otherPolygon.verticesList.size(); ++i)
        addVertex(otherPolygon.verticesList[i]);
    return *this;
}

bool Polygon::operator==(const Polygon& otherPolygon) const
{
    bool isEqual;
    if(verticesList.size() != otherPolygon.verticesList.size())
        return false;
    for(unsigned int i = 0; i < verticesList.size(); ++i)
    {
        isEqual = false;
        for(unsigned int j = 0; j < verticesList.size(); ++j)
            if(verticesList[i] == otherPolygon.verticesList[j])
            {
                isEqual = true;
                j = verticesList.size();
            }
        if(!isEqual)
            return false;
    }
    return true;
}

void Polygon::updateMinMax(const Vertex& v)
{
	double vX = v.getX();
	double vY = v.getY();

	if (vX < xMin) 
		xMin = vX;
	else if (vX > xMax) 
		xMax = vX;

	if (vY < yMin)
		yMin = vY;
	else if (vY > yMax)
		yMax = vY;
}

double Polygon::getXMin()
{
	return xMin;
}

double Polygon::getYMin()
{
	return yMin;
}

double Polygon::getXMax()
{
	return xMax;
}

double Polygon::getYMax()
{
	return yMax;
}
void Polygon::addVertex(const Vertex& v)
{
    verticesList.push_back(v);
	updateMinMax(v);
}

bool Polygon::isInside(const Vertex& p)
{
	double pX = p.getX();
	double pY = p.getY();
	if (pX >= xMin && pX <= xMax && pY >= yMin && pY <= yMax)
	{
		Vertex outPoint(xMax + 3, yMax + 7);
		LineSegment halfLine(p, outPoint);

		//cout << p.getX() << " " << p.getY() << endl;
		int intersectionCount = 0;
		int next;
		for (int i = 0; i < verticesList.size(); ++i)
		{
			next = (i + 1) % verticesList.size();
			LineSegment line(verticesList[i], verticesList[next]);
			
			if (line.isOnSegment(p))
				return true;

			if (line.doIntersect(halfLine))
			{
				pair<bool, Vertex> intersectionPoint = line.getIntersectionPoint(halfLine);

				if (intersectionPoint.first)
					++intersectionCount;
				// if vertex
				if (intersectionPoint.second == line.getV1() || intersectionPoint.second == line.getV2())
					++i;
			}
		}
		return intersectionCount % 2 == 0 ? false : true;
	}
	return false;
}

vector<Vertex> Polygon::getVerticesList() const
{
    return verticesList;
}

void Polygon::printPolygon() const
{
    for(unsigned int i = 0; i < verticesList.size(); ++i)
        cout << verticesList[i].toString() << " ";
    cout << endl;
}

string Polygon::toString() const
{
	stringstream polygonString;
	for (int i = 0; i < verticesList.size(); i++)
		polygonString << verticesList[i].toString() << " ";
	return polygonString.str();
}

Polygon::~Polygon()
{
}

