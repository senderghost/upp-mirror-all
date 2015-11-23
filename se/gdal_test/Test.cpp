#include <Core/Core.h>

#include <gdal\gcore\gdal_priv.h>
#include <gdal\port\cpl_conv.h>

CONSOLE_APP_MAIN
{
	GDALAllRegister();
	GDALDataset  *poDataset = (GDALDataset *) GDALOpen("something", GA_ReadOnly );
}

