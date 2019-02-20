// KMeans clustering , main function
// Author : Yichen Jia (yjia@csc.lsu.edu)
// Class: CSC7442 Data Mining and Knowledge Discovery from Databases
// Instructor: Professor E. Triantaphyllou

#ifndef MAIN_CPP
#define MAIN_CPP 

#include <vector>
#include "point.h"
#include "kmeans.h"
#include "cluster.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void usage() {
  cout << "Usage: ./KMeans" << endl;
  cout << "  elements in config file are amount of attributes, number of clusters, max_iterations respectively ."
  << endl;
  cout << "  elements in dataset are data points, each point per line!"
  << endl;
  return;
}

int main(int argc, char *argv[])
{
        
        srand (time(NULL));

        usage();

	int total_points, total_values, num_clusters, max_iterations, has_name;

        ifstream inputFile("config");
        std::string line;

        while (getline(inputFile, line))
        {
            istringstream ss(line);

            string name;

            ss >> total_values >> num_clusters >> max_iterations;
            cout << total_values << endl << num_clusters << endl 
                 << max_iterations << endl;
        }

	vector<Point> points;
	string point_name;

        ifstream inputDataset("dataset");
        total_points = 0;

        while (getline(inputDataset,line))
        { 
            vector<double> values;
            std::istringstream is(line);
            double value;
            while(is >> value){
                values.push_back(value);
            }
            Point p(total_points, values);
            points.push_back(p);
            total_points++;
        }
        cout << total_points <<endl;
        
        KMeans kmeans(num_clusters, total_points, total_values, max_iterations);
        kmeans.run(points);

        return 0;
}
#endif //MAIN
