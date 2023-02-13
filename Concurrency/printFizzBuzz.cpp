class FizzBuzz {
private:
    int n;
    // a mutex to synchronize to share variable
    std::mutex mtx;
    // a condiational variable to wait for a condition to be met
    std::condition_variable cond;
    int curr;

public:
    FizzBuzz(int n) {
        this->n = n;
        curr = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(true){
            // acquire the mutex to protect access to share variable
            std::unique_lock<std::mutex> lock(mtx);
            // wait for the condition to be true
            // it's important to check if curr> n in lambda funcion to so that it doen't wait infinitetly
            cond.wait(lock, [this](){return curr > n || (curr % 3 == 0 && curr % 5 != 0);});
            if (curr > n){
                break;
            }
            printFizz();
            curr++;
            // notify other thread
            cond.notify_all();
        }
        
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(true){
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [this](){return curr > n || (curr % 5 == 0 && curr % 3 != 0);});
            if (curr > n){
                break;
            }
            printBuzz();
            curr++;
            cond.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(true){
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [this](){return curr > n || (curr % 3 == 0 && curr % 5 == 0);});
            if (curr > n){
                break;
            }
            printFizzBuzz();
            curr++;
            cond.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(true){
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [this](){return curr > n || (curr % 3 != 0 && curr % 5 != 0);});
            if (curr > n){
                break;
            }
            printNumber(curr);
            curr++;
            cond.notify_all();
        }
    }
};
