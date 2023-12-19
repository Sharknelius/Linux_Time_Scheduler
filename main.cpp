/*
Jasmine Rodriguez
Jake Meetre
COP 3415

The program emulates a Linux Task Scheduler where threads and priority queues
are used to schedule tasks.

References
https://www.thecrazyprogrammer.com/2014/11/c-cpp-program-for-priority-scheduling-algorithm.html
https://www.geeksforgeeks.org/program-for-priority-cpu-scheduling-set-1/
https://www.tutorialspoint.com/cplusplus-program-for-priority-scheduling
*/
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

// Rename files at needed
FILE *inFile, *outFile;

class ScheduleJob {
   private:
    // Priority/start of the job, used for scheduling
    long priority;
    // unique id for the job
    int id;

    // Constructor that initializes a job with a start time and an ID
   public:
    ScheduleJob(long startTime, int timeId) {
        priority = startTime;
        id = timeId;
    }
    // Getter amd Setter methods
    long getPriority() {
        return priority; 
    }

    int getId() const {
        return id; 
    }

    void setStartTime(long time) {
        priority = time; 
    }
};
// Compare two jobs by their priority and return the greater one
bool comparison(ScheduleJob &a, ScheduleJob &b) {
    if (a.getPriority() == b.getPriority()) return a.getId() > b.getId();

    return (a.getPriority() > b.getPriority());
}
int main() {
    inFile = fopen("inFile.txt", "r");
    outFile = fopen("outFile.txt", "w");

    if (inFile == NULL) {
        cout << "No input file present.";
        return 1;
    }

    if (outFile == NULL) {
        cout << "Error opening output file.";
        if (inFile != NULL) fclose(inFile);
        return 1;
    }

    // Read number of threads and jobs from input file
    int n, m;
    // Expect 2 items, if not then close files
    if (fscanf(inFile, "%d %d", &n, &m) != 2) {
        cout << "Error reading number of threads and jobs.";
        fclose(inFile);
        fclose(outFile);
        return 1;
    }
    // Priority queue to manage the schedule jobs
    priority_queue<ScheduleJob, vector<ScheduleJob>, decltype(&comparison)>
        threads(comparison);
    // Initialize the priority queue with ScheduleJob objects
    for (int i = 0; i < n; i++) {
        threads.push(ScheduleJob(0, i));
    }

    // Schedule and process jobs
    for (int i = 0; i < m; i++) {
        long jobTime;
        if (fscanf(inFile, "%ld", &jobTime) != 1) {
            cout << "Error reading time.";
            break;
        }

        ScheduleJob next = threads.top();
        threads.pop();

        fprintf(outFile, "%d %ld\n", next.getId(), next.getPriority());
        // Print the job ID and priority to the console
        cout << next.getId() << " " << next.getPriority() << "\n";

        // Update the start time of the job and reinsert it into the queue
        next.setStartTime(next.getPriority() + jobTime);
        threads.push(next);
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}
