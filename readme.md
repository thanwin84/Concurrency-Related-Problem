# Some important topics to know to solve concurency problem in c++

## Unique Lock
**std::unique_lock** is used to temporarily own a mutex for the duration of a scope. The purpose of using a **std::unique_lock** is to provide a more flexible and safer way of acquiring and releasing a mutex compared to using a raw **std::mutex**.

The std::unique_lock provides several useful features such as:

- Locking and unlocking the mutex in a more flexible way than with a raw mutex, as it can be locked and unlocked multiple times within the same scope.
- Providing a way to lock the mutex conditionally, so that the lock is only acquired if a certain condition is met.
- Providing a way to transfer ownership of the lock to another std::unique_lock object.
- Providing the ability to lock the mutex in a scope-based manner, so that the lock is automatically released when the std::unique_lock object goes out of scope.
## How to use conditional Variable ?
Condition variable is used for two purpose
1. notify other threads
2. wait for some condition

Condional variable allows running thred to wait on some condition and once the conditons are met the waiting thread is notified using 
+ **notify_one()**
+ **notify_all()**

You need mutex to use conditional variable if some thread want to wait on some condition then it has to do these things
+ aquire the mutex lock using **std::unique_lock<mutex> lock(m1)**
+ execute wait, wait_for, wait_until. the wait operation automatically release the mutex and suspend the execution of the thread.
+ When the condional variable is notified, the thread is awakened and resume waking if the wake up was spurious
  
```
#include <iostream>
#include<thread>
#include<mutex>

using namespace std;
// a mutex to synchronize access to share variable
std::mutex m;
// A condition variable to wait for a condition to be met (i.e. `ready` to become `true`)
std::condition_variable cond;
bool ready = false;
void print_data() {
	// Acquire the mutex to protect access to `ready`
	std::unique_lock<std::mutex> lock(m);
	// Wait for the condition variable to be notified
	cond.wait(lock, []() {return ready ? true : false;});
	// Now that the condition is met, we can print the numbers 0 to 5
	for (int i = 0; i <= 5; i++) {
		cout << i << endl;
	}
}
void set_ready() {
	std::unique_lock<std::mutex> lock(m);
	ready = true;
	// Notify the condition variable that the condition has been met
	cond.notify_one();
}
int main() {
	std::thread t1(print_data);
	std::thread t2(set_ready);
	t1.join();
	t2.join();
	return 0;
}

 ```
In this code, two threads are created, **t1** and **t2**. The first thread, **t1**, waits for a condition to be met (i.e. the ready flag to become true) by calling the wait method on the condition_variable cv. The second thread, **t2**, sets the ready flag to true and notifies the condition_variable that the condition has been met.

The unique_lock class is used to protect access to the shared **ready** flag, and to ensure that the lock is automatically released when the scope of the lock ends. The wait method is called with the lock as its argument, and the lock is automatically released while the thread is waiting for the condition to be met. When the condition is met and the **notify_one** method is called, the wait method returns, and the lock is automatically re-acquired.

Another way to write cv.wait is to wrap it in a while loop. Wrapping the **cv.wait()** function in a while loop ensures that the thread will continue to wait until the condition is actually met. This is called [spurious wake up](https://www.justsoftwaresolutions.co.uk/threading/condition-variable-spurious-wakes.html)
```
	while (!ready) {
		cond.wait(lock);
	}
```

