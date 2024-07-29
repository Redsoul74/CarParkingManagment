#include <iostream>
#include <vector>
#include <ctype.h>
#include <cstring>
#include <fstream>
#include <iomanip>

class Car{
    private:
    int plate;
    std::string brand;
    std::string color;
    int year;
    public:
    Car(int plate,std::string brand,std::string color,int year)
    {
    this->plate=plate;
    this->brand=brand;
    this->color=color;
    this->year=year;
    }

    void setPlate(int plate);
    int getPlate();
    void setBrand(std::string brand);
    std::string getBrand();
    void setColor(std::string color);
    std::string getColor();
    void setYear(int year);
    int getYear();
    void displayCar();
};

std::vector<std::string>carCompanies;
std::vector<std::string>carColors;

void addCar(std::vector<Car> &car);
void displayAllCar(std::vector<Car> car);
void displayPlates(std::vector<Car> car);
void removeCar(std::vector<Car> &car);
void modifyCar(std::vector<Car> &car);
void plateSearching(std::vector<Car> car);
void brandSearching(std::vector<Car> car);
void colorSearching(std::vector<Car> car);
void yearSearching(std::vector<Car> car);
void updateData(std::vector<Car> car);
void menu();
void searchMenu();
bool isInteger(std::string userInput,int* number);
bool userInputOnlySpace(std::string userInput);
void userIntegerInput(int* number);
void makeUpperCase(std::string& word);
int searchByPlate(std::vector<Car> car);
bool samePlate(int plate,std::vector<Car> car);
bool checkPlate(int plate);
bool checkBrand(std::string brand,std::vector<std::string> carCompanies);
bool checkColor(std::string color,std::vector<std::string> carColors);
bool checkYear(int year);
void getData(std::vector<Car>& car);
void getInfoCars(std::vector<std::string>& carCompanies,std::vector<std::string>& carColors);
void displayCompanies(std::vector<std::string> carCompanies);
void displayColors(std::vector<std::string> carColors);
void sortByPlate(std::vector<Car>& car);

int main(){
    int choice;
    std::vector<Car>car;
    getInfoCars(carCompanies,carColors);
    getData(car);
    do{
        menu();
        userIntegerInput(&choice);
        if(choice == 0 )exit(1);
        switch (choice)
        {
        case 1:
            displayAllCar(car);
            break;
        case 2:
            addCar(car);
            break;
        case 3:
            removeCar(car);
            break;
        case 4:
            modifyCar(car);
            break;
        case 5:
            do{
                searchMenu();
                userIntegerInput(&choice);
                if(choice == 0) break;
                switch(choice){
                    case 1:
                        plateSearching(car);
                        break;
                    case 2:
                        brandSearching(car);
                        break;
                    case 3:
                        colorSearching(car);
                        break;
                    case 4:
                        yearSearching(car);
                        break;
                    default:
                        std::cout << "Invalid Input:";
                        break;
                }
                system("PAUSE");
            }while(true);
            break;
        case 6:
            updateData(car);
        default:
        std::cout<<"Invalid Number.\n";
            break;
        }
        sortByPlate(car);
        system("PAUSE");
    }while(true);

    return 0;
}

void Car::setPlate(int plate)
{
    this->plate=plate;
}
void Car::setBrand(std::string brand){
    this->brand=brand;
}
void Car::setColor(std::string color){
    this->color=color;
}
void Car::setYear(int year){
    this->year=year;
}
int Car::getPlate(){
    return plate;
}
std::string Car::getBrand(){
    return brand;
}
std::string Car::getColor(){
    return color;
}
int Car::getYear(){
    return year;
}

void Car::displayCar()
{
    std::cout << std::left << std::setw(16) << plate << std::setw(16) << brand << std::setw(16) << color << std::setw(4) << year << "\n";

}
//need to add checkers for their lentght of their input
void addCar(std::vector<Car> &car){
    int plate;
    std::string brand;
    std::string color;
    int year;
    while(true){
        std::cout << "Add Plate: ";
        userIntegerInput(&plate);
        if(!samePlate(plate,car)){
            if(checkPlate(plate))break;
        }  
    }
    displayCompanies(carCompanies);
    while(true){
        std::cout << "Add Brand: ";
        std::getline(std::cin,brand);
        makeUpperCase(brand);
        if(checkBrand(brand,carCompanies))break;
    }
    displayColors(carColors);
    while(true){
        std::cout << "Add Color: ";
        std::getline(std::cin,color);
        makeUpperCase(color);
        if(checkColor(color,carColors))break;
    }
    while(true){
        std::cout << "Add Year: ";
        userIntegerInput(&year);
        if(checkYear(year))break;
    }
    Car newCar(plate,brand,color,year);
    car.push_back(newCar);

}

