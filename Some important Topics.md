## Unique Lock
**std::unique_lock** is used to temporarily own a mutex for the duration of a scope. The purpose of using a **std::unique_lock** is to provide a more flexible and safer way of acquiring and releasing a mutex compared to using a raw **std::mutex**.

The std::unique_lock provides several useful features such as:

-Locking and unlocking the mutex in a more flexible way than with a raw mutex, as it can be locked and unlocked multiple times within the same scope.
-Providing a way to lock the mutex conditionally, so that the lock is only acquired if a certain condition is met.
-Providing a way to transfer ownership of the lock to another std::unique_lock object.
-Providing the ability to lock the mutex in a scope-based manner, so that the lock is automatically released when the std::unique_lock object goes out of scope.
