#ifndef ODDATA_H
#define ODDATA_H
#include <ogr_feature.h>


class ODdata
{
public:

    //timestamp:Point.Z or Point.M
    OGRPoint O;
    OGRPoint D;
    ODdata();
    ODdata(OGRPoint,OGRPoint);
};

#endif // ODDATA_H
