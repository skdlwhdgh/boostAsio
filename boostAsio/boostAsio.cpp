// boostAsio.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>
#include <array>

// ������ ����
int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	const char SERVER_IP[] = "127.0.0.1";
	const unsigned short PORT = 8000;

	// I/O �̺�Ʈ�� ����ġ ���ִ� Ŭ����. �ش� Ŭ������ ���� ��Ʈ��ũ �̺�Ʈ�� �� �� �ִ�.
	boost::asio::io_service io_service;

	// endpoint : ��Ʈ��ũ �ּ� ����.(IPv4 �ּ�ü�� ���)
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT);

	// acceptor : Ŭ���̾�Ʈ�� ������ �޾Ƶ��δ�.
	// ������ ��Ʈ��ũ�̱� ������  accept ȣ�� �� Ŭ���̾�Ʈ ������ �Ϸ� �� ������ ����Ѵ�.
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
	boost::asio::ip::tcp::socket socket(io_service);

	acceptor.accept(socket);

	cout << "client accepted" << endl;

	while(true)
	{
		char buf[128] = {0,};

		// error_code : �ý��� ������ ��� ���� Ŭ����
		boost::system::error_code error;

		// �޼��� �ޱ�. ������ ũ�� ��ȯ. ������ �̹Ƿ� �����͸� �� ���� ������ ����Ѵ�.
		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if(0 != error)
		{
			if(boost::asio::error::eof == error)
			{
				cout << "client disconnected" << endl;
			}
			else
			{
				cout << "error No: " << error.value() << " error Message: " << error.message() << endl;
			}
			break;

		}

		cout << "Recieve: " << &buf[0] << endl;

		char szMessage[128] = {0,};
		sprintf_s(szMessage, 128-1, "Re:%s", &buf[0]);

		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		// �޼����� �������� ���� �������� lenth�� �����ϸ�, szMessage�� �ִ� �����͸� ��� ������ �ʰ� ������ �縸ŭ ������.
		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);

		cout << "Echo: " << szMessage << endl;

	}

	getchar();
	return 0;

	



	return 0;
}

