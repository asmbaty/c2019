#include <iostream>
#include <functional>
#include <list>

class Observer
{
public:
    using Callback = std::function<void()>;
    using CallbackID = std::list<Callback>::iterator;
public:
    CallbackID Subscribe(Callback callback)
    {
        callbacks.emplace_back(callback);
        return --callbacks.end();
    }
    void Unsubscribe(CallbackID id)
    {
        callbacks.erase(id);
    }

    void NotifyAll()
    {
        for(auto const& f : callbacks) {
            f();
        }
    }
private:
    std::list<Callback> callbacks;
};

int main()
{
    Observer observer;

    auto id1 = observer.Subscribe([](){
        std::cout << "Callback 1\n";
    });

    auto id2 = observer.Subscribe([](){
        std::cout << "Callback 2\n";
    });

    observer.NotifyAll();
    observer.Unsubscribe(id2);
    observer.NotifyAll();


    return 0;
}