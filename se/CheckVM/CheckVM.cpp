#include <Core/Core.h>
#include <SysInfo/SysInfo.h>

using namespace Upp;

double CircularLength(double d, double R)
{
	double fi = 2;
	DDUMP(fi);
	return R * asin(d / R / 2);
}

bool GetWMIInfo(String system, Vector <String> &data, Array <Value> *ret[], String nameSpace = "root\\cimv2");

bool GetWMIInfo(String system, String data, Value &res, String nameSpace = "root\\cimv2");
/*
		"ChassisSKUNumber",
		"Manufacturer",
		"Model",
		"SystemFamily",
		"SystemSKUNumber",
		"SystemType",
*/

/*
			"Manufacturer",
			"Product",
*/
/*
		"Manufacturer",
		"Name",
		"SerialNumber",
*/


bool IsVirtualMachine() {
	auto Test = [&] (const char *system, const char *types) -> bool {
		Vector<String> id = Split(types, ';');
		Buffer<Array<Value>> ret(id.GetCount());
		Buffer<Array<Value> *> retptr(id.GetCount());
		for(int i = 0; i < id.GetCount(); i++)
			retptr[i] = &ret[i];
		GetWMIInfo(system, id, retptr);
		for(int i = 0; i < id.GetCount(); i++)
			for(const String& s : ret[i]) {
				String h = ToLower(s);
				if(h.Find("vmware") >= 0 || h.Find("440BX") >= 0 || h.Find("virtual") >= 0 || h.Find("innotek") >= 0)
					return true;
			}
		return false;
	};
	if(Test("Win32_ComputerSystem", "ChassisSKUNumber;Manufacturer;Model;SystemFamily;SystemSKUNumber;SystemType"))
		return true;
	if(Test("Win32_BaseBoard", "Manufacturer;Product"))
		return true;
	if(Test("Win32_BIOS", "Manufacturer;Name;SerialNumber"))
		return true;
	return false;
}

CONSOLE_APP_MAIN
{
}
