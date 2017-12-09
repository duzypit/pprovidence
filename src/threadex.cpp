#include <thread>
#include <iostream>
//https://rafalcieslak.wordpress.com/2014/05/16/c11-stdthreads-managed-by-a-designated-class/
class MyClass{
public:
    /* Explicitly using the default constructor to
     * underline the fact that it does get called */
    MyClass() : the_thread() {}
    ~MyClass(){
        stop_thread = true;
        if(the_thread.joinable()) the_thread.join();
    }
    void Start(){
        // This will start the thread. Notice move semantics!
        std::cout << "Starting the thread" << std::endl;
        the_thread = std::thread(&MyClass::ThreadMain,this);
    }
private:
    void ThreadMain(){
        while(!stop_thread){
            // Do something useful, e.g:
            std::this_thread::sleep_for( std::chrono::seconds(3) );
            std::cout<< "It works!" <<std::endl;
        }
    }

    bool stop_thread = false;
    std::thread the_thread;
    /****/
};

int main(){
    MyClass a;
    a.Start();
    return 0;
}
