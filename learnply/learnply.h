/*
Data structures for learnply
Eugene Zhang 2005
*/
#ifndef __LEARNPLY_H__
#define __LEARNPLY_H__

#include "ply.h"
#include "icVector.H"
#include <vector>//

const double EPS = 1.0e-6;
const double PI=3.1415926535898;

/* forward declarations */
class Triangle;

class Vertex {
public:
  double x,y,z;
  int index;

  int ntris;
  Triangle **tris;
  int max_tris;

	icVector3 normal;
  void *other_props;

public:
  Vertex(double xx, double yy, double zz) { x = xx; y = yy; z = zz; }
};

class Edge {
public:
  int index;
  Vertex *verts[2];
  int ntris;
  Triangle **tris;
	double length;
};

class Triangle {
public:
  int index;
  int nverts;
  Vertex *verts[3];
  Edge *edges[3];

	double angle[3];
	float area;

	icVector3 normal;
  void *other_props;
};

class VertexList {

public:

  int num_verts;
  int max_verts;
  Vertex **verts;

  VertexList (int max) {
    max_verts = max;
    verts = new Vertex *[max_verts];
    num_verts = 0;
  }
	void finalize() {
		if (this != NULL) {
			free(verts);
			free(this);
		}
	}
	void append(Vertex *v)
	{
		int i;

		/* first make sure there is enough room for new vertex */

		if (num_verts >= max_verts) {
			max_verts += 10;
			Vertex **tlist = new Vertex *[max_verts];
			for (i = 0; i < num_verts; i++)
				tlist[i] = verts[i];
			delete (verts);
			verts = tlist;
		}

		/* add new vertex to list */

		verts[num_verts] = v;
		num_verts++;
	}

};

class TriangleList {
public:

  int num_tris;
  int max_tris;
  Triangle **tris;

  TriangleList (int max) {
    max_tris = max;
    tris = new Triangle *[max_tris];
    num_tris = 0;
  }
	void append(Triangle *t)
	{
		int i;

		/* first make sure there is enough room for new triangle */

		if (num_tris >= max_tris) {
			max_tris += 10;
			Triangle **tlist = new Triangle *[max_tris];
			for (i = 0; i < num_tris; i++)
				tlist[i] = tris[i];
			delete (tris);
			tris = tlist;
		}

		/* add new triangle to list */

		tris[num_tris] = t;
		num_tris++;
	}
};

class EdgeList {

public:

  int num_edges;
  int max_edges;
  Edge **edges;

  EdgeList (int max) {
    max_edges = max;
    edges = new Edge *[max_edges];
    num_edges = 0;
  }
	void append(Edge *e)
	{
		int i;

		/* first make sure there is enough room for new edge */

		if (num_edges >= max_edges) {
			max_edges += 10;
			Edge **tlist = new Edge *[max_edges];
			for (i = 0; i < num_edges; i++)
				tlist[i] = edges[i];// buffer overrun to tlist?
			delete (edges);
			edges = tlist;
		}

		/* add new edge to list */

		edges[num_edges] = e; // buffer overrun to edges[]?
		num_edges++;
	}
};

class Polyhedron {
public:

	int index;

  Triangle **tlist;  /* list of triangles */
  int ntris;
  int max_tris;

  Vertex **vlist;    /* list of vertices */
  int nverts;
  int max_verts;

  Edge **elist;      /* list of edges */
  int nedges;
  int max_edges;


	icVector3 center;
	double radius;
	double area;

	int seed;

  PlyOtherProp *vert_other,*face_other;

	void average_normals();

  void create_edge(Vertex *, Vertex *);
  void create_edges();
  int face_to_vertex_ref(Triangle *, Vertex *);
  void order_vertex_to_tri_ptrs(Vertex *);
  void vertex_to_tri_ptrs();
  Triangle *find_common_edge(Triangle *, Vertex *, Vertex *);
  Triangle *other_triangle(Edge *, Triangle *);
	void calc_bounding_sphere();
	void calc_face_normals_and_area();
	void calc_edge_length();

	Polyhedron();
  Polyhedron(FILE *);
  void write_file(FILE *);

  void create_pointers();

	// initialization and finalization
	void initialize();
	void finalize();

	//p3-1 test
  //Corner ** clist; // this is polyhedron?
  //int num_corners, max_corners;
	  //std::vector<Corner> clist;
  
  //void display_irre_ver();
	//
};


//P3-1 _ Classes

// 1st attempt
class Corner;

class Corner {
public:

	Corner() {};//default 
	//1s
	// constructor -- Todo add rest of variables to it
	int num_edges;
	Corner(int num_edges) :num_edges(num_edges), cEdges(num_edges){}; // class constructer needed to make non constant vector
	std::vector<Edge> cEdges;//a vector instead of built in array
	~Corner() {}; // destructor - needed for vec with dynamic amount of class edge vars (unconstant)
	Triangle* cTriangle;
	Vertex* cVertex;
	Edge *cEdge;
	//we need Index(id) list //const int num_edges=0;//Edge* cEdges[num_edges];// Triangle/int triangle_id;//Vertex vert;//int nedges;	//Edge** edges; // opposite of corner

	int index = 0;
	Vertex* vertex = NULL; //vertex of corner
	Corner* opp = NULL; // opposite of corner
	Corner* prev = NULL; // previous corner
	Corner* next = NULL;// nextcorner
};
/*
class CornerList {
public:
	int num_corners; // this is CornerList?
	int max_corners;
	Corner** corners;

	///*
	CornerList(int max) {
		max_corners = max;
		corners = new Corner * [max_corners];
		num_corners = 0;
	}
	
	void CornerList1(Polyhedron* poly);

	void append(Corner* e)
	{
		int i;
		// first make sure there is enough room for new Corner /
		if (num_corners >= max_corners) {
			max_corners += 10;
			Corner** clist = new Corner * [max_corners];
			for (i = 0; i < num_corners; i++)
				clist[i] = corners[i];
			delete (corners);
			corners = clist;
		}

		// add new edge to list 

		corners[num_corners] = e;
		num_corners++;
	}
};
*/
//test stuff - unused - from Du-1
//std::vector<Triangle*> tris;
//std::vector<Corner*> corners;
//

#endif /* __LEARNPLY_H__ */
