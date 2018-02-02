// Sync_Client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

	// endpoint : 접속할 서버의 IP, PORT 지정
	// from_string을 통해 문자열을 Asio에서 사용하는 IP주소로 변환해준다.
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT);

	boost::system::error_code connect_error;
	boost::asio::ip::tcp::socket socket(io_service);

	// connect : 접속이 성공 or 실패 할때까지 대기한다.
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

	// is_open() == true 라면 연결된 상태
	if(socket.is_open())
	{
		socket.close();
	}

	getchar();
	return 0;

	return 0;
}

