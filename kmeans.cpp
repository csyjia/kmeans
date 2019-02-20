// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "kmeans.h"
using namespace std;
/**
  getIDNearestCenter(Point point): return the ID of the nearest cluster.
*/
int KMeans::getIDNearestCenter(Point point)
{
	double sum = 0.0, min_dist;
	int id_cluster_center = 0;

	for(int i = 0; i < total_values; i++)
	{
		sum += pow(clusters[0].getCentralValue(i) -
			   point.getValue(i), 2.0);
	}

	min_dist = sqrt(sum);

	for(int i = 1; i < K; i++)
	{
		double dist;
		sum = 0.0;

		for(int j = 0; j < total_values; j++)
		{
			sum += pow(clusters[i].getCentralValue(j) -
					   point.getValue(j), 2.0);
		}

		dist = sqrt(sum);

		if(dist < min_dist)
		{
			min_dist = dist;
			id_cluster_center = i;
		}
	}

	return id_cluster_center;
}

/**
  init(vector<Point> &points): initilize the cluster by random choose a centroid.
*/


bool KMeans::init(vector<Point> &points) {
        vector<int> prohibited_indexes;

        // choose K distinct values for the centers of the clusters
        for(int i = 0; i < K; i++)
        {
              while(true)
              {
                   int index_point = rand() % total_points;

                   if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
                           index_point) == prohibited_indexes.end())
                   {
                           prohibited_indexes.push_back(index_point);
                           points[index_point].setCluster(i);
                           Cluster cluster(i, points[index_point]);
                           clusters.push_back(cluster);
                           break;
                   }
              }
         }
        
}
/**
 assign(vector<Point> &points): assign each point to the corresponding cluster.
*/
void KMeans::assign(vector<Point> & points)
{
      for(int i = 0; i < total_points; i++)
      {
               int id_old_cluster = points[i].getCluster();
               int id_nearest_center = getIDNearestCenter(points[i]);
               if(id_old_cluster != id_nearest_center)
               {
                        if(id_old_cluster != -1)
                        {
                             clusters[id_old_cluster].removePoint(points[i].getID());
                        }
                        points[i].setCluster(id_nearest_center);
                        clusters[id_nearest_center].addPoint(points[i]);
                        done = false;
               }
     }
}

/**
 assign(vector<Point> &points): update the new means of the clusters.
*/

void KMeans::updateMeans(vector<Point> & points)
{
       for(int i = 0; i < K; i++)
       {
               for(int j = 0; j < total_values; j++)
               {
                    int total_points_cluster = clusters[i].getTotalPoints();
                    double sum = 0.0;
                    if(total_points_cluster > 0)
                    {
                            for(int p = 0; p < total_points_cluster; p++)
                            {
                                    sum += clusters[i].getPoint(p).getValue(j);
                            }
                            clusters[i].setCentralValue(j, sum / total_points_cluster);
                    }
               }
       }
}
/**
  plot(): plot the clustering result
*/
void KMeans::plot()
{
       for(int i = 0; i < K; i++)
       {
               int total_points_cluster =  clusters[i].getTotalPoints();

               cout << "Cluster " << clusters[i].getID() + 1 << endl;
               for(int j = 0; j < total_points_cluster; j++)
               {
                        cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
                        for(int p = 0; p < total_values; p++)
                        {
                                cout << clusters[i].getPoint(j).getValue(p) << " ";
                        }
                        cout << endl;
                }

                cout << "Cluster values: ";

                for(int j = 0; j < total_values; j++)
                {
                        cout << clusters[i].getCentralValue(j) << " ";
                }
                cout << "\n\n";
        }
}
/**
    intra_cluster_distance(): calculate the intra_cluster_distance. the sum of distance square between each point and the centroid in each cluster.
*/
void KMeans::intra_cluster_distance()
{
       double intra_cluster_distance=0.0;
       for(int i = 0; i < K; i++)
       {
               int total_points_cluster =  clusters[i].getTotalPoints();

               for(int j = 0; j < total_points_cluster; j++)
               {
                        for(int p = 0; p < total_values; p++)
                        {
                                intra_cluster_distance+=pow(clusters[i].getPoint(j).getValue(p)-clusters[i].getCentralValue(p),2.0);
                        }
                }
        }
        cout << "intra_cluster_distance is " << intra_cluster_distance << endl;        
}
/**
inter_cluster_distance(): calculate the inter_cluster_distance. the sum of weighted distance square of centroids of each cluster.
*/
void KMeans::inter_cluster_distance()
{
       double inter_cluster_distance=0.0;
       for(int i = 0; i < K; i++)
       {
               int total_points_cluster_1 =  clusters[i].getTotalPoints();
               for(int j = i+1; j < K; j++)
               {
                        int total_points_cluster_2 =  clusters[j].getTotalPoints();
                        double distance = 0;
                        for(int p = 0; p < total_values; p++)
                        {
                                distance+=pow(clusters[j].getCentralValue(p)-clusters[i].getCentralValue(p),2.0);
                        }
                        double weight=(total_points_cluster_1+total_points_cluster_2)/(double)total_points;
                        //cout << weight << endl;
                        inter_cluster_distance+=distance;
                }
        }
        cout << "inter_cluster_distance is " << inter_cluster_distance << endl;
}


void KMeans::run(vector<Point> & points)
{
	if(K > total_points)
		return;
                 
        init(points);
 
	int iter = 1;

	while(true)
	{
		done = true;

		// associates each point to the nearest center
                assign(points);
		// recalculating the center of each cluster
                updateMeans(points);
			
                if(done == true || iter >= max_iterations)
		{
			cout << "Break in iteration " << iter << "\n\n";
			break;
		}

		iter++;
	}

	// shows elements of clusters
        plot();        
        intra_cluster_distance();
        inter_cluster_distance();
}

