#include <iostream>
#include <cstring>
#include <vector>
#include "image.h"
#include "pbm.h"
#include "pgm.h"
#include "ppm.h"
#include "imageFactory.h"
using namespace std;

vector<vector<Image*>> sessions;
vector<vector<string>> transformations;

vector<Image*> imagesInSession;
vector<string> transformationsInSession;

bool isEqual(const char* strOne, const char* strTwo) {
	int lenOne = strlen(strOne);
	int lenTwo = strlen(strTwo);
	if (lenOne != lenTwo) return false;
	else {
		for (int i = 0; i < lenOne; i++) {
			if (strOne[i] != strTwo[i]) return false;
		}
	}
	return true;
}

//извлича само командата от въведените от потребителя входни данни
char* getCommand(const char* input) {
	int getCommandLen = 0;
	for (; input[getCommandLen] != ' ' && input[getCommandLen] != '\0'; getCommandLen++) {}
	char* command = new char[getCommandLen + 1];
	for (int i = 0; i < getCommandLen; i++) {
		command[i] = input[i];
	}
	command[getCommandLen] = '\0';
	return command;
}

//извлича името на файла (name.ppm)
char* getFilePath(const char* input) {
	int getCommandLen = 0;
	for (; input[getCommandLen] != ' '; getCommandLen++) {}
	getCommandLen++;// +1 за " "
	char* filePath = new char[strlen(input) - getCommandLen];

	for (int i = 0; i < strlen(input) - getCommandLen; i++) {
		filePath[i] = input[i + getCommandLen];
	}
	filePath[strlen(input) - getCommandLen] = '\0';
	return filePath;
}

//извлича разширението/формата на файла
char* getExtension(const char* input) {
	char* extension = new char[4];
	extension[3] = '\0';
	for (int i = 2; i >= 0; i--) {
		extension[i] = input[strlen(input) - 3 + i];
	}
	return extension;
}

void loadTxtInformation(const char* file) {
	ifstream info;
	info.open(file, ios::in);
	if (info.is_open()) {
		char line[200];
		while (!info.eof()) {
			info.getline(line, 200);
			cout << line << endl;
		}
		info.close();
	}
	else cout << "There was a problem loading the information." << endl;
}


