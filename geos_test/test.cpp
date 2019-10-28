#include"test.h"



#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

//// Set to 0 to skip section
//#define GEOMETRIC_SHAPES 1
//#define RELATIONAL_OPERATORS 1
//#define COMBINATIONS 1
//#define UNARY_OPERATIONS 1
//#define LINEMERGE 1
//#define POLYGONIZE 1


int test_getdistance(list<OGRLayer*> mylayers)
{

	
	OGRLayer * current_lyr = mylayers.front();
	double dis;

	try
	{
		dis = get_poly_distance(3, 6, current_lyr);
		int64 a, b;
		get_feature_byid(3, &a, current_lyr, "attribute", "taz_id");
		get_feature_byid(6, &b, current_lyr, "attribute", "taz_id");

		cout << a
			<< "��";
		cout << b
			<< "�ľ���Ϊ��"
			<< endl << dis << " m" << endl;
		//cout << (char*)get_feature_byid(0, current_lyr, "attribute", "NAME", "string")
		//	<< "���Ϊ��"
		//	<< endl;
		//cout<< *(double*)get_feature_byid(0, current_lyr, "attribute", "Shape_Area", "double")
		//	<< endl;
		//	//ogrtest();
	}
	catch (const exception &e)
	{
		cerr << "Standard exception thrown: " << e.what() << endl;
		exit(1);
	}
	
	return 0;
}




void ogrtest()
{

	GDALAllRegister();
	GDALDataset   *poDS;
	CPLSetConfigOption("SHAPE_ENCODING", "");  //���������������
	//��ȡshp�ļ�
	poDS = (GDALDataset*)GDALOpenEx("G:/Workshop/gis_software/bou2_4p.shp", GDAL_OF_VECTOR, NULL, NULL, NULL);

	if (poDS == NULL)
	{
		printf("Open failed.\n");
		system("pause");
		return;
	}

	OGRLayer  *poLayer;
	poLayer = poDS->GetLayer(0); //��ȡ��
	OGRFeature *poFeature;

	poLayer->ResetReading();
	int i = 0;
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		if (poFeature->GetFieldAsDouble("AREA") < 1) continue; //ȥ�������С��polygon

		i = i++;
		cout << i << "  ";
		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
		int iField;
		int n = poFDefn->GetFieldCount(); //����ֶε���Ŀ��������ǰ�����ֶΣ�FID,Shape);
		for (iField = 0; iField < n; iField++)
		{
			//���ÿ���ֶε�ֵ
			cout << poFeature->GetFieldAsString(iField) << "    ";
		}
		cout << endl;
		OGRFeature::DestroyFeature(poFeature);
		poFDefn->Release();
	}

	poLayer->ResetReading();
	OGRFeature *poFeature1, *poFeature2, *poFeature3;
	poFeature1 = poLayer->GetFeature(205); //�Ĵ�ʡ
	poFeature2 = poLayer->GetFeature(0); //������ʡ
	poFeature3 = poLayer->GetFeature(66); //�ຣʡ
	OGRGeometry *p1 = poFeature1->GetGeometryRef();
	OGRGeometry *p3 = poFeature2->GetGeometryRef();
	OGRGeometry *p2 = poFeature3->GetGeometryRef();
	cout << p1->IsEmpty() << endl   //ͼ���Ƿ�Ϊ��
		<< p1->IsSimple() << endl  //�Ƿ��ǵ�������ͼ��
		<< p1->getGeometryType() << endl   //����ͼ�ε����ͣ�polygon����3
		<< p1->getGeometryName() << endl   //����ͼ�ε�����
		<< p1->getDimension() << endl     //ͼ�ε�ά��
		<< p1->getCoordinateDimension() << endl   //�����ά��
		<< p1->getSpatialReference() << endl;    //�ռ�ο�
	if (p2->Disjoint(p1))
		cout << "���ཻ" << endl;
	else
	{
		if (p2->Touches(p1))
			cout << "�Ӵ�" << endl;
		else if (p2->Overlaps(p1))
			cout << "�����ص�" << endl;
		else if (p2->Contains(p1))
			cout << "����" << endl;
		else
			cout << "unknown" << endl;
	}
	GDALClose(poDS);

}

string str(bool flag)
{
	string result = (flag == true) ? "�ཻ" : "���ཻ";
	return result;
}


