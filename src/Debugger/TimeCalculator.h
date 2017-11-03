//
//  TimeCalculator.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#ifndef __UglyMan_Stitiching__TimeCalculator__
#define __UglyMan_Stitiching__TimeCalculator__

#include <iostream>
#include <string>
#include <stdio.h>
#include <inttypes.h>

using namespace::std;

class TimeCalculator {
public:
    void start();
    int64_t end(const string output) const;
private:
    int64_t begin_time;
};

#endif /* defined(__UglyMan_Stitiching__TimeCalculator__) */
