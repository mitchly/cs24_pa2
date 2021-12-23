// main.cpp
// Joshua Thomas, 3937661. Michelle Ly: 3774189
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include "movies.cpp"
#include <time.h>
using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
  vector<string> allMovies;
  vector<float> allTimes;
  vector<int> nodesVisited;
  if(argc < 4){
    cerr << "Usage: " << argv[ 0 ] << "arg1 arg2 arg3" << endl;
    exit(1);
  }

  bool flag = false;
  if(strcmp(argv[1], "true") == 0){
    flag = true;
  } else if(strcmp(argv[1], "false") == 0) {
    flag = false;
  } else {
    cerr << "Argument 1 must be a boolean (true/false)" << endl;
    exit(1);
  }

  ifstream movieFile (argv[2]);
  string line, movieName;
  double movieRating;

  if (movieFile.fail()){
    cerr << "Could not open file " << argv[2];
    exit(1);
  }

  // Create an objects of the BST class you defined
  movies movielist;
  // to contain the name and rating in the input file

  // Read each file and store the name and rating
  while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
    // Use std::string movieName and double movieRating
    movielist.insert(string(movieName), double(movieRating));
    // to construct your Movie objects
    //cout << movieName << " has rating " << movieRating << endl;
  }
  movieFile.clear();
  movieFile.seekg(0, movieFile.beg);

  while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
    allMovies.push_back(string(movieName));
  }

    movieFile.close();

    //movielist.setDepth();
    for(int n = 0; n < allMovies.size(); n++){
      nodesVisited.push_back(movielist.getDepth(movielist.getNodeFor(allMovies[n])));
    }

  //arg 2 true
    if(flag == true){
    //movielist.setDepth();
    movielist.printPreOrder();
    string s(argv[3]);
    movielist.printGetBest(s);
  }

  //arg 2 false
  if(flag == false){
    int N = allMovies.size();
    int W;
    cout << "Please input how many iterations of search you want to use (preferably 50)" << endl;
    cin >> W;
    int i = 0;
    while(i < W){
      clock_t t = clock();
      for(int j = 0; j < N; j++){
        movielist.getNodeFor(allMovies[j]);
      }
      t = clock() - t;
      allTimes.push_back(t);
      i++;
    }
    movielist.bstTime(allTimes, N, W);

    for(int i = 0; i < N; i++){
      movielist.addToCSVFile(i+1, nodesVisited[i]);
    }
  }

  return 0;
}
bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "", movieRating = 0.0, flag = false;

  for (int i = 0; i < line.length(); i++){
    if(flag) tempRating += line[i];
    else if(line[i]==','&& line[0]!='"') flag = true;
    else {
      if(i==0 && line[0]=='"') continue;
      if(line[i]=='"'){ i++; flag=true; continue;}
      movieName += line[i];
    }
  }

  movieRating = stod(tempRating);
  return true;
}