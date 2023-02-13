// leetcode: 1114
class Foo {
    std::mutex m;
    std::condition_variable cond;
    int turn;
public:
    Foo() {
        turn = 0;
    }
    bool check(int t){
        if (turn == t){
            return true;
        }
        else {
            return false;
        }
    }
    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        turn = 1;
        cond.notify_all();
        
    }
    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        std::unique_lock<mutex> ul(m);
        cond.wait(ul, [this](){return turn == 1 ? true: false;});
        printSecond();
        turn = 2;
        cond.notify_all();
        
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        std::unique_lock<mutex> ul(m);
        cond.wait(ul, [this](){return turn == 2 ? true: false;});
        printThird();
    }
};

// another way to write 

class Foo {
    std::mutex m;
    std::condition_variable cond;
    int turn;
public:
    Foo() {
        turn = 0;
    }
    bool check(int t){
        if (turn == t){
            return true;
        }
        else {
            return false;
        }
    }
    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        turn = 1;
        cond.notify_all();
        
    }
    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        std::unique_lock<mutex> ul(m);
        while(turn != 1){
            cond.wait(ul);
        }
        printSecond();
        turn = 2;
        cond.notify_all();
        
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        std::unique_lock<mutex> ul(m);
        while(turn != 2){
            cond.wait(ul);
        }
        printThird();
    }
};
