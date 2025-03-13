#include <curl/curl.h>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <vector>
#include <rapidjson/document.h>

using namespace std;

size_t my_write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {

    string* mystring = (string*)userdata;

    mystring->append(ptr, size * nmemb);

    return nmemb * size;
}

string urlEncode(const string &value) {
    string encoded;
    char hex[4];

    for (unsigned char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        } else {
            snprintf(hex, sizeof(hex), "%%%02X", c);
            encoded += hex;
        }
    }
    return encoded;
}

vector<string> bfs(string startNode, int depth) {
    //definition of url we are using
    string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/" + urlEncode(startNode);
    CURL *curl;
    CURLcode res;
    string readBuffer;
    vector<string> neighbors;

    //sourced from video you shared
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

        if (readBuffer.empty()) {
            cerr << "Error: Received empty response from" << endl;
            return neighbors;
        }

        rapidjson::Document doc;
        if (doc.Parse(readBuffer.c_str()).HasParseError()) {
            cerr << "JSON error at node " << doc.GetErrorOffset()
                 << ": " << rapidjson::GetParseErrorFunc()(doc.GetParseError()) << endl;
            return neighbors;
        }

        if (doc.HasMember("neighbors") && doc["neighbors"].IsArray()) {
            for (const auto& neighbor : doc["neighbors"].GetArray()) {
                if (neighbor.IsString()) {
                    neighbors.push_back(neighbor.GetString());
                } else {
                    cerr << "Error: Unexpected neighbor type or name" << endl;
                }
            }
        } else {
            cerr << "Error: 'neighbors' is not recognized: possible typo detected" << endl;
        }
    }

    return neighbors;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Missing component(s) while trying to execute " << argv[0] << " file. make sure to type <startNode> and <depth>\n";
        return 1;
    }

    string startNode = argv[1];
    int depth = stoi(argv[2]);

    auto start = chrono::high_resolution_clock::now();
    vector<string> neighbors = bfs(startNode, depth);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "\n\nRecorded Time: " << elapsed.count() << " seconds\n";

    cout << "Neighboring nodes of " << startNode << " with depth " << depth << ":\n";
    for (const auto& neighbor : neighbors) {
        cout << "  " << neighbor << endl;
    }

    return 0;
}
