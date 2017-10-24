
#include "KMLReader.h"

void main()
{
	GPS_Pack gps_points = readKML("area.kml");

	printGPS_Pack(gps_points);

}