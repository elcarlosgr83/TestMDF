#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Interfaz que queremos simular
class Foo {
public:
    virtual ~Foo() = default;
    virtual int DoSomething(int x) = 0;
};

// Mock de la interfaz usando gMock
class MockFoo : public Foo {
public:
    MOCK_METHOD(int, DoSomething, (int x), (override));
};

// Test con gMock
TEST(GMockSanityTest, CanMockMethod) {
    MockFoo mock;

    // Configuramos expectativa: se llamará con 5 y devolverá 10
    EXPECT_CALL(mock, DoSomething(5))
        .Times(1)
        .WillOnce(::testing::Return(10));

    // Ejecutamos y verificamos
    int result = mock.DoSomething(5);
    EXPECT_EQ(result, 10);
}
