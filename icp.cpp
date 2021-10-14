//
// Created by tr on 21-10-14.
//
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

using namespace std;

int main(){
    Eigen::Matrix3d R=Eigen::Matrix3d::Identity();
    Eigen::AngleAxisd rotationVector(M_PI/4, Eigen::Vector3d(0,0,1));
    R=rotationVector.toRotationMatrix();
    cout<<"R: "<<R<<endl;
    
    //3points
    Eigen::Vector3d p1 =Eigen::Vector3d(1,2,3);
    Eigen::Vector3d p2 =Eigen::Vector3d(6,5,4);
    Eigen::Vector3d p3 =Eigen::Vector3d(8,7,9);

    vector<Eigen::Vector3d> points1={p1,p2,p3};

    vector<Eigen::Vector3d> points2;

    for(auto p:points1)
    {
        points2.push_back(R*p);
        cout<<"p1:"<<p<<endl;
    }

//    for (auto p2:points2)
//    {
//        cout<<"p2: "<<p2<<endl;
//    }

Eigen::Vector3d qa=Eigen::Vector3d(0,0,0);
    Eigen::Vector3d qb=Eigen::Vector3d(0,0,0);

    for(int i =0; i<points1.size();i++)
    {
        for(int j=0;j<3; j++)
        {
            qa[j]+=points1[i][j];
            qb[j]+=points2[i][j];
        }
    }
qa=qa/points1.size();qb=qb/points2.size();
cout<<"qa:"<<qa<<endl;
cout<<"qb"<<qb<<endl;

    for (int i=0; i<points1.size();i++)
    {
points1[i]=points1[i]-qa;
points2[i]=points2[i]-qb;
    }
    Eigen::Matrix3d W=Eigen::Matrix3d::Zero();
    for(int i=0;i<points1.size();i++)
    {
        W+=points1[i]*points2[i].transpose();
    }
    cout<<"W:"<<W<<endl;
//svd


Eigen::JacobiSVD<Eigen::Matrix3d> svd (W,Eigen::ComputeFullU|Eigen::ComputeFullV);
    Eigen::Matrix3d U= svd.matrixU();
    Eigen::Matrix3d V=svd.matrixV();

    Eigen::Matrix3d Rr=U*V.transpose();
    cout <<"Rr"<<Rr<<endl;

    return 0;



}
