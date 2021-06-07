#include <iostream>
#include <cctype>
#include<bits/stdc++.h>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

char menu();
void chooseSong(); // Функция, която търси поръчаната песен в списъка с налични парчета.
string getSongName(); // Функция, която взима име на песента от клавиатурата.
void addNewSongs(); // Функция, която добавя неоткритите песни към трак листа.

int main()
{
    addNewSongs();
    while(1)
    {
        switch(menu())
        {
        case '1':
            chooseSong();
            break;
        case '0':
            exit(0);
            break;
            return 0;
        }
    }
}
char menu()
{
    char i;
    printf("\n");
    printf("1. Enter song. \n");
    printf("0. Exit. \n");
    do
    {
        printf("Select option 0/1: \n");
        fflush(stdin);
        scanf("%c", &i);
    }
    while(i < '0' || i > '1');
    return i;
}
string getSongName()
{
    string songName;
    printf("\nEnter song name. \n");
    cin.ignore();
    getline(cin, songName);
    //cout<<songName<<endl;
    transform(songName.begin(), songName.end(), songName.begin(), ::toupper);
    cout<<"The song that you want to sing is: "<<songName<<endl;
    return songName;
}
void chooseSong()
{
    string orderedSong;
    orderedSong = getSongName();
    int j;
    string track;
    ifstream trackList ("trackList.txt");
    if (trackList.is_open())
    {
        while ( getline (trackList,track) )
        {
            //cout<<track<<endl;
            transform(track.begin(), track.end(), track.begin(), ::toupper);
            //cout<<track<<endl;
            if(orderedSong.compare(track)==0)
            {
                cout<<"We have the song you've ordered in the track list. Now you can start singing! :)"<<endl;
                j=0;
                break;
            }
            else
            {
                j=1;
            }
        }
    }
    else
    {
        cout << "Unable to open the track list";
        exit(1);
    }
    trackList.close();
    //cout<<"j = "<<j<<endl;
    ofstream tempList;
    tempList.open("tempTrackList.txt", std::ios_base::app);

    if(j!=0)
    {
        cout<<"Sorry, we don't have the song that you've ordered. Next time you can sing it! :)"<<endl;
        if (tempList.is_open())
        {
            tempList << orderedSong << "\n";
        }
        else
        {
            cout << "Unable to open temporary track list"<<endl;
            exit(1);
        }
    }
    tempList.close();

}

void addNewSongs()
{
    ifstream tempList("tempTrackList.txt");
    string newSong;
    ofstream trackList;
    trackList.open("trackList.txt", ios_base::app);
    if(tempList.is_open())
    {
        while ( getline (tempList,newSong) )
        {
            if(trackList.is_open()){
              trackList<<newSong<<endl;
              cout<<"New songs added from last time. Now you can sing: "<<newSong<<endl;
            }
            else{
                cout<<"Can't open track list to add songs."<<endl;
                exit(1);
            }
        }
        trackList.close();
    }
    else
    {
        cout<<"Can't open tempTrackList.txt"<<endl;
        exit(1);
    }
    tempList.close();
    ofstream tempL;
    tempL.open("tempTrackList.txt",ios_base::trunc);
    tempL.close();

}

