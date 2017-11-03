SRC_DIR=src

LIBS=-L/home/alex/work/vlfeat/bin/glnxa64

INCLUDES=-I${SRC_DIR}/Stitching \
	 -I${SRC_DIR}/Mesh \
	 -I${SRC_DIR}/Feature \
	 -I${SRC_DIR}/Debugger \
	 -I${SRC_DIR}/Util \
	 -I${SRC_DIR}


SRCS=${SRC_DIR}/main.cpp \
     ${SRC_DIR}/Stitching/NISwGSP_Stitching.cpp \
     ${SRC_DIR}/Mesh/MeshOptimization.cpp \
     ${SRC_DIR}/Mesh/MeshGrid.cpp \
     ${SRC_DIR}/Mesh/Mesh2D.cpp \
     ${SRC_DIR}/Feature/MultiImages.cpp \
     ${SRC_DIR}/Feature/ImageData.cpp \
     ${SRC_DIR}/Feature/FeatureController.cpp \
     ${SRC_DIR}/Stitching/APAP_Stitching.cpp \
     ${SRC_DIR}/Stitching/Parameter.cpp \
     ${SRC_DIR}/Util/Statistics.cpp \
     ${SRC_DIR}/Util/Blending.cpp \
     ${SRC_DIR}/Util/InputParser.cpp \
     ${SRC_DIR}/Util/Transform.cpp \
     ${SRC_DIR}/Debugger/ImageDebugger.cpp \
     ${SRC_DIR}/Debugger/ErrorController.cpp \
     ${SRC_DIR}/Debugger/TimeCalculator.cpp \
     ${SRC_DIR}/Debugger/ColorMap.cpp \


all: ${SRCS}
	g++ -g -O0 -fpermissive ${INCLUDES} -o test $^ ${LIBS} -lvl `pkg-config --cflags --libs opencv`
