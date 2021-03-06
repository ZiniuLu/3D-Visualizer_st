/* Created on: 08/05/2021
 *     Author: Ziniu Lu (luziniuoskar@outlook.com)
 */

#pragma once

#include <igl/list_to_matrix.h>
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Dense>

typedef Eigen::Matrix<double, Eigen::Dynamic, 3> MAT_3d;
typedef Eigen::Matrix<int, Eigen::Dynamic, 3>	 MAT_3i;
typedef Eigen::Matrix<int, Eigen::Dynamic, 2>	 MAT_2i;
typedef Eigen::RowVector3d						 RVec_3d;
typedef igl::opengl::glfw::Viewer				 IGL_Viewer;


