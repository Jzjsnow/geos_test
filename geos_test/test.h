#pragma once
#include<iostream>
#include<string.h>
#include <vector>
#include <cstdlib> // exit()
#include<list>

#include"collection/flowcollection.h"
#include"method/CalculateBtwId.h"
#include "collection/flowgraph.h"
#include"method/DistanceDecayPara.h"
using namespace std;



void do_all();
string str(bool flag);
int proj_test();
void ogrtest();
int test_getdistance(list<OGRLayer*> mylayers);
void test_igraph();
void test_od(list<OGRLayer*> mylayers);

