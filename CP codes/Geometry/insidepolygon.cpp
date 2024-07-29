struct Point {
    int x, y;
};


double crossProduct(const Point& p1, const Point& p2, const Point& p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// Function to check if point p lies on segment p1p2
bool isPointOnSegment(const Point& p, const Point& p1, const Point& p2)
{
    return crossProduct(p1, p2, p) == 0
           && p.x >= min(p1.x, p2.x)
           && p.x <= max(p1.x, p2.x)
           && p.y >= min(p1.y, p2.y)
           && p.y <= max(p1.y, p2.y);
}

// Function to compute the winding number of a point with
// respect to a polygon
int windingNumber(const vector<Point>& polygon,
                  const Point& point)
{
    int n = polygon.size();
    int windingNumber = 0;

    for (int i = 0; i < n; i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];

        if (isPointOnSegment(point, p1, p2)) {
            return 1;
        }

        // Calculate the cross product to determine winding
        // direction
        if (p1.y <= point.y) {
            if (p2.y > point.y
                && crossProduct(p1, p2, point) > 0) {
                windingNumber++;
            }
        }
        else {
            if (p2.y <= point.y
                && crossProduct(p1, p2, point) < 0) {
                windingNumber--;
            }
        }
    }
    return windingNumber;
}

// Function to check if a point is inside a polygon using
// the winding number algorithm
bool isPointInPolygon(const vector<Point>& polygon, const Point& point)
{
    return windingNumber(polygon, point) != 0;
}