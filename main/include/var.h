#pragma once

struct Var final {
	String AppData; // ��������Ŀ¼
	CLSID GUID_BMP{}; // BMP������
	CLSID GUID_JPG{}; // JPG������
	CLSID GUID_PNG{}; // PNG������
	Bin BackGroundImage; // ����ͼƬ
	Bin NewSkinWindow; // �´���Ƥ��
	ConfigEntry Config; // ������
	DataEntry Data; // ������
	VDSwitcher vds; // V/D������
	std::unordered_map<String, int> TypeMap; // �ļ�����ͼ��ӳ��
};