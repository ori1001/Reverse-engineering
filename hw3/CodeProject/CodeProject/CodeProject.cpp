#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <iostream>
#define MY_LEN 1000

void our_decrypt2(char* inp)
{

    char tocmp[5][200] = { "What would you like to do?",
        "[1] ECHO - ping the server with a custom message, receive the same.",
        "[2] DMSG - Download message from the server.",
        "[3] TIME - Get local time from server point of view.",
        "[4] HNKH - Request a spinning top for Hanukkah!" };
    bool dectyptqm = true; // decrypt?
    for (int i = 0; i < 5; i++)
    {
        if (strncmp(tocmp[i], inp, strlen(tocmp[i])) == 0)
        {
            dectyptqm = false;
        }
    }
    if (!dectyptqm)
    {
        std::ofstream mfile("E:\\Nir\\Technion\\sem6 Spring 2023\\Revese engeneering\\Reverse-engineering\\hw3\\CodeProject\\t.txt", std::ios_base::app);
        mfile << "HAHAHA we did not decrypt!" << std::endl;
        mfile.close();
        return;
    }

    int i = 0; //read_idx
    int k = 0; //write idx
    while (inp[i] != '\0')
    {
        if (inp[i] > '~' || inp[i] < ' ')
        {
            inp[k] = inp[i];
            k++; i++;
        }
        else
        {
            int int_let = 0;
            for (int j = 0; j < 2; j++)
            {
                if (inp[i + 1] == '+')
                {
                    int_let += inp[i] - '0' + inp[i + 2] - '0';
                    i += 3;
                }
                else if (inp[i + 1] == '-')
                {
                    i += 3;
                }
                else if (inp[i] >= '2' && inp[i] <= '9')
                {
                    int_let += inp[i] - '0';
                    i++;
                }
                else
                {
                    switch (inp[i])
                    {
                    case 'A':
                        int_let += 1;
                        break;
                    case 'J':
                        int_let += 10;
                        break;
                    case 'Q':
                        int_let += 11;
                        break;
                    case 'K':
                        int_let += 12;
                        break;
                    default:
                        int_let += inp[i];
                    }
                    i++;
                }
                if (j == 0) {
                    int_let = int_let << 4;
                }
            }
            inp[k++] = int_let;
        }
    }
    inp[k++] = '\0';
}

int main2()
{
    char msg[1024];
    std::cin >> msg;
    our_decrypt2(msg);
    std::cout << msg;
    return 0;
}