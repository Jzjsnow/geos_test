#include "auxiliary_func.h"
#define PI                      3.141592654
#define EARTH_RADIUS            6378.137        //地球近似半径

auxiliary_func::auxiliary_func()
{

}
vector<string> auxiliary_func::split(const string &str, const string &delim)
{
    vector<string> res;
    if("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char * strs = new char[str.length() + 1] ; //不要忘了
    strcpy(strs, str.c_str());

    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while(p) {
        string s = p; //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }

    return res;
}

OGRLayer * auxiliary_func::generateGrid(OGRPoint bottomleft, OGRPoint topright, double gridsize)
{
    OGRLayer * templayer=NULL;
    for(double x=bottomleft.getX();x<topright.getX();x=x+gridsize)
    {
        for(double y=bottomleft.getY();y<topright.getY();y=y+gridsize)
        {
            OGRGeometry * bb;
            string wkt="POLYGON(("+to_string(x)+" "+to_string(y)+","+\
                    to_string(x+gridsize)+" "+to_string(y)+","+\
                    to_string(x+gridsize)+" "+to_string(y+gridsize)+","+\
                    to_string(x)+" "+to_string(y+gridsize)+"))";
            //这一块 还有点问题
            //char * cc[2];
            //strcpy(cc[0],wkt.c_str());
            /*bb->importFromWkt(cc);
            OGRFeature * aa;
            aa=OGRFeature::CreateFeature(templayer->GetLayerDefn());
            aa->SetGeometry(bb);
            templayer->CreateFeature(aa);*/
        }
    }
    return templayer;
}

double get_distance(OGRPoint point1, OGRPoint point2)
{
    double radLat1 = point1.getX() * PI / 180.0;   //角度1˚ = π / 180
    double radLat2 = point2.getX() * PI / 180.0;   //角度1˚ = π / 180
    double a = radLat1 - radLat2;//纬度之差
    double b = point1.getY() * PI / 180.0 - point2.getY() * PI / 180.0;  //经度之差
    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2))));
    dst = dst * EARTH_RADIUS;
    dst = round(dst * 10000000) / 10000;
    return dst;
}

int get_angle(OGRPoint point1, OGRPoint point2)
{
    double x = point1.getX() - point2.getX();//t d
    double y = point1.getY() - point2.getY();//z y
    int angle = -1;
    if (y == 0 && x > 0) angle = 0;
    if (y == 0 && x < 0) angle = 180;
    if (x == 0 && y > 0) angle = 90;
    if (x == 0 && y < 0) angle = 270;
    if (angle == -1)
    {
        OGRPoint p1(point1.getX(),point2.getY());
        OGRPoint p2(point2.getX(),point1.getY());
        double dislat = get_distance(p1, point2);
        double dislng = get_distance(p2, point2);
        if (x > 0 && y > 0) angle = atan2(dislng, dislat) / PI * 180;
        if (x < 0 && y > 0) angle = atan2(dislat, dislng) / PI * 180 + 90;
        if (x < 0 && y < 0) angle = atan2(dislng, dislat) / PI * 180 + 180;
        if (x > 0 && y < 0) angle = atan2(dislat, dislng) / PI * 180 + 270;
    }
    return angle;
}

double get_weight(double weight) {
    return weight;
}
