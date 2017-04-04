#include "FaceFinder.h"

//------------------------------------------------------------------------------------------//
//--------------------------------Constructor and destructor--------------------------------//
//------------------------------------------------------------------------------------------//

FaceFinder::FaceFinder() { }

FaceFinder::FaceFinder(std::string &cascadePath)
{
	pathToCascadeFace = cascadePath;

	//Get cascade face detector
	if (!faceCascade.load(pathToCascadeFace))
	{
		std::cout << "Error loading face cascade" << std::endl;
		return;
	}
}

FaceFinder::~FaceFinder()
{
}

//------------------------------------------------------------------------------------------//
//-----------------------------------Setters and getters------------------------------------//
//------------------------------------------------------------------------------------------//

void FaceFinder::setPathToCascadeFace(std::string path)
{
	pathToCascadeFace = path;
	if (!faceCascade.load(pathToCascadeFace))
	{
		std::cout << "Error loading face cascade" << std::endl;
	}
}

void FaceFinder::setNumIntersect(int input)
{
	numIntersect = input;
}

void FaceFinder::setNumRescalingsFullScan(int input)
{
	numRescalingsFullScan = input;
}

void FaceFinder::setMinFaceFractionScreenFullScan(double input)
{
	minFaceFractionScreenFullScan = input;
}

void FaceFinder::setMaxFaceFractionScreenFullScan(double input)
{
	maxFaceFractionScreenFullScan = input;
}

void FaceFinder::setNumRescalingsShortScan(int input)
{
	numRescalingsShortScan = input;
}

void FaceFinder::setMinFacePrevFraction(double input)
{
	minFacePrevFraction = input;
}

void FaceFinder::setMaxFacePrevFraction(double input)
{
	maxFacePrevFraction = input;
}

void FaceFinder::setRoiResize(double input)
{
	roiResize = input;
}

std::string FaceFinder::getPathToCascadeFace() { return pathToCascadeFace; }
int FaceFinder::getNumIntersect() { return numIntersect; }
int FaceFinder::getNumRescalingsFullScan() { return numRescalingsFullScan; }
int FaceFinder::getNumRescalingsShortScan() { return numRescalingsShortScan; }
double FaceFinder::getMinFaceFractionScreenFullScan() { return minFaceFractionScreenFullScan; }
double FaceFinder::getMaxFaceFractionScreenFullScan() { return maxFaceFractionScreenFullScan; }
double FaceFinder::getMinFacePrevFraction() { return minFacePrevFraction; }
double FaceFinder::getMaxFacePrevFraction() { return maxFacePrevFraction; }
double FaceFinder::getRoiResize() { return roiResize; }

int FaceFinder::getMinFaceShortScan() { return minFaceShortScan; }
int FaceFinder::getMaxFaceShortScan() { return maxFaceShortScan; }
double FaceFinder::getScaleShortScan() { return scaleShortScan; }
cv::Rect FaceFinder::getRoiRect() { return roiRect; }


//------------------------------------------------------------------------------------------//
//-------------------------------Parameters for Viola Jones --------------------------------//
//------------------------------------------------------------------------------------------//

void FaceFinder::violaJonesParametersFullScan(const cv::Mat &frame)
{
	if (frame.cols <= frame.rows)
	{
		minFaceFullScan = (int)(((double)frame.cols) * minFaceFractionScreenFullScan);
		maxFaceFullScan = (int)(((double)frame.cols) * maxFaceFractionScreenFullScan);
	}
	else
	{
		minFaceFullScan = (int)(((double)frame.rows) * minFaceFractionScreenFullScan);
		maxFaceFullScan = (int)(((double)frame.rows) * maxFaceFractionScreenFullScan);
	}

	scaleFullScan = pow(maxFaceFractionScreenFullScan / minFaceFractionScreenFullScan, 1.0 / ((double)numRescalingsFullScan - 1.0));
}

