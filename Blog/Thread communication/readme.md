# Thread communication (very basic i suppose?)

Here's my understanding, could be wrong...

`std::unique_lock`: create a lock,and lock it. All done upon creation.
`std::condition_variable::wait`: temporary unlocks the lock, and wait until notified. When notified, it will lock the lock again.

```c++
void generateNumbers(std::queue<int> & numbers, std::condition_variable & cv, std::mutex & m, std::atomic<bool> & workdone)
{
    while(!workdone.load())
    {
        std::unique_lock<std::mutex> lk(m);
        int rndNum = rand() % 100;
        numbers.push(rndNum);
        producer_count++;
        cv.notify_one(); // Notify worker
        cv.wait(lk); // Wait for worker to complete
     }
}

void work(std::queue<int> & numbers, std::condition_variable & cv, std::mutex & m, std::atomic<bool> & workdone)
{
    while(!workdone.load() or !numbers.empty())
    {
        std::unique_lock<std::mutex> lk(m);
        cv.notify_one(); // Notify generator (placed here to avoid waiting for the lock)
        if (numbers.empty())
            cv.wait(lk); // Wait for the generator to complete
        if (numbers.empty())
            continue;
        std::cout << numbers.front() << ' ';
        numbers.pop();
        consumer_count++;
     }
}
```

For the code above, if `generateNumbers` thread runs first, it will acquire the lock, make a number, put the number to queue, release the lock and wait for notification.
Then, `work` thread acquires the lock (after `generateNumbers` release it), notify `generateNumbers` to acquire the lock (the next link of code after `cv.wait`) when it release it, pop the number from the queue and print it, and finally release the lock (when a while loop finishes or somehow it reaches its `cv.wait`).
