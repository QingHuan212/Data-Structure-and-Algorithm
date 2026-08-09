#include <iostream>
using namespace std;

class Clock{
public:
    Clock(){
        hour = 0;
        minute = 0;
        second = 0;
    }
    Clock(int h, int m, int s){
        setHour(h);
        setMinute(m);
        setSecond(s);
    }
    void setHour(int h){
        hour = ((h >= 0 && h<=23) ? h : 0);
    }
    void setMinute(int m){
        minute = ((m >= 0 && m<=59) ? m : 0);
    }
    void setSecond(int s){
        second = ((s >= 0 && s<=59) ? s : 0);
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
    int hour,minute,second;
};

int main(){
    Clock c1;
    cout << c1.getHour() << ":" << c1.getMinute() << ":" << c1.getSecond() << endl;
    c1.setHour(23);
    c1.setMinute(46);
    c1.setSecond(61);
    cout << c1.getHour() << ":" << c1.getMinute() << ":" << c1.getSecond() << endl;

    Clock c2(22,22,22);
    cout << c2.getHour() << ":" << c2.getMinute() << ":" << c2.getSecond() << endl;

    //Clock* c3 = NULL; //空指针
    Clock* c3 = &c1;
    cout << c3->getHour() << ":" << c3->getMinute() << ":" << c3->getSecond() << endl;
    c3->setHour(5);
    cout << c1.getHour() << ":" << c1.getMinute() << ":" << c1.getSecond() << endl;
    cout << c3->getHour() << ":" << c3->getMinute() << ":" << c3->getSecond() << endl;

    Clock* c4 = new Clock(14,14,14);
    cout << c4->getHour() << ":" << c4->getMinute() << ":" << c4->getSecond() << endl;.

    // 回顾一下 break 和 continue

    return 0;
}
