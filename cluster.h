// KMeans clustering , cluster class
// Author : Yichen Jia (yjia@csc.lsu.edu)

#ifndef KMEANS_CLUSTER_H
#define KMEANS_CLUSTER_H

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "point.h"
using namespace std;

class Cluster
{
private:
        int id_cluster;
        vector<double> central_values;
        vector<Point> points;

public:
        Cluster(int id_cluster, Point point)
        {
                this->id_cluster = id_cluster;

                int total_values = point.getTotalValues();

                for(int i = 0; i < total_values; i++)
                {
                    central_values.push_back(point.getValue(i));
                }
                points.push_back(point);
        }

        void addPoint(Point point)
        {
                points.push_back(point);
        }

        bool removePoint(int id_point)
        {
                int total_points = points.size();

                for(int i = 0; i < total_points; i++)
                {
                        if(points[i].getID() == id_point)
                        {
                                points.erase(points.begin() + i);
                                return true;
                        }
                }
                return false;
        }

        double getCentralValue(int index)
        {
                return central_values[index];
        }

        void setCentralValue(int index, double value)
        {
                central_values[index] = value;
        }

        Point getPoint(int index)
        {
                return points[index];
        }

        int getTotalPoints()
        {
                return points.size();

        }

        int getID()
        {
                return id_cluster;
        }

 
};

#endif //KMEANS_CLUSTER_H
