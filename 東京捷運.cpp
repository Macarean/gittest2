#include<iostream>
#include<list>
#include<cstring>
#include<string>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

class graph {
public:
	string letter = "";
	string name = "";
	int num = 0;
	int milage = 0;
	int i = 0;
	int j = 0;
	int rec_num = -1;
	graph* next = nullptr;
	graph* prev = nullptr;
	list<graph>add;//存額外的位置
	void addition(graph &buffer) {
		add.push_back(buffer);
		/*if (next != nullptr) {

			buffer.add.push_back(*(next->prev));
		}
		else if(prev!=nullptr){
			buffer.add.push_back(*(prev->next));
		}*/
		/*if (add.empty()) {
			
		}*/
		/*else {
			int rec = 0;
			for (int i = 0; i < add.size(); i++) {
				if (buffer.name == name) {
					rec = 1;
					break;
				}
			}
			if (rec == 1) {
				return;
			}
			if (rec == 0) {
				add.push_back(&buffer);
				if (next != nullptr) {

					buffer.addition(*(next->prev));
				}
				else {
					buffer.addition(*(prev->next));
				}
			}
		}*/
	}
	string operator<<(graph p) {
		return p.name;
	}
	/*graph operator[](int p) {
		list<graph>::iterator buffer;
		buffer = add.begin().
	}*/
};

struct rec_po {
	int s_i = 0;
	int s_j = 0;
	int e_i = 0;
	int e_j = 0;
};



//初始化好
void inimap(graph**& map);

void output(graph**& map);

//找起始點 找終點
void find_name(graph**& map,rec_po &position,string start[], graph*& com_map);

//找所有路
void find_way(graph**& map, rec_po position, string letter_list[], graph*& com_map,int cost[][61], string map_letter[][61],int num[][61]);

//比較所有路
void compare_way(graph**& map,rec_po position, graph*& com_map, int cost[][61], vector<graph>recpo[61], string map_letter[][61], int num[][61]);

int choose(int distance[], bool found[]);

int DFS(bool found[], int& num, vector<graph>recpo[61], int u, int j);

int main(int argc, char* argv[]) {
	ifstream fin1;
	//fin1.open(argv[1]);
	graph** map = new graph * [15]{};
	graph* com_map = new graph [61]{};
	//inimap(map);
	fin1.open("S1-input.txt", ios::in);
	string a;
	int col = 0;
	int row = 0;
	int rec = 0;
	string buffer;
	string start[2] = {};
	bool stop = false;
	while (!fin1.eof()) {
		map[col] = new graph[40]{};

		while (getline(fin1, a)) {
			if (a == "target:") {
				stop = true;
				break;
			}
			if (a.empty()) {
				map[col][row - 1].next = nullptr;
				break;
			}
			else {
				map[col][row - 1].next = &map[col][row];
			}
			map[col][row].letter = a[0];
			map[col][row].i = col;
			map[col][row].j = row;
			if (((int)a[1] <= 65 && (int)a[1] >= 90) || (int)a[1] >= 97 && (int)a[1] <= 122) {
				map[col][row].letter += a[1];
				a.erase(a.begin() + 1);
			}
			if ((int)a[2] < 65 && (int)a[3] < 65) {
				map[col][row].num = (((int)a[2]) - 48) * 10 + ((int)a[3] - 48);//修改
				for (int i = 5; i <= a.size() - 1; i++) {
					if ((int)a[i] == 32 || (int)a[i] == 9) {
						break;
					}
					rec++;
				}
				map[col][row].name = a.substr(5, rec);
				for (int i = 6 + rec; i <= a.size() - 1; i++) {
					if ((int)a[i] == 32 || (int)a[i] == 9) {
						continue;
					}
					if (((int)a[i] <= 57 && (int)a[i] >= 48) || a[i] == '.') {
						buffer += a[i];
					}
				}
				if (!buffer.empty()) {
					int num = ((int)buffer[0] - 48) * 10 + (int)buffer[2] - 48;
					map[col][row].milage = num;
				}
			}
			else {
				map[col][row].name = a.substr(2);
			}

			if (row - 1 >= 0) {
				map[col][row].prev = &map[col][row - 1];
			}
			row += 1;
			rec = 0;
			buffer.clear();
		}
		if (stop == true) {
			break;
		}
		row = 0;
		rec = 0;
		buffer.clear();
		col += 1;
	}
	getline(fin1, a);
	rec = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '>') {
			break;
		}
		else {
			rec++;
		}
	}
	start[0] = a.substr(0, rec - 2);
	start[1] = a.substr(rec + 2);
	fin1.close();
	inimap(map);
	
	string letter_list[15] = { "A","C","C","E","F","G","H","I","M","Mb","N","S","T","Y","Z" };
	//                          0   1   2   3   4    5   6  7   8   9    10  11  12   13  14
	rec_po position;
	find_name(map,position,start,com_map);
	int cost[61][61] = {};
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			cost[i][j] = 10000;
		}
	}
	vector<graph>recpo[61];
	/*for (int i = 0; i < 59; i++) {
		cout << com_map[i].name << endl;
	}
	cout << endl;*/
	string map_letter[61][61] = {};
	int num[61][61] = {};
	find_way(map, position, letter_list, com_map, cost,map_letter,num);

	/*for (int i = 0; i < 59; i++) {
		for (int j = 0; j < 59; j++) {
			if (map_letter[i][j] == "") {
				cout << 0;
			}
			else {
				cout << map_letter[i][j] << " ";
			}
		}
		cout << endl << endl;
	}*/
	

	compare_way(map,position, com_map, cost, recpo, map_letter,num);
}


