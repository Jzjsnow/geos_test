#pragma once

#include "../geometries/flowdata.h"
#include "../auxiliary_func.h"
#include "ogrsf_frmts.h"
#include <vector>
#include <fstream>


#ifndef FLOWCOLLECTION_H
#define FLOWCOLLECTION_H

using namespace std;
class flowcollection
{
public:
    vector<flowdata> flows;
    OGRLayer * layerConnection;

	flowcollection() {};
    flowcollection(vector<flowdata> _flows) { flows = _flows; };
	flowcollection(string filename, bool with_headers, string delimeter);//new added
    void Addflow(flowdata newflow) 
	{
		flows.push_back(newflow);
	};
	void Deleteflow(int index) {};
    flowdata Getflow(int index) 
	{
		return flows[index];
	};
    int Countflow()
	{
		return flows.size();
	};
    void setLayerConnection(OGRLayer * layer)
	{
		layerConnection = layer;
	};
	int Countflowid();//new added
};
#endif // FLOWCOLLECTION_H

