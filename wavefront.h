#include "matrixlib.h"

struct Wavefront
{

/*float minx, maxx;
float miny, maxy;
float minz, maxz;*/

Box box;

private:

  struct Face
  {
    int v[3];       	   
    int n[3];
    int mat;  // material index
  };
  
  struct Material
  {
    char name[80];
    float r, g, b;       
  };

  vector<Vector> points;
  vector<Vector> normals;
  vector<Face> faces;
  vector<Material> materials;




  void loadfile(char *filename, char *mtlfilename, float scale)
  {
    char line[2048];
    int spaces = 0;          
    FILE *fp;

    Material mat;                       

    // read the materials    
    
    fp = fopen(mtlfilename, "r");
    if (!fp) {MessageBox(NULL, "could not open material file", "error", MB_OK); return;}
    while (fgets(line, 2048, fp))
      {          
	if (!strncmp(line, "newmtl ", 7)) sscanf(line+7, "%s", mat.name);
	
	if (!strncmp(line, "Ka ", 3)) 
	  {
	    sscanf(line+4, "%f %f %f", &mat.r, &mat.g, &mat.b);
	    materials.push_back(mat);
	  }
      }        	     
    fclose(fp); 
    

    if (!materials.size()) {MessageBox(NULL, "could not find any materials in material file", "error", MB_OK); return;}


    int curmat = 0;


box.minx = 9999999;
box.miny = 9999999;
box.minz = 9999999;

box.maxx = -9999999;
box.maxy = -9999999;
box.maxz = -9999999;


    // read the geometry

    fp = fopen(filename, "r");
    if (!fp) {MessageBox(NULL, "could not open file", "error", MB_OK); return;}
      
    while (fgets(line, 2048, fp))
      {          

	// vertex
	if (!strncmp(line, "v ", 2)) {
	  Vector v;
	  sscanf(line+2, "%f %f %f", &v[0], &v[1], &v[2]);
	  
	  v[0]*=scale;
	  v[1]*=scale;
	  v[2]*=scale;
	  
	  if (v[0] > box.maxx) box.maxx = v[0];
	  if (v[1] > box.maxy) box.maxy = v[1];
	  if (v[2] > box.maxz) box.maxz = v[2];
	  
	  if (v[0] < box.minx) box.minx = v[0];
	  if (v[1] < box.miny) box.miny = v[1];
	  if (v[2] < box.minz) box.minz = v[2];

	  points.push_back(v);	    
	}

	// normal
	if (!strncmp(line, "vn ", 2)) {
	  Vector n;
	  sscanf(line+2, "%f %f %f", &n[0], &n[1], &n[2]);
	  normals.push_back(n);	    
	}
	
	
	if (!strncmp(line, "usemtl ", 7)) {

	  char matname[80];
	  sscanf(line+7, "%s", matname);

	  for (int ctr = 0; ctr < materials.size(); ctr++) if (!strcmp(materials[ctr].name, matname)) curmat = ctr;
                       
	}

	// face	    
	if (!strncmp(line, "f ", 2)) {
	  Face f;

	  // this is just to read the texture coord indices since we're not using them
	  int junk;

	  if (strstr(line, "//"))   		   
	    sscanf(line+2, "%d//%d %d//%d %d//%d", &f.v[0],  &f.n[0], &f.v[1], &f.n[1], &f.v[2], &f.n[2]);
	  else	  sscanf(line+2, "%d/%d/%d %d/%d/%d %d/%d/%d", &f.v[0],  &junk, &f.n[0], &f.v[1],&junk, &f.n[1], &f.v[2], &junk, &f.n[2]);

	  // subtract 1 so it indexes properly into our vector object
	  f.v[0]--;
	  f.v[1]--;
	  f.v[2]--;
	  
	  f.n[0]--;
	  f.n[1]--;
	  f.n[2]--;	  
	  f.mat = curmat;
	  faces.push_back(f);	    
	}	    
          
      }        	     
    fclose(fp); 
    
    
  }

 public:

  Wavefront(char *filename, char *mtlfilename, float scale)
    {
      loadfile(filename, mtlfilename, scale);
    }


  void draw(void)
  {
    glEnable(GL_COLOR_MATERIAL);              
    vector<Face>::iterator i = faces.begin();
    
    glBegin (GL_TRIANGLES);
    while (i != faces.end())
      {
	Face &f = *i;
	glColor3f(materials[f.mat].r, materials[f.mat].g, materials[f.mat].b);

	glNormal3f (normals[f.n[0]][0], normals[f.n[0]][1], normals[f.n[0]][2]);
	glVertex3f (points[f.v[0]][0], points[f.v[0]][1], points[f.v[0]][2]);

	glNormal3f (normals[f.n[1]][0], normals[f.n[1]][1], normals[f.n[1]][2]);
	glVertex3f (points[f.v[1]][0], points[f.v[1]][1], points[f.v[1]][2]);

	glNormal3f (normals[f.n[2]][0], normals[f.n[2]][1], normals[f.n[2]][2]);
	glVertex3f (points[f.v[2]][0], points[f.v[2]][1], points[f.v[2]][2]);
       	 
	i++;      	 
      }
    glEnd ();
  }



};
