#ifndef BBOX_H
#define BBOX_H
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include<stdio.h>

using namespace std;
namespace bbox{
    class black_box{
        public:
            void addToTrackingFile(string data);
            void cleanTrackingFile();
            string getTrackingFile();
        
    };
}

#endif 