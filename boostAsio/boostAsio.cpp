// boostAsio.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>
#include <array>

// 동기형 서버
int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	const char SERVER_IP[] = "127.0.0.1";
	const unsigned short PORT = 8000;

	// I/O 이벤트를 디스패치 해주는 클래스. 해당 클래스를 통해 네트워크 이벤트를 알 수 있다.
	boost::asio::io_service io_service;

	// endpoint : 네트워크 주소 설정.(IPv4 주소체계 사용)
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT);

	// acceptor : 클라이언트의 접속을 받아들인다.
	// 동기형 네트워크이기 때문에  accept 호출 후 클라이언트 접속이 완료 될 때까지 대기한다.
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
	boost::asio::ip::tcp::socket socket(io_service);

	acceptor.accept(socket);

	cout << "client accepted" << endl;

	while(true)
	{
		char buf[128] = {0,};

		// error_code : 시스템 에러를 얻기 위한 클래스
		boost::system::error_code error;

		// 메세지 받기. 데이터 크기 반환. 동기형 이므로 데이터를 다 받을 떄까지 대기한다.
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

		// 메세지를 보낼때는 보낼 데이터의 lenth를 지정하며, szMessage에 있는 데이터를 모두 보내지 않고 지정한 양만큼 보낸다.
		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);

		cout << "Echo: " << szMessage << endl;

	}

	getchar();
	return 0;

	



	return 0;
}

