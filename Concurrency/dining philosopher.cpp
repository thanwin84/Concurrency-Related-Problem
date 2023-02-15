class Semaphore {
	std::mutex m;
	std::condition_variable cond;
	int count;
public:
    void setCount(int n){
        this->count = n;
    }
	void signal() {
		std::unique_lock<std::mutex> lock(m);
		count++;
		cond.notify_one();
	}
	void wait() {
		std::unique_lock<std::mutex> lock(m);
		if (count == 0) {
			cond.wait(lock);
		}
		count--;
	}
};
class DiningPhilosophers {
    Semaphore forks[5];
    std::mutex mtx;
public:
    DiningPhilosophers() {
        for (int i = 0; i < 5; i++){
            forks[i].setCount(1);
            
        }
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
                    int left_fork = philosopher;
                    int right_fork = (philosopher + 1) % 5;
                    std::lock_guard<std::mutex> lock(mtx);
                    forks[left_fork].wait();
                    forks[right_fork].wait();
                    pickLeftFork();
                    pickRightFork();
                    eat();
                    forks[left_fork].signal();
                    forks[right_fork].signal();
                    putLeftFork();
                    putRightFork();

    }
};
