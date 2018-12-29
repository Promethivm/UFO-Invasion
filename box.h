struct Box
{
  float minx, maxx;       
  float miny, maxy;       
  float minz, maxz;       
};

float min(float a, float b)
{
  return (a < b ? a : b);
}

float max(float a, float b)
{
  return (a > b ? a : b);
}

// translates a box
Box movebox(Box b, float x, float y, float z)
{
  b.minx+=x;
  b.maxx+=x;

  b.miny+=y;
  b.maxy+=y;

  b.minz+=z;
  b.maxz+=z;

  return b;    
}


// translates a box
Box scalebox(Box b, float x, float y, float z)
{
  b.minx*=x;
  b.maxx*=x;

  b.miny*=y;
  b.maxy*=y;

  b.minz*=z;
  b.maxz*=z;

  return b;    
}


// returns whether or not two boxes intersect
bool intersect(const Box &b1, const Box &b2)
{
  if (b1.minx > b2.maxx) return false;
  if (b2.minx > b1.maxx) return false;

  if (b1.miny > b2.maxy) return false;
  if (b2.miny > b1.maxy) return false;
          
  if (b1.minz > b2.maxz) return false;
  if (b2.minz > b1.maxz) return false;

  return true;
}

// pre-condition: boxes must intersect
// returns the intersection of two boxes
Box isection(const Box &b1, const Box &b2)
{
  Box b3;
  b3.minx = max(b1.minx, b2.minx);
  b3.maxx = min(b1.maxx, b2.maxx);

  b3.miny = max(b1.miny, b2.miny);
  b3.maxy = min(b1.maxy, b2.maxy);

  b3.minz = max(b1.minz, b2.minz);
  b3.maxz = min(b1.maxz, b2.maxz);

  return b3;
}

