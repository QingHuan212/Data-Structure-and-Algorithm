#include <iostream>
using namespace std;

class Clock{
public:
    Clock(){
        hour = 1;
        minute = 1;
        second = 1;
    }
    Clock(int h, int m, int s){
        setHour(h);
        setMinute(m);
        setSecond(s);
    }
    void setHour(int h){
        hour = ((h >=0 && h<=23)? h : 1);
    }
    void setMinute(int m){
        minute = ((m >=0 && m<=59)? m : 1);
    }
    void setSecond(int s){
        second = ((s >=0 && s<=59)? s : 1);
    }
    int getHour(){
        return hour;
    }
    int getMinute(){
        return minute;
    }
    int getSecond(){
        return second;
    }
private:
    int hour, minute, second;
};


int main(){
    Clock c1;
    cout << c1.getHour() << ":" << c1.getMinute() << ":" << c1.getSecond() << endl;
    c1.setHour(16);
    c1.setMinute(44);
    c1.setSecond(45);
    cout << c1.getHour() << ":" << c1.getMinute() << ":" << c1.getSecond() << endl;

    Clock c2(16,45,50);
    cout << c2.getHour() << ":" << c2.getMinute() << ":" << c2.getSecond() << endl;

    Clock* c3 = &c2;
    cout << c3->getHour() << ":" << c3->getMinute() << ":" << c3->getSecond() << endl;
    c3->setHour(20);
    cout << c3->getHour() << ":" << c3->getMinute() << ":" << c3->getSecond() << endl;
    cout << c2.getHour() << ":" << c2.getMinute() << ":" << c2.getSecond() << endl;

    Clock* c4 = new Clock(20,20,20);
    cout << c4->getHour() << ":" << c4->getMinute() << ":" << c4->getSecond() << endl;

    // 回顾一下 continue 和 break

    return 0;
}
