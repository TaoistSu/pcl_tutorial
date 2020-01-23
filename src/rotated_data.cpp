/***********************************************************
关于使用sensor_msgs/PointCloud2，
***********************************************************/

#include <ros/ros.h>
// PCL 的相关的头文件
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//滤波的头文件
#include <pcl/filters/voxel_grid.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>


//申明发布器
ros::Publisher pub;
 //回调函数
void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)  //特别注意的是这里面形参的数据格式
{
  sensor_msgs::PointCloud2 output;
  pcl::PCLPointCloud2 pcl_pc2;
  pcl_conversions::toPCL(*input,pcl_pc2); //把sensor数据转维PCL
  pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);//把PCL转PCL2
  //printf("size of the cloud = %d\n",temp_cloud->points.size ());
  for(int i=0;i<temp_cloud->points.size ();i++)
  {
  	temp_cloud->points[i].x = -temp_cloud->points[i].x; //沿着x轴旋转180度
        temp_cloud->points[i].x = temp_cloud->points[i].x - 1; //平移
  }
  pcl::toROSMsg(*temp_cloud,output);
  //发布命令
  pub.publish (output);




}

int
main (int argc, char** argv)
{
  // 初始化 ROS节点
  ros::init (argc, argv, "rotated_data");
  ros::NodeHandle nh;   //声明节点的名称

  // 为接受点云数据创建一个订阅节点
  ros::Subscriber sub = nh.subscribe ("points_raw", 1, cloud_cb);

  //创建ROS的发布节点
  pub = nh.advertise<sensor_msgs::PointCloud2> ("points_raw_rotated", 1);

  // 回调
  ros::spin ();
}
