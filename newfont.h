#include <vector.h>

struct Newfont
{

  private:

  char charmap[256];

  float minx[100];
  float maxx[100];

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
  vector<Face> faces[100];
  vector<Material> materials;




  void loadfile(char *filename, char *mtlfilename, float scale)
  {
       
    for (int ctr = 0; ctr < 100; ctr++)
      {
	minx[ctr] = 9999999;    
	maxx[ctr] = -9999999;    
      }       
       
       
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
	  int fontnum = int(fabs(points[f.v[1]][1]));	  

	  float x0 = points[f.v[0]][0];
	  float x1 = points[f.v[1]][0];
	  float x2 = points[f.v[2]][0];

	  if (x0 > maxx[fontnum]) maxx[fontnum] = x0;
	  if (x1 > maxx[fontnum]) maxx[fontnum] = x1;
	  if (x2 > maxx[fontnum]) maxx[fontnum] = x2;

	  if (x0 < minx[fontnum]) minx[fontnum] = x0;
	  if (x1 < minx[fontnum]) minx[fontnum] = x1;
	  if (x2 < minx[fontnum]) minx[fontnum] = x2;


	  faces[fontnum].push_back(f);	    
	}	    
          
      }        	     
    fclose(fp); 
    
    
    // move all the letters to the origin
    
    
    for (int ctr = 0; ctr < points.size(); ctr++)
      {
	points[ctr][1]-=    int(points[ctr][1]);
	points[ctr][1]+=0.5;
      }
 
    // clear the char map
    memset(charmap, 0, 256); 
    
    // map the letters
    for (int ctr = 0; ctr < 26; ctr++)
      {
	charmap['a'+ctr] = 26 + ctr;        
	charmap['A'+ctr] = ctr;        
      }    
    
    // map the numbers    
    for (int ctr = 0; ctr < 10; ctr++)
      {
	charmap['0'+ctr] = 52 + ctr;        
      }    
    
    charmap[';'] = 62;    
    charmap['!'] = 63;    
    charmap['.'] = 64;    
    charmap[':'] = 65;    
    charmap['$'] = 66;    
    charmap['%'] = 67;    
    
  }

  public:

  Newfont(char *filename, char *mtlfilename, float scale)
  {
    loadfile(filename, mtlfilename, scale);
  }


  void draw(int letnum)
  {
       
//    glColor3f(1, 1, 1);
       
    vector<Face>::iterator i = faces[letnum].begin();
    
    
    
    glBegin (GL_TRIANGLES);
    while (i != faces[letnum].end())
      {
                             
	Face &f = *i;	
	
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

  void drawchar(char c)
  {
    draw(charmap[c]);      
  }

  void drawstring(char *str, float spacing=0.1, float spacesize=.3)
  {
    glPushMatrix();
    for (int ctr = 0; ctr < strlen(str); ctr++)
      {
	if (str[ctr]==' ') {glTranslatef(spacesize, 0, 0); continue;}
	int charnum = charmap[str[ctr]];
	glTranslatef(-minx[charnum], 0, 0);
	drawchar(str[ctr]);    
	glTranslatef(maxx[charnum], 0, 0);
	glTranslatef(spacing, 0, 0);

      }     
    glPopMatrix();
     
  }
  
  float getwidth(char *str, float spacing=0.1, float spacesize=.3)
  {
 float width = 0;       

   for (int ctr = 0; ctr < strlen(str); ctr++)
      {
	if (str[ctr]==' ') {width+=spacesize; continue;}
	int charnum = charmap[str[ctr]];
	width-=minx[charnum];
	width+=maxx[charnum];
	width+=spacing;

      }     

return width;        
}
  
  

};
