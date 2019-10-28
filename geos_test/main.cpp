#include"method/CalculateBtwId.h"
#include"test.h"

list<OGRLayer*> mylayers;
vector<flowcollection> flowcollections;
int main()
{
	try
	{
		GDALAllRegister();
		GDALDataset   *poDS;
		CPLSetConfigOption("SHAPE_ENCODING", "");  //���������������
		//��ȡshp�ļ�
		poDS = (GDALDataset*)GDALOpenEx("../../../data/beijing_taz/taz_polygon.shp", GDAL_OF_VECTOR, NULL, NULL, NULL);

		if (poDS == NULL)
		{
			printf("Open failed.\n%s");
			system("pause");
			return 0;
		}

		OGRLayer  *poLayer;
		poLayer = poDS->GetLayer(0); //��ȡ��
		mylayers.push_back(poLayer);

		//proj_test();
		test_getdistance(mylayers);
		//test_igraph();
		test_od(mylayers);

		GDALClose(poDS);
	}
	catch (const exception &e)
	{
		cerr << "Standard exception thrown: " << e.what() << endl;
		exit(1);
	}
	//// and this is a catch-all non standard ;)
	//catch (...)
	//{
	//	cerr << "unknown exception trown!\n";
	//	exit(1);
	//}

	// Unload is no more necessary
	//io::Unload::Release();

	system("pause");
	return 1;
}