int proj_test()
{
	{
		// ����һ������54�ĺ���ī����ͶӰ����ϵ
		// +proj=lcc    ͶӰ���ͣ�����ī����ͶӰ
		// +ellps=krass ������
		// +lat_1=25n +lat_2=47n    ά�ȷ�Χ(��׼γ��)
		// +lon_0=117e  ���뾭��Ϊ����117��
		// +x_0=20500000    X��(��)����ƫ����
		// +y_0=0           Y��(��)����ƫ����
		// +units=m         ��λ
		// +k=1.0           ����

		const char* beijing1954 = "+proj=lcc +ellps=krass +lat_1=25n +lat_2=47n +lon_0=117e +x_0=20500000 +y_0=0 +units=m +k=1.0";
		//�������ת����WGS84��׼ 
		//"+towgs84=22,-118,30.5,0,0,0,0"

		projPJ pj;  // ����ϵ����ָ��
		// ��ʼ������ϵ����
		if (!(pj = pj_init_plus(beijing1954))) {
			exit(-1);   // ��ʼ��ʧ�ܣ��˳�����
		}

		// ��ת��������(ͶӰ����)
			// ע������ϵ�����е�+x_0=20500000������ֵӦ��Ҳ�Ǵ��д��ŵ�
		projUV parr[4] = {
			{20634500.0,4660000.0},
			{20635000.0,4661000.0},
			{20635500.0,4659000.0},
			{20634000.0,4662000.0}
		};

		printf("DEG_TO_RAD = %f  (1��=%f����)\n", DEG_TO_RAD, DEG_TO_RAD);

		// ���ת��
		for (int i = 0; i < 4; i++)
		{
			printf("\n--------------ת����%d��---------------\n", i + 1);
			projUV p;

			p = pj_inv(parr[i], pj); // ͶӰ��任(ͶӰ����ת��γ������)
			printf("����54ͶӰ  ����:%10lf,%10lf\n", parr[i].u, parr[i].v);
			printf("����54��γ������:%10lf,%10lf\n", p.u / DEG_TO_RAD, p.v / DEG_TO_RAD);    // �����ʱ�򣬽�����ת��Ϊ��

			p = pj_fwd(p, pj);       // ͶӰ���任(��γ������תͶӰ����)
			printf("����54ͶӰ  ����:%10lf,%10lf\n", p.u, p.v);
		}

		// �ͷ�ͶӰ�����ڴ�
		pj_free(pj);
		return 0;
	}
}



void test_igraph()
{
	igraph_t graph;
	igraph_vector_t v;
	igraph_vector_t result;
	igraph_real_t edges[] = { 
							  1, 2, 1, 3, 1, 7, 1,13, 1,17, 1,19, 1,21, 1,30,
							  2, 3, 2, 7, 2,27, 2,28, 2,32, 2, 9, 2, 8, 2,13,
							  3, 7, 3,12, 3,13, 4, 6, 4,10, 5, 6, 5,10, 5,16,
							  6,16, 8,30, 8,32, 8,33, 9,33,13,33,14,32,14,33,
							 15,32,15,33,18,32,18,33,19,33,20,32,20,33,
							 22,32,22,33,23,25,23,27,23,32,23,33,23,29,
							 24,25,24,27,24,31,25,31,26,29,26,33,27,33,
							 28,31,28,33,29,32,29,33,30,32,30,33,31,32,31,33,
							 32,33,33,39
	};

	igraph_vector_view(&v, edges, sizeof(edges) / sizeof(double));
	igraph_create(&graph, &v, 0, IGRAPH_UNDIRECTED);
	cout << igraph_ecount(&graph) << endl<< igraph_vcount(&graph);
	igraph_vector_init(&result, 0);

	igraph_degree(&graph, &result, igraph_vss_all(), IGRAPH_ALL,
		IGRAPH_LOOPS);
	printf("Maximum degree is      %10i, vertex %2i.\n",
		(int)igraph_vector_max(&result), (int)igraph_vector_which_max(&result));

	////igraph_closeness(&graph, &result, igraph_vss_all(), IGRAPH_ALL,
	////	/*weights=*/ 0);
	//printf("Maximum closeness is   %10f, vertex %2i.\n",
	//	(double)igraph_vector_max(&result), (int)igraph_vector_which_max(&result));

	//igraph_betweenness(&graph, &result, igraph_vss_all(),
	//	IGRAPH_UNDIRECTED, /*weights=*/ 0, /*nobigint=*/ 1);
	//printf("Maximum betweenness is %10f, vertex %2i.\n",
	//	(double)igraph_vector_max(&result), (int)igraph_vector_which_max(&result));

	igraph_vector_destroy(&result);
	igraph_destroy(&graph);
}


void test_od(list<OGRLayer*> mylayers)
{
	string filename = "../../../data/beijing_taz/taxi trips.txt";
	flowcollection taxiflows(filename,1," ");
	taxiflows.setLayerConnection(mylayers.front());

	//Initiate the od graph
	flowgraph od_graph(&taxiflows);
	//cout << od_graph.get_ecount() << endl << od_graph.get_vcount() << endl;
	//igraph_vector_t degree;
	vector<vector<double>> res;
	double b = distance_decay_parameter(od_graph, res);
	cout << b << endl;
	//igraph_vector_destroy(&degree);
	
	//flowcollection *flow_col= new flowcollection(filename);
}
