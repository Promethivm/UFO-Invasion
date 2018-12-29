// compute the area of a triangle using Heron's formula
float triarea(float a, float b, float c)
{
    float s = (a + b + c)/2.0;
    return sqrt(s*(s-a)*(s-b)*(s-c));           
}

// compute the distance between two 2d points
float dist(float x0, float y0, float x1, float y1)
{
    float a = x1 - x0;      
    float b = y1 - y0;      
    return sqrt(a*a + b*b);
}

// compute the barycentric coordinates of a 2d point inside a 2d triangle
// (x0, y0) (x1, y1) (x2, y2) are the vertices of a 2d triangle
// (vx, vy) is a point inside the 2d triangle 
// u, v, w are the barycentric coordinates of (vx, vy) in the triangle
void barycent(float x0, float y0, float x1, float y1, float x2, float y2, 
    float vx, float vy,
    float *u, float *v, float *w)
{
    // compute the area of the big triangle
    float a = dist(x0, y0, x1, y1);
    float b = dist(x1, y1, x2, y2);
    float c = dist(x2, y2, x0, y0);
    float totalarea = triarea(a, b, c);

    // compute the distances from the outer vertices to the inner vertex
    float length0 = dist(x0, y0, vx, vy);      
    float length1 = dist(x1, y1, vx, vy);      
    float length2 = dist(x2, y2, vx, vy);      

    // divide the area of each small triangle by the area of the big triangle
    *u = triarea(b, length1, length2)/totalarea;
    *v = triarea(c, length0, length2)/totalarea;
    *w = triarea(a, length0, length1)/totalarea;      
}
