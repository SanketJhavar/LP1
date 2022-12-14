#include <bits/stdc++.h>
using namespace std;

void fifo(int *pr, int prl)
{
    int fsize;
    int pagefault = 0;
    cout<<"Enter the frame size: ";
    cin >> fsize;
    vector<int> que(fsize, -1);
    int pointer = 0;
    for(int i = 0; i < prl; i++){
        bool exists = count(que.begin(), que.end(), pr[i]) > 0;
        if(exists){
            cout<<"Page hit = "<<pr[i]<<"\n";
            for(int it: que ){
            cout<<it<<" ";
            }
            cout<<"\n";
        }else{
            cout<<"Page Fault = "<<pr[i]<<"\n";
            pagefault++;
            que[pointer] = pr[i];
            for(int it: que ){
                cout<<it<<" ";
            }
            pointer = (pointer+1) % fsize;
            cout<<"\n";
        }
        
    }
    cout<<"Total page fault: "<<pagefault<<"\n";
}

void LRU(int *pr, int prl){
    int fsize, pagefault = 0 , pagehit = 0;
    cout<<"Enter the frame size: ";
    cin >> fsize;

    vector<int> frame, que;
    int front = -1, end = -1;
    for(int i = 0; i < prl; i++){
        bool exists = count(frame.begin(), frame.end(), pr[i]) > 0;
        if(!exists){
            cout<<"Page fault = "<<pr[i]<<"\n";
            pagefault++;
            if(frame.size() != fsize){
                frame.push_back(pr[i]);
                if(que.empty()){
                    que.push_back(pr[i]);
                    front++; end++;
                }else{
                    que.push_back(pr[i]);
                    end++;
                }
            }else{
                for(int j = 0; j < fsize; j++){
                    if(frame[j] == que[front]){
                        frame[j] = pr[i];
                        que.push_back(pr[i]);
                        que.erase(que.begin());
                        break;
                    }
                }
            }
        }else{
            cout<<"Page hit = "<<pr[i]<<"\n";
            pagehit++ ;
            for(auto it = que.begin(); it != que.end();){
                if(*it == pr[i]){
                    que.erase(it);
                    que.push_back(pr[i]);
                    break;
                }else
                    ++it;
            }
        }
        cout<<"FRAME: ";
        for(auto it : frame){
            cout<<it<<" ";
        }
        cout<<"\nQUE: ";
        for(auto it : que){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
    cout<<"LRU :: Total no. of page faults: "<<pagefault<<"\n";
    cout<<"LRU :: Total no. of page hits: "<<pagehit<<"\n";
}

void MRU(int *pr, int prl){
    int fsize, pagefault = 0 , pagehit = 0;
    cout<<"Enter the frame size: ";
    cin >> fsize;

    vector<int> frame, que;
    int front = -1, end = -1;
    for(int i = 0; i < prl; i++){
        bool exists = count(frame.begin(), frame.end(), pr[i]) > 0;
        if(!exists){
            cout<<"Page fault = "<<pr[i]<<"\n";
            pagefault++;
            if(frame.size() != fsize){
                frame.push_back(pr[i]);
                if(que.empty()){
                    que.push_back(pr[i]);
                    front++; end++;
                }else{
                    que.push_back(pr[i]);
                    end++;
                }
            }else{
                for(int j = 0; j < fsize; j++){
                    if(frame[j] == que[end]){
                        frame[j] = pr[i];
                        que.erase(que.end() - 1);
                        que.push_back(pr[i]);
                        break;
                    }
                }
            }
        }else{
            cout<<"Page hit = "<<pr[i]<<"\n";
            pagehit++ ;
            for(auto it = que.begin(); it != que.end();){
                if(*it == pr[i]){
                    que.erase(it);
                    que.push_back(pr[i]);
                    break;
                }else
                    ++it;
            }
        }
        cout<<"FRAME: ";
        for(auto it : frame){
            cout<<it<<" ";
        }
        cout<<"\nQUE: ";
        for(auto it : que){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
    cout<<"LRU :: Total no. of page faults: "<<pagefault<<"\n";
    cout<<"LRU :: Total no. of page hits: "<<pagehit<<"\n";
}



int main()
{
    int ch;
    int nopr;
    cout << "Enter the no of page references: ";
    cin >> nopr;

    int *pr = new int[nopr];
    cout<<"Enter the page references: ";
    for (int i = 0; i < nopr; i++)
    {
        cin >> pr[i];
    }

    do{
    cout<<"1. FIFo\n2. Least Recently used\n3. Most Recently used\n";
    cout<<"Enter your Choice: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        fifo(pr, nopr);
        break;
    case 2:
        LRU(pr, nopr);
        break;
    case 3:
        MRU(pr, nopr);
        break;

    case -1:
        cout<<"Program terminated !\n";
        break;

    default:
        cout<<"Invalid choice..\n";
        break;
    }
    }while(ch != -1);

    return 0;
}