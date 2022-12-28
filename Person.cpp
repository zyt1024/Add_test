#include<iostream>

class Person{
    public:
        Person(const std::string name = "", int age = 0):name_(name),age_(age){
            std::cout << " init " << std::endl;
        }
        ~Person(){
            std::cout << " destory person" << std::endl;
        }

        const std::string& getname() const {
            return this->name_;
        }
        int getaAge() const {
            return this->age_;
        }
    
    private:
        const std::string name_;
        int age_;
};

int main(){
    Person p;  

    extern int a;
    a = 1;
    a = 2;
    
    return 0;
}

/*
*当main函数执行完毕后会自动调用析构函数来销毁对象，因此我们在使用资源的时候吗，
*可以在构造函数中进行初始化,在析构函数中进行销毁。

RALL: RAII(Resource Acquisition is Initialization)，也称为“资源获取就是初始化”，
是c++等编程语言常用的管理资源、避免内存泄露的方法。它保证在任何情况下，使用对象时先构造对象，最后析构对象。
RAII的核心思想:
将资源或者状态与对象的生命周期绑定，通过C++的语言机制，实现资源和状态的安全管理,智能指针是RAII最好的例子.

*整个RAII过程我总结四个步骤：
    a.设计一个类封装资源

    b.在构造函数中初始化

    c.在析构函数中执行销毁操作

    d.使用时声明一个该对象的类
*
*
*
*/ 