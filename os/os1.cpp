#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<unistd.h>
#include<iterator>
#include<algorithm>
using namespace std;
class schedular{
    public:
    vector<int> arrival_time,burst_time,priority,job_id;
    int time_quantum,no_of_process;
    void getdata(){
        int a;
        cout<<"\nEnter number of process:";
        cin>>no_of_process;
        for(int i=0;i<no_of_process;i++){
            cout<<"\n process "<<i+1<<':';
            job_id.push_back(i+1);
            cout<<"\narrival time :";
            cin>>a;
            arrival_time.push_back(a);
            cout<<"\nburst time :";
            cin>>a;
            burst_time.push_back(a);
            cout<<"\npriority :";
            cin>>a;
            priority.push_back(a);
        }
        cout<<"\nenter time Quantum for round robin:";
        cin>>time_quantum;
    }

    void show(vector<int>CT,vector<int>TAT,vector<int>WT,vector<int>RT){
        cout<<"job id"<<'\t'<<"priority"<<'\t'<<"arrival time"<<'\t'<<"burst time"<<'\t'<<"completion time"<<'\t'<<"  TAT"<<'\t'<<"    WT"<<'\t'<<"   RT"<<'\n';
        for(int i=0;i<no_of_process;i++){
            // cout<<i+1<<'\t'<<priority[i]<<'\t'<<arrival_time[i]<<'\t'<<burst_time[i]<<'\t'<<CT[i]<<'\t'<<TAT[i]<<'\t'<<WT[i]<<'\t'<<RT[i]<<'\n';
            printf("%3d       %3d             %3d             %3d                %3d         %3d       %3d    %3d \n", i + 1, priority[i],arrival_time[i],burst_time[i], CT[i], TAT[i], WT[i],RT[i]);
        }
    }

    bool nothing_to_do(vector<int>t){
        for(int i=0;i<t.size();i++){
            if(t[i]!=0)
                return false;
        }
        return true;
    }