void FaceFinder::violaJonesParametersShortScan(const cv::Mat &frame, cv::Rect &prevFaceLocation)
{
	//scaleShortScan = pow(maxFacePrevFraction / minFacePrevFraction, 1.0 / ((double)numRescalingsShortScan - 1.0));
	minFaceShortScan = (int)(((double)prevFaceLocation.width) * minFacePrevFraction);
	maxFaceShortScan = (int)(((double)prevFaceLocation.width) * maxFacePrevFraction);

	//Check that maximum face size is not bigger than the frame
	if (maxFaceShortScan > frame.cols)
	{
		maxFaceShortScan = frame.cols - 1;
	}

	if (maxFaceShortScan > frame.rows || maxFaceShortScan > frame.cols)
	{
		maxFaceShortScan = frame.rows - 1;
	}

	//The same for minimum
	if (minFaceShortScan > frame.cols)
	{
		minFaceShortScan = frame.cols - 1;
	}

	if (minFaceShortScan > frame.rows || minFaceShortScan > frame.cols)
	{
		minFaceShortScan = frame.rows - 1;
	}

	scaleShortScan = pow( ((double) maxFaceShortScan) / ((double) minFaceShortScan), 1.0 / ((double)numRescalingsShortScan - 1.0));

	//How much we move coordinates of the left upper corner
	int delta = (int)(roiResize*((double)prevFaceLocation.width) / 2.0);

	if (prevFaceLocation.x > delta)
	{
		roiRect.x = prevFaceLocation.x - delta;
	}
	else
	{
		roiRect.x = 0;
	}

	if (prevFaceLocation.y > delta)
	{
		roiRect.y = prevFaceLocation.y - delta;
	}
	else
	{
		roiRect.y = 0;
	}

	if (roiRect.x + prevFaceLocation.width + 2 * delta < frame.cols)
	{
		roiRect.width = prevFaceLocation.width + 2 * delta;
	}
	else
	{
		roiRect.width = frame.cols - roiRect.x - 1;
	}

	if (roiRect.y + prevFaceLocation.width + 2 * delta < frame.rows)
	{
		roiRect.height = prevFaceLocation.width + 2 * delta;
	}
	else
	{
		roiRect.height = frame.rows - roiRect.y - 1;
	}
}

void FaceFinder::violaJonesParametersShortScan(const cv::Mat &frame, int prevWidth)
{
	//scaleShortScan = pow(maxFacePrevFraction / minFacePrevFraction, 1.0 / ((double)numRescalingsShortScan - 1.0));
	minFaceShortScan = (int)(((double)prevWidth) * minFacePrevFraction);
	maxFaceShortScan = (int)(((double)prevWidth) * maxFacePrevFraction);

	//Check that maximum face size is not bigger than the frame
	if (maxFaceShortScan > frame.cols)
	{
		maxFaceShortScan = frame.cols - 1;
	}

	if (maxFaceShortScan > frame.rows || maxFaceShortScan > frame.cols)
	{
		maxFaceShortScan = frame.rows - 1;
	}

	//The same for minimum
	if (minFaceShortScan > frame.cols)
	{
		minFaceShortScan = frame.cols - 1;
	}

	if (minFaceShortScan > frame.rows || minFaceShortScan > frame.cols)
	{
		minFaceShortScan = frame.rows - 1;
	}

	scaleShortScan = pow(((double)maxFaceShortScan) / ((double)minFaceShortScan), 1.0 / ((double)numRescalingsShortScan - 1.0));
}


//------------------------------------------------------------------------------------------//
//------------------------------------Viola Jones scan--------------------------------------//
//------------------------------------------------------------------------------------------//

bool FaceFinder::violaJonesScan(const cv::Mat &frame, cv::Rect &faceLocation)
{
	//Calculate parameters
	violaJonesParametersFullScan(frame);

	//Vector with faces
	std::vector<cv::Rect> faces;

	//Apply cascade face detector
	faceCascade.detectMultiScale(frame, faces, 1.1, numIntersect, 0 | cv::CASCADE_SCALE_IMAGE , cv::Size(minFaceFullScan, minFaceFullScan), cv::Size(maxFaceFullScan, maxFaceFullScan));

	//Check that we found a face
	if (faces.size() > 0)
	{
		faceLocation = faces[0];
		return true;
	}
	else
	{
		return false;
	}
}

