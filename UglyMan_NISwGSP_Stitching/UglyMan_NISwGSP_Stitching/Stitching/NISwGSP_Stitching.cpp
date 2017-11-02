//
//  NISwGSP_Stitching.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include "NISwGSP_Stitching.h"

NISwGSP_Stitching::NISwGSP_Stitching(MultiImages & _multi_images) : MeshOptimization(_multi_images) {
    
}

void NISwGSP_Stitching::setWeightToAlignmentTerm(const double _weight) {
    MeshOptimization::setWeightToAlignmentTerm(_weight);
}

void NISwGSP_Stitching::setWeightToLocalSimilarityTerm(const double _weight) {
    MeshOptimization::setWeightToLocalSimilarityTerm(_weight);
}

void NISwGSP_Stitching::setWeightToGlobalSimilarityTerm(const double _weight_beta,
                                                        const double _weight_gamma,
                                                        const GLOBAL_ROTATION_METHODS _global_rotation_method) {
    MeshOptimization::setWeightToGlobalSimilarityTerm(_weight_beta, _weight_gamma, _global_rotation_method);
}

Mat NISwGSP_Stitching::solve(const BLENDING_METHODS & _blend_method) {
    const MultiImages & multi_images = getMultiImages();
    
    vector<Triplet<double> > triplets;
    vector<pair<int, double> > b_vector;
    
    reserveData(triplets, b_vector, DIMENSION_2D);
    
    triplets.emplace_back(0, 0, STRONG_CONSTRAINT);
    triplets.emplace_back(1, 1, STRONG_CONSTRAINT);
    b_vector.emplace_back(0,    STRONG_CONSTRAINT);
    b_vector.emplace_back(1,    STRONG_CONSTRAINT);
    
    prepareAlignmentTerm(triplets);
    prepareSimilarityTerm(triplets, b_vector);
    
    vector<vector<Point2> > original_vertices;

    original_vertices = getImageVerticesBySolving(triplets, b_vector);
    
    Size2 target_size = normalizeVertices(original_vertices);
    
    Mat result = multi_images.textureMapping(original_vertices, target_size, _blend_method);

    if (multi_images.parameter.debug_dir.length()) {
        multi_images.writeResultWithMesh(
            result, original_vertices,
            "-[NISwGSP]" +
                GLOBAL_ROTATION_METHODS_NAME[getGlobalRotationMethod()] +
                BLENDING_METHODS_NAME[_blend_method] + "[Mesh]",
            false);
        multi_images.writeResultWithMesh(
            result, original_vertices,
            "-[NISwGSP]" +
                GLOBAL_ROTATION_METHODS_NAME[getGlobalRotationMethod()] +
                BLENDING_METHODS_NAME[_blend_method] + "[Border]",
            true);
    }

    return result;
}

void NISwGSP_Stitching::writeImage(const Mat & _image, const string _post_name) const {
    const MultiImages & multi_images = getMultiImages();
    const Parameter & parameter = multi_images.parameter;
    //string file_name = parameter.output_name;
    
    imwrite(parameter.output_dir + parameter.output_name, _image);
}