void inimap(graph**& map) {
	map[0][8].addition(map[7][4]);
	map[0][9].addition(map[3][21]);
	map[0][10].addition(map[5][8]);
	map[0][11].addition(map[6][10]);
	map[0][13].addition(map[5][11]);
	map[0][13].addition(map[12][10]);
	map[0][14].addition(map[6][14]);
	map[0][17].addition(map[3][12]);
	map[0][18].addition(map[5][19]);
	map[0][20].addition(map[14][14]);
	map[1][1].addition(map[2][19]);
	map[2][3].addition(map[4][15]);
	map[2][4].addition(map[5][2]);
	map[2][4].addition(map[14][2]);
	map[2][7].addition(map[8][14]);
	map[2][8].addition(map[6][7]);
	map[2][8].addition(map[8][15]);
	map[2][9].addition(map[6][8]);
	map[2][9].addition(map[7][8]);
	map[2][11].addition(map[7][9]);
	map[2][11].addition(map[8][18]);
	map[2][11].addition(map[12][9]);
	map[2][11].addition(map[14][8]);
	map[2][18].addition(map[6][22]);
	map[3][3].addition(map[4][12]);
	map[3][7].addition(map[10][10]);
	map[3][7].addition(map[12][6]);
	map[3][7].addition(map[13][13]);
	map[3][7].addition(map[10][10]);
	map[3][8].addition(map[7][12]);
	map[3][9].addition(map[8][21]);
	map[3][14].addition(map[11][11]);
	map[3][15].addition(map[14][11]);
	map[3][16].addition(map[12][12]);
	map[3][17].addition(map[13][21]);
	map[3][23].addition(map[10][4]);
	map[3][24].addition(map[6][4]);
	map[3][25].addition(map[5][4]);
	map[3][25].addition(map[14][3]);
	map[3][28].addition(map[8][8]);
	map[3][29].addition(map[3][1]);
	map[3][31].addition(map[8][6]);
	map[3][31].addition(map[9][4]);
	map[4][1].addition(map[13][1]);
	map[4][2].addition(map[13][2]);
	map[4][3].addition(map[13][3]);
	map[4][4].addition(map[13][4]);
	map[4][5].addition(map[13][5]);
	map[4][6].addition(map[13][6]);
	map[4][7].addition(map[13][7]);
	map[4][8].addition(map[13][8]);
	map[4][9].addition(map[13][9]);
	map[4][9].addition(map[8][25]);
	map[4][13].addition(map[8][9]);
	map[4][13].addition(map[11][2]);
	map[4][16].addition(map[5][1]);
	map[4][16].addition(map[14][1]);
	//map[5][1].addition(map[14][1]);
	//map[5][2].addition(map[14][2]);
	//map[5][4].addition(map[14][3]);
	map[5][5].addition(map[8][13]);
	map[5][6].addition(map[10][6]);
	map[5][9].addition(map[6][9]);
	//map[5][11].addition(map[12][10]);
	map[5][12].addition(map[14][9]);
	map[5][16].addition(map[6][18]);
	//map[6][7].addition(map[8][15]);
	//map[6][8].addition(map[7][8]);
	//map[6][9].addition(map[8][16]);
	map[6][13].addition(map[12][11]);
	map[7][1].addition(map[10][1]);
	map[7][2].addition(map[10][2]);
	map[7][3].addition(map[10][3]);
	//map[7][9].addition(map[8][18]);
	//map[7][9].addition(map[12][9]);
	//map[7][9].addition(map[14][8]);
	map[7][10].addition(map[11][6]);
	map[7][10].addition(map[14][7]);
	//map[8][6].addition(map[9][4]);
	map[8][8].addition(map[11][1]);
	//map[8][9].addition(map[11][2]);
	map[8][12].addition(map[10][8]);
	//map[8][18].addition(map[12][9]);
	//map[8][18].addition(map[14][8]);
	map[8][22].addition(map[10][11]);
	map[10][7].addition(map[13][16]);
	map[10][7].addition(map[14][4]);
	map[10][9].addition(map[11][4]);
	map[10][9].addition(map[13][14]);
	//map[10][10].addition(map[12][6]);
	//map[10][10].addition(map[13][13]);
	//map[11][4].addition(map[13][14]);
	map[11][5].addition(map[12][7]);
	map[11][5].addition(map[14][6]);
	//map[11][6].addition(map[14][7]);
	map[11][13].addition(map[14][12]);
	//map[12][6].addition(map[13][13]);
	//map[12][7].addition(map[14][6]);
	//map[12][9].addition(map[14][8]);
	//map[13][16].addition(map[14][4]);

}

