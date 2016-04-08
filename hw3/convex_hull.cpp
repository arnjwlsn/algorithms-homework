#include <chrono>
#include <cstdio>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>

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

int side_of_line(const Point &point1, const Point &point2, const Point &point3);
float distance_from_line(const Point &point1, const Point &point2, const Point &point3);
bool point_in_triangle(const Point &p, const Point &point1, const Point &point2, const Point &point3);
void find_hull(const std::vector<Point> &Sk, const Point P, const Point Q, std::vector<Point> &hull_points);
void quick_hull(const std::vector<Point> &s, std::vector<Point> &hull_points);

int main() {
  const size_t number_of_points = 100;
  std::vector<Point> points;
  points.reserve(number_of_points);
  std::vector<Point> hull_points;

  // Random number generator
  std::mt19937 mersenne_twister(std::chrono::high_resolution_clock::now().time_since_epoch().count());

  // Generate random points
  for (int i = 0; i < number_of_points; ++i) {
    Point pt;
    pt.x = (float)(mersenne_twister() % 1000);
    pt.y = (float)(mersenne_twister() % 1000);
    points.push_back(pt);
  }

  std::sort(points.begin(), points.end());
  quick_hull(points, hull_points);

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
    for (const auto &pt : hull_points) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }
}

int side_of_line(const Point &point1, const Point &point2, const Point &point3) {
    return (point2.x - point1.x) * (point3.y - point1.y) - (point2.y - point1.y) * (point3.x - point1.x);
}

float distance_from_line(const Point &point1, const Point &point2, const Point &point3) {
  return (std::abs((point2.y - point1.y) * point3.x - (point2.x - point1.x) * point3.y + point2.x * point1.y - point2.y * point1.x)
         / std::sqrt((point2.y - point1.y) * (point2.y - point1.y) + (point2.x - point1.x) * (point2.x - point1.x)));
}

bool point_in_triangle(const Point &p, const Point &point1, const Point &point2, const Point &point3) {
  float a = ((point2.y - point3.y) * (p.x - point3.x) + (point3.x - point2.x) * (p.y - point3.y)) / ((point2.y - point3.y) * (point1.x - point3.x) + (point3.x - point2.x) * (point1.y - point3.y));
  float b = ((point3.y - point1.y) * (p.x - point3.x) + (point1.x - point3.x) * (p.y - point3.y)) / ((point2.y - point3.y) * (point1.x - point3.x) + (point3.x - point2.x) * (point1.y - point3.y));
  float c = 1.0f - a - b;
  return (0.0f < a && 0.0f < b && 0.0f < c);
}

// http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html
void find_hull(const std::vector<Point> &Sk, const Point P, const Point Q, std::vector<Point> &hull_points) {
  if (Sk.size() == 0) return;

  std::vector<Point> S0;
  std::vector<Point> S1;
  std::vector<Point> S2;

  float furthestDistance = 0.0f;
  Point C;
  for (const auto &pt : Sk) {
    float distance = distance_from_line(P, Q, pt);
    if (distance > furthestDistance) {
      furthestDistance = distance;
      C = pt;
    }
  }

  hull_points.push_back(C);

  for (const auto &pt : Sk) {
    if (point_in_triangle(pt, P, C, Q)) {
      S0.push_back(pt);
    } else if (0 < side_of_line(P, C, pt)) {
      S1.push_back(pt);
    } else if (0 < side_of_line(C, Q, pt)) {
      S2.push_back(pt);
    }
  }

  find_hull(S1, P, C, hull_points);
  find_hull(S2, C, Q, hull_points);
}

// http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html
void quick_hull(const std::vector<Point> &s, std::vector<Point> &hull_points) {
  Point A = s[0];
  Point B = s[s.size() - 1];
  hull_points.push_back(A);
  hull_points.push_back(B);

  std::vector<Point> S1;
  std::vector<Point> S2;

  for (auto it = s.begin() + 1; it != s.end() - 1; ++it) {
    const Point pt = *it;
    const int s1 = side_of_line(A, B, pt);
    const int s2 = side_of_line(B, A, pt);
    if (0 < s1) {
      S1.push_back(pt);
    } else if (0 < s2) {
      S2.push_back(pt);
    }
  }

  find_hull(S1, A, B, hull_points);
  find_hull(S2, B, A, hull_points);
}
