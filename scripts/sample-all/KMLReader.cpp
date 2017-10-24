
#include "KMLReader.h"
#include <iomanip>

GPS_Pack	readKML(char* kml)
{
	std::string string_gps = getStringFromKML(kml);

	GPS_Pack gps_points = parseGPSFromString(string_gps);
	
	//std::cout << string_gps << std::endl;

	return gps_points;
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

GPS_Pack parseGPSFromString(std::string coordinates)
{
	std::string stdHead = "\n\t\t\t\t\t\t";
	std::string stdEnd = "\n\t\t\t\t\t";
	std::string str_TrimLeftSpace = coordinates.substr(stdHead.size(), coordinates.size() - stdHead.size() - stdEnd.size());
	std::vector<std::string> lines;
	SplitString( str_TrimLeftSpace, lines, " ");

	GPS_Pack gps_points;

	for each (std::string line in lines)
	{
		std::vector<std::string> elements;
		SplitString(line, elements, ",");

		std::vector<double> gps_point;
		for each (std::string element in elements)
		{
			double cord = atof( element.c_str() );
			gps_point.push_back(cord);
		}

		gps_points.push_back( gps_point );
	}

	return gps_points;
}

std::string getStringFromKML(char* kml)
{
	pugi::xml_document doc;

	doc.load_file(kml);

	pugi::xml_node node = doc.child("kml").child("Document").
		child("Placemark").child("Polygon").child("outerBoundaryIs").
		child("LinearRing").child("coordinates");

	std::string string_gps = node.first_child().value();

	return string_gps;
}

void printGPS_Pack(GPS_Pack& pack)
{
	for each (std::vector<double> gps_point in pack)
		std::cout << "gps list:" << std::endl
		<< std::setprecision(16) 
		<< gps_point[0] << ", " 
		<< gps_point[1] << ", " 
		<< gps_point[2] << std::endl;

}