void displayAllCar(std::vector<Car> car){
    if(car.empty()){
        std::cout<<"Not Found..."<<std::endl;
        return;
    }
    std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
    for(int i=0;i<car.size();i++){
        car[i].displayCar();
    }
}
void displayPlates(std::vector<Car> car)
{
    for(int i=0;i<car.size();i++){
        std::cout << std::left << std::setw(6) << car[i].getPlate();
    }
    std::cout << "\n";
}
// need to fix the user input
void removeCar(std::vector<Car> &car)
{
    std::string choice;
    displayPlates(car);
    std::cout << "Please enter the Car Number Plate to Delete:";
    int IDCar = searchByPlate(car);
    if(IDCar !=-1){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        car[IDCar].displayCar();
        std::cout << "Delete car press Y ";
        std::getline(std::cin,choice);
        if(choice == "Y" || choice == "y")
        {
            car.erase(car.begin()+IDCar);
            std::cout << "It was succesfully deleted\n";
        }else std::cout << "It was not succesfully deleted\n";
    }else std::cout << "The plate that you entered does not exist.\n";
}
//need to check if input lenght and brand and color
void modifyCar(std::vector<Car> &car)
{
    int plate;
    std::string brand;
    std::string color;
    int year;
    displayPlates(car);
    std::cout << "Please the plate number of car that you want to modify. ";
    int IDCar = searchByPlate(car);
    if(IDCar!=-1)
    {
        while(true){
            std::cout << "Add Plate (Current Plate:" << car[IDCar].getPlate() << "):";
            userIntegerInput(&plate);
            if(plate!=car[IDCar].getPlate()){
                if(!samePlate(plate,car)){
                    if(checkPlate(plate))break;
                }
            }else break;
        }
        car[IDCar].setPlate(plate);
        displayCompanies(carCompanies);
        while(true){
            std::cout << "Add Brand (Current Brand: "<< car[IDCar].getBrand() << "):";
            std::cout << " (Press \"-\" For same Brand)";
            std::getline(std::cin,brand);
            if(brand == "-") break;
            makeUpperCase(brand);
            if(checkBrand(brand,carCompanies)){
                car[IDCar].setBrand(brand);
                break;
            }
        }
        displayColors(carColors);
        while(true){
            std::cout << "Add Color (Current Color: "<<car[IDCar].getColor() <<"):";
            std::cout << " (Press \"-\" For same Color)";
            std::getline(std::cin,color);
            if(color == "-") break;
            makeUpperCase(color);
            if(checkColor(color,carColors)){
                car[IDCar].setColor(color);
                break;
            }
        }
        while(true){
            std::cout << "Add Year (Current Year: "<< car[IDCar].getYear() <<"):";
            userIntegerInput(&year);
            if(checkYear(year))break;
        }
        car[IDCar].setYear(year);
    }else std::cout << "The plate does not exist.";
    
}

void plateSearching(std::vector<Car> car)
{
    int plate;
    std::string choice;
    std::cout << "Type a number plate to search by: ";
    userIntegerInput(&plate);
    std::cout << "Press \"<\" for Higher plates and  \">\" for Lower plates.";
    std::getline(std::cin,choice);
    if(choice == "<"){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        for(int i=0;i<car.size();i++){
            if(plate <= car[i].getPlate())car[i].displayCar();
        }
    }
    if(choice == ">"){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        for(int i=0;i<car.size();i++){
            if(plate >= car[i].getPlate())car[i].displayCar();
        }
    }
}

void brandSearching(std::vector<Car> car)
{
    std::string brand;
    displayCompanies(carCompanies);
    std::cout << "Put the Company names that you want to search: ";
    std::getline(std::cin,brand);
    makeUpperCase(brand);
    if(checkBrand(brand,carCompanies)){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        for(int i=0;i<car.size();i++){
            if(brand == car[i].getBrand())car[i].displayCar();
        }
    }  
}

