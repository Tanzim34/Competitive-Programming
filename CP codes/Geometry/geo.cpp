#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define ld long double
typedef long long ll;
typedef double T;
const ll mod = 1e9 + 7;
const int inf = 1e9 + 5;
const double pi = acos(-1);

struct pt{

  T x,y;
  pt operator+(pt p) {return {x+p.x, y+p.y};}
  pt operator-(pt p) {return {x-p.x, y-p.y};}
  pt operator*(T d) {return {x*d, y*d};}
  pt operator/(T d) {return {x/d, y/d};} // only for floatingpoint

};

bool operator==(pt a, pt b) {return a.x == b.x && a.y == b.y;}
bool operator!=(pt a, pt b) {return !(a == b);}

template <typename T> int sgn(T x) {
  return (T(0) < x) - (x < T(0));
}

T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}  // Distance from origin


pt translate(pt v, pt p) {return p+v;} // Translation
pt scale(pt c, double factor, pt p) {  // Scaling
   return c + (p-c)*factor;
}
pt rot(pt p, double a) {
   return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
}


// Dot Product

T dot(pt v, pt w) {return v.x*w.x + v.y*w.y;}
bool isPerp(pt v, pt w) {return dot(v,w) == 0;}

double angle(pt v, pt w) {
double cosTheta = dot(v,w) / abs(v) / abs(w);
return acos(max(-1.0, min(1.0, cosTheta)));
}

// Cross Product

T cross(pt v, pt w) {return v.x*w.y - v.y*w.x;}
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);}  // > 0 if c is on the left of AB
                                                     // < 0 if c is on the right of AB
													                           // == 0 if c is on AB

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
  pt pq = q-p, num{cross(pq, fq-fp), dot(pq, fq-fp)};
	return fp + pt{cross(r-p, num), dot(r-p, num)} / sq(pq);    // Points p,q,r are undergone linear transformation a*p + b with fp , fq the transformed points. then find a,b
}                                                            // Returned pt is a , also b = fp-a*p

bool inAngle(pt a, pt b, pt c, pt p) {
	assert(orient(a,b,c) != 0);
	if (orient(a,b,c) < 0) swap(b,c);   // returns true if p lies in the angle formed by AB and AC
	return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {  // Returns directed angle <BAC
	if (orient(a,b,c) >= 0)
	return angle(b-a, c-a);
	else return 2*pi - angle(b-a, c-a);
}

bool isConvex(vector<pt> &p) {    // Checks if polygon p is convex
	bool hasPos=false, hasNeg=false;
	for (int i=0, n=p.size(); i<n; i++) {
	int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
	if (o > 0) hasPos = true;
	if (o < 0) hasNeg = true;
	}
	return !(hasPos && hasNeg);
}

bool half(pt p) { // true if in blue half
	assert(p.x != 0 || p.y != 0); // the argument of (0,0) isundefined
	return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt> &v) {
	sort(v.begin(), v.end(), [](pt v, pt w) {
	return make_tuple(half(v), 0) < make_tuple(half(w), cross(v,w));
	});
}

void polarSortAround(vector<pt> &v) {     // PolarSort around O
  sort(v.begin(), v.end(), [](pt v, pt w) {
  return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v,w), sq(w));});
}


struct line{

  pt v; T c;
  // From direction vector v and offset c
  line(pt v, T c) : v(v), c(c) {}
  // From equation ax+by=c
  line(T a, T b, T c) : v({b,-a}), c(c) {}
  // From points P and Q
  line(pt p, pt q) : v(q-p), c(cross(v,p)) {}

  T side(pt p) {return cross(v,p)-c;} // Gives the value of ax+by-c , > 0 if on the left side, < 0 for right side

  double dist(pt p) {return abs(side(p)) / abs(v);} // Distance from P to l

  double sqDist(pt p) {return side(p)*side(p) / (double)sq(v);} 

  pt perp(pt v){
  	 return {-v.y,v.x};
  }

  line perpThrough(pt p) {return {p, p + perp(v)};}  // perperndicular line from p to l

  bool cmpProj(pt p, pt q) {    // Used for sorting points in a line
		return dot(v,p) < dot(v,q);
	} 

	line translate(pt t) {return {v, c + cross(v,t)};}
	line shiftLeft(double dist) {return {v, c + dist*abs(v)};} // Translate in the perp direction

	pt proj(pt p) {return p - perp(v)*side(p)/sq(v);}
	pt refl(pt p) {return p - perp(v)*2*side(p)/sq(v);}

};

bool inter(line l1, line l2, pt &out) {
		T d = cross(l1.v, l2.v);
		if (d == 0) return false;
		out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
		return true;
}

line bisector(line l1, line l2, bool interior) {
		assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
		double sign = interior ? 1 : -1;
		return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
		l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}

bool properInter(pt a, pt b, pt c, pt d, pt &out) { // Intersection of segments AB, CD
		double oa = orient(c,d,a),
		ob = orient(c,d,b),
		oc = orient(a,b,c),
		od = orient(a,b,d);
		// Proper intersection exists iff opposite signs
		if (oa*ob < 0 && oc*od < 0) {
			out = (a*ob - b*oa) / (ob-oa);
			return true;
		}
		return false;
}

bool inDisk(pt a, pt b, pt p) {
		return dot(a-p, b-p) <= 0;
}

bool onSegment(pt a, pt b, pt p) {   // checks if p is on segment AB
 		return orient(a,b,p) == 0 && inDisk(a,b,p);
}

double segPoint(pt a, pt b, pt p) {   // Minimum Distance from p to AB segment
	if (a != b) {
		line l(a,b);
		if (l.cmpProj(a,p) && l.cmpProj(p,b)) // if closest to projection
			return l.dist(p); // output distance to line
	}
	return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}

double segSeg(pt a, pt b, pt c, pt d) {  // segment - segment  minimum distance
	pt dummy;
	if (properInter(a,b,c,d,dummy))
		return 0;
	return min({segPoint(a,b,c), segPoint(a,b,d),segPoint(c,d,a), segPoint(c,d,b)});
}

double areaTriangle(pt a, pt b, pt c) {
	return abs(cross(b-a, c-a)) / 2.0;
}

double areaPolygon(vector<pt> p) {
	double area = 0.0;
	for (int i = 0, n = p.size(); i < n; i++) {
		area += cross(p[i], p[(i+1)%n]); // wrap back to 0 if i == n-1
	}
	return abs(area) / 2.0;
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p) {
	return p.y >= a.y;
}
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
	return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}

// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
	int numCrossings = 0;
	for (int i = 0, n = p.size(); i < n; i++) {
		if (onSegment(p[i], p[(i+1)%n], a))
			return !strict;
		numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
	}
	return numCrossings & 1; // inside if odd number of crossings
}

pt perp(pt v){
  	 return {-v.y,v.x};
}

pt circumCenter(pt a, pt b, pt c) {
	b = b-a, c = c-a; // consider coordinates relative to A
	assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
	return a + perp(b*sq(c) - c*sq(b))/cross(b,c)/2;
}

int circleLine(pt o, double r, line l, pair<pt,pt> &out) {
	double h2 = r*r - l.sqDist(o);
	if (h2 >= 0) { // the line touches the circle
		pt p = l.proj(o); // point P
		pt h = l.v*sqrt(h2)/abs(l.v); // vector parallel to l, of length h
		out = {p-h, p+h};
	}
	return 1 + sgn(h2);
}

int circleCircle(pt o1, double r1, pt o2, double r2, pair<pt,pt> &out) {
	pt d=o2-o1; double d2=sq(d);
	if (d2 == 0) {assert(r1 != r2); return 0;} // concentric circles
	double pd = (d2 + r1*r1 - r2*r2)/2; // = |O_1P| * d
	double h2 = r1*r1 - pd*pd/d2; // = hˆ2
	if (h2 >= 0) {
		pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
		out = {p-h, p+h};
	}
	return 1 + sgn(h2);
}

int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt,pt>> &out) {
	if (inner) r2 = -r2;   // Finds the common inner or outer tangent of two circles
	pt d = o2-o1;           // For tangent from a point, set r2 = 0
	double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
	if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
	for (double sign : {-1,1}) {
		pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
		out.push_back({o1 + v*r1, o2 + v*r2});
	}
	return 1 + (h2 > 0);
}


int main(){
	return 0;
}