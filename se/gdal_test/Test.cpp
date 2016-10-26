#include <Core/Core.h>

#include <plugin/gdal/ogr/ogr_spatialref.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	OGRSpatialReference oSRS;
	
	String h = LoadFile("D:/aws.data/SOMERC/TA_pub_rg_rp_kantonsstrasse.prj");
//	String h = LoadFile("D:/aws.data/Ireland/OSNI_Open_Data_50K_Admin_Boundaries_–_Counties.prj");
	
	StringBuffer b = h;
	char *x = ~b;
	DDUMP(oSRS.importFromWkt(&x));
	
	DDUMP(oSRS.exportToProj4(&x));
	DDUMP(x);
}

