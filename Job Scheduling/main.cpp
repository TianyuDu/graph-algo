#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

/*
Minimizing the weighted sum of completion times.

Input file format:

[job_0_weight] [job_0_length]
[job_1_weight] [job_1_length]
*/

vector< pair<long double, long double> > loadData(string fileDir) {
  vector< pair<long double, long double> > jobs;
  ifstream infile(fileDir);

  long double w, l;
  while (infile >> w >> l) {
    pair<long double, long double> pair(w, l);
    jobs.push_back(pair);
  }

  infile.close();
  return jobs;
}

long double compute_loss(const vector< pair<long double, long double> > & jobs, vector< pair<long double, int> > & scores) {
  long double fTime = 0;
  long double weightedCost = 0;

  // Sort using the first element of pair.
  sort(scores.begin(), scores.end());
  // Traverse in reverse (descending) order.
  for (auto iter = scores.rbegin(); iter != scores.rend(); iter ++) {
    int jobId = iter -> second;
    long double w = jobs[jobId].first;
    long double l = jobs[jobId].second;
    fTime += l;  // update current time.
    // cout << fTime << endl;
    long double cj = w * fTime;
    weightedCost += cj;
  }
  return weightedCost;
}

vector< pair<long double, int> > greedy_using_difference(const vector< pair<long double, long double> > & jobs) {
  // Schedules jobs in decreasing order of the difference (weight - length).
  vector< pair<long double, int> > scores;
  int numJobs = jobs.size();
  for (int jobId = 0; jobId < numJobs; jobId ++) {
    long double w = jobs[jobId].first;  // w ranges from 0 to 100.
    long double l = jobs[jobId].second;  // l ranges from 0 to 100.
    // if two jobs have equal difference (weight - length), you should schedule the job with higher weight first.
    long double s = w - l + (w / 1000.0);  // adding small value w / 200 (< 1) does not affect the over scheduling but breaks ties using weight.
    pair<long double, int> p(s, jobId);
    scores.push_back(p);
  }

  return scores;
}

vector< pair<long double, int> > greedy_using_ratio(const vector< pair<long double, long double> > & jobs) {
  // schedules jobs (optimally) in decreasing order of the ratio (weight/length).
  vector< pair<long double, int> >  scores;
  int numJobs = jobs.size();
  for (int jobId = 0; jobId < numJobs; jobId ++) {
    long double w = jobs[jobId].first;
    long double l = jobs[jobId].second;
    long double s = w / l;
    pair<long double, int> p(s, jobId);
    scores.push_back(p);
  }

  return scores;
}

int main() {
  auto jobs = loadData("./jobs.txt");
  cout << "Number of jobs received: " << jobs.size() << endl;

  cout.precision(30);
  auto v1 = greedy_using_difference(jobs);
  auto c1 = compute_loss(jobs, v1);
  cout << c1 << endl;

  auto v2 = greedy_using_ratio(jobs);
  auto c2 = compute_loss(jobs, v2);
  cout << c2 << endl;
  return 0;
}
