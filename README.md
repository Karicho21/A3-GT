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

Way to execute this program using Centaurus
1. Connecting hpc lab computer by "ssh hpc-student.charlotte.edu -l your-username"
2. Authenticate with Duo
3. Type "g++ gt.cpp -o gtg -I ~/rapidjson/include -lcurl" gtg is the name of the executable file and gt.cpp is the source code. g++ allows us to make executable file that is binary so CPU can process the high level program.
4. Type './gtg "Tom Hanks" 2' ./gtg is command to  execute the gtg file, then followed by starting node and integer which is the depth of the node you are looking for. If you want to look for the cast members of movie "Cast Away" you can type that instead  of "Tom Hanks" in example.
5. You will see a time at the very top, this is a time that computer  took to find the neighboring nodes. More you include, longer it takes.


Keys:
If you accidentally miss components when you try to execute, it will give you an error message that says "Missing component(s) while trying to execute gtg file. make sure to type <startNode> and <depth>". Start node can be anything as long as it is in the database. To follow the instruction, I put Tom Hanks. I don't know him but he is in a lot of movies!

Records from my end:
./gtg "Tom Hanks" 2: Recorded Time: 0.171754 seconds