int main(){
	sessions.clear();
	transformations.clear();
	
	loadTxtInformation("menu.txt");

	char choice[30];
	cout << "Your choice:\n >> ";
	cin.getline(choice, 30);

	while (!isEqual(getCommand(choice), "Exit") || !isEqual(getCommand(choice), "exit")) {
		if (isEqual(getCommand(choice), "load")) {
			cout << "--------------------------------------------------\n";
			cout << "Session with ID: "<< sessions.size()+1 <<" started.\n";

			imagesInSession.clear();
			transformationsInSession.clear();
			
			//задаваме възможните трансформации да са "невалидни", което по желание на потребителя по време на действие на програмата се променя
			//стартираме с 0 изображения всяка сесия
			int imagesInSessionCount = 0;
			bool monochrome = false;
			bool negative = false;
			bool grayscale = false;

			//създаваме обект от съответния тип, ако е валиден, и с него зареждаме желаното изображение
			imagesInSession.push_back(ImageFactory::make(getExtension(choice)));
			imagesInSession[imagesInSessionCount]->load(getFilePath(choice));
			cout << "Image "<< imagesInSession[imagesInSessionCount]->getImageName() << " added.\n";

			cout << "\nYour next choice:\n >> ";
			cin.getline(choice, 30);

			while (!isEqual(getCommand(choice), "load") && !isEqual(getCommand(choice), "switch") && !isEqual(getCommand(choice), "info") ) {

				if (isEqual(getCommand(choice), "add")) {
					imagesInSessionCount++;
					imagesInSession.push_back(ImageFactory::make(getExtension(choice)));
					imagesInSession[imagesInSessionCount]->load(getFilePath(choice));
					cout << "Image " << imagesInSession[imagesInSessionCount]->getImageName() << " added.\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "collage")) {
					cout << "Horizontal / Vertical ?\n >>";
					cin.getline(choice, 30);
					if (isEqual(choice, "Horizontal") || isEqual(choice, "horizontal")) {
						char imageOne[30];
						cout << "Name of the first image: ";
						cin.getline(imageOne, 30);
						char imageTwo[30];
						cout << "Name of the first image: ";
						cin.getline(imageTwo, 30);

						//проверяваме дали изображенията са от еднакъв тип и ако да - правим колаж
						if (isEqual(getExtension(imageOne), getExtension(imageTwo))) {
							imagesInSessionCount++;
							char collageName[30];
							cout << "Name of the collage: ";
							cin.getline(collageName, 30);
							imagesInSession.push_back(ImageFactory::make(getExtension(imageOne)));
							imagesInSession[imagesInSessionCount]->makeHorizontalCollage(imageOne, imageTwo, collageName);

						}
						else cout << "Cannot make a collage from different types!";
					}

					else if (isEqual(choice, "Vertical") || isEqual(choice, "vertical")) {
						char imageOne[30];
						cout << "Name of the first image: ";
						cin.getline(imageOne, 30);
						char imageTwo[30];
						cout << "Name of the first image: ";
						cin.getline(imageTwo, 30);

						if (isEqual(getExtension(imageOne), getExtension(imageTwo))) {
							imagesInSessionCount++;
							char collageName[30];
							cout << "Name of the collage: ";
							cin.getline(collageName, 30);
							imagesInSession.push_back(ImageFactory::make(getExtension(imageOne)));
							imagesInSession[imagesInSessionCount]->makeVerticalCollage(imageOne, imageTwo, collageName);

						}
						else cout << "Cannot make a collage from different types!";
					}
					
					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);

				}
				else if (isEqual(getCommand(choice), "monochrome")) {
					//ако потребителят желае да се приложи някаква трансформация, то тя се записва във вектор и промена стойността си на "валидна"
					monochrome = true;
					transformationsInSession.push_back("monochrome");
					cout << "Monochrome applying..\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "negative")) {
					negative = true;
					transformationsInSession.push_back("negative");
					cout << "Negaive applying..\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "grayscale")) {
					grayscale = true;
					transformationsInSession.push_back("grayscale");
					cout << "Grayscale applying..\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "undo")) {
					//проверяваме коя е последно добавената трансформация, задаваме я като "невалидна" и я премахваме от вектора
					if (transformationsInSession[transformationsInSession.size() - 1] == "monochrome") monochrome = false;
					else if (transformationsInSession[transformationsInSession.size() - 1] == "negative") negative = false;
					else grayscale = false;
					transformationsInSession.pop_back();
					cout << "Last change undone.\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "save")) {
					for (int i = 0; i < imagesInSession.size(); i++) {
						if (monochrome && (imagesInSession[i]->getMagicNum() != "P1") && !imagesInSession[i]->isMonochrome()) {
							imagesInSession[i]->makeMonochrome();
						}
						if (grayscale && (imagesInSession[i]->getMagicNum() == "P3") && !imagesInSession[i]->isAlreadyGrayscaled()) {
							imagesInSession[i]->grayscale();
						}
						if (negative) {
							imagesInSession[i]->makeNegative();
						}

						imagesInSession[i]->save();
						cout << "Changes are saved. ";
					}

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "saveAs")) {
					
					for (int i = 0; i < imagesInSession.size(); i++) {
						if(monochrome && (imagesInSession[i]->getMagicNum() != "P1") && !imagesInSession[i]->isMonochrome()){
							imagesInSession[i]->makeMonochrome();
						}
						if (grayscale && (imagesInSession[i]->getMagicNum() == "P3") && !imagesInSession[i]->isAlreadyGrayscaled()) {
							imagesInSession[i]->grayscale();
						}
						if (negative) {
							imagesInSession[i]->makeNegative();
						}

						char newImagePath[30];
						cout << "Set new path for " << imagesInSession[i]->getImageName() << " \n  >> ";
						cin.getline(newImagePath, 30);
						imagesInSession[i]->saveAs(newImagePath);
						cout << "Saving as..\n";
					}

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "sessionInfo")) {
					cout << "\n\nImages: ";
					for (int i = 0; i < imagesInSession.size(); i++) {
						cout << imagesInSession[i]->getImageName() << " ";
					}
					cout << "\nTransformations: ";
					for (int i = 0; i < transformationsInSession.size(); i++) {
						cout << transformationsInSession[i]<< " ";
					}

					cout << "\n\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else {
					if (!isEqual(getCommand(choice), "Exit") && !isEqual(getCommand(choice), "exit")) {
						cout << "No such command\n";
						cout << "\nYour next choice:\n >> ";
						cin.getline(choice, 30);
					}
					else break;

				}
			
			}
			//добавяме текущите сесия и трансформации към векторите, съдържащи други такива
				sessions.push_back(imagesInSession);
				transformations.push_back(transformationsInSession);

		}
		else if (isEqual(getCommand(choice), "switch")) {
		    //при превключване на сесията трябва да изчислим нейния ID
			int sessionID = (int)(choice[strlen(choice) - 1] - '0');
			
			//броят на изображенията ще е равен на дължината на вектора със съответния ID 
			int imagesInSessionCount = sessions[sessionID-1].size();
			
			//при обиколка на вектора от изчакващи трансформации, булевите променливи ще придобият стойност true, 
			//ако името им бъде срещнато
			bool monochrome = false;
			bool negative = false;
			bool grayscale = false;
			
			cout << "\n--------------------------------------------------\n";
			cout << "\nYou switched to session with ID " << sessionID << "\nName of images in the session: ";
			for (int i = 0; i < sessions[sessionID - 1].size(); i++) {
				cout << sessions[sessionID - 1][i]->getImageName() << "   ";
			}

			cout << "\nPending transformations: ";
			for (int i = 0; i < transformations[sessionID - 1].size(); i++) {
				cout << transformations[sessionID - 1][i] << "   ";
				if (transformations[sessionID - 1][i] == "monochrome") monochrome = true;
				else if (transformations[sessionID - 1][i] == "negative") negative = true;
				else if (transformations[sessionID - 1][i] == "grayscale") grayscale = true;
			}

			cout << "\n\nYour next choice:\n >> ";
			cin.getline(choice, 30);
		


			while (!isEqual(getCommand(choice), "load") && !isEqual(getCommand(choice), "switch") && !isEqual(getCommand(choice), "info")) {

				if (isEqual(getCommand(choice), "add")) {
					imagesInSessionCount++;
					sessions[sessionID-1].push_back(ImageFactory::make(getExtension(choice)));
					sessions[sessionID - 1][imagesInSessionCount]->load(getFilePath(choice));
					cout << "Image " << sessions[sessionID - 1][imagesInSessionCount]->getImageName() << " added";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "collage")) {
					cout << "Horizontal / Vertical ?\n >>";
					cin.getline(choice, 30);
					if (isEqual(choice, "Horizontal") || isEqual(choice, "horizontal")) {
						char imageOne[30];
						cout << "Name of the first image: ";
						cin.getline(imageOne, 30);
						char imageTwo[30];
						cout << "Name of the first image: ";
						cin.getline(imageTwo, 30);

						if (isEqual(getExtension(imageOne), getExtension(imageTwo))) {
							imagesInSessionCount++;
							char collageName[30];
							cout << "Name of the collage: ";
							cin.getline(collageName, 30);
							sessions[sessionID - 1].push_back(ImageFactory::make(getExtension(imageOne)));
							sessions[sessionID - 1][imagesInSessionCount]->makeHorizontalCollage(imageOne, imageTwo, collageName);

						}
						else cout << "Cannot make a collage from different types!";

					}
					else if (isEqual(choice, "Vertical") || isEqual(choice, "vertical")) {
						char imageOne[30];
						cout << "Name of the first image: ";
						cin.getline(imageOne, 30);
						char imageTwo[30];
						cout << "Name of the first image: ";
						cin.getline(imageTwo, 30);

						if (isEqual(getExtension(imageOne), getExtension(imageTwo))) {
							imagesInSessionCount++;
							char collageName[30];
							cout << "Name of the collage: ";
							cin.getline(collageName, 30);
							sessions[sessionID - 1].push_back(ImageFactory::make(getExtension(imageOne)));
							sessions[sessionID - 1][imagesInSessionCount]->makeVerticalCollage(imageOne, imageTwo, collageName);

						}
						else cout << "Cannot make a collage from different types!";
					}

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);

				}
				else if (isEqual(getCommand(choice), "monochrome")) {
					monochrome = true;
					transformations[sessionID - 1].push_back("monochrome");
					cout << "Monochrome applying..\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "negative")) {
					negative = true;
					transformations[sessionID - 1].push_back("negative");
					cout << "Negaive applying..\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "grayscale")) {
					grayscale = true;
					transformations[sessionID - 1].push_back("grayscale");
					cout << "Grayscale applying..\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "undo")) {
					if (transformations[sessionID - 1][transformations[sessionID - 1].size() - 1] == "monochrome") monochrome = false;
					else if (transformations[sessionID - 1][transformations[sessionID - 1].size() - 1] == "negative") negative = false;
					else grayscale = false;
					transformations[sessionID - 1].pop_back();
					cout << "Last change undone.\n";

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "save")) {
					cout << "save..\n";
					for (int i = 0; i < sessions[sessionID - 1].size(); i++) {
						if (monochrome && (sessions[sessionID - 1][i]->getMagicNum() != "P1") && !sessions[sessionID - 1][i]->isMonochrome()) {
							sessions[sessionID - 1][i]->makeMonochrome();
						}
						if (grayscale && (sessions[sessionID - 1][i]->getMagicNum() == "P3") && !sessions[sessionID - 1][i]->isAlreadyGrayscaled()) {
							sessions[sessionID - 1][i]->grayscale();
						}
						if (negative) {
							sessions[sessionID - 1][i]->makeNegative();
						}

						sessions[sessionID - 1][i]->save();
						cout << "Changes are saved. ";
					}

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "saveAs")) {

					
					for (int i = 0; i < sessions[sessionID - 1].size(); i++) {
						if (monochrome && (sessions[sessionID - 1][i]->getMagicNum() != "P1") && !sessions[sessionID - 1][i]->isMonochrome()) {
							sessions[sessionID - 1][i]->makeMonochrome();
						}
						if (grayscale && (sessions[sessionID - 1][i]->getMagicNum() == "P3") && !sessions[sessionID - 1][i]->isAlreadyGrayscaled()) {
							sessions[sessionID - 1][i]->grayscale();
						}
						if (negative) {
							sessions[sessionID - 1][i]->makeNegative();
						}

						char newImagePath[30];
						cout << "Set new path for " << sessions[sessionID - 1][i]->getImageName() << " \n  >> ";
						cin.getline(newImagePath, 30);
						sessions[sessionID - 1][i]->saveAs(newImagePath);
					}
					cout << "Saving as...\n";
					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else if (isEqual(getCommand(choice), "sessionInfo")) {
					cout << "\nImages: ";
					for (int i = 0; i < sessions[sessionID - 1].size(); i++) {
						cout << sessions[sessionID - 1][i]->getImageName() << " ";
					}
					cout << "\nTransformations: ";
					for (int i = 0; i < transformations[sessionID - 1].size(); i++) {
						cout << transformations[sessionID - 1][i] << " ";
					}

					cout << "\nYour next choice:\n >> ";
					cin.getline(choice, 30);
				}
				else {
					if (!isEqual(getCommand(choice), "Exit") && !isEqual(getCommand(choice), "exit")) {
						cout << "No such command\n";
						cout << "\nYour next choice:\n >> ";
						cin.getline(choice, 30);
					}
					else break;
				}
			}
		}
		else if (isEqual(choice, "info")) {
		loadTxtInformation("info.txt");

			cout << "Your next choice:\n >> ";
			cin.getline(choice, 30);
		}
		else { 
			if (!isEqual(getCommand(choice), "Exit") && !isEqual(getCommand(choice), "exit")) {
				cout << "No such command\n";
				cout << "Your next choice:\n >> ";
				cin.getline(choice, 30);
			}
			else break;
			
		}
	}

	cout << "Exiting the program...";

	return 0;
}