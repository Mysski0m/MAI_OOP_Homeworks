#include "pentagon.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "vector.h"
#include <gtest/gtest.h>

using namespace figure;
using namespace vector;

TEST(TrapezoidTest, GeomCenter) {
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid t(p1, p2, p3, p4);
  Point center = t.GeomCenter();
  EXPECT_DOUBLE_EQ(center.x, 1.0);
  EXPECT_DOUBLE_EQ(center.y, 0.5);
}

TEST(TrapezoidTest, Area) {
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid t(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(t.Area(), 1.5);
}

TEST(TrapezoidTest, DoubleCast) {
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid t(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(static_cast<double>(t), 1.5);
}

TEST(TrapezoidTest, Equality) {
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid t1(p1, p2, p3, p4);
  Trapezoid t2(p1, p2, p3, p4);
  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 != t2);

  Point p5(0, 0), p6(3, 0), p7(2, 1), p8(1, 1);
  Trapezoid t3(p5, p6, p7, p8);
  EXPECT_FALSE(t1 == t3);
}

TEST(TrapezoidTest, CopyConstructor) {
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid t1(p1, p2, p3, p4);
  Trapezoid t2 = t1;
  EXPECT_DOUBLE_EQ(t2.Area(), 1.5);
  EXPECT_TRUE(t1 == t2);
}

TEST(TrapezoidTest, AssignmentOperator) {
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid t1(p1, p2, p3, p4);
  Trapezoid t2;
  t2 = t1;
  EXPECT_DOUBLE_EQ(t2.Area(), 1.5);
  EXPECT_TRUE(t1 == t2);
}

TEST(RhombusTest, GeomCenter) {
  Point p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus r(p1, p2, p3, p4);
  Point center = r.GeomCenter();
  EXPECT_DOUBLE_EQ(center.x, 0.0);
  EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RhombusTest, Area) {
  Point p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus r(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(r.Area(), 2.0);
}

TEST(RhombusTest, DoubleCast) {
  Point p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus r(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(static_cast<double>(r), 2.0);
}

TEST(RhombusTest, Equality) {
  Point p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus r1(p1, p2, p3, p4);
  Rhombus r2(p1, p2, p3, p4);
  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 != r2);
}

TEST(PentagonTest, GeomCenter) {
  Point p1(1, 0);
  Point p2(0.309, 0.951);
  Point p3(-0.809, 0.588);
  Point p4(-0.809, -0.588);
  Point p5(0.309, -0.951);
  Pentagon p(p1, p2, p3, p4, p5);
  Point center = p.GeomCenter();
  EXPECT_NEAR(center.x, 0.0, 1e-3);
  EXPECT_NEAR(center.y, 0.0, 1e-3);
}

TEST(PentagonTest, Area) {
  Point p1(1, 0);
  Point p2(0.309, 0.951);
  Point p3(-0.809, 0.588);
  Point p4(-0.809, -0.588);
  Point p5(0.309, -0.951);
  Pentagon p(p1, p2, p3, p4, p5);
  EXPECT_NEAR(p.Area(), 2.37764, 1e-3);
}

TEST(PentagonTest, Equality) {
  Point pts[5] = {Point(1, 0), Point(0.309, 0.951), Point(-0.809, 0.588),
                  Point(-0.809, -0.588), Point(0.309, -0.951)};
  Pentagon p1(pts[0], pts[1], pts[2], pts[3], pts[4]);
  Pentagon p2(pts[0], pts[1], pts[2], pts[3], pts[4]);
  EXPECT_TRUE(p1 == p2);
}

TEST(VectorTest, PushBackAndSize) {
  Vector v;
  Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid *t = new Trapezoid(p1, p2, p3, p4);
  v.PushBack(t);
  EXPECT_EQ(v.Size(), 1);
}

TEST(VectorTest, TotalArea) {
  Vector v;

  Point tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
  Trapezoid *t = new Trapezoid(tp1, tp2, tp3, tp4);

  Point rp1(0, 0), rp2(1, 1), rp3(0, 2), rp4(-1, 1);
  Rhombus *r = new Rhombus(rp1, rp2, rp3, rp4);

  Point pp1(1, 0), pp2(0.309, 0.951), pp3(-0.809, 0.588), pp4(-0.809, -0.588),
      pp5(0.309, -0.951);
  Pentagon *p = new Pentagon(pp1, pp2, pp3, pp4, pp5);

  v.PushBack(t);
  v.PushBack(r);
  v.PushBack(p);

  double total = v.TotalArea();
  EXPECT_NEAR(total, 1.5 + 2.0 + 2.37764, 1e-3);
}

TEST(VectorTest, SeparateGeomCenterAndArea) {
  Vector v;

  Point tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
  Trapezoid *t = new Trapezoid(tp1, tp2, tp3, tp4);
  v.PushBack(t);

  Point rp1(0, 0), rp2(1, 1), rp3(0, 2), rp4(-1, 1);
  Rhombus *r = new Rhombus(rp1, rp2, rp3, rp4);
  v.PushBack(r);

  Pentagon *p = new Pentagon(Point(0, 0), Point(1, 0), Point(1, 1),
                             Point(0.5, 1.5), Point(0, 1));
  v.PushBack(p);
}

TEST(PolymorphismTest, VirtualMethods) {
  Point tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
  Trapezoid *t = new Trapezoid(tp1, tp2, tp3, tp4);

  Point rp1(0, 0), rp2(1, 1), rp3(0, 2), rp4(-1, 1);
  Rhombus *r = new Rhombus(rp1, rp2, rp3, rp4);

  Pentagon *p = new Pentagon(Point(0, 0), Point(2, 0), Point(2, 2), Point(1, 3),
                             Point(0, 2));

  Figure *f1 = t;
  EXPECT_DOUBLE_EQ(f1->Area(), 1.5);
  Point c1 = f1->GeomCenter();
  EXPECT_DOUBLE_EQ(c1.x, 1.0);
  EXPECT_DOUBLE_EQ(c1.y, 0.5);
  EXPECT_DOUBLE_EQ(static_cast<double>(*f1), 1.5);

  Figure *f2 = r;
  EXPECT_DOUBLE_EQ(f2->Area(), 2.0);
  Point c2 = f2->GeomCenter();
  EXPECT_DOUBLE_EQ(c2.x, 0.0);
  EXPECT_DOUBLE_EQ(c2.y, 1.0);
  EXPECT_DOUBLE_EQ(static_cast<double>(*f2), 2.0);

  Figure *f3 = p;
  double area_p = f3->Area();
  EXPECT_GT(area_p, 0.0);
  Point c3 = f3->GeomCenter();
  EXPECT_TRUE(std::isfinite(c3.x) && std::isfinite(c3.y));

  delete t;
  delete r;
  delete p;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}