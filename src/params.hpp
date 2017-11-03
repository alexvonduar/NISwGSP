#ifndef _PARAMS_H_
#define _PARAMS_H_

#include <iostream>
#include <string>
#include <vector>

#include "Configure.h"

typedef struct _ProgramParams {
    GLOBAL_ROTATION_METHODS rotation_method;
    bool debug;
    BLENDING_METHODS blend;
    bool default_name;
    std::string output_name;
    std::vector<std::string> img_names;
    _ProgramParams()
        : rotation_method(GLOBAL_ROTATION_3D_METHOD), debug(false),
          blend(BLEND_LINEAR), default_name(true), output_name("result.jpg"){};
} ProgramParams;

static void printUsage() {
    std::cout << "Rotation model images stitcher.\n\n"
                 "PROGRAM_NAME img1 img2 [...imgN] [flags]\n\n"
                 "Flags:\n"
                 "  --transform (2|3)\n"
                 "      Use 2D or 3D transform. The default is "
                 "3D.\n"
                 "  --blend (average|linear)\n"
                 "      Blending method. The default is 'linear'.\n"
                 "  --output <result_img>\n"
                 "      The default is 'result.jpg'.\n"
                 "  --debug (on|off) \n"
                 "      default is off.\n";
}

static int parse_cmd_args(const int &argc, const char *argv[],
                          ProgramParams &params) {
    if (argc < 2) {
        printUsage();
        return -1;
    }

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "/?") {
            printUsage();
            return -1;
        } else if (std::string(argv[i]) == "--transform") {
            if (std::string(argv[i + 1]) == "2") {
                params.rotation_method = GLOBAL_ROTATION_2D_METHOD;
            } else if (std::string(argv[i + 1]) == "3") {
                params.rotation_method = GLOBAL_ROTATION_3D_METHOD;
            } else {
                std::cout << "Bad --transform flag value\n";
                return -1;
            }
            i++;
        } else if (std::string(argv[i]) == "--blend") {
            if (std::string(argv[i + 1]) == "average") {
                params.blend = BLEND_AVERAGE;
            } else if (std::string(argv[i + 1]) == "linear") {
                params.blend = BLEND_LINEAR;
            } else {
                std::cout << "Bad --blend flag value\n";
                return -1;
            }
            i++;
        } else if (std::string(argv[i]) == "--debug") {
            if (std::string(argv[i + 1]) == "on") {
                params.debug = true;
            } else if (std::string(argv[i + 1]) == "off") {
                params.debug = false;
            } else {
                std::cout << "Bad --debug flag value\n";
                return -1;
            }
            i++;
        } else if (std::string(argv[i]) == "--output") {
            params.output_name = argv[i + 1];
            params.default_name = false;
            i++;
        } else {
            params.img_names.push_back(argv[i]);
        }
    }
    return 0;
}

#endif //_PARAMS_H_
