#include <stdio.h>

typedef struct {
    int x, y;
} Point;

// Function to find orientation of ordered triplet (p, q, r)
// 0 --> collinear, 1 --> clockwise, 2 --> counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;          // collinear
    return (val > 0) ? 1 : 2;        // 1=clockwise, 2=counterclockwise
}

// Function to print convex hull
void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    int hull[n];
    int l = 0;  // find leftmost point
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    int p = l, q;
    int count = 0;

    printf("Points in Convex Hull are:\n");
    do {
        hull[count++] = p;
        q = (p + 1) % n;

        for (int i = 0; i < n; i++)
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;

        p = q;

    } while (p != l);

    for (int i = 0; i < count; i++)
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
}

int main() {
    
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);
    return 0;
}
