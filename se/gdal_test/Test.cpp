#include <Core/Core.h>

#include <plugin/gdal/ogr/ogr_spatialref.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	OGRSpatialReference oSRS;
	
	String h = LoadFile("D:/aws.data/Ireland/OSNI_Open_Data_50K_Admin_Boundaries_–_Counties.prj");
	
	StringBuffer b = h;
	char *x = ~b;
	DDUMP(oSRS.importFromWkt(&x));
	
	DDUMP(x);
	DDUMP(oSRS.exportToProj4(&x));
	
	DDUMP(oSRS.importFromEPSG(29900));
	oSRS.exportToProj4(&x);
	DDUMP(x);

}