void colorSearching(std::vector<Car> car)
{
    std::string color;
    displayColors(carColors);
    std::cout << "Put the Color that you want to search: ";
    std::getline(std::cin,color);
    makeUpperCase(color);
    if(checkColor(color,carColors)){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        for(int i=0;i<car.size();i++){
            if(color == car[i].getColor())car[i].displayCar();
        }
    }
}

void yearSearching(std::vector<Car> car)
{
    int year;
    std::string choice;
    std::cout << "Type a number year to search by: ";
    userIntegerInput(&year);
    std::cout << "Press \"<\" for Higher year and  \">\" for Lower year.";
    std::getline(std::cin,choice);
    if(choice == "<"){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND" << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        for(int i=0;i<car.size();i++){
            if(year <= car[i].getYear())car[i].displayCar();
        }
    }
    if(choice == ">"){
        std::cout << std::left << std::setw(16)<<"PLATE"<< std::setw(16) << "BRAND"
        << std::setw(16) << "COLOR" << std::setw(4) << "YEAR" << "\n";
        for(int i=0;i<car.size();i++){
            if(year >= car[i].getYear())car[i].displayCar();
        }
    }
}

void updateData(std::vector<Car> car)
{
    std::fstream filecar;
    filecar.open("Cars.txt",std::ios::out);
    if(!filecar){
        std::cout << "The file Cars.txt does not exist.\n";
        exit(1);
        }
    while(true){
        for(int i=0;i<car.size();i++){
            filecar << std::left << std::setw(16)<<car[i].getPlate()<< std::setw(16) << car[i].getColor()
            << std::setw(16) << car[i].getBrand() << std::setw(4) << car[i].getYear();
            if(i!=car.size()-1) filecar << "\n";
        }
        break;
    }
    std::cout << "Update successfully!";
}

void menu()
{
    system("cls");
    std::cout << "====================\n";
    std::cout << "========Menu========\n";
    std::cout << "====================\n";
    std::cout << "1.Display All Car\n";
    std::cout << "2.Add Car\n";
    std::cout << "3.Remove Car\n";
    std::cout << "4.Modify Car\n";
    std::cout << "5.Search Car\n";
    std::cout << "6.Update Data\n";
    std::cout << "0.Exit\n";
}

void searchMenu(){

    system("cls");
    std::cout << "===================\n";
    std::cout << "====Search Menu====\n";
    std::cout << "===================\n";
    std::cout << "1.Search Plate\n";
    std::cout << "2.Search Brand\n";
    std::cout << "3.Search Color\n";
    std::cout << "4.SearCh Year\n";
    std::cout << "0.Exit\n";
}

bool isInteger(std::string userInput,int* number)
{
    int i=0;
    char word[userInput.size()];
    int wordBuffer=0;
    while(isspace(userInput[i])) i++;
    while(i<userInput.size() && !isspace(userInput[i]))
    {
        if(!isdigit(userInput[i]))return false;
        word[wordBuffer]=userInput[i];
        wordBuffer++;
        i++;
    }
    word[wordBuffer]='\0';
    while(isspace(userInput[i]))i++;
    if(userInput[i]!='\0')return false;
    *number = atoi(word);
    return true;
    
}
bool userInputOnlySpace(std::string userInput)
{
    int i=0,counter=0;
    for(i;i<userInput.size();i++){
        if(isspace(userInput[i]))counter++;
    }
    if(i==counter)return true;
    return false;
}

void userIntegerInput(int* number)
{
    std::string userInput;
    do{
        std::getline(std::cin,userInput);
        if(!userInput.empty()){
            if(!userInputOnlySpace(userInput))
            {
                if(!isInteger(userInput,number))
                {
                std::cout << "Invalid Input:";
                }else return;
            }
        }
    }while(true);
}

void makeUpperCase(std::string& word){
    char* ch;
    for(int i=0;i<word.size();i++){
        ch[i] = toupper(word[i]);
    }
    for(int i=0;i<word.size();i++){
       word[i]=ch[i];
    }
}

