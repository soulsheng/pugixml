
#pragma once

#include <iostream>
#include <vector>
#include "pugixml.hpp"

typedef std::vector<std::vector<double>> GPS_Pack;

GPS_Pack	readKML(char* kml);

GPS_Pack	parseGPSFromString(std::string coordinates);
std::string	getStringFromKML(char* kml);
void		printGPS_Pack(GPS_Pack& pack);

