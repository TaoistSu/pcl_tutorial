#include<>

#time : 2020-01-23

#funcion:

1/example.cpp

把输入的雷达话题修改个话题直接发布出去

subscriber:
/input

publish:
/output


2/example_voxelgrid_pcl_types.cpp

功能1-read_downsample()
读取pcd文件并采样1m间隔采样

功能2-cloud_cb (const pcl::PCLPointCloud2ConstPtr& cloud)
输入input 点云 过滤出  output点云
rosrun my_pcl_tutorial example_voxelgrid_pcl_types input:=/points_raw


3/rotated_data.cpp

读取雷达话题按x轴旋转，然后发布
