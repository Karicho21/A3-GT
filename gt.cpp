#include <curl/curl.h>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <vector>
#include <rapidjson/document.h>

using namespace std;

// Callback function for curl to write response data into a string
size_t my_write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    string* mystring = (string*)userdata;
    for (size_t i = 0; i < nmemb; ++i) {
        mystring->push_back(ptr[i]);
    }
    return nmemb;
}

// BFS function
vector<string> bfs(string startNode, int depth) {
    string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/" + startNode;
    CURL *curl;
    CURLcode res;
    string readBuffer;
    vector<string> neighbors;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);

        // Parse JSON response
        rapidjson::Document doc;
        if (doc.Parse(readBuffer.c_str()).HasParseError()) {
            cerr << "JSON parse error at offset " << doc.GetErrorOffset()
                << ": " << rapidjson::GetParseErrorFunc()(doc.GetParseError()) << endl;
            return neighbors;
        }

        if (readBuffer.empty()) {
            cerr << "Error: Received empty response" << endl;
            return neighbors;
        }

        if (doc.HasMember("neighbors") && doc["neighbors"].IsArray()) {
            for (const auto& neighbor : doc["neighbors"].GetArray()) {
                if (neighbor.IsString()) {
                    neighbors.push_back(neighbor.GetString());
                } else {
                    cerr << "Error: Unexpected neighbor type" << endl;
                }
            }
        } else {
            cerr << "Error: 'neighbors' field not found or is not an array" << endl;
        }
        return neighbors;
    }

    return neighbors;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <startNode> <depth>\n";
        return 1;
    }

    string startNode = argv[1];
    int depth = stoi(argv[2]);

    auto start = chrono::high_resolution_clock::now();
    vector<string> neighbors = bfs(startNode, depth);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Time: " << elapsed.count() << " seconds\n";

    cout << "Neighboring node of " << startNode << ":\n";
    for (const auto& neighbor : neighbors) {
        cout << "  " << neighbor << endl;
    }

    return 0;
}

