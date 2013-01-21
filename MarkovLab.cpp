//David Fennell | 10365511
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <queue>
using namespace std;

int main(int argc, char* argv[])
{

  map<string, map<string, double> > outerMap;
  map<string, double> innerMap;

  queue<string> inputs;
  queue<string> lastInputs;
  ifstream in("grimm.txt");

  int k = 2;
  vector<string> words;
  string word;

  while ( in>> word )
  {
    words.push_back ( word );
  }
  string prefix;
  int size = words.size();
  for(int i = 0; i < size-k; i++)
  {

    for(int j = i; j < i+k ; j++)
    {
      prefix += words[j] + " ";

    }


    if(outerMap.count(prefix) > 0)
    {


      innerMap = outerMap[prefix];
    }
    if(innerMap.count(words[i+k]) > 0)
    {


      innerMap[words[i+k]]++;

    }
    else
    {
      innerMap.insert(make_pair(words[i+k], 1));

    }

    outerMap.insert(make_pair(prefix, innerMap));
    outerMap[prefix] = innerMap;
    innerMap.clear();
    prefix = "";

  }

  map <string, map <string, double> >::iterator outerit;
  map <string, double>::iterator innerit;
  int count = 0;
  for(outerit= outerMap.begin(); outerit != outerMap.end(); outerit++)
  {

    for(innerit = outerit->second.begin(); innerit != outerit->second.end(); innerit++)
    {

      count += innerit->second;
    }
    for(innerit = outerit->second.begin(); innerit != outerit->second.end(); innerit++)
    {

      innerit->second = floor((innerit->second/count)*10);
    }
    count = 0;
  }
  for(outerit= outerMap.begin(); outerit != outerMap.end(); outerit++)
  {

    for(innerit = outerit->second.begin(); innerit != outerit->second.end(); innerit++)
    {

    }
  }

  int wordCount = 0;

  srand(time(NULL));
  int random;
  string input;
  random = rand()%(words.size()-k);

  for(int i = random; i < ( random+k ); i++)
  {
    inputs.push(words[i]);
    lastInputs = inputs;

  }


  for(int i = 0; !inputs.empty(); i++)
  {
    input += inputs.front() + " ";
    inputs.pop();
  }
  string outputStr="";
  string last;
  double val = 2;
  bool picked = false;
  int max = atoi(argv[1]);
  while(wordCount != max && outerMap[input].size() >0)
  {
    innerMap = outerMap[input];
    input = "";
    inputs = lastInputs;
    for(innerit= innerMap.begin(); innerit != innerMap.end(); innerit++)
    {
      if(innerit->second+val > rand()%10)
      {
        outputStr = innerit->first;
        picked = true;
      }
    }
    if(picked == false)
    {
      innerit=innerMap.begin();
      outputStr = innerit->first;
    }
    picked = false;
    inputs.pop();
    inputs.push(outputStr);
    lastInputs = inputs;
    innerMap[outputStr]--;

    for(int i = 0; !inputs.empty(); i++)
    {
      input += inputs.front() + " ";
      inputs.pop();
    }
    cout << outputStr << " ";


    wordCount++;
  }




  cout << endl;
  return 0;
}
