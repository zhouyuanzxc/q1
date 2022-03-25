// adam.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
//#include <zmotion/zauxdll2.h>
#include "ZMCard.h"
#include <Windows.h>
#include "cinifile.h"
bool isNeedLoop = true;//连续运动
float dpos = 0;

void RunLoop(bool isLoop, ZMCard* pZMCard);

#define FilePath "E:\\work_cpp\\adam\\sysconfig.ini"



int main()
{



    std::cout << "Hello World!\n";
    //ZMCard* pZMCard;
    //pZMCard = new ZMCard(1);
    CIniFile inifile;

    if (inifile.isiniExists(FilePath))
    {
        //save
    }
    else {
        //read
    }
    //DEVSpeedSet devSpeedInfoSet;
    //pZMCard->setDEVSpeedSet(&devSpeedInfoSet);







    //pZMCard->getAxisPos(0, dpos);
    //cout << dpos << endl;

    ////pZMCard->

    system("pause");
}


void RunLoop(bool isLoop, ZMCard* pZMCard) {

    if (!isLoop) //非连续跑轨迹
    {
    
    }
    else {
        std::thread _th([&]()->void {
            while (isNeedLoop) {
                pZMCard->getAxisPos(0, dpos);
                cout << "dpos->" << dpos << endl;;
            }
        });
        _th.join();
    
    }

}
