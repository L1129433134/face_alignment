#ifndef _TRACKER_
#define _TRACKER_

#include "Def_type.h"
#include "joint_face.h"
#include "feat.h"
#include <vector>

using namespace std;

#define MODEL_NUM 3

namespace tracker
{		
	class Desc_feat
	{
		public:
			Desc_feat();
			~Desc_feat();
			void Init(int cellsize);
			bool GetVec(float* data,int rows, int cols, int channels, float* vDesc);
			void Destroy();	
		private:
			Feat*      _feat;
			int        _nCellSize,_nNumBins;
	};

	typedef struct Model_t
	{
		TMat_f m;
		TMat_f v;
		TMat_f w;
	} Model;
	
	class trackerClass
	{

	public:
		trackerClass(int false_count_times,float is_face_threshold);										                                               
		~trackerClass(){};
        bool  load_model(const char *detectionmodel, const char *trackingmodel);	  //����ģ��
		bool  Track2D(cv::Mat &src, std::vector<float>& face_pts);
		inline int GetPtsNum(){return _ptsSize;}
		void GetPose(double* pose);
		vector<cv::Point3d>       _model_points;                                      //��ά�ռ��   
	private:
		bool  load_face_detector(const char* cascadePath);
		int   detect_face(cv::Mat &inputImage);
		bool  TrackFeats2D(cv::Mat &src,long count,bool &isTrackingSuccess);
		bool  Desec_Get(cv::Mat inImg, float fx, float fy, float *vDesc);			  //���ָ��λ�þֲ�����
		bool  Desec_GetAll(cv::Mat inImg,int curStage);	                              //�����������
	private:
		detector::Cascade              _fd;                                           //����ʶ����
		std::vector<Model>        _tmModels[MODEL_NUM];                               //����ģ��
		std::vector<Model>        _tmValModels[MODEL_NUM];                            //������֤ģ��
		TMat_f                    _tmMeanShp[MODEL_NUM];                              //��״��ֵ
		cv::Point2f               _tmCenter[MODEL_NUM];                               //���ĵ�
		uint32_t                  _stage;                                             //��������
		TVec_f                    _curShape;                                          //��ǰ��״
		int                       _cur_model_idx;                                     //��ǰmodel���
		int                       _ptsSize;                                           //�������
		int                       _nDescLen;                                          //��������
		TVec_f                    _tvDescPlusList;                                    //��������
		Desc_feat                 _descHandl;				                          //HOG������ȡ��
		int						  _false_count_times;                                 //��������׷��ʧ�ܵ�֡����
		float                     _is_face_threshold;                                 //�ж��Ƿ��������ķָ���ֵ
		double                    _params[6];
	};
	void  show_image(char* name,cv::Mat &image, vector<float>landmarks, cv::Scalar color = cv::Scalar(0, 255, 0));
}


#endif