//Scan in certain ROI based on the previous face location
bool FaceFinder::violaJonesScanROI(const cv::Mat &frame, cv::Rect &prevFaceLocation, cv::Rect &newFaceLocation)
{
	//Calculate parameters for scan
	violaJonesParametersShortScan(frame, prevFaceLocation);

	cv::Mat searchArea = frame(roiRect);//Area for face search

	//Vector with faces
	std::vector<cv::Rect> faces;

	faceCascade.detectMultiScale(searchArea, faces, scaleShortScan, numIntersect, 0 | cv::CASCADE_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(minFaceShortScan, minFaceShortScan), cv::Size(maxFaceShortScan, maxFaceShortScan));

	if (faces.size() > 0)
	{
		faces[0].x = roiRect.x + faces[0].x;
		faces[0].y = roiRect.y + faces[0].y;
		newFaceLocation = faces[0];
		return true;
	}
	else
	{
		return false;
	}
}

bool FaceFinder::violaJonesScanROI(const cv::Mat & frame, int prevWidth, cv::Rect & newFaceLocation)
{
	//Calculate parameters for scan
	violaJonesParametersShortScan(frame, prevWidth);

	//Vector with faces
	std::vector<cv::Rect> faces;

	faceCascade.detectMultiScale(frame, faces, scaleShortScan, numIntersect, 0 | cv::CASCADE_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(minFaceShortScan, minFaceShortScan), cv::Size(maxFaceShortScan, maxFaceShortScan));

	if (faces.size() > 0)
	{
		faces[0].x = roiRect.x + faces[0].x;
		faces[0].y = roiRect.y + faces[0].y;
		newFaceLocation = faces[0];
		return true;
	}
	else
	{
		return false;
	}
}

//First reduce an image by factor 2 until it reaches a certain minimum size and then apply ROI Viola-Jones scan
bool FaceFinder::violaJonesScanROIContract(const cv::Mat & frame, cv::Rect & prevFaceLocation, cv::Rect & newFaceLocation)
{
	//Recalculate parameters for scan
	violaJonesParametersShortScan(frame, prevFaceLocation);

	cv::Mat searchArea;//Area for face search
        cv::Mat rrr = frame(roiRect);
	int factor = reduceByTwo(rrr, searchArea);

	//Vector with faces
	std::vector<cv::Rect> faces;

	//Calculate the result mininmum and maximum face size
	minFaceShortScan = minFaceShortScan / factor;
	maxFaceShortScan = maxFaceShortScan / factor;

	faceCascade.detectMultiScale(searchArea, faces, scaleShortScan, numIntersect, 0 | cv::CASCADE_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(minFaceShortScan, minFaceShortScan), cv::Size(maxFaceShortScan, maxFaceShortScan));

	if (faces.size() > 0)
	{
		faces[0].x = roiRect.x + factor*faces[0].x;
		faces[0].y = roiRect.y + factor*faces[0].y;
		faces[0].width = factor * faces[0].width;
		faces[0].height = factor * faces[0].height;
		newFaceLocation = faces[0];
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------------------//
//----------------------------------Supplementary methods-----------------------------------//
//------------------------------------------------------------------------------------------//

//Reduce an image by factor 2 until it reaches specified minimum size
//Returns the factor by which we reduce an image
int FaceFinder::reduceByTwo(cv::Mat &input, cv::Mat &output)
{
	//Find the number of reductions
	int k = 1;//the number of reductions
	while (minSize * (2 ^ k) < input.rows)
	{
		k++;
	}

	//INTER_NEAREST
	resize(input, output, cv::Size(), 1.0 / ((float)(2 ^ (k - 1))), 1.0 / ((float)(2 ^ (k - 1))), cv::INTER_LINEAR);

	return 2 ^ (k - 1);
}
