#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace std;

sf::TcpSocket socket;
char receivedText[2000];
size_t sizeOfReceivedData;
bool shouldreceive=true;
bool shouldwrite=true;
string temp;
sf::IpAddress myIp=sf::IpAddress::getLocalAddress();
sf::IpAddress targetIp;
char choice;
string text="Connected to: ";
string textToSend;
string targetIpString;

void Receive()
{
    while(shouldreceive)
    {
        socket.receive(receivedText, sizeof(receivedText), sizeOfReceivedData);
        if(sizeOfReceivedData > 0)
        {
            cout << endl << "<<< " <<receivedText << endl << ">>> ";
        }
    }
}

int main()
{
    cout << "s: server, c:client" << endl;
    cin >> choice;
    getline(cin, temp);
    if(choice=='s')
    {
        cout << "server ip is: " << myIp << endl;
        sf::TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);
        text += "Server";
    }
    else if(choice=='c')
    {
        cout << "what's your server ip: ";
        getline(cin, targetIpString);
        targetIp=targetIpString;
        socket.connect(targetIp, 2000);
        text += "Client";
    }
    socket.send(text.c_str(), text.length()+1);
    socket.receive(receivedText, sizeof(receivedText), sizeOfReceivedData);
    cout << receivedText << endl << "if you want to exit type \"exit\"" << endl;
    thread Receiver(Receive);
    while(shouldwrite)
    {
        cout << ">>> ";
        getline(cin, textToSend);
        if(textToSend=="exit")
        {
            shouldwrite=false;
            break;
        }
        socket.send(textToSend.c_str(), textToSend.length()+1);
    }
    shouldreceive=false;
    Receiver.join();
    return 0;
}
