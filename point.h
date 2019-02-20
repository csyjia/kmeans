// Class point
// Author: Yichen Jia (yjia@csc.lsu.edu)
#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H

#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Point
{
private:
        int id_point, id_cluster;
        vector<double> values;
        int total_values;

public:
        Point(int id_point, vector<double>& values)
        {
                this->id_point = id_point;
                total_values = values.size();

                for(int i = 0; i < total_values; i++)
                        this->values.push_back(values[i]);

                id_cluster = -1;
        }
        int getID()
        {
                return id_point;
        }

        void setCluster(int id_cluster)
        {
                this->id_cluster = id_cluster;
        }

        int getCluster()
        {
                return id_cluster;
        }

        double getValue(int index)
        {
                return values[index];
        }

        int getTotalValues()
        {
                return total_values;
        }

        void addValue(double value)
        {
                values.push_back(value);
        }

};

#endif  // __KMEANS_POINT_H_