int searchByPlate(std::vector<Car> car)
{
    int plate;
    userIntegerInput(&plate);
    for(int i=0;i<car.size();i++){
        if(car[i].getPlate()==plate)return i;
    }
    return -1;  //with this indicates that it didnt match with any in the vector.
}

bool samePlate(int plate, std::vector<Car> car)
{
    for(int i=0;i<car.size();i++){
        if(plate == car[i].getPlate()){
            std::cout << "This plate already exist.\n";
            return true;
        }
    }
    return false;
}

bool checkPlate(int plate)
{
    if(plate > 999 && plate < 10000) return true;
    std::cout << "Your input must be 1000 till 9999.\n";
    return false;
}

bool checkBrand(std::string brand, std::vector<std::string> carCompanies)
{
    for(int i=0;i<carCompanies.size();i++){
        if(brand == carCompanies[i])return true;
    }
    std::cout << "You need to put the same brand as the list above.\n";
    return false;
}

bool checkColor(std::string color, std::vector<std::string> carColors)
{
    for(int i=0;i<carColors.size();i++){
        if(color == carColors[i])return true;
    }
    std::cout << "You need to put the same color as the list above.\n";
    return false;
}

bool checkYear(int year)
{
    if(year > 1949 && year < 2025) return true;
    std::cout << "You need to input between 1950 till 2024.\n";
    return false;
}

void getData(std::vector<Car>& car){
    std::fstream carFile;
    carFile.open("Cars.txt",std::ios::in);
    if(!carFile){
        std::cout << "The file Cars.txt does not exist\nThe program will be terminated";
        system("Pause");
        exit(1);
    }else{
        int plate,year;
        std::string brand,color;
        while(!carFile.eof()){
            carFile >> plate;
            if(!checkPlate(plate) || carFile.eof()){
                std::cout << "There is a problem with the file Cars.txt getting data\nThe program will be terminated\n";
                system("Pause");
                exit(1);
            }
            carFile >> color;
            if(!checkColor(color,carColors) || carFile.eof()){
                std::cout << "There is a problem with the file Cars.txt getting data\nThe program will be terminated\n";
                system("Pause");
                exit(1);
            }
            carFile >> brand;
            if(!checkBrand(brand,carCompanies) || carFile.eof()){
                std::cout << "There is a problem with the file Cars.txt getting data\nThe program will be terminated\n";
                system("Pause");
                exit(1);
            }
            carFile >> year;
            if(!checkYear(year)){
                std::cout << "There is a problem with the file Cars.txt getting data\nThe program will be terminated\n";
                system("Pause");
                exit(1);
            }
            Car newCar(plate,brand,color,year);
            car.push_back(newCar);
        }
    }
}

void getInfoCars(std::vector<std::string> &carCompanies, std::vector<std::string> &carColors)
{
    std::string company;
    std::fstream comp;
    comp.open("Companies.txt",std::ios::in);
    if(comp.is_open()){
        while(!comp.eof()){
            comp >> company;
            carCompanies.push_back(company);
        }
    }else{
        std::cout << "Your Companies.txt is not found\nThe program will terminate\n";
        system("Pause");
        exit(1);
    }
    comp.close();
    std::string color;
    std::fstream clr;
    clr.open("BasicColors.txt",std::ios::in);
    if(clr.is_open()){
        while(!clr.eof()){
            clr >> color;
            carColors.push_back(color);
        }
    }else {
        std::cout << "Your BasicColors.txt is not found\nThe program will terminate\n";
        system("Pause");
        exit(1);
    }
    clr.close();
}


void displayCompanies(std::vector<std::string> carCompanies){
    for(int i=0;i<carCompanies.size();i++){
        std::cout << carCompanies[i] << "\n";
    }
}

void displayColors(std::vector<std::string> carColors)
{
    for(int i=0;i<carColors.size();i++){
        std::cout << carColors[i] << "\n";
    }
}

void sortByPlate(std::vector<Car> &car)
{
    for(int i=0;i<car.size();i++){
        for(int j=0;j<car.size()-1;j++){
            if(car[i].getPlate()<car[j].getPlate()){
                Car temp(car[i]);
                car[i] = car[j];
                car[j] = temp; 
            }
        }
    }
}