void output(graph**& map) {
	int k = 0;
	for (int i = 0; i < 15; i++) {
		if (map[i] == nullptr) {
			break;
		}
		for (int j = 0; j < 40; j++) {
			if (map[i][j].name.empty()) {
				break;
			}
			cout << map[i][j].letter << " " << map[i][j].num << " " << map[i][j].name << " " << map[i][j].milage << " ";
			//if (!map[i][j].add.empty()) {
			//	k += 1;
			//	list<graph>::iterator buffer = map[i][j].add.begin();
			//	for (;buffer!=map[i][j].add.end();buffer++) {
			//		
			//		cout << buffer->name << " ";
			//		cout << buffer->letter << " ";
			//		cout << buffer->num << " ";
			//	}
			//	//cout << map[i][j].add.size();
			//}
			
			cout << endl;
		}
	}
	cout << k;
}

void find_name(graph**& map, rec_po& position,string start[],graph*&com_map) {
	int k = 0;
	int h = 0;
	int col = 0;

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 40; j++) {
			if (map[i][j].name.empty()) {
				break;
			}
			if (map[i][j].name == start[0]&&k!=1) {
				com_map[col] = map[i][j];
				map[i][j].rec_num = col;
				position.s_i = col;
				if (!map[i][j].add.empty()) {
					list<graph>::iterator buffer = map[i][j].add.begin();
					for (; buffer != map[i][j].add.end(); buffer++) {
						map[buffer->i][buffer->j].rec_num = col;
					}
				}
				com_map[col].rec_num = col;
				k = 1;
				col += 1;
			}
			if (map[i][j].name == start[1]&&h!=1) {
				com_map[col] = map[i][j];
				map[i][j].rec_num = col;
				position.e_i = col;
				h = 1;
				if (!map[i][j].add.empty()) {
					list<graph>::iterator buffer = map[i][j].add.begin();
					for (; buffer != map[i][j].add.end(); buffer++) {
						map[buffer->i][buffer->j].rec_num = col;
					}
				}
				com_map[col].rec_num = col;
				col += 1;
			}
			if (!map[i][j].add.empty()&&map[i][j].name!=start[0]&&map[i][j].name!=start[1]) {
				list<graph>::iterator buffer = map[i][j].add.begin();
				for (; buffer != map[i][j].add.end(); buffer++) {
					map[buffer->i][buffer->j].rec_num = col;
				}
				map[i][j].rec_num = col;
				com_map[col] = map[i][j];
				com_map[col].rec_num = col;
				col += 1;
			}
			/*
			if (k == 1 && h == 1) {
				break;
			}*/
		}
		/*if (k == 1 && h == 1) {
			break;
		}*/
	}
}

