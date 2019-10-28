#include "odcollection.h"
#include "../auxiliary_func.h"
ODcollection::ODcollection()
{

}

ODcollection::ODcollection(vector<ODdata> _ODs)
{
    ODs=_ODs;
}

ODcollection::ODcollection(string filename)
{
    string templine;
    ifstream ifs(filename);
    vector<ODdata> tempOD;
    while (getline(ifs,templine))
    {
        try {
            vector<string> strVec=auxiliary_func::split(templine,",");
            tempOD.push_back(ODdata(OGRPoint(stod(strVec[0]),stod(strVec[1]),stod(strVec[2])),\
                    OGRPoint(stod(strVec[3]),stod(strVec[4]),stod(strVec[5]))));
        } catch (...) {

        }
    }
    ODs=tempOD;
}

int ODcollection::CountOD()
{
    return ODs.size();
}

ODdata ODcollection::GetOD(int index)
{
    return ODs[index];
}

void ODcollection::AddOD(ODdata newOD)
{
    ODs.push_back(newOD);
}
