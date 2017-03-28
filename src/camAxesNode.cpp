//
// Created by bolunzhang on 3/27/17.
//

#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
class camRB {
	public:
		camRB(ros::NodeHandle n): it_(n) {
			sub_cam1_ = it_.subscribe("camera2/image_color",
																5, &camRB::updateImg1, this);
			sub_cam2_ = it_.subscribe("camera3/image_color",
																5, &camRB::updateImg2, this);
			pub_image_ = it_.advertise("/cam2_cam3_rb", 5);
			std::cout << "constructor" << std::endl;
			cv::Mat image = cv::imread("/home/bolunzhang/workspace/opencv_test/build/lena.jpg", CV_LOAD_IMAGE_COLOR);
			cv::imshow("view", image);
			std::cout << "constructor end" << std::endl;
		}
		
		void updateImg1(const sensor_msgs::ImageConstPtr& msg) {
			std::cout << "update1" << std::endl;
			try {
				cv_sub1 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
			} catch (cv_bridge::Exception& e){
				ROS_ERROR("cv_bridge camAxes exception:: %s", e.what());
				return;
			}
			//publishImg();
		}
	
		void updateImg2(const sensor_msgs::ImageConstPtr& msg) {
			std::cout << "update2" << std::endl;
			try {
				cv_sub2 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
			} catch (cv_bridge::Exception& e){
				ROS_ERROR("cv_bridge camAxes exception:: %s", e.what());
				return;
			}
		}
	
	  void publishImg() {
			cv::Mat out_img(720, 1280, CV_8UC3);
			//cv::Mat image = cv::imread("/home/bolunzhang/workspace/opencv_test/build/lena.jpg", CV_LOAD_IMAGE_COLOR);
			/*
			cv::Mat in_img = cv::Mat::zeros(left_img.rows, left_img.cols, left_img.type());
			float M_data[2][3] = {{1, 0, img_offset}, {0, 1, 0}};
			cv::Mat M(2, 3, CV_32F, &M_data);
			std::cout << out_img.type() << std::endl;
			cv::warpAffine(left_img, in_img, M, left_img.size(), CV_INTER_LINEAR, CV_HAL_BORDER_TRANSPARENT);
			cv::Mat out_array[] = {out_img};
			cv::Mat in_array[] = {in_img, cv_sub2 -> image};
			int from_to[] = {0, 0, 5, 2};
			cv::mixChannels(in_array, 2, out_array, 1, from_to, 2);
			cv_pub.reset(new cv_bridge::CvImage(cv_sub1->header, cv_sub1-> encoding, out_img));
			pub_image_.publish(cv_pub -> toImageMsg());
			*/
		}

	private:
		image_transport::ImageTransport it_;
		// subscribe to source images
		image_transport::Subscriber sub_cam1_;
	  image_transport::Subscriber sub_cam2_;
		// publish superimposed image
		image_transport::Publisher pub_image_;
		cv_bridge::CvImagePtr cv_sub1;
		cv_bridge::CvImagePtr cv_sub2;
		cv_bridge::CvImagePtr cv_pub;
		// pixel horizontal offset for overlay
		int img_offset = 0;
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "cam_axes");
	ros::NodeHandle n;
	camRB cam_rb(n);
	ros::spin();

	return 0;
}