void find_way(graph**& map, rec_po position, string letter_list[], graph*& com_map, int cost[][61],string map_letter[][61], int num[][61]) {
	//找線
	//1. 轉一條是不是終點的線  next prev addition
	//2. 轉兩條判斷第二條是不是同條線
	//3. 要判斷是不是對的
	//4. 靠邀 忘記算在哪裡
	
	//vector<vector<rec_po>>total;

	//int cal_i = 0;
	//graph* pointer = &map[position.s_i][position.s_j];
	//rec_po buffer;
	//string* recs = new string[5];

	//recs[0] = map[position.s_i][position.s_j].letter;
	//for (int i = 0; i < map[position.s_i][position.s_j].add.size(); i++) {

	//}
	//if (map[position.s_i][position.s_j].letter == map[position.e_i][position.e_j].letter) {
	//	if (map[position.s_i][position.s_j].num > map[position.e_i][position.e_j].num) {
	//		while (pointer!=nullptr) {
	//			buffer.s_i = pointer->i;
	//			buffer.s_j = pointer->j;
	//			total[cal_i].push_back(buffer);
	//			if (pointer->name != map[position.e_i][position.e_j].name) {
	//				pointer = pointer->next;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//	}
	//	cal_i += 1;
	//	/*else {
	//		if (!pointer->add.empty()||!map[position.e_i][position.e_j].add.empty()) {
	//			list<graph>::iterator i = map[position.s_i][position.s_j].add.begin();
	//			list<graph>::iterator j = map[position.e_i][position.e_j].add.begin();
	//			for (; i != map[position.s_i][position.s_j].add.end(); i++) {
	//				

	//			}
	//		}
	//	}*/
	//}

	

	//有轉運站
	int k = 0;
	int milage = 0;
	graph* pointer = &map[com_map[0].i][com_map[0].j];
	for (int i = 0; i < 59; i++) {
		cost[i][i] = 0;
		pointer = &map[com_map[i].i][com_map[i].j];
		//next 
		k = com_map[i].j;
		while (pointer->next!= nullptr) {
			k += 1;
			pointer = &map[com_map[i].i][k];
			milage += pointer->milage;
			if (pointer->rec_num!=-1||(pointer->name== com_map[position.e_i].name)) {
				break;
			}
		}
		if (pointer->next != nullptr || pointer->rec_num != -1) {
			map_letter[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = com_map[i].letter;
			num[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = map[com_map[i].i][com_map[i].j].num;
			cost[i][pointer->rec_num] = milage;
			//cout << pointer->name << endl;
		}
		pointer = &map[com_map[i].i][com_map[i].j];
		milage = 0;
		k = com_map[i].j;

		//prev
		while (pointer->prev!= nullptr) {
			//milage += pointer->milage;
			milage += pointer->milage;
			k -= 1;
			pointer = &map[com_map[i].i][k];
			if (pointer->rec_num != -1 || (pointer->name == com_map[position.e_i].name)) {
				break;
			}
		}
		if (pointer->rec_num != -1&&pointer->num != 0) {
			map_letter[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = com_map[i].letter;
			num[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = map[com_map[i].i][com_map[i].j].num;
			cost[i][pointer->rec_num] = milage;
			//cout << pointer->name << endl;
		}
		pointer = &map[com_map[i].i][com_map[i].j];
		milage = 0;


		//addition  有錯
		list<graph>::iterator buffer = map[com_map[i].i][com_map[i].j].add.begin();
		for (; buffer != map[com_map[i].i][com_map[i].j].add.end(); buffer++) {
			pointer = buffer->next;
			if (pointer != nullptr) {
				while (pointer->next != nullptr) {
					milage += pointer->milage;
					if (pointer->rec_num != -1 || (pointer->name == com_map[position.e_i].name)) {
						break;
					}
					pointer = pointer->next;
					
				}
				if (pointer->next != nullptr || pointer->rec_num != -1) {
					if (cost[i][pointer->rec_num] > milage) {
						cost[i][pointer->rec_num] = milage;
						num[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = buffer->num;
						map_letter[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = buffer->letter;
					}
					
					//cost[i][pointer->rec_num] = milage;
					
					/*if (pointer->rec_num != map[com_map[i].i][com_map[i].j].next->rec_num) {
						
					}*/
					//cout << pointer->name << endl;
				}
				
			}
			
			pointer = buffer->prev;
			milage = 0;
			//prev
			if (buffer->prev != nullptr) {
				milage = buffer->milage;
				while (pointer->prev != nullptr) {
					if (pointer->rec_num != -1 || (pointer->name == com_map[position.e_i].name)) {
						break;
					}
					milage += pointer->milage;
					pointer = pointer->prev;
				}
				if (pointer->rec_num != -1&&pointer->num!=0) {
					if (cost[i][pointer->rec_num] > milage) {
						cost[i][pointer->rec_num] = milage;
						num[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = buffer->num;
						map_letter[map[com_map[i].i][com_map[i].j].rec_num][pointer->rec_num] = buffer->letter;
					}
					/*if (pointer->rec_num != map[com_map[i].i][com_map[i].j].next->rec_num) {
						
					}*/
					
					//cost[i][pointer->rec_num] = milage;
				}
			}
			
			pointer = &map[com_map[i].i][com_map[i].j];
			milage = 0;
		}
	}

}

void compare_way(graph**& map,rec_po position, graph*& com_map, int cost[][61], vector<graph>recpo[61], string map_letter[][61], int num[][61]){
	bool found[61] = { false };
	int distance[61] = {};
	int u;
	int buffer = -1;
	//int** recpo = new int* [59]{};
	int repete = 0;
	int k = 0;
	vector<int>count[61];

	for (int i = 0; i < 61; i++) {
		distance[i] = cost[position.s_i][i];
	}
	found[position.s_i] = true;
	for (int i = 0; i < 59;i++) {
		u = choose(distance, found);
		/*for (int j = 0; j < 59; j++) {
			if (j == u) {
				continue;
			}
			if (found[j] == true && cost[j][u] < distance[u]) {
				for (int m= recpo[position.s_i].size()-1; m>=0; m--) {
					if (recpo[position.s_i][m].rec_num != j) {
						cout << "pop_back: : " << recpo[position.s_i][recpo[position.s_i].size() - 1].name << endl;
						recpo[position.s_i].pop_back();
					}
					else if (recpo[position.s_i][m].rec_num == j) {
						break;
					}
				}
				distance[u] = cost[j][u];
				if (recpo[position.s_i].empty()) {
					recpo[position.s_i].push_back(com_map[j]);
				}
				repete = 1;
				break;
			}

		}*/
		//if (buffer != -1) {
		//	for (int j = 0; j < recpo[buffer].size(); j++) {
		//		if (u == recpo[buffer][j].rec_num) {
		//			repete = 1;
		//			break;
		//		}
		//	}
		//	//還有連接上下
		//	if (cost[buffer][u] != 10000) {
		//		repete = 1;
		//	}
		//}
		//if (!recpo[position.s_i].empty() && repete == 0) {
		//	cout << "pop_back: : " << recpo[position.s_i][recpo[position.s_i].size() - 1].name << endl;
		//	recpo[position.s_i].pop_back();
		//}
		if (u == -1) {
			break;
		}
		recpo[position.s_i].push_back(com_map[u]);
		cout << "push_back: " << recpo[position.s_i][recpo[position.s_i].size() - 1].name <<" "<< distance[u] << endl;
		
		if (u == position.e_i) {
			break;
		}

		found[u] = true;
		
		buffer = u;

		for (int j = 0; j < 61; j++) {
			if (!found[j]) {
				if (distance[u] + cost[u][j] < distance[j]) {//v->u->j   vs   v->j 
					//cout << com_map[j].name << " " << distance[j] << "-->";
					/*if (com_map[j].name == "Jimbocho") {
						system("pause");
					}*/
					/*int num1 = distance[j];
					recpo[j].push_back(com_map[u]);
					int num2 = distance[u] + cost[u][j];
					int num3 = DFS(found, num3, recpo, u, j);

					if (count[j].empty()) {
						count[j].push_back(num3);
						distance[j] = distance[u] + cost[u][j];
					}
					else {
						if (num3 < count[j][count[j].size() - 1]) {
							count[j].pop_back();
							count[j].push_back(num3);
							distance[j] = distance[u] + cost[u][j];
						}
						else {
							recpo[j].pop_back();
						}
					}*/


					distance[j] = distance[u] + cost[u][j];
					recpo[j].push_back(com_map[u]);
					//for (int k = 0; k< 59; k++) {
					//	if (k == j) {
					//		continue;
					//	}
					//	if (found[k] == true/*&&cost[k][j]<10000*/) {//處理直達問題
					//		for (int m = 0; m < 59; m++) {
					//			if (distance[k] + cost[k][m] + cost[m][j] < distance[j]) {
					//				cout << com_map[k].name << " " <<"-->"<< com_map[m].name<<"-->"<< com_map[j].name << distance[j] << "-->";
					//				distance[j] = distance[k] + cost[k][m] + cost[m][j];

					//				repete = k;
					//			}
					//		}
					//	}
					//}
					//cout << distance[j] << endl;
					k = 1;
					repete = 0;
				}
			}
		}
		//cout<<endl;
		/*for (int j = 0; j < 59; j++) {
			cout << distance[j] << " ";
		}
		cout << endl;*/
		/*if (k == 0) {
			if (!recpo[position.s_i].empty()) {
				cout << "pop_back: : " << recpo[position.s_i][recpo[position.s_i].size() - 1].name << endl;
				recpo[position.s_i].pop_back();
			}
		}*/
		k = 0;
	}
	cout << distance[position.e_i];
	cout << endl;
	vector<graph>output;
	output.push_back(com_map[position.e_i]);
	int buffer1 = position.e_i;
	int buffer3 = 0;



	while (1) {
		if (recpo[buffer1].size() == 0) {
			output.push_back(com_map[position.s_i]);
			break;
		}
		output.push_back(recpo[buffer1][recpo[buffer1].size() - 1]);
		if (recpo[buffer1][recpo[buffer1].size() - 1].rec_num == position.s_i) {
			break;
		}
		buffer3 = recpo[buffer1][recpo[buffer1].size() - 1].rec_num;
		buffer1 = buffer3;
	}


	/*for (int i = 0; i < output.size(); i++) {
		cout << output[i].name<<" "<< output[i].rec_num << " ";
	}*/
	

	string letter;
	int buffer2 = 0;
	if (map_letter[position.s_i][output[output.size() - 2].rec_num] == com_map[position.s_i].letter) {
		letter = com_map[position.s_i].letter;
		buffer2 = com_map[position.s_i].num;
	}
	else {
		list<graph>::iterator i = map[com_map[position.s_i].i][com_map[position.s_i].j].add.begin();
		for (; i !=map[com_map[position.s_i].i][com_map[position.s_i].j].add.end(); i++) {
			//cout << map_letter[position.s_i][output[output.size() - 2].rec_num];
			if (i->letter == map_letter[position.s_i][output[output.size() - 2].rec_num]) {
				letter = i->letter;
				buffer2 = i->num;
				break;
			}
		}
	}

	cout << letter << "-" ;
	if (buffer2 < 10) {
		cout << 0;
	}
	cout << buffer2 << " " << com_map[position.s_i].name << " -> ";
	
	if (letter != map_letter[output[output.size() - 2].rec_num][output[output.size() - 3].rec_num]) {
		cout << letter << "-";
		if (num[output[output.size() - 2].rec_num][position.s_i] < 10) {
			cout << 0;
		}
		cout<< num[output[output.size() - 2].rec_num][position.s_i] << " " << com_map[output[output.size() - 2].rec_num].name << " -> ";
		cout << map_letter[output[output.size() - 2].rec_num][output[output.size() - 3].rec_num] << "-" ;
		if (num[output[output.size() - 3].rec_num][output[output.size() - 2].rec_num] < 10) {
			cout << 0;
		}
		cout << num[output[output.size() - 2].rec_num][output[output.size() - 3].rec_num] << " " << com_map[output[output.size() - 2].rec_num].name << " -> ";
		letter = map_letter[output[output.size() - 2].rec_num][output[output.size() - 3].rec_num];
	}

	/*cout << endl;
	for (int i = output.size() - 1; i >= 0; i--) {
		if (i - 1 < 0) {
			break;
		}
		cout << map_letter[output[i].rec_num][output[i-1].rec_num];
	}*/

	for (int i = output.size()-3; i >= 0; i--) {//找起始點
		
		if (i - 1 < 0) {
			break;
		}
		if (map_letter[output[i].rec_num][output[i-1].rec_num] == letter) {
			continue;
		}

		cout<<letter<<"-";
		if (num[output[i].rec_num][output[i + 1].rec_num] < 10) {
			cout << 0;
		}
		cout << num[output[i].rec_num][output[i + 1].rec_num] << " " << output[i].name << " -> ";
		letter = map_letter[output[i].rec_num][output[i -1].rec_num];
		cout << map_letter[output[i].rec_num][output[i-1].rec_num] << "-" ;
		if (num[output[i].rec_num][output[i - 1].rec_num] < 10) {
			cout << 0;
		}
		cout << num[output[i].rec_num][output[i - 1].rec_num] << " " << output[i].name << " -> ";
	}
	
	cout << map_letter[output[1].rec_num][output[0].rec_num] << "-" ;
	if (num[output[0].rec_num][output[1].rec_num] < 10) {
		cout << 0;
	}
	cout << num[output[0].rec_num][output[1].rec_num] << " " << output[0].name;


	/*for (int i = 0; i < recpo[position.s_i].size(); i++) {
		cout << recpo[position.s_i][i].name<< " ";
	}*/
}

int choose(int distance[],bool found[]) {
	int i, min, minpos;
	min = 10000;
	minpos = -1;
	for (int i = 0; i < 59; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

int DFS(bool found[],int &num, vector<graph>recpo[61],int u,int j) {
	
	int buffer = 0;
	while (1) {
		if (!recpo[j].empty()) {
			j=recpo[j][recpo[j].size() - 1].rec_num;
			buffer += 1;
		}
		if (recpo[j].empty()) {
			buffer += 1;
			return buffer;
		}
	}
	
}