    void fcfs(){
        cout<<endl<<"First come first serve :"<<endl;
        queue<int>ready_queue;
        vector<int>gant_chart,completion_time(no_of_process),turn_around_time(no_of_process),waiting_time(no_of_process),response_time(no_of_process,0);
        vector<int> burst=burst_time;
        int i=0;
        while(!nothing_to_do(burst)){
            // sleep(1);
            for(int j=0;j<no_of_process;j++){
                if(arrival_time[j]==i){
                    ready_queue.push(job_id[j]);
                }
            }
            // for(int i=0;i<gant_chart.size();i++){
            //     cout<<gant_chart[i];
            // }
            // cout<<'\n';
            if(!ready_queue.empty()){
                gant_chart.push_back(ready_queue.front());
                burst[ready_queue.front()-1]--;
                if(burst[ready_queue.front()-1]==0){
                    completion_time[ready_queue.front()-1]=i+1;
                    ready_queue.pop();
                }
            }
            else{
                gant_chart.push_back(0);
            }
            i++;
        }
        float avg_turn_around=0,avg_waiting=0;
        for(int i=0;i<no_of_process;i++){
            turn_around_time[i]=completion_time[i]-arrival_time[i];
            avg_turn_around+=turn_around_time[i];
            waiting_time[i]=turn_around_time[i]-burst_time[i];
            avg_waiting+=waiting_time[i];
        }
        avg_turn_around=avg_turn_around/no_of_process;
        avg_waiting=avg_waiting/no_of_process;
        // for(int i=0;i<gant_chart.size();i++){
        //     cout<<gant_chart[i];
        // }
        // cout<<'\n';
        show(completion_time,turn_around_time,waiting_time,response_time);
        cout<<endl<<"average turn around time :"<<avg_turn_around<<endl<<"average waiting time :"<<avg_waiting<<endl;
    }
    struct CompareHeight {
        bool operator()(vector<int>&p1,vector<int>&p2)
        {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1[1]> p2[1];
        }
    };
    void Priority_f(){
        cout<<endl<<"Priority :"<<endl;
        priority_queue<vector<int>,vector<vector<int>>,CompareHeight> ready_queue;
        vector<int> burst=burst_time;
        vector<int>gant_chart,completion_time(no_of_process),turn_around_time(no_of_process),waiting_time(no_of_process),response_time(no_of_process,0);
        int i=0;
        while(!nothing_to_do(burst)){
            // sleep(1);
            for(int j=0;j<no_of_process;j++){
                if(arrival_time[j]==i){
                    ready_queue.push({job_id[j],priority[j]});
                }
            }
            // for(int i=0;i<gant_chart.size();i++){
            //     cout<<gant_chart[i];
            // }
            // cout<<'\n';
            if(!ready_queue.empty()){
                gant_chart.push_back(ready_queue.top()[0]);
                burst[ready_queue.top()[0]-1]--;
                if(burst[ready_queue.top()[0]-1]==0){
                    completion_time[ready_queue.top()[0]-1]=i+1;
                    ready_queue.pop();
                }
            }
            else{
                gant_chart.push_back(0);
            }
            i++;
        }
       float avg_turn_around=0,avg_waiting=0;
        for(int i=0;i<no_of_process;i++){
            turn_around_time[i]=completion_time[i]-arrival_time[i];
            avg_turn_around+=turn_around_time[i];
            waiting_time[i]=turn_around_time[i]-burst_time[i];
            avg_waiting+=waiting_time[i];
        }
        avg_turn_around=avg_turn_around/no_of_process;
        avg_waiting=avg_waiting/no_of_process;
        // for(int i=0;i<gant_chart.size();i++){
        //     cout<<gant_chart[i];
        // }
        // cout<<'\n';
        show(completion_time,turn_around_time,waiting_time,response_time);
        cout<<endl<<"average turn around time :"<<avg_turn_around<<endl<<"average waiting time :"<<avg_waiting<<endl;
    }
    void Round_robin(){
        cout<<endl<<"Round Robin :"<<endl;
        queue<int> ready_queue;
        vector<int> burst=burst_time;
        vector<int>gant_chart,completion_time(no_of_process),turn_around_time(no_of_process),waiting_time(no_of_process),response_time(no_of_process,0);
        int i=0;
        int shift=1;
        while (!nothing_to_do(burst))
        {
            // sleep(1);
            // for(int i=0;i<burst.size();i++){
            //     cout<<burst[i];
            // }
            // cout<<'\n';
                for(int k=0;k<time_quantum;k++){
                    // for(int i=0;i<gant_chart.size();i++){
                    //     cout<<gant_chart[i];
                    // }
                    // cout<<'\n';
                    for(int j=0;j<no_of_process;j++){
                        if(arrival_time[j]==i){
                            ready_queue.push(job_id[j]);
                        }   
                    }
                    if(k==0){
                            if(shift==0){
                            int f=ready_queue.front();
                            ready_queue.pop();
                            ready_queue.push(f);
                        }
                        else
                            shift=0;
                    }   
                    // cout<<ready_queue.front()<<'\n';
                    if(!ready_queue.empty()){
                        gant_chart.push_back(ready_queue.front());
                        burst[ready_queue.front()-1]--;
                        if(burst[ready_queue.front()-1]==0){
                            completion_time[ready_queue.front()-1]=i+1;
                            ready_queue.pop();
                            shift=1;
                        }
                    }
                    else{
                        gant_chart.push_back(0);
                    }
                    i++;
                }
            // cout<<gant_chart.front()<<'\n';
        }
        float avg_turn_around=0,avg_waiting=0;
        for(int i=0;i<no_of_process;i++){
            turn_around_time[i]=completion_time[i]-arrival_time[i];
            avg_turn_around+=turn_around_time[i];
            waiting_time[i]=turn_around_time[i]-burst_time[i];
            avg_waiting+=waiting_time[i];
        }
        avg_turn_around=avg_turn_around/no_of_process;
        avg_waiting=avg_waiting/no_of_process;
        // for(int i=0;i<gant_chart.size();i++){
        //     cout<<gant_chart[i];
        // }
        // cout<<'\n';
        show(completion_time,turn_around_time,waiting_time,response_time);
        cout<<endl<<"average turn around time :"<<avg_turn_around<<endl<<"average waiting time :"<<avg_waiting<<endl;

    }
};
int main(){
    schedular s;
    // s.getdata();
    s.job_id={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    s.arrival_time={2,3,4,5,6,7,8,9,2,3,4,5,6,7,8,8,9,3,4,5,6,7,8,4,5,6,7,4,5,6};
    s.no_of_process=30;
    s.burst_time={2,3,4,5,6,7,8,9,2,4,6,7,8,3,6,5,6,3,8,9,3,7,3,7,8,9,3,5,7,8};
    s.priority={1,2,4,5,15,30,6,7,25,26,27,28,8,9,10,12,13,17,18,20,21,11,3,22,14,23,16,24,29};
    s.time_quantum=2;
    // s.job_id={1,2,3,4};
    // s.arrival_time={0,1,2,4};
    // s.no_of_process=4;
    // s.burst_time={5,4,2,1};
    // s.priority={1,2,4,5};
    // s.time_quantum=2;
    s.fcfs();
    s.Priority_f();
    s.Round_robin();
    return 0;
}