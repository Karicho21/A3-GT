
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <bits/stdc++.h>


size_t my_write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {

    std::string* mystring = (std::string*)userdata;

    for (size_t i = 0; i < nmemb; ++i) {
        mystring -> push_back(ptr[i]);
    }
    
    return nmemb;
}

vector<int> bfs(vector<vector<int>>& adj, int s)  {
    int V = adj.size();

    vector<int> res;
    queue<int> q;  
    
    // Initially mark all the vertices as not visited
    vector<bool> visited(V, false);

    // Mark source node as visited and enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate over the queue
    while (!q.empty()) {
      
        // Dequeue a vertex from queue and store it
        int curr = q.front();
        q.pop();
        res.push_back(curr);
        
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    // time measuring
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <startNode> <depth>\n";
        return 1;
    }

    std::string startNode = argv[1];
    int depth = std::stoi(argv[2]);

    auto start = std::chrono::high_resolution_clock::now();
    bfs(startNode, depth);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    //curl  part... lawd
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/");
    std::string myoutstring;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&myoutstring);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_data);

    curl_easy_perform(curl);

    std::cout<<myoutstring<<"\n";

    curl_easy_cleanup(curl);

    return 0;

   
}
