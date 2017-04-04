#include <vector>
#include <iostream>
#include <math.h>

#include <opencv2/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

class FaceFinder
{
public:
	FaceFinder(std::string &cascadePath);
	FaceFinder();
	~FaceFinder();

	//-----------------------Setters-------------------------//
	void setPathToCascadeFace(std::string path);
	void setNumIntersect(int input);
	void setNumRescalingsFullScan(int input);
	void setNumRescalingsShortScan(int input);
	void setMinFaceFractionScreenFullScan(double input);
	void setMaxFaceFractionScreenFullScan(double input);
	void setMinFacePrevFraction(double input);
	void setMaxFacePrevFraction(double input);
	void setRoiResize(double input);

	//-----------------------Getters-------------------------//
	std::string getPathToCascadeFace();
	int getNumIntersect();
	int getNumRescalingsFullScan();
	int getNumRescalingsShortScan();
	double getMinFaceFractionScreenFullScan();
	double getMaxFaceFractionScreenFullScan();
	double getMinFacePrevFraction();
	double getMaxFacePrevFraction();
	double getRoiResize();
	int getMinFaceShortScan();
	int getMaxFaceShortScan();
	double getScaleShortScan();
	cv::Rect getRoiRect();

	//-----------------------Viola Jones parameters-------------------------//
	//Calculate Viola Joines paramters for Full scan
	void violaJonesParametersFullScan(const cv::Mat &frame);

	//Calculate Viola Jones paramters for Short scan
	void violaJonesParametersShortScan(const cv::Mat &frame, cv::Rect &prevFaceLocation);//Scan in the area of previous location
	void violaJonesParametersShortScan(const cv::Mat &frame, int prevWidth);//Correct only face size

	//-----------------------Run image scan--------------------------//
	//Full scan of an image
	bool violaJonesScan(const cv::Mat &frame, cv::Rect &faceLocation);

	//Scan of an image where we contract the image by factor 2 until we reach a specified size
	bool violaJonesScanROIContract(const cv::Mat &frame, cv::Rect &prevFaceLocation, cv::Rect &newFaceLocation);

	//Scan within some ROI
	bool violaJonesScanROI(const cv::Mat & frame, cv::Rect & prevFaceLocation, cv::Rect & newFaceLocation);

	//Scan within in the whole frame but with size paramters
	bool violaJonesScanROI(const cv::Mat & frame, int prevWidth, cv::Rect & newFaceLocation);

	//--------------------Supplementary methods---------------------//
	//Method to reduce the size of an image by factor 2 until it's lerger than defined size - returns the reduction factor
	int reduceByTwo(cv::Mat &input, cv::Mat &output);

private:

	//Rectangle that is used for search of a face when it's found in the previous frame
	cv::Rect roiRect;

	//--------------Paths to the face detector--------------//
	std::string pathToCascadeFace;//Path to cascade classifier

	//-----------Parameters for cascade classifier----------//
	cv::CascadeClassifier faceCascade;//Cascade
	int numIntersect = 3;//Number of intersections to detect face

	int numRescalingsFullScan = 6;//The number of rescalings during full scan
	int numRescalingsShortScan = 3;//The number of rescalings during short scan (when we found face in the previous frame)

	double minFaceFractionScreenFullScan = 0.4;//Minimum face fraction of the screen smallest side (full scan of the screen)
	double maxFaceFractionScreenFullScan = 0.8;//Maximum face fraction of the screen smallest side (full scan of the screen)

	double minFacePrevFraction = 0.8;//Minimum face fraction of the previous frame's face size (when we found face in the previous frame)
	double maxFacePrevFraction = 1.2;//Maximum face fraction of the previous frame's face size (when we found face in the previous frame)

	double roiResize = 0.32;//ROI as an extra fraction of the previous face size (0.32 - increase by 32%)

	int minSize = 80;//We reduce the size of a search image till it reaches minSize;

	//-----------------Parameters that are calculated for full scan----------------//
	double scaleFullScan;
	int minFaceFullScan;
	int maxFaceFullScan;

	//-----------------Parameters that are calculated for short scan----------------//
	double scaleShortScan;
	int minFaceShortScan;
	int maxFaceShortScan;
};

