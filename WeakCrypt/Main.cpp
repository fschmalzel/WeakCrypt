/*	Programmname:			Verschluesslung
Autor:					Felix S.
Version:				1.0
Letzte Überarbeitung:	2016/12/26 00:41
*/

#include <iostream>
#include <string>

using namespace std;

void getCryptTable(char cryptTable[6][6]) {
	char passphrase[26 + 4 + 1];//26 Buchstaben, 4 Leerzeichen, 1 Nullterminator
	char c;
	bool flag = true;
	bool exists;
	short position = 0;
	//short offset = 0;
	//Erstellung der Passphrase
	cin >> noskipws;
	cout << "Passphrase: ";
	do { //Userinput
		cin >> c;
		exists = false;
		if (c >= 65 && c <= 90) {
			c += 32;
		}
		if (c >= 97 && c <= 122) {
			for (int i = 0; i < 25; i++) {
				if (passphrase[i] == c) {
					exists = true;
				}
			}
			if (exists == false) {
				passphrase[position] = c;
				position++;
			}
		}
		/*else if (c == ' ' && offset < 4) {
			passphrase[position] = c;
			position++;
			offset++;
		}*/
	} while (c != '\n');
	cin >> skipws;

	for (char i = 97; i <= 122; i++) {//Auffüllen mit den restlichen Buchstaben des Alphabets
		exists = false;
		//for (int i2 = 0; i2 <= 29; i2++) {
		for (int i2 = 0; i2 <= 25; i2++) {
			if (i == passphrase[i2]) {
				exists = true;
			}
		}
		if (exists == false) {
			passphrase[position] = i;
			position++;
		}
	}

	//for (short i = 26 + offset; i <= 29; i++) {//Die letzten 4 Zeichen sind Leerzeichen und ein Nullterminator
	for (short i = 26; i <= 29; i++) {
		passphrase[i] = ' ';
	}

	passphrase[26 + 4] = '\0';
	//cout << passphrase << endl;

	for (int i = 0; i <= 6 - 1; i++) { //Konvertieren des 1-dimensionalen Arrays zu dem 2-dimensionalen Array
		for (int j = 0; j <= 6 - 1; j++) {
			if (j < 5) {
				cryptTable[i][j] = passphrase[i * 5 + j];
			}
			else {
				cryptTable[i][j] = '\0';
			}
		}
	}

}

char* getCharInput() {
	char c;
	unsigned int arrayLength = 0;
	char* inputString;
	char* placeholder;
	inputString = new char[1];
	inputString[arrayLength] = '\0';
	cin >> noskipws;
	do {
		cin >> c;
		if (c >= 65 && c <= 90) {
			c += 32;
		}
		if ((c >= 97 && c <= 122) || (c == ' ')) {
			placeholder = inputString;
			inputString = new char[arrayLength + 2];
			for (unsigned int i = 0; i <= arrayLength; i++) {
				inputString[i] = placeholder[i];
			}
			delete[] placeholder;
			inputString[arrayLength] = c;
			inputString[arrayLength + 1] = '\0';
			arrayLength++;
		}
	} while (c != '\n' || arrayLength == 0);

	cin >> skipws;

	return inputString;
}

short findCharInVeTa(char cryptTable[6][6], char c) {
	for (short i = 0; i <= 5; i++) {
		for (short j = 0; j <= 4; j++) {
			if (cryptTable[i][j] == c) {
				return (i + 1) * 10 + j + 1;
			}
		}
	}
	return 255;
}

void encrypt(char cryptTable[6][6], char *input, short *output, unsigned int len) {
	for (unsigned int i = 0; i < len; i++) {
		output[i] = findCharInVeTa(cryptTable, input[i]);
	}
}

int main() {
	//ASCII 97 - 122 inklusive
	char cryptTable[6][6];
	char *inputString;
	short *outputArray;
	unsigned int arrayLength = 0;
	int i = 0;

	getCryptTable(cryptTable);
	cout << "Text: ";
	inputString = getCharInput();
	while (inputString[arrayLength] != '\0') {
		arrayLength++;
	}

	//cout << inputString << endl;
	outputArray = new short[arrayLength + 1];
	outputArray[arrayLength] = 0;

	encrypt(cryptTable, inputString, outputArray, arrayLength);
	cout << "Encrypted Text: ";
	while (outputArray[i] != 0) {
		cout << outputArray[i] << ' ';
		i++;
	}

	cout << endl;
	system("pause");
	return 0;

}

