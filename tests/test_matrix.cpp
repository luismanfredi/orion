#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <orion/matrix.hpp>

TEST_CASE("Matrix initialization and basic properties", "[matrix][constructors]") {
  orion::Matrix A(2, 2, 1);
  orion::Matrix B{{1, 2}, {3, 4}};

  SECTION("Verify Matrix size") {
    REQUIRE(A.rows() == 2);
    REQUIRE(A.cols() == 2);

    REQUIRE(B.rows() == 2);
    REQUIRE(B.cols() == 2);
  }

  SECTION("Verify Matrix values") {
    orion::Matrix C{{1, 1}, {1, 1}};
    orion::Matrix D{{1, 2}, {3, 4}};

    REQUIRE(A == C);
    REQUIRE(B == D);
  }

  SECTION("Verify rows with different size") {
    REQUIRE_THROWS_AS((orion::Matrix{{1, 2}, {1}}), orion::InvalidMatrixDimensions);
    REQUIRE_THROWS_AS((orion::Matrix{{1, 2}, {1, 2}, {1, 2, 3}}), orion::InvalidMatrixDimensions);
  }

  SECTION("Verify default value in matrix initialization") {
    orion::Matrix C(2, 2);
    orion::Matrix D{{0.0, 0.0}, {0.0, 0.0}};

    REQUIRE(C == D);
  }
}

TEST_CASE("Matrix element access", "[matrix][access]") {
  orion::Matrix A{{1, 2}, {3, 4}};

  SECTION("Verify access operator '()'") {
    REQUIRE(A(0, 0) == 1);
    REQUIRE(A(0, 1) == 2);
    REQUIRE(A(1, 0) == 3);
    REQUIRE(A(1, 1) == 4);
  }

  SECTION("Verify get operator '()'") {
    A(0, 0) = 0;
    A(0, 1) = 0;
    A(1, 0) = 0;
    A(1, 1) = 0;

    orion::Matrix B(2, 2);

    REQUIRE(A == B);
  }

  SECTION("Operator '()' must throw exception") {
    REQUIRE_THROWS_AS(A(3, 3), orion::PositionNotInMatrix);
    REQUIRE_THROWS_AS(A(0, 3), orion::PositionNotInMatrix);
    REQUIRE_THROWS_AS(A(3, 0), orion::PositionNotInMatrix);
  }
}

TEST_CASE("Matrix fills methods", "[matrix][fill]") {
  orion::Matrix A{{1, 2}, {3, 4}};
  orion::Matrix B{{5, 6}, {7, 8}};

  SECTION("Verify fill and fillRange methods") {
    orion::Matrix C(2, 2, 5);
    orion::Matrix D{{0, 2}, {4, 6}};

    A.fill(5);

    REQUIRE(A.rows() == 2);
    REQUIRE(A.cols() == 2);
    REQUIRE(A == C);

    B.fillRange(0, 2);
    REQUIRE(B.rows() == 2);
    REQUIRE(B.cols() == 2);
    REQUIRE(B == D);
  }
}

TEST_CASE("Matrix arithmetic operations", "[matrix][math]") {
  orion::Matrix A{{1, 2}, {3, 4}};
  orion::Matrix B{{5, 6}, {7, 8}};
  orion::Matrix K(5, 5);

  SECTION("Verify sum (+) operator") {
    orion::Matrix C{{6, 8}, {10, 12}};

    REQUIRE((A + B) == C);
    REQUIRE(C.rows() == 2);
    REQUIRE(C.cols() == 2);
    REQUIRE_THROWS_AS(A + K, orion::InvalidMatrixDimensions);
  }

  SECTION("Verify subtraction (-) operator") {
    orion::Matrix C{{-4, -4}, {-4, -4}};

    REQUIRE((A - B) == C);
    REQUIRE(C.rows() == 2);
    REQUIRE(C.cols() == 2);
    REQUIRE_THROWS_AS(A - K, orion::InvalidMatrixDimensions);
  }

  SECTION("Verify multiply (*) operator") {
    orion::Matrix C{{19, 22}, {43, 50}};
    orion::Matrix D{{2, 4}, {6, 8}};

    REQUIRE((A * B) == C);
    REQUIRE(C.rows() == 2);
    REQUIRE(C.cols() == 2);
    REQUIRE_THROWS_AS(A * K, orion::InvalidMatrixDimensions);

    REQUIRE((A * 2) == D);
    REQUIRE(D.rows() == 2);
    REQUIRE(D.cols() == 2);
  }

  SECTION("Verify (*) with different matrices sizes") {
    orion::Matrix C(2, 3, 1);
    orion::Matrix D(3, 2, 1);
    orion::Matrix E(2, 2, 3);

    REQUIRE(C * D == E);
  }
}

TEST_CASE("Test Random methods", "[matrix][random]") {
  SECTION("Verify fillRandom() method") {
    orion::Matrix A{{1, 2}, {3, 4}};
    orion::Matrix B{{1, 2}, {3, 4}};

    A.fillRandom();
    REQUIRE(A(0, 0) >= 0);
    REQUIRE(A(0, 0) <= 1);
    REQUIRE(A(0, 1) >= 0);
    REQUIRE(A(0, 1) <= 1);
    REQUIRE(A(1, 0) >= 0);
    REQUIRE(A(1, 0) <= 1);
    REQUIRE(A(1, 1) >= 0);
    REQUIRE(A(1, 1) <= 1);
    REQUIRE(A.rows() == 2);
    REQUIRE(A.cols() == 2);
    REQUIRE(A != B);
  }

  SECTION("Verify random() factory function") {
    orion::Matrix A = orion::Matrix::random(2, 2);

    REQUIRE(A(0, 0) >= 0);
    REQUIRE(A(0, 0) <= 1);
    REQUIRE(A(0, 1) >= 0);
    REQUIRE(A(0, 1) <= 1);
    REQUIRE(A(1, 0) >= 0);
    REQUIRE(A(1, 0) <= 1);
    REQUIRE(A(1, 1) >= 0);
    REQUIRE(A(1, 1) <= 1);
    REQUIRE(A.rows() == 2);
    REQUIRE(A.cols() == 2);
  }
}

TEST_CASE("Other Matrix methods", "[matrix][other]") {
  orion::Matrix A{{1, 2}, {3, 4}};

  SECTION("Verify transpose() method") {
    orion::Matrix B{{1, 3}, {2, 4}};

    REQUIRE(A.transpose() == B);

    orion::Matrix C{{1, 2, 3}, {4, 5, 6}};
    orion::Matrix D{{1, 4}, {2, 5}, {3, 6}};

    REQUIRE(C.transpose() == D);
  }

  SECTION("Verify setIdentity() method") {
    orion::Matrix B{{1.0, 0.0}, {0.0, 1.0}};

    A.setIdentity();
    REQUIRE(A == B);
  }

  SECTION("Verify setZeros() method") {
    orion::Matrix B(2, 2);

    A.setZeros();
    REQUIRE(A == B);
  }

  SECTION("Verify setOnes() method") {
    orion::Matrix B(2, 2, 1.0);

    A.setOnes();
    REQUIRE(A == B);
  }
}

TEST_CASE("Matrix factory functions", "[matrix][factory]") {
  SECTION("Verify zeros() fuction") {
    orion::Matrix A = orion::Matrix::zeros(2, 2);
    orion::Matrix B{{0.0, 0.0}, {0.0, 0.0}};

    REQUIRE(A == B);
  }

  SECTION("Verify ones() fuction") {
    orion::Matrix A = orion::Matrix::ones(2, 2);
    orion::Matrix B{{1.0, 1.0}, {1.0, 1.0}};

    REQUIRE(A == B);
  }

  SECTION("Verify identity() fuction") {
    orion::Matrix A = orion::Matrix::identity(2);
    orion::Matrix B{{1.0, 0.0}, {0.0, 1.0}};

    REQUIRE(A == B);
  }
}