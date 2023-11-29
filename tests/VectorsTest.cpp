#include <drn/vec.hpp>
#include <drn/Testing.hpp>

using namespace drn;

std::string drn::TestFileName{"Vectors"}; 

std::string Vector2IntCreation() {
    Vec2<int> TestVector{3, 4};

    return TestVector.toString();
}

std::string Vec2Adding() {
    Vec2<int> Vector1{1, 1};
    Vec2<int> Vector2{3, 2};

    return (Vector1 + Vector2).toString();
}

std::string Vec2Subtracting() {
    Vec2<int> Vector1{3, 2};
    Vec2<int> Vector2{1, 1};

    return (Vector1 - Vector2).toString();
}

TestLabel Vec2Label("2D Vector Tests");
Test<std::string> Test1("Create Vector <3, 4>", Vector2IntCreation, "<3, 4>");
Test<std::string> Test2("Running <3, 2> + <1, 1> = <4, 3>", Vec2Adding, "<4, 3>");
Test<std::string> Test3("Running <3, 2> - <1, 1> = <2, 1>", Vec2Subtracting, "<2, 1>");