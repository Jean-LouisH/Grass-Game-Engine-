void geometry_plotPolygon(int objectNumber);//plot polygon points based on number of sides, and radius.
void geometry_plotBlock(int objectNumber);//plot box points based on centre, height and width.
void geometry_transform(); //update points based on velocity.
double geometry_findDistance(unsigned char firstObject, int firstObjectNumber,
                             unsigned char secondObject, int secondObjectNumber);
