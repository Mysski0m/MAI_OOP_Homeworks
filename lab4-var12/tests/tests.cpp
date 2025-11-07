#include "pentagon.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "vector.h"
#include <gtest/gtest.h>

using namespace figure;
using namespace vector;

TEST(TrapezoidTest, GeomCenter) {
  figure::Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  figure::Trapezoid<double> t(p1, p2, p3, p4);
  figure::Point<double> center = t.GeomCenter();
  EXPECT_DOUBLE_EQ(center.x, 1.0);
  EXPECT_DOUBLE_EQ(center.y, 0.5);
}

TEST(TrapezoidTest, Area) {
  Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid<double> t(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(t.Area(), 1.5);
}

TEST(TrapezoidTest, DoubleCast) {
  Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid<double> t(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(static_cast<double>(t), 1.5);
}

TEST(TrapezoidTest, Equality) {
  Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid<double> t1(p1, p2, p3, p4);
  Trapezoid<double> t2(p1, p2, p3, p4);
  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 != t2);

  Point<double> p5(0, 0), p6(3, 0), p7(2, 1), p8(1, 1);
  Trapezoid<double> t3(p5, p6, p7, p8);
  EXPECT_FALSE(t1 == t3);
}

TEST(TrapezoidTest, CopyConstructor) {
  Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid<double> t1(p1, p2, p3, p4);
  Trapezoid<double> t2 = t1;
  EXPECT_DOUBLE_EQ(t2.Area(), 1.5);
  EXPECT_TRUE(t1 == t2);
}

TEST(TrapezoidTest, AssignmentOperator) {
  Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  Trapezoid<double> t1(p1, p2, p3, p4);
  Trapezoid<double> t2;
  t2 = t1;
  EXPECT_DOUBLE_EQ(t2.Area(), 1.5);
  EXPECT_TRUE(t1 == t2);
}

TEST(RhombusTest, GeomCenter) {
  Point<double> p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus<double> r(p1, p2, p3, p4);
  Point<double> center = r.GeomCenter();
  EXPECT_DOUBLE_EQ(center.x, 0.0);
  EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RhombusTest, Area) {
  Point<double> p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus<double> r(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(r.Area(), 2.0);
}

TEST(RhombusTest, DoubleCast) {
  Point<double> p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus<double> r(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(static_cast<double>(r), 2.0);
}

TEST(RhombusTest, Equality) {
  Point<double> p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
  Rhombus<double> r1(p1, p2, p3, p4);
  Rhombus<double> r2(p1, p2, p3, p4);
  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 != r2);
}

TEST(PentagonTest, GeomCenter) {
  Point<double> p1(1, 0);
  Point<double> p2(0.309, 0.951);
  Point<double> p3(-0.809, 0.588);
  Point<double> p4(-0.809, -0.588);
  Point<double> p5(0.309, -0.951);
  Pentagon<double> p(p1, p2, p3, p4, p5);
  Point<double> center = p.GeomCenter();
  EXPECT_NEAR(center.x, 0.0, 1e-3);
  EXPECT_NEAR(center.y, 0.0, 1e-3);
}

TEST(PentagonTest, Area) {
  Point<double> p1(1, 0);
  Point<double> p2(0.309, 0.951);
  Point<double> p3(-0.809, 0.588);
  Point<double> p4(-0.809, -0.588);
  Point<double> p5(0.309, -0.951);
  Pentagon<double> p(p1, p2, p3, p4, p5);
  EXPECT_NEAR(p.Area(), 2.37764, 1e-3);
}

TEST(PentagonTest, Equality) {
  Point<double> pts[5] = {Point<double>(1, 0), Point<double>(0.309, 0.951), Point<double>(-0.809, 0.588),
                  Point<double>(-0.809, -0.588), Point<double>(0.309, -0.951)};
  Pentagon<double> p1(pts[0], pts[1], pts[2], pts[3], pts[4]);
  Pentagon<double> p2(pts[0], pts[1], pts[2], pts[3], pts[4]);
  EXPECT_TRUE(p1 == p2);
}

TEST(VectorTest, PushBackAndSize) {
  Vector<std::shared_ptr<Figure<double>>> v;
  Point<double> p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
  auto t = std::make_shared<Trapezoid<double>>(p1, p2, p3, p4);
  v.PushBack(t);
  EXPECT_EQ(v.Size(), 1);
}

TEST(VectorTest, TotalArea) {
  Vector<std::shared_ptr<Figure<double>>> v;

  Point<double> tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
  auto t = std::make_shared<Trapezoid<double>>(tp1, tp2, tp3, tp4);

  Point<double> rp1(0, 0), rp2(1, 1), rp3(0, 2), rp4(-1, 1);
  auto r = std::make_shared<Rhombus<double>>(rp1, rp2, rp3, rp4);

  Point<double> pp1(1, 0), pp2(0.309, 0.951), pp3(-0.809, 0.588), pp4(-0.809, -0.588),
      pp5(0.309, -0.951);
  auto p = std::make_shared<Pentagon<double>>(pp1, pp2, pp3, pp4, pp5);

  v.PushBack(t);
  v.PushBack(r);
  v.PushBack(p);

  double total = v.template TotalArea<Figure<double>>();
  EXPECT_NEAR(total, 1.5 + 2.0 + 2.37764, 1e-3);
}

TEST(VectorTest, SeparateGeomCenterAndArea) {
  Vector<std::shared_ptr<Figure<double>>> v;

  Point<double> tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
  auto t = std::make_shared<Trapezoid<double>>(tp1, tp2, tp3, tp4);
  v.PushBack(t);

  Point<double> rp1(0, 0), rp2(1, 1), rp3(0, 2), rp4(-1, 1);
  auto r = std::make_shared<Rhombus<double>>(rp1, rp2, rp3, rp4);
  v.PushBack(r);

  auto p = std::make_shared<Pentagon<double>>(Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1),
                             Point<double>(0.5, 1.5), Point<double>(0, 1));
  v.PushBack(p);

  v.template PrintAllCenters<Figure<double>>();
  v.template PrintAllAreas<Figure<double>>();
}

TEST(PolymorphismTest, VirtualMethods) {
  Point<double> tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
  auto t = std::make_shared<Trapezoid<double>>(tp1, tp2, tp3, tp4);

  Point<double> rp1(0, 0), rp2(1, 1), rp3(0, 2), rp4(-1, 1);
  auto r = std::make_shared<Rhombus<double>>(rp1, rp2, rp3, rp4);

  auto p = std::make_shared<Pentagon<double>>(Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 2), Point<double>(1, 3),
                             Point<double>(0, 2));

  Figure<double> *f1 = t.get();
  EXPECT_DOUBLE_EQ(f1->Area(), 1.5);
  Point<double> c1 = f1->GeomCenter();
  EXPECT_DOUBLE_EQ(c1.x, 1.0);
  EXPECT_DOUBLE_EQ(c1.y, 0.5);
  EXPECT_DOUBLE_EQ(static_cast<double>(*f1), 1.5);

  Figure<double> *f2 = r.get();
  EXPECT_DOUBLE_EQ(f2->Area(), 2.0);
  Point<double> c2 = f2->GeomCenter();
  EXPECT_DOUBLE_EQ(c2.x, 0.0);
  EXPECT_DOUBLE_EQ(c2.y, 1.0);
  EXPECT_DOUBLE_EQ(static_cast<double>(*f2), 2.0);

  Figure<double> *f3 = p.get();
  double area_p = f3->Area();
  EXPECT_GT(area_p, 0.0);
  Point<double> c3 = f3->GeomCenter();
  EXPECT_TRUE(std::isfinite(c3.x) && std::isfinite(c3.y));
}

TEST(ScalarTypeTest, IntType) {
  Point<int> p1(0, 0), p2(2, 0), p3(1, 1), p4(0, 1);
  Trapezoid<int> t(p1, p2, p3, p4);
  EXPECT_DOUBLE_EQ(t.Area(), 1.5);
  Point<int> center = t.GeomCenter();
  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);
}

TEST(ScalarTypeTest, FloatType) {
  Point<float> p1(0.0f, 0.0f), p2(2.0f, 0.0f), p3(1.5f, 1.0f), p4(0.5f, 1.0f);
  Trapezoid<float> t(p1, p2, p3, p4);
  EXPECT_FLOAT_EQ(static_cast<float>(t), 1.5f);
  Point<float> center = t.GeomCenter();
  EXPECT_FLOAT_EQ(center.x, 1.0f);
  EXPECT_FLOAT_EQ(center.y, 0.5f);
}

TEST(VectorTest, DifferentFigureTypes) {
  Vector<std::shared_ptr<Figure<double>>> v;

  auto t = std::make_shared<Trapezoid<double>>(Point<double>(0, 0), Point<double>(2, 0), 
                                               Point<double>(1.5, 1), Point<double>(0.5, 1));
  auto r = std::make_shared<Rhombus<double>>(Point<double>(0, 0), Point<double>(1, 1), 
                                             Point<double>(0, 2), Point<double>(-1, 1));
  auto p = std::make_shared<Pentagon<double>>(Point<double>(0, 0), Point<double>(1, 0), 
                                              Point<double>(1, 1), Point<double>(0.5, 1.5), 
                                              Point<double>(0, 1));

  v.PushBack(t);
  v.PushBack(r);
  v.PushBack(p);

  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v.Capacity(), 10);
}

TEST(VectorTest, EraseOperation) {
  Vector<std::shared_ptr<Figure<double>>> v;

  auto t = std::make_shared<Trapezoid<double>>(Point<double>(0, 0), Point<double>(2, 0), 
                                               Point<double>(1.5, 1), Point<double>(0.5, 1));
  auto r = std::make_shared<Rhombus<double>>(Point<double>(0, 0), Point<double>(1, 1), 
                                             Point<double>(0, 2), Point<double>(-1, 1));

  v.PushBack(t);
  v.PushBack(r);

  EXPECT_EQ(v.Size(), 2);
  v.Erase(0);
  EXPECT_EQ(v.Size(), 1);
  
  EXPECT_DOUBLE_EQ(v[0]->Area(), 2.0);
}

TEST(VectorTest, InsertOperation) {
  Vector<std::shared_ptr<Figure<double>>> v;

  auto t = std::make_shared<Trapezoid<double>>(Point<double>(0, 0), Point<double>(2, 0), 
                                               Point<double>(1.5, 1), Point<double>(0.5, 1));
  auto r = std::make_shared<Rhombus<double>>(Point<double>(0, 0), Point<double>(1, 1), 
                                             Point<double>(0, 2), Point<double>(-1, 1));

  v.PushBack(t);
  v.Insert(0, r);

  EXPECT_EQ(v.Size(), 2);
  EXPECT_DOUBLE_EQ(v[0]->Area(), 2.0);
  EXPECT_DOUBLE_EQ(v[1]->Area(), 1.5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}