// Sync_Client.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;

	const char SERVER_IP[] = "127.0.0.1";
	const unsigned short PORT = 8000;

	boost::asio::io_service io_service;

	// endpoint : ������ ������ IP, PORT ����
	// from_string�� ���� ���ڿ��� Asio���� ����ϴ� IP�ּҷ� ��ȯ���ش�.
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT);

	boost::system::error_code connect_error;
	boost::asio::ip::tcp::socket socket(io_service);

	// connect : ������ ���� or ���� �Ҷ����� ����Ѵ�.
	socket.connect(endpoint, connect_error);

	if(connect_error)
	{
		cout << "connect failed. errorNo: " << connect_error.value() << ", Message: " << connect_error.message() << endl;

		getchar();
		return 0;
	}
	else
	{
		cout << "connect succeed" << endl;
	}

	int nCount = 0;
	while(true)
	{
		char szMessage[128] = {0,};
		scanf("%s", szMessage);
		sprintf_s(szMessage, 128-1, "%s", szMessage);
		int nMsgLen = strnlen_s(szMessage, 128-1);

		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);

		cout << "Send: " << szMessage << endl;

		char buf[128] = {0,};

		boost::system::error_code error;
		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if(0 != error)
		{
			if(boost::asio::error::eof == error)
			{
				cout << "server disconnected" << endl;
			}
			else
			{
				cout << "errorNo: " << error.value() << " error Message: " << error.message().c_str() << endl;
			}
			break;
		}

		cout << "Recv: " << &buf[0] << endl;

		++nCount;

	}

	// is_open() == true ��� ����� ����
	if(socket.is_open())
	{
		socket.close();
	}

	getchar();
	return 0;

	return 0;
}

