#include "flowcollection.h"



//#include "gdal_priv.h"


flowcollection::flowcollection(string filename, bool with_headers, string delimeter)
{
	string templine;
	ifstream ifs(filename);
	vector<flowdata> tempflows;
	while (getline(ifs, templine))
	{
		if (with_headers)
		{
			with_headers = 0;
			continue;
		}
		try {
			//vector<string> strVec=auxiliary_func::split(templine,",");
			vector<string> strVec = auxiliary_func::split(templine, delimeter);
			if (strVec.size() != 3)
			{
				delimeter = "\t";
				strVec = auxiliary_func::split(templine, delimeter);
			}
			if (strVec.size() != 3)
			{
				delimeter = " ";
				strVec = auxiliary_func::split(templine, delimeter);
			}
			if (strVec.size() == 3)
			{
				tempflows.push_back(flowdata(stoi(strVec[0]), stoi(strVec[1]), stod(strVec[2])));
			}
		}
		catch (...) {

		}
	}
	flows = tempflows;
}


int flowcollection::Countflowid()
{
	return layerConnection->GetFeatureCount();
}