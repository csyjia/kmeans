// KMeans clustering , core clustering class
// Author : Yichen Jia (yjia@csc.lsu.edu)


#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "point.h"
#include "cluster.h"
#include "fstream"
//using namespace std;

class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations;
	vector<Cluster> clusters;

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point point);
        bool done;

public:
        //bool loadPoints(const string &filepath, vector<Point> *points, int total_values);
	KMeans(int K, int total_points, int total_values, int max_iterations)
	{
		this->K = K;
		this->total_points = total_points;
		this->total_values = total_values;
		this->max_iterations = max_iterations;
                this->done=true;
	}

	void run(vector<Point> & points);
        bool init(vector<Point> & points);
        void assign(vector<Point> & points);
        void updateMeans(vector<Point> & points);
        void plot();
        void intra_cluster_distance();
        void inter_cluster_distance();
        
};
#endif //KMEANS_H
