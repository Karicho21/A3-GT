

This program is for ITCS4145 Assignment 3, Graph-crawer

This  program  aims to find neighboring nodes of node you specify. This database holds cast members' name and quite a lot of movies. I hope you enjoy!

But before you begin, make sure you have access to:

- A Linux-based system with SLURM workload management
- gcc compiler (this is critical to execute the program)
- Access to hpc lab computer Centaurus
- UNC Charlotte VPN if you are outside of campus or not using "eduroam" network

There are two ways to run this program.
1. Using centaurus
2. Using your local machine

I highly recommend using Centaurus since all  of the libraries are available already. I will get to the way to  use this program win local machine later on.

Way to execute this program using Centaurus:
1. Connecting hpc lab computer by "ssh hpc-student.charlotte.edu -l your-username"
2. Authenticate with Duo
3. Type "g++ gt.cpp -o gtg -I ~/rapidjson/include -lcurl" gtg is the name of the executable file and gt.cpp is the source code. g++ allows us to make executable file that is binary so CPU can process the high level program.
4. Schedule the job by "sbatch gtg.sh"
5. Outcome should be something like "Submitted batch job [????]", pay attention to the number.
6. Wait a bit for command to finish running and record the time it takes.
7. There are 3 jobs scheduled in gtg.sh file. To look at the time it took for each process, open record.txt by typing "cat record.txt"

Way to execute his program using your local machine:
1. libcurl is a library for making HTTP requests in C++. To install it:
	- On Ubuntu/Debian: sudo apt install libcurl4-openssl-dev
	- On macOS: brew install curl
2. RapidJSON is a fast JSON parser for C++. To install it using GitHub: git clone https://github.com/Tencent/rapidjson.git 
3. Run these commands: cd rapidjson, mkdir build && cd build, cmake .., sudo make install
4. Type "g++ gt.cpp -o gtg -I ~/rapidjson/include -lcurl" gtg is the name of the executable file and gt.cpp is the source code. g++ allows us to make executable file that >
5. Schedule the job by "sbatch gtg.sh"
6. Outcome should be something like "Submitted batch job [????]", pay attention to the number.
7. Wait a bit for command to finish running and record the time it takes.
8. There are 3 jobs scheduled in gtg.sh file. To look at the time it took for each process, open record.txt by typing "cat record.txt"


Keys:
If you accidentally miss components when you try to execute, it will give you an error message that says "Missing component(s) while trying to execute gtg file. make sure to type <startNode> and <depth>". Start node can be anything as long as it is in the database. To follow the instruction, I put Tom Hanks. I don't know him but he is in a lot of movies!
If you would like to run the progarm with your sets of data, you can execute it by "./gtg <Starting node> <Depth> "

Records from my end: (It vaires every time, but should  be similar)
- ./gtg "Tom Hanks" 2: Recorded Time: 0.171754 seconds
- ./gtg "Tom Hanks" 3: Recorded Time: 0.170985 seconds
- ./gtg "Tom Hanks" 4: Recorded Time: 0.184771 seconds
