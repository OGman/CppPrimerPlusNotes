This repository is used for recording my C++ primer excises

第六章 函数
    函数是命名了的代码块
6.1 函数基础
    调用运算符()
    调用函数主要完成两件事：用参数列表初始化形参，将控制权交给被调函数
    函数return语句完成两件事：返回值，返回控制权
    
    实参的求值顺序是未定义的行为
    传入参数时会发生隐式的类型转换

    函数的返回值不能是数组类型和函数类型，但可以是指向数组的指针或指向函数的指针

6.1.1 局部对象
    形参与语句块内定义的变量是局部变量
    只存在于块执行期间的对象称为自动对象，未指定初始值时执行默认初始化
    局部静态变量直到程序终止时才被销毁，未指定初值时执行值初始化

6.1.2 函数声明
    函数建议在头文件中声明，在源文件中定义
    变量也一样

第七章 类

7.2 访问控制与封装

