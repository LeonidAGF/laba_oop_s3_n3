#include <gtest/gtest.h>
#include <utility>

#include "set.hpp"

TEST(Test, t1) {
    Set s;
    ASSERT_EQ(s.size(), 0u);
    ASSERT_EQ(s.empty(), true);
    ASSERT_EQ(s.contains(GeoCoordinate{ 0, 0 }), false);
    ASSERT_EQ(s(GeoCoordinate{ 1, 2 }), false);
}

TEST(Test, t2) {
    Set s;
    ASSERT_EQ(s.add(GeoCoordinate{ 1, 2 }), true);
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.add(GeoCoordinate{ 1, 2 }), false);
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.add(GeoCoordinate{ 1, 3 }), true);
    ASSERT_EQ(s.size(), 2u);
    ASSERT_EQ(s.empty(), false);
}

TEST(Test, t3) {
    Set s;
    s.add(GeoCoordinate{ 1, 1 });
    s.add(GeoCoordinate{ 2, 2 });
    s.add(GeoCoordinate{ 3, 3 });

    ASSERT_EQ(s.remove(GeoCoordinate{ 2, 2 }), true);
    ASSERT_EQ(s.size(), 2u);
    ASSERT_EQ(s.contains(GeoCoordinate{ 2, 2 }), false);
    ASSERT_EQ(s.remove(GeoCoordinate{ 2, 2 }), false);
    ASSERT_EQ(s.remove(GeoCoordinate{ 9, 9 }), false);
    ASSERT_EQ(s.size(), 2u);

    ASSERT_EQ(s.contains(GeoCoordinate{ 1, 1 }), true);
    ASSERT_EQ(s.contains(GeoCoordinate{ 3, 3 }), true);

    ASSERT_EQ(s.remove(GeoCoordinate{ 1, 1 }), true);
    ASSERT_EQ(s.remove(GeoCoordinate{ 3, 3 }), true);
    ASSERT_EQ(s.empty(), true);
    ASSERT_EQ(s.remove(GeoCoordinate{ 3, 3 }), false);
}

TEST(Test, t4) {
    Set s;
    s.add(GeoCoordinate{ 10, 20 });
    s.add(GeoCoordinate{ -5, 7 });
    for (double lat = -6; lat <= 11; lat += 1) {
        GeoCoordinate g{ lat, 20 };
        ASSERT_EQ(s(g), s.contains(g));
    }
    ASSERT_EQ(s(GeoCoordinate{ 10, 20 }), true);
    ASSERT_EQ(s.contains(GeoCoordinate{ -5, 7 }), true);
    ASSERT_EQ(s(GeoCoordinate{ 10, 21 }), false);
}

TEST(Test, t5) {
    Set s;
    (s += GeoCoordinate{ 1, 1 }) += GeoCoordinate{ 2, 2 };
    ASSERT_EQ(s.size(), 2u);
    (s -= GeoCoordinate{ 1, 1 }) -= GeoCoordinate{ 5, 5 };
    ASSERT_EQ(s.size(), 1u);
    ASSERT_EQ(s.contains(GeoCoordinate{ 2, 2 }), true);
}

TEST(Test, t6) {
    Set a;
    a.add(GeoCoordinate{ 1, 1 });
    a.add(GeoCoordinate{ 2, 2 });

    Set b(a);
    ASSERT_EQ(b == a, true);
    b.add(GeoCoordinate{ 3, 3 });
    b.remove(GeoCoordinate{ 1, 1 });

    ASSERT_EQ(a.size(), 2u);
    ASSERT_EQ(a.contains(GeoCoordinate{ 1, 1 }), true);
    ASSERT_EQ(a.contains(GeoCoordinate{ 3, 3 }), false);
    ASSERT_EQ(b.size(), 2u);

    Set c;
    c.add(GeoCoordinate{ 9, 9 });
    c = a;
    c.add(GeoCoordinate{ 4, 4 });
    ASSERT_EQ(a.size(), 2u);
    ASSERT_EQ(c.size(), 3u);
    ASSERT_EQ(c.contains(GeoCoordinate{ 9, 9 }), false);

    Set& ref = c;
    c = ref;
    ASSERT_EQ(c.size(), 3u);
    ASSERT_EQ(c.contains(GeoCoordinate{ 4, 4 }), true);
}

TEST(Test, t7) {
    Set a;
    a.add(GeoCoordinate{ 1, 1 });
    a.add(GeoCoordinate{ 2, 2 });

    Set b(std::move(a));
    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(b.contains(GeoCoordinate{ 2, 2 }), true);
    ASSERT_EQ(a.size(), 0u);
    ASSERT_EQ(a.empty(), true);
    ASSERT_EQ(a.contains(GeoCoordinate{ 1, 1 }), false);

    // источник остаётся рабочим
    ASSERT_EQ(a.add(GeoCoordinate{ 7, 7 }), true);
    ASSERT_EQ(a.size(), 1u);

    Set c;
    c.add(GeoCoordinate{ 5, 5 });
    c = std::move(b);
    ASSERT_EQ(c.size(), 2u);
    ASSERT_EQ(c.contains(GeoCoordinate{ 5, 5 }), false);
    ASSERT_EQ(b.size(), 0u);
    ASSERT_EQ(b.empty(), true);

    Set d;
    Set e(std::move(d));
    ASSERT_EQ(e.size(), 0u);
    ASSERT_EQ(d.size(), 0u);
}

TEST(Test, t8) {
    GeoCoordinate pa[] = { {1, 1}, {2, 2}, {3, 3} };
    GeoCoordinate pb[] = { {3, 3}, {4, 4}, {0, 0} };

    Set a;
    for (std::size_t i = 0; i < 3; ++i)
        a.add(pa[i]);

    Set b;
    for (std::size_t i = 0; i < 3; ++i)
        b.add(pb[i]);
    

    GeoCoordinate pu[] = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4} };
    GeoCoordinate pd1[] = { {1, 1}, {2, 2} };
    GeoCoordinate pd2[] = { {0, 0}, {4, 4} };

    Set s1;
    for (std::size_t i = 0; i < 5; ++i)
        s1.add(pu[i]);

    Set s2;
    s2.add({ 3, 3 });

    Set s3;
    for (std::size_t i = 0; i < 2; ++i)
        s3.add(pd1[i]);

    Set s4;
    for (std::size_t i = 0; i < 2; ++i)
        s4.add(pd2[i]);

    Set u = a | b;
    ASSERT_EQ(u.size(), (size_t)5);
    ASSERT_EQ(u == s1, true);

    Set i = a & b;
    ASSERT_EQ(i.size(), 1u);
    ASSERT_EQ(i == s2, true);

    Set d1 = a - b;
    ASSERT_EQ(d1.size(), 2u);
    ASSERT_EQ(d1 == s3, true);

    Set d2 = b - a;
    ASSERT_EQ(d2.size(), 2u);
    ASSERT_EQ(d2 == s4, true);
}

TEST(Test, t9) {
    Set a;
    a.add(GeoCoordinate{ 1, 1 });
    a.add(GeoCoordinate{ 2, 2 });
    Set e;

    ASSERT_EQ((a | e) == a, true);
    ASSERT_EQ((e | a) == a, true);
    ASSERT_EQ((a & e).empty(), true);
    ASSERT_EQ((a - e) == a, true);
    ASSERT_EQ((e - a).empty(), true);

    Set low;
    low.add(GeoCoordinate{ 1, 1 });
    low.add(GeoCoordinate{ 2, 2 });
    Set high;
    high.add(GeoCoordinate{ 5, 5 });

    ASSERT_EQ((low | high).size(), 3u);
    ASSERT_EQ((high | low).size(), 3u);
    ASSERT_EQ((low | high) == (high | low), true);
    ASSERT_EQ((low | high).contains(GeoCoordinate{ 5, 5 }), true);
    ASSERT_EQ((low | high).contains(GeoCoordinate{ 1, 1 }), true);
    ASSERT_EQ((low - high) == low, true);
    ASSERT_EQ((high - low) == high, true);
    ASSERT_EQ((low & high).size(), 0u);
}

TEST(Test, t10) {
    Set a;
    a.add(GeoCoordinate{ 1, 5 });
    a.add(GeoCoordinate{ 3, 3 });
    Set b;
    b.add(GeoCoordinate{ 1, 5 });
    b.add(GeoCoordinate{ 2, 2 });
    b.add(GeoCoordinate{ 3, 3 });

    ASSERT_EQ(a <= b, true);
    ASSERT_EQ(b <= a, false);
    ASSERT_EQ(a <= a, true);

    Set e;
    ASSERT_EQ(e <= a, true);
    ASSERT_EQ(a <= e, false);

    Set x;
    x.add(GeoCoordinate{ 1, 0 });
    x.add(GeoCoordinate{ 5, 0 });
    Set y;
    y.add(GeoCoordinate{ 1, 0 });
    y.add(GeoCoordinate{ 3, 0 });
    ASSERT_EQ(x <= y, false);
}

TEST(Test, t11) {
    Set a, b;
    a.add(GeoCoordinate{ 1, 1 });
    a.add(GeoCoordinate{ 2, 2 });
    b.add(GeoCoordinate{ 2, 2 });
    b.add(GeoCoordinate{ 1, 1 });

    ASSERT_EQ(a == b, true);
    ASSERT_EQ(a != b, false);

    b.add(GeoCoordinate{ 3, 3 });
    ASSERT_EQ(a == b, false);
    ASSERT_EQ(a != b, true);

    b.remove(GeoCoordinate{ 3, 3 });
    b.remove(GeoCoordinate{ 1, 1 });
    b.add(GeoCoordinate{ 1, 2 });
    ASSERT_EQ(a == b, false);
    ASSERT_EQ(a != b, true);

    Set e1, e2;
    ASSERT_EQ(e1 == e2, true);
    ASSERT_EQ(e1 != e2, false);
}

TEST(Test, t12) {
    Set s1;
    s1.add(GeoCoordinate{ 2, 1 });
    s1.add(GeoCoordinate{ 1, 5 });
    s1.add(GeoCoordinate{ 1, 2 });
    s1.add(GeoCoordinate{ 3, 0 });

    Set s2;
    s2.add(GeoCoordinate{ 3, 0 });
    s2.add(GeoCoordinate{ 1, 2 });
    s2.add(GeoCoordinate{ 1, 5 });
    s2.add(GeoCoordinate{ 2, 1 });

    Set s3;
    s3.add(GeoCoordinate{ 1, 2 });
    s3.add(GeoCoordinate{ 1, 5 });
    s3.add(GeoCoordinate{ 2, 1 });
    s3.add(GeoCoordinate{ 3, 0 });

    ASSERT_EQ(s1 == s2, true);
    ASSERT_EQ(s1 == s3, true);
}

TEST(Test, t13) {
    Set s;
    const int N = 1000;

    for (int i = 0; i < N; ++i) {
        int k = (i * 7) % N;
        ASSERT_EQ(s.add(GeoCoordinate{ double(k), double(k * 2) }), true);
    }
    ASSERT_EQ(s.size(), (std::size_t)N);

    for (int i = 0; i < N; ++i)
        ASSERT_EQ(s.add(GeoCoordinate{ double(i), double(i * 2) }), false);
    ASSERT_EQ(s.size(), (std::size_t)N);

    for (int i = 0; i < N; ++i) {
        ASSERT_EQ(s.contains(GeoCoordinate{ double(i), double(i * 2) }), true);
        ASSERT_EQ(s.contains(GeoCoordinate{ double(i), double(i * 2 + 1) }), false);
    }

    for (int i = 0; i < N; i += 2)
        ASSERT_EQ(s.remove(GeoCoordinate{ double(i), double(i * 2) }), true);
    ASSERT_EQ(s.size(), (std::size_t)(N / 2));
}