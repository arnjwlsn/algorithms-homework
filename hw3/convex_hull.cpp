#include <chrono>
#include <cstdio>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  const size_t number_of_points = 100;
  std::vector<Point> points;
  points.reserve(number_of_points);
  std::vector<Point> hullPoints;

  // Random number generator
  std::mt19937 mersenne_twister(std::chrono::high_resolution_clock::now().time_since_epoch().count());

  // Generate random points
  for (int i = 0; i < number_of_points; ++i) {
    Point pt;
    pt.x = (float)(mersenne_twister() % 1000);
    pt.y = (float)(mersenne_twister() % 1000);
    points.push_back(pt);
  }

  // Sort points so that we can find min and max
  std::sort(points.begin(), points.end());
  // Find convex hull points and place them into hullPoints
  quick_hull(points, hullPoints);

  // Save all points to a file
  {
    FILE *fp = fopen("points.csv", "w");
    for (const auto &pt : points) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }

  // Save only convex hull points
  {
    FILE *fp = fopen("hull.csv", "w");
    for (const auto &pt : hullPoints) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }
}

struct Point {
  float x;
  float y;

  bool operator<(const Point &pt) const {
    if (x == pt.x) {
      return (y <= pt.y);
    }
    return (x < pt.x);
  }
};

// http://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
int32_t find_side_of_line(const Point &point1, const Point &point2, const Point &point3) {
    return (point2.x - point1.x) * (point3.y - point1.y) - (point2.y - point1.y) * (point3.x - point1.x);
}

// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_two_points
float find_distance_from_line(const Point &point1, const Point &point2, const Point &point3) {
  return (std::abs((point2.y - point1.y) * point3.x - (point2.x - point1.x) * point3.y + point2.x * point1.y - point2.y * point1.x) 
         / std::sqrt((point2.y - point1.y) * (point2.y - point1.y) + (point2.x - point1.x) * (point2.x - point1.x)));
}

// http://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
bool find_point_in_triangle(const Point &p, const Point &point1, const Point &point2, const Point &point3) {
  float a = ((point2.y - point3.y) * (p.x - point3.x) + (point3.x - point2.x) * (p.y - point3.y)) / ((point2.y - point3.y) * (point1.x - point3.x) + (point3.x - point2.x) * (point1.y - point3.y));
  float b = ((point3.y - point1.y) * (p.x - point3.x) + (point1.x - point3.x) * (p.y - point3.y)) / ((point2.y - point3.y) * (point1.x - point3.x) + (point3.x - point2.x) * (point1.y - point3.y));
  float c = 1.0f - a - b;
  return (0.0f < a && 0.0f < b && 0.0f < c);
}

// http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html
void find_hull(const std::vector<Point> &Sk, const Point P, const Point Q, std::vector<Point> &hullPoints) {
  // If Sk has no point, then  return
  if (Sk.size() == 0) return;

  std::vector<Point> S0;
  std::vector<Point> S1;
  std::vector<Point> S2;

  // From the given set of points in Sk, find farthest point, say C, from segment PQ 
  float furthestDistance = 0.0f;
  Point C;
  for (const auto &pt : Sk) {
    float distance = find_distance_from_line(P, Q, pt);
    if (distance > furthestDistance) {
      furthestDistance = distance;
      C = pt;
    }
  }
  // Add point C to convex hull at the location between P and Q 
  hullPoints.push_back(C);

  /*
   * Three points P, Q, and C partition the remaining points of Sk into 3 subsets: S0, S1, and S2 
   * where S0 are points inside triangle PCQ, S1are points on the right side of the oriented 
   * line from  P to C, and S2 are points on the right side of the oriented line from C to Q.
   */
  for (const auto &pt : Sk) {
    if (find_point_in_triangle(pt, P, C, Q)) {
      S0.push_back(pt);
    } else if (0 < find_side_of_line(P, C, pt)) {
      S1.push_back(pt);
    } else if (0 < find_side_of_line(C, Q, pt)) {
      S2.push_back(pt);
    }
  }

  find_hull(S1, P, C, hullPoints);
  find_hull(S2, C, Q, hullPoints);
}

// http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html
void quick_hull(const std::vector<Point> &s, std::vector<Point> &hullPoints) {
  // Find left and right most points, say A & B, and add A & B to convex hull 
  Point A = s[0];
  Point B = s[s.size() - 1];
  hullPoints.push_back(A);
  hullPoints.push_back(B);

  std::vector<Point> S1;
  std::vector<Point> S2;

  /*
   * Segment AB divides the remaining (n-2) points into 2 groups S1 and S2 
   * where S1 are points in S that are on the right side of the oriented line from A to B, 
   * and S2 are points in S that are on the right side of the oriented line from B to A 
   */
  for (auto it = s.begin() + 1; it != s.end() - 1; ++it) {
    const Point pt = *it;
    const int32_t s1 = find_side_of_line(A, B, pt);
    const int32_t s2 = find_side_of_line(B, A, pt);
    if (0 < s1) {
      S1.push_back(pt);
    } else if (0 < s2) {
      S2.push_back(pt);
    }
  }

  find_hull(S1, A, B, hullPoints);
  find_hull(S2, B, A, hullPoints);
}
