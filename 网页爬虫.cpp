#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "winsock2.h"
#include <time.h>
#include <queue>
#include <hash_set>

#define MAX_URL_LEN  2083   //����url �ĳ���
#define HOST_NAME    256

#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define DEFAULT_PAGE_BUF_SIZE 1048576

queue<string> hrefUrl;
hash_set<string> visitedUrl;
hash_set<string> visitedImg;
//int g_depth = 0;
int g_ImgCnt = 1;

/*************************************
 * ������������URL���н������õ�����������Դ��
 *
 * ����ֵ�� �ɹ� - ture , ʧ�� - false
 *************************************/

bool ParseURL(const string & url, string & host, string & resource) {
	char pHost[HOST_NAME];
	char pResource[MAX_URL_LEN];
	const char * pos = NULL;

	if (strlen(url.c_str()) > MAX_URL_LEN) {
		return false;
	}
	
	//��λ��������λ��
	pos = strstr(url.c_str(), "http://");

	if (pos == NULL) {
		pos = url.c_str();
	}else {
		pos += strlen("http://");
	}

	if (strstr(pos, "/") == 0) {
		return false;
	}
	
	sscanf_s(pos, "%[^/]%s", pHost, HOST_NAME, pResource, MAX_URL_LEN);
	host = pHost;
	resource = pResource;
	return true;
}

/********************************************
 *���ܣ�����http Get���󵽷���������ȡ��Ӧҳ��
 *����ֵ�� �ɹ� - ture , ʧ�� - false
 ********************************************/
bool GetHttpResponse(const string &url, char * &response, int &bytesRead) {
	string host, resource;
	if (!ParseURL(url, host, resource)) {
		cout << "Can not parse the url" << endl;
		return false;
	}

	//������������ȡ������Ӧ��ip��ַ
	struct hostent * hp = gethostbyname(host.c_str());
	if (hp == NULL) {
		cout << "Can not find host address" << endl;
		return false;
	}


	//�����׽���
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1 || sock == -2) {
		cout << "Can not create sock." << endl;
		return false;
	}

	//������������ַ
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80);
	memcpy(&sa.sin_addr, hp->h_addr, 4);

	//��������
	if (0 != connect(sock, (SOCKADDR*)&sa, sizeof(sa))) {
		cout << "Can not connect to : " << url << endl;
		closesocket(sock);
		return false;
	};

	//׼������http ��������
	string request = "GET " + resource + " HTTP/1.1\r\nHost:" + host + "\r\nConnection:Close\r\n\r\n";

	//��������
	if (SOCKET_ERROR == send(sock, request.c_str(), request.size(), 0)) {
		cout << "send error" << endl;
		closesocket(sock);
		return false;
	}

	//��������
	int contentLength = DEFAULT_PAGE_BUF_SIZE;
	char *pageBuf = (char *)malloc(contentLength);
	memset(pageBuf, 0, contentLength);

	bytesRead = 0;
	int ret = 1;
	cout << "Read: ";
	while (ret > 0) {
		ret = recv(sock, pageBuf + bytesRead, contentLength - bytesRead, 0);

		if (ret > 0)
		{
			bytesRead += ret;
		}

		if (contentLength - bytesRead<1024) {
			cout << "\nRealloc memorry" << endl;
			contentLength *= 2;
			pageBuf = (char*)realloc(pageBuf, contentLength);       //���·����ڴ�
		}
		cout <<" read: "<< ret << " ";
	}
	cout << endl;

	pageBuf[bytesRead] = '\0';
	response = pageBuf;
	closesocket(sock);
	return true;
	
}

//
/********************************************
*���ܣ�  ��ȡ���е���ҳURL�Լ�ͼƬ��Ӧ��URL
*����ֵ�� �ɹ� - ture , ʧ�� - false
********************************************/
void HTMLParse(string & htmlResponse, vector<string> & imgurls, const string & host) {
	//���������ӣ�����queue��
	const char *p = htmlResponse.c_str();
	char *tag = "href=\"";
	const char *pos = strstr(p, tag);
	ofstream ofile("url.txt", ios::app);
	while (pos) {
		pos += strlen(tag);
		const char * nextQ = strstr(pos, "\"");
		if (nextQ) {
			char * url = new char[nextQ - pos + 1];
			//char url[100]; //�̶���С�Ļᷢ�������������Σ��
			sscanf(pos, "%[^\"]", url);
			string surl = url;  // ת����string���ͣ������Զ��ͷ��ڴ�
			if (visitedUrl.find(surl) == visitedUrl.end()) {
				visitedUrl.insert(surl);
				ofile << surl << endl;
				hrefUrl.push(surl);
			}
			pos = strstr(pos, tag);
			delete[] url;  // �ͷŵ�������ڴ�
		}
	}
	ofile << endl << endl;
	ofile.close();

	tag = "<img ";
	const char* att1 = "src=\"";
	const char* att2 = "lazy-src=\"";
	const char *pos0 = strstr(p, tag);
	while (pos0) {
		pos0 += strlen(tag);
		const char* pos2 = strstr(pos0, att2);
		if (!pos2 || pos2 > strstr(pos0, ">")) {
			pos = strstr(pos0, att1);
			if (!pos) {
				pos0 = strstr(att1, tag);
				continue;
			}
			else {
				pos = pos + strlen(att1);
			}
		}
		else {
			pos = pos2 + strlen(att2);
		}

		const char * nextQ = strstr(pos, "\"");
		if (nextQ) {
			char * url = new char[nextQ - pos + 1];
			sscanf(pos, "%[^\"]", url);
			cout << url << endl;
			string imgUrl = url;
			if (visitedImg.find(imgUrl) == visitedImg.end()) {
				visitedImg.insert(imgUrl);
				imgurls.push_back(imgUrl);
			}
			pos0 = strstr(pos0, tag);
			delete[] url;
		}
	}
	cout << "end of Parse this html" << endl;
}

