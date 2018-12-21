#include"saveslot.h"


SaveSlot::SaveSlot(int number,string root) {
	this->number = number;
	generateDefaultName();
	this->root=root;
	path= root + name + ".save";
	//string PATH = root + name + ".save";
	const char *c_s = path.c_str();

	//fopen_s(&saveFile, c_s, "r");
	//loadInfo(); �����ǩ
	//UserConfigs.checkCorruption(this); �û�����
}

void SaveSlot::createFile(){
	if (isEmpty())
	{
		fopen_s(&saveFile, path.c_str(), "w+");
		fclose(saveFile);
	}
}

SaveSlot::SaveSlot(int number, string name,string root) {
	this->number = number;
	this->root = root;
	this->name = name;
	path = root + name;
	const char *c_s=path.c_str();

	//fopen_s(&saveFile, c_s, "r");
	//loadInfo();
	//UserConfigs.checkCorruption(this);
}

void SaveSlot::reName(string name) {
	string oldpath = path;
	string newpath = root + name + ".save";
	if (oldpath != "")
	{
		rename(oldpath.c_str(), newpath.c_str());
		path = newpath;
		//fopen_s(&saveFile, path.c_str(), "w+");
		//fclose(saveFile);
	}
	else
	{
		cout << "�浵������";
	}
}
void SaveSlot::deletefile() {
	
	name = "";
	root = "";
	number = -1;
	const char *c_s = path.c_str();
	if (remove(c_s) == 0)
	{
		cout << "ɾ���ɹ�"<<endl;
	}
	else
	{
		cout << "ɾ���浵ʧ��"<<endl;
	};

	path = "";
}