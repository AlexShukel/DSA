#include <iostream>

class A {
public:
    virtual void hello() const = 0;

    virtual ~A() = default;
};

class B : public A {
public:
    void hello() const override;
};

void B::hello() const {
    std::cout << "hello" << std::endl;
}

int main() {
    B b;
    b.hello();
    return 0;
}