/*********************************************
 *��URLת��Ϊ�ļ���,ת�������ַ����Ᵽ��ʧ��
 *������
 *      url - ��ת����url·��
 *����ֵ��
 *      ת������ַ���
 *********************************************/
string UrlToFileName(const string &url) {
	string fileName;
	fileName.resize(url.size());
	int k = 0;
	for (int i = 0; i<(int)url.size(); i++) {
		char ch = url[i];
		if (ch != '\\'&&ch != '/'&&ch != ':'&&ch != '*'&&ch != '?'&&ch != '"'&&ch != '<'&&ch != '>'&&ch != '|') {
			fileName[k++] = ch;
		}
		else {
			fileName[k++] = '-';
		}
	}
	return fileName.substr(0, k) + ".txt";
}


/*********************************************
*����ͼƬ�б����浽img�ļ���
*������
*      url - ͼƬ��Ӧ��·������������ת���ɱ���ͼƬ���ļ��е�����
*      immgurls - �����ص�ͼƬ�б�
*����ֵ��
*      ��
*********************************************/
void DownLoadImg(vector<string> & imgurls, const string &url) {

	//���ɱ����url��ͼƬ���ļ���
	string foldname = UrlToFileName(url);
	foldname = "./img/" + foldname;
	if (!CreateDirectory(foldname.c_str(), NULL))
		cout << "Can not create directory:" << foldname << endl;
	char *image;
	int byteRead;
	for (unsigned int i = 0; i<imgurls.size(); i++) {
		//�ж��Ƿ�ΪͼƬ��bmp��jgp��jpeg��gif 
		string str = imgurls[i];
		int pos = str.find_last_of(".");
		if (pos == string::npos)
			continue;
		else {
			string ext = str.substr(pos + 1, str.size() - pos - 1);
			if (ext != "bmp"&& ext != "jpg" && ext != "jpeg"&& ext != "gif"&&ext != "png")
				continue;
		}
		//�������е�����
		if (GetHttpResponse(imgurls[i], image, byteRead)) {
			if (strlen(image) == 0) {
				continue;
			}
			const char *p = image;
			const char * pos = strstr(p, "\r\n\r\n") + strlen("\r\n\r\n");
			int index = imgurls[i].find_last_of("/");
			if (index != string::npos) {
				string imgname = imgurls[i].substr(index, imgurls[i].size());
				ofstream ofile(foldname + imgname, ios::binary);
				if (!ofile.is_open())
					continue;
				cout << g_ImgCnt++ << foldname + imgname << endl;
				ofile.write(pos, byteRead - (pos - p));
				ofile.close();
			}
			free(image);
		}
	}
}



/************************************************
 *���ñ����ķ�ʽ��ȡ��ҳ�е�url
 *������
 *     url - Ŀ��url 
 *����ֵ��
 *        ��
*************************************************/
void WebSpider(const string &url) {
	char * response;
	int bytes;
	// ��ȡ��ҳ����Ӧ������response�С�
	if (!GetHttpResponse(url, response, bytes)) {
		cout << "The url is wrong! ignoring..." << endl;
		return;
	}
	string httpResponse = response;
	free(response);
	string filename = UrlToFileName(url);
	ofstream ofile("./html/" + filename);
	if (ofile.is_open()) {
		// �������ҳ���ı�����
		ofile << httpResponse << endl;
		ofile.close();
	}
	vector<string> imgurls;
	//��������ҳ�����ڱ���վ����ҳ���ӣ��Լ�����ͼƬ���ӣ�����imgurls����
	HTMLParse(httpResponse, imgurls, url);
	
	//�������е�ͼƬ��Դ
	DownLoadImg(imgurls, url);
}

void main()
{
	//��ʼ��socket������tcp��������
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return;
	}

	// �����ļ��У�����ͼƬ����ҳ�ı��ļ�
	CreateDirectory("./img", 0);
	CreateDirectory("./html", 0);

	string  kongjie1 = "http://www.xinkongjie.com/d/file/meinv/mnkj/2019-02-26/6552ef0eafbbe01f358e9fd1a6cb8e54.jpg";

	//WebSpider(kongjie1);
	vector<string> imgurls;
	imgurls.push_back(kongjie1);

	DownLoadImg(imgurls, "www.xinkongjie.com/d");



	/*
	string urlStart = "http://www.xinkongjie.com/meinv/";

	
	// ʹ�ù�ȱ���
	// ��ȡ��ҳ�еĳ����ӷ���hrefUrl�У���ȡͼƬ���ӣ�����ͼƬ��
	WebSpider(urlStart);

	// ���ʹ�����ַ��������
	visitedUrl.insert(urlStart);

	while (hrefUrl.size() != 0) {
		string url = hrefUrl.front();  // �Ӷ��е��ʼȡ��һ����ַ
		cout << url << endl;
		WebSpider(url);					  // ������ȡ�������Ǹ���ҳ����������ĳ�������ҳ����hrefUrl��������������ı���ͼƬ
		hrefUrl.pop();                 // ������֮��ɾ�������ַ

		if (g_ImgCnt > 50) break;
	}

	*/
	WSACleanup();
	return;
}