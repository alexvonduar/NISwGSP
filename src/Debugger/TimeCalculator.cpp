//
//  TimeCalculator.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include "TimeCalculator.h"
#include "opencv2/opencv.hpp"

void TimeCalculator::start() {
    begin_time = cv::getTickCount();
}
int64_t TimeCalculator::end(const string output) const {
    int64_t result = cv::getTickCount() - begin_time;
    if(output.empty() == false) {
        printf("[TIME] %ds : %s\n", (int)(result / 1000000), output.c_str());
    }
    return result;
}

