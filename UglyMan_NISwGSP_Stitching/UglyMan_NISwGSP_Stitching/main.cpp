//
//  main.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include "NISwGSP_Stitching.h"
#include "TimeCalculator.h"
#include <iostream>

#include "params.hpp"

using namespace std;

int main(int argc, const char *argv[]) {

    ProgramParams params;

    if (parse_cmd_args(argc, argv, params) != 0) {
        return -1;
    }

    if (params.img_names.size() == 0) {
        printError("we need images to process");
        return -1;
    } else if (params.img_names.size() == 1) {
        // TODO: need only warp the image
        return 0;
    }

    Eigen::initParallel(); /* remember to turn off "Hardware Multi-Threading */
    cout << "nThreads = " << Eigen::nbThreads() << endl;

    TimeCalculator timer;

    MultiImages multi_images(params, LINES_FILTER_WIDTH, LINES_FILTER_LENGTH);

    timer.start();
    NISwGSP_Stitching niswgsp(multi_images);

    niswgsp.setWeightToAlignmentTerm(1);
    niswgsp.setWeightToLocalSimilarityTerm(0.75);
    niswgsp.setWeightToGlobalSimilarityTerm(6, 20, params.rotation_method);

    niswgsp.writeImage(niswgsp.solve(params.blend),
                       BLENDING_METHODS_NAME[params.blend]);
    timer.end("[NISwGSP] " + multi_images.parameter.file_name);
    return 0;
}
