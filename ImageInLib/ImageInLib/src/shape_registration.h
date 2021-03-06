#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#ifndef SHAPE_REGISTRATION
#define SHAPE_REGISTRATION
	//==============================================================================
	/*
	* Header file to contain general functions, variables, structs
	* These can be used in different shape registration algorithms
	* Avoids redefinitions elsewhere
	*/
	//==============================================================================
	// Includes
#include "common_functions.h"
#include "generate_3d_shapes.h"
#include "transformations.h"
#include "data_initialization.h"
#include "data_storage.h"
#include "fast_marching.h"
#include "distance_function.h"
#include "registration_params.h"
#include "edgedetection.h"
//==============================================================================
// TypeDefs
//==============================================================================
// Uniform or Directional Scale and Rotation components
#ifndef UNIFORM
#define UNIFORM
#endif // !UNIFORM
#undef UNIFORM

#ifndef DIRECTIONAL
#define DIRECTIONAL
#endif // !DIRECTIONAL
//#undef DIRECTIONAL
//==============================================================================
// Use Narrow band for calculations
#ifndef USE_NARROWBAND
#define USE_NARROWBAND
#endif // !USE_NARROWBAND

//#undef USE_NARROWBAND
//==============================================================================
// Narrow band
#define NDelta 10
//==============================================================================
// Variables for OpenMp
#define PAD 16 // assumes 256kb l1 cache
#define NUM_THREADS 4
//==============================================================================
// Prototypes
// Run the Shape Registration Function
/*
* dPtr - destination, sPtr - source, resultPtr - resulting data after applying registration results
* zDim, xDim, yDim - are the dimension of 3D object
* tol - accepted level for minimized energy, step_size - learning rate for the GD method
* gDescentMethod - choice of 1 for Simple, 2 for Stochastic GD method
* pathResults - path to where a vtk file for the resulting registered data
*/
	void run_registration(dataType **fixedData, dataType **movingData, dataType **resultPtr, size_t zDim, size_t xDim, size_t yDim, Registration_Params params, Optimization_Method gdescentMethod);
	//==============================================================================
	ClipBox findClipBoxSingle(dataType ** Source, size_t imageHeight, size_t imageLength, size_t imageWidth);
	ClipBox findClipBoxTwo(dataType ** destination, dataType ** source, size_t imageHeight, size_t imageLength, size_t imageWidth);
	void fillNarrowBandArea(dataType ** sourceDist, dataType ** bandContainer, size_t imageHeight, size_t imageLength, size_t imageWidth, dataType insideValue, dataType outsideValue);
	//==============================================================================
	// Cla. if the distance is within delta
	inline int NFunction(dataType val1, dataType val2, dataType delta);
	inline int NFunctionBinary(dataType v1, dataType v2, dataType delta);
	int NFunctionOne(dataType v1, dataType delta);
	// Calc. the distance differences
	dataType energyFunction(dataType ** destination, dataType **distTrans, size_t imageHeight, size_t imageLength, size_t imageWidth, dataType h);
	dataType energyFunctionClip(dataType ** destination, dataType **distTrans, ClipBox coord, size_t imageLength);
	dataType energyFunctionClipBandArea(dataType ** destination, dataType ** distTrans, ClipBox coord, size_t imageLength, dataType ** fixedNBandPtr, dataType ** movingNBandPtr, dataType imageForeground);
	// Calc. Finite difference X direction
	inline dataType finiteDifX(dataType ** distPtr, dataType h, size_t x, size_t k, size_t i, size_t imageLength);
	// Calc. Finite difference Y direction
	inline dataType finiteDifY(dataType ** distPtr, dataType h, size_t k, size_t i, size_t j, size_t imageLength, size_t imageWidth);
	// Calc. Finite difference Z direction
	inline dataType finiteDifZ(dataType ** distPtr, dataType h, size_t x, size_t k, size_t i, size_t imageLength, size_t imageHeight);
	// Calc. and return the gradient descent components
	Affine_Parameter gradientComponents(dataType **destPtr, dataType **distTrans, dataType h, Affine_Parameter *params, size_t imageHeight, size_t imageLength, size_t imageWidth);
	Affine_Parameter gradientComponentsClip(dataType ** destPtr, dataType ** distTrans, dataType h, Affine_Parameter * params, size_t imageHeight, size_t imageLength, size_t imageWidth, ClipBox bestFit);
	// Calc the transformation parameters from Registration of two images using Simple GD method
	Affine_Parameter registration3D(dataType ** destination, dataType ** source, Affine_Parameter initTransform, dataType steps, dataType tol, size_t imageHeight, size_t imageLength, size_t imageWidth, dataType centroid[3], Registration_Params params);
	// Cals Registration using Stochastic GD method
	Affine_Parameter registrationStochastic3D(dataType ** destination, dataType ** source, Affine_Parameter initTransform, dataType steps, dataType tol, size_t imageHeight, size_t imageLength, size_t imageWidth, dataType centroid[3], Registration_Params params);
	//==============================================================================
	//==============================================================================
	ClipBox findClipBoxSingle(dataType ** Source, size_t imageHeight, size_t imageLength, size_t imageWidth);
	ClipBox findClipBoxTwo(dataType ** destination, dataType ** source, size_t imageHeight, size_t imageLength, size_t imageWidth);
	void fillNarrowBandArea(dataType ** sourceDist, dataType ** bandContainer, size_t imageHeight, size_t imageLength, size_t imageWidth, dataType insideValue, dataType outsideValue);
	//==============================================================================
	void transformClip(ClipBox *bestfit, Point3D translation, Point3D scaling, Point3D rotation, dataType centroid[3], size_t imageHeight, size_t imageLength, size_t imageWidth);
	//==============================================================================
#endif // !SHAPE_REGISTRATION

#ifdef __cplusplus
}
#endif