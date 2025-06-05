#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define ld long double
typedef long long ll;
typedef double T;
const ll mod = 1e9 + 7;
const int inf = 1e9 + 5;
const double pi = acos(-1);

const double eps = 1e-9; // Precision for floating pt comparisons
int sign(double x) { return (x > eps) - (x < -eps); }

struct pt{

  T x,y;
  pt operator+(pt p) {return {x+p.x, y+p.y};}
  pt operator-(pt p) {return {x-p.x, y-p.y};}
  pt operator*(T d) {return {x*d, y*d};}
  pt operator/(T d) {return {x/d, y/d};} // only for floatingpt

    bool operator < (pt a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (pt a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
	double norm() { return sqrtl(x * x + y * y); }

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
T cross2(pt a, pt b, pt c) { return cross(b - a, c - a); }
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);}  // > 0 if c is on the left of AB
                                                     // < 0 if c is on the right of AB
													                           // == 0 if c is on AB

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
  pt pq = q-p, num{cross(pq, fq-fp), dot(pq, fq-fp)};
	return fp + pt{cross(r-p, num), dot(r-p, num)} / sq(pq);    // pts p,q,r are undergone linear transformation a*p + b with fp , fq the transformed pts. then find a,b
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

void polarSortAround(pt o, vector<pt> &v) {
	sort(v.begin(), v.end(), [o](pt v, pt w) {
		return make_tuple(half(v-o), 0) < make_tuple(half(w-o), cross(v-o, w-o));
	});
}


struct line{

  pt v; T c;
  // From direction vector v and offset c
  line(pt v, T c) : v(v), c(c) {}
  // From equation ax+by=c
  line(T a, T b, T c) : v({b,-a}), c(c) {}
  // From pts P and Q
  line(pt p, pt q) : v(q-p), c(cross(v,p)) {}

  T side(pt p) {return cross(v,p)-c;} // Gives the value of ax+by-c , > 0 if on the left side, < 0 for right side

  double dist(pt p) {return abs(side(p)) / abs(v);} // Distance from P to l

  double sqDist(pt p) {return side(p)*side(p) / (double)sq(v);} 

  pt perp(pt v){
  	 return {-v.y,v.x};
  }

  line perpthrough(pt p) {return {p, p + perp(v)};}  // perperndicular line from p to l

  bool cmpProj(pt p, pt q) {    // Used for sorting pts in a line
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
		out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-pt coordinates
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

// returns true if  pt p is on line segment ab
bool is_pt_on_seg(pt a, pt b, pt p) {
    if (fabs(cross(p - b, a - b)) < eps) {
        if (p.x < min(a.x, b.x) - eps || p.x > max(a.x, b.x) + eps) return false;
        if (p.y < min(a.y, b.y) - eps || p.y > max(a.y, b.y) + eps) return false;
        return true;
    }
    return false;
}

// intersection pt between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(pt a, pt b, pt c, pt d, pt &ans) {
    double oa = cross2(c, d, a), ob = cross2(c, d, b);
    double oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0){
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}
// intersection pt between segment ab and segment cd assuming unique intersection may not exists
// se.size()==0 means no intersection
// se.size()==1 means one intersection
// se.size()==2 means range intersection
set<pt> seg_seg_intersection_inside(pt a,  pt b,  pt c,  pt d) {
    pt ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<pt> se;
    if (is_pt_on_seg(c, d, a)) se.insert(a);
    if (is_pt_on_seg(c, d, b)) se.insert(b);
    if (is_pt_on_seg(a, b, c)) se.insert(c);
    if (is_pt_on_seg(a, b, d)) se.insert(d);
    return se;
}

bool inDisk(pt a, pt b, pt p) {
		return dot(a-p, b-p) <= 0;
}

bool onSegment(pt a, pt b, pt p) {   // checks if p is on segment AB
 		return orient(a,b,p) == 0 && inDisk(a,b,p);
}

double segpt(pt a, pt b, pt p) {   // Minimum Distance from p to AB segment
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
	return min({segpt(a,b,c), segpt(a,b,d),segpt(c,d,a), segpt(c,d,b)});
}

double areaTriangle(pt a, pt b, pt c) {
	return abs(cross(b-a, c-a)) / 2.0;
}

double areaPolygon(vector<pt> p) {
	int area = 0;
	for (int i = 0, n = p.size(); i < n; i++) {
		area += cross(p[i], p[(i+1)%n]); // wrap back to 0 if i == n-1
	}
	return abs(area);
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

// Check if pt is inside edge (from clip1 to clip2)
bool inside(pt& p, pt& clip1, pt& clip2) {
    return (cross((clip2 - clip1),(p - clip1))) >= 0;
}

// Get intersection pt of lines (s1, e1) and (s2, e2)
pt intersection(pt& s1, pt& e1, pt& s2, pt& e2) {
    pt d1 = e1 - s1, d2 = e2 - s2;
    double cross_d = cross(d1,d2);
    if (abs(cross_d) < eps) return s1; // parallel, arbitrary pt

    double t = cross(s2 - s1, d2) / cross_d;
    return {s1.x + d1.x * t, s1.y + d1.y * t};
}

vector<pt> polygon_intersection(const vector<pt>& subject, const vector<pt>& clip) {
    vector<pt> output = subject;

    for (int i = 0; i < clip.size(); i++) {
        pt clip1 = clip[i];
        pt clip2 = clip[(i + 1) % clip.size()];
        vector<pt> input = output;
        output.clear();

        for (int j = 0; j < input.size(); j++) {
            pt curr = input[j];
            pt prev = input[(j + input.size() - 1) % input.size()];

            bool curr_in = inside(curr, clip1, clip2);
            bool prev_in = inside(prev, clip1, clip2);

            if (curr_in && prev_in) {
                output.push_back(curr);
            } else if (!curr_in && prev_in) {
                output.push_back(intersection(prev, curr, clip1, clip2));
            } else if (curr_in && !prev_in) {
                output.push_back(intersection(prev, curr, clip1, clip2));
                output.push_back(curr);
            }
        }
    }

    return output;
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
		pt p = l.proj(o); // pt P
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

double circle_circle_area(pt a, double r1, pt b, double r2) {
    double d = (a - b).norm();
    if(r1 + r2 <= d + eps) return 0;
    if(r1 + d < r2 + eps) return PI * r1 * r1;
    if(r2 + d < r1 + eps) return PI * r2 * r2;
    double theta_1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d)), 
    	theta_2 = acos((r2 * r2 + d * d - r1 * r1)/(2 * r2 * d));
    return r1 * r1 * (theta_1 - sin(2 * theta_1)/2.) + r2 * r2 * (theta_2 - sin(2 * theta_2)/2.);
}

int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt,pt>> &out) {
	if (inner) r2 = -r2;   // Finds the common inner or outer tangent of two circles
	pt d = o2-o1;           // For tangent from a pt, set r2 = 0
	double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
	if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
	for (double sign : {-1,1}) {
		pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
		out.push_back({o1 + v*r1, o2 + v*r2});
	}
	return 1 + (h2 > 0);
}


// contains all points p such that: cross(b - a, p - a) >= 0
struct HP {
    pt a, b;
    HP() {}
    HP(pt a, pt b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (HP& rhs) {
        pt p = b - a;
        pt q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (cross(p, q)) return cross(p, q) > 0;
        return cross(p, rhs.b - a) < 0;
    }
    pt line_line_intersection(pt a, pt b, pt c, pt d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * cross(c, d) / cross(b, d);
    }
    pt intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};
int check(HP a, HP b, HP c) {
    return cross(a.b - a.a, b.intersection(c) - a.a) > -eps; //-eps to include polygons of zero area (straight lines, points)
}
// consider half-plane of counter-clockwise side of each line
// if lines are not bounded add infinity rectangle
// returns a convex polygon, a point can occur multiple times though
// complexity: O(n log(n))
vector<pt> half_plane_intersection(vector<HP> h) {
    sort(h.begin(), h.end());
    vector<HP> tmp;
    for (int i = 0; i < h.size(); i++) {
        if (!i || cross(h[i].b - h[i].a, h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
    vector<HP> q(h.size() + 10);
    int qh = 0, qe = 0;
    for (int i = 0; i < h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;
    vector<HP> res; 
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    vector<pt> hull;
    if (res.size() > 2) {
        for (int i = 0; i < res.size(); i++) {
             hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
        }
    }
    return hull;
}

//Rotating Calipers, A,B are anti podal if they have parallel support line
vector<pair<int,int>> all_anti_podal(vector<pt> &p){

    int n = p.size(), p1 = 0, p2 = 0;
    vector<pair<int,int>> res;

    //Parallel edges should not be visited twice
    vector<bool> vis(n, false);

    for(; p1 < n; p1++){
        pt edge = p[(p1+1)%n] - p[p1];

        //find the opposite anti - podal point with different sign
        while(p2 == p1 || p2 == (p1+1)%n || sign(cross(edge, p[(p2+1)%n] - p[p2])) == sign(cross(edge, p[p2] - p[(p2-1+n)%n]))){
            p2 = p2+1;
            if(p2 >= n) p2 -= n;
        }

        if(vis[p1]) continue;

        //Now the edge (p1,p1+1) is a support line and p2 is the opposite point

        vis[p1] = 1;

        res.push_back({p1, p2});
        res.push_back({(p1+1)%n, p2});

        //if both edges from p1 and p2 are parallel
        if(cross(edge, p[(p2+1)%n] - p[p2]) == 0){
            res.push_back({p1, (p2+1)%n});
            res.push_back({(p1+1)%n, (p2+1)%n});
            vis[p2] = 1;
        }

    }

    return res;
}


int main(){
	return 0;
}