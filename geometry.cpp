const int COLINEAR = 0;
const int CW = 1;
const int CCW = 2;

const int INSIDE = 0;
const int OUTSIDE = 1;
const int ONEDGE = 2;

struct point {
    ld x, y;
    point(ld xloc, ld yloc) : x(xloc), y(yloc) {}
    point() {}
    point& operator= (const point& other) {
        x = other.x, y = other.y;
        return *this;
    }
    bool operator== (const point& other) const {
        return abs(other.x - x) < prec && abs(other.y - y) < prec;
    }
    bool operator!= (const point& other) const {
        return !(abs(other.x - x) < prec && abs(other.y - y) < prec);
    }
    bool operator< (const point& other) const {
        return (x < other.x ? true : (x == other.x && y < other.y));
    }
};

struct vect {
    ld i, j;
};

struct segment {
    point p1, p2;
    segment(point a, point b) : p1(a), p2(b) {}
    segment() {}
};

ld crossproduct(point a, point b, point c) {
    vect ab, ac;
    ab.i = b.x - a.x;
    ab.j = b.y - a.y;
    ac.i = c.x - a.x;
    ac.j = c.y - a.y;
    return (ab.i * ac.j - ab.j * ac.i);
}

ld dotproduct(point a, point b, point c) {
    vect ab, bc;
    ab.i = b.x - a.x;
    ab.j = b.y - a.y;
    bc.i = c.x - b.x;
    bc.j = c.y - b.y;
    return (ab.i * bc.i + ab.j * bc.i);
}

int orientation(point p, point q, point r) {
    int val = (int) crossproduct(p, q, r);
    if(val == 0) return COLINEAR;
    return (val > 0) ? CW : CCW;
}

bool onsegment(point p, segment s) {
    return (p.x <= max(s.p1.x, s.p2.x) && p.x >= min(s.p1.x, s.p2.x) &&
            p.y <= max(s.p1.y, s.p2.y) && p.y >= min(s.p1.y, s.p2.y));
}

ld pointsquareddist(point a, point b) {
    return pow(a.x-b.x, 2) + pow(a.y-b.y, 2);
}

ld pointdist(point a, point b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

bool straddle(segment s1, segment s2) {
    ld cross1 = crossproduct(s1.p1, s1.p2, s2.p1);
    ld cross2 = crossproduct(s1.p1, s1.p2, s2.p2);
    if((cross1 > 0 && cross2 > 0) || (cross1 < 0 && cross2 < 0)) return false;
    if(cross1 == 0 && cross2 == 0 && orientation(s1.p2, s2.p1, s2.p2) != COLINEAR) return false;
    return true;
}

vector<point> intersect(segment s1, segment s2) {
    vector<point> res;
    point a = s1.p1, b = s1.p2, c = s2.p1, d = s2.p2;
    if(orientation(a,b,c) == 0 && orientation(a,b,d) == 0 &&
            orientation(c,d,a) == 0 && orientation(c,d,b) == 0) {
        point min_s1 = min(a,b), max_s1 = max(a,b);
        point min_s2 = min(c,d), max_s2 = max(c,d);
        if(min_s1 < min_s2) {
            if(max_s1 < min_s2) return res;
        }
        else if(min_s2 < min_s1 && max_s2 < min_s1) return res;
        point start = max(min_s1,min_s2), end = min(max_s1,max_s2);
        if(start == end) res.pb(start);
        else {
            res.pb(min(start,end));
            res.pb(max(start,end));
        }
        return res;
    }
    ld x1 = (b.x-a.x);
    ld y1 = (b.y-a.y);
    ld x2 = (d.x-c.x);
    ld y2 = (d.y-c.y);
    ld u1 = (-y1 * (a.x-c.x) + x1 * (a.y-c.y)) / (-x2 * y1 + x1 * y2);
    ld u2 = (x2 * (a.y-c.y) - y2 * (a.x-c.x)) / (-x2 * y1 + x1 * y2);
    if(u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1) {
        res.pb(point((a.x + u2 * x1), (a.y + u2 * y1)));
    }
    return res;
}

ld linepointdist(segment s, point p, bool issegment) {
    if(s.p1 == s.p2) {
        if(p == s.p1) return 0;
        return pointdist(p, s.p1);
    }
    if(issegment) {
        if(dotproduct(s.p1, s.p2, p) > 0) return pointdist(s.p2, p);
        if(dotproduct(s.p2, s.p1, p) > 0) return pointdist(s.p1, p);
    }
    return abs(crossproduct(s.p1,s.p2,p) / pointdist(s.p1,s.p2));
}

// A utility function to find next to top in a stack
point nextToTop(stack<point> &S) {
    point p = S.top();
    S.pop();
    point res = S.top();
    S.push(p);
    return res;
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
point p0;
bool convex_onedge;
int convexcompare(const void *vp1, const void *vp2) {
    point *p1 = (point *)vp1;
    point *p2 = (point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0 && !convex_onedge)
        return (pointsquareddist(p0, *p2) >= pointsquareddist(p0, *p1))? -1 : 1;
    if (o == 0 && convex_onedge)
        return 1;

    return (o == 2)? -1: 1;
}

vector<point> convexhull(vector<point> points, bool onedge = false) {
    convex_onedge = onedge;
    int n = points.size();
    if(n < 3) {
        return {};
    }

    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;

        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                    points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted ouput if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(point), convexcompare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++) {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        if(!onedge) {
            while (i < n-1 && (orientation(p0, points[i], points[i+1]) == 0))
                i++;
        }

        points[m] = points[i];
        m++;  // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) return {};

    // Create an empty stack and push first three points
    // to it.
    stack<point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++) {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while((orientation(nextToTop(S), S.top(), points[i]) == 0 && !onedge) ||
              (orientation(nextToTop(S), S.top(), points[i]) == 1))
            S.pop();
        S.push(points[i]);
    }

    // Now stack has the output points, build a vector to return
    vector<point> result;
    while(!S.empty()) {
        result.pb(S.top());
        S.pop();
    }
    return result;
}

ld polyarea(vector<point>& p) {
    ld result = 0;
    for(int i = 0, j = 1, n = p.size(); i < n; i++, j = (i+1)%n)
        result += (p[i].x * p[j].y) - (p[i].y * p[j].x);
    return result / 2.0;
}

int insidepoly(vector<point> poly, point p) {
    bool inside = false;
    point outside(iinf, p.y);
    vector<point> intersection;
    for(uint i = 0, j = poly.size()-1; i < poly.size(); i++, j=i-1) {
        if(p == poly[i] || p == poly[j]) return ONEDGE;
        if(orientation(p,poly[i],poly[j]) == COLINEAR &&
                onsegment(p,segment(poly[i],poly[j]))) return ONEDGE;
        intersection = intersect(segment(p,outside), segment(poly[i],poly[j]));
        if(intersection.size() == 1) {
            if(poly[i] == intersection[0] && poly[j].y <= p.y) continue;
            if(poly[j] == intersection[0] && poly[i].y <= p.y) continue;
            inside = !inside;
        }
    }
    return inside ? INSIDE : OUTSIDE;
}
