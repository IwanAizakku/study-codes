/*
TMF1434 Data Structure & Algorithms Assignment 1 - Jam Oasis Band Management system Sem 2,2023/2024
*/

#include <iostream>
#include <string>
using namespace std;

const int maxMusicians = 10;	// Sets max musicians that can be added (max number of data in array)
const int maxBands = maxMusicians;

// (Encapsulation) Creates Musician class containing private strings: name, category and instrument
class Musician {
private:
    string musicianName;
    string musicianCategory;
    string musicianInstrument;

public:
    Musician(string name = "", string category = "", string instrument = "") : musicianName(name), musicianCategory(category), musicianInstrument(instrument) {}
	// Obtains current string value and returns it.
    string GetName() const {
        return musicianName;
    }
    string GetCategory() const {
        return musicianCategory;
    }
    string GetInstrument() const {
        return musicianInstrument;
    }
    // Whenever user's input is obtained, assigns it to the respective string
    void SetName(string newName) {
        musicianName = newName;
    }
    void SetCategory(string newCategory) {
        musicianCategory = newCategory;
    }
    void SetInstrument(string newInstrument) {
        musicianInstrument = newInstrument;
    }
	// Displays the current value of the respective string
    void DisplayName() const {
        cout << "Name: " << musicianName << endl;
    }
    void DisplayCategory() const {
        cout << "Category: " << musicianCategory << endl;
    }
    void DisplayInstrument() const {
        cout << "Instrument: " << musicianInstrument << endl;
    }
};

// (Inheritance) Inherits infomation from Musician class and adds additional private strings: Ic, age and hometown
class MusicianDetail : public Musician {
private:
    string musicianIc;
    string musicianAge;
    string musicianHometown;

public:
    MusicianDetail(string name = "", string category = "", string instrument = "", string ic = "", string age = "", string hometown = "") : Musician(name, category, instrument), musicianIc(ic), musicianAge(age), musicianHometown(hometown) {}

    string GeticNumber() const {
        return musicianIc;
    }
    string GetAge() const {
        return musicianAge;
    }
    string GetHometown() const {
        return musicianHometown;
    }

    void SeticNumber(string newic) {
        musicianIc = newic;
    }
    void SetAge(string newAge) {
        musicianAge = newAge;
    }
    void SetHometown(string newHometown) {
        musicianHometown = newHometown;
    }

    void DisplayDetails() const {
        DisplayName();
        DisplayCategory();
        DisplayInstrument();
        cout << "IC: " << musicianIc << endl;
        cout << "Age: " << musicianAge << endl;
        cout << "Hometown: " << musicianHometown << endl;
    }
};

class Band {
private:
    MusicianDetail* bandMembers[maxMusicians];
    int numMembers; // Member variable to track the number of members
    string bandName;
    static Band* bands[maxBands];
    static int numBands;

public:
    Band(const string& name) : bandName(name), numMembers(0) {
        bands[numBands++] = this;
    }

    ~Band() {
        for (int i = 0; i < numMembers; ++i) {
            delete bandMembers[i];
        }
    }

    void AddMusicianToBand(const MusicianDetail& musician) {
        if (numMembers < maxMusicians) {
            bandMembers[numMembers++] = new MusicianDetail(musician);
        } else {
            cout << "Band is full, cannot add more musicians." << endl;
        }
    }
	
	// (Polymorphism) Poins to MusicianDetail class as a common object to display data from it. 
    void DisplayBandDetails() const {
        cout << "\nBand members:\n";
        for (int i = 0; i < numMembers; ++i) {
            cout << "Member (" << i + 1 << ")\n";
            bandMembers[i]->DisplayDetails();
            cout << endl;
        }
    }

    static void DisplayAllBands() {
        cout << "\nList of bands and their musicians:\n\n";
        for (int i = 0; i < numBands; ++i) {
            cout << i + 1 << ". Band: " << bands[i]->bandName;
            bands[i]->DisplayBandDetails();
        }
    }
};

Band* Band::bands[maxBands];
int Band::numBands = 0;

// Initialize presets data of Name, Category, Instrument, ic, age and hometown. 
// Array max data is set using maxMusicians
MusicianDetail preSet[maxMusicians] = {
    MusicianDetail("Ivan", "Classical", "Pianist", "000309120941", "24", "Sabah"),
    MusicianDetail("Elena", "Jazz", "Saxophone", "262716092736", "30", "Penang"),
    MusicianDetail("Alex", "Rock", "Guitarist", "2621520815267", "27", "Kuala Lumpur"),
    MusicianDetail("Sophia", "Pop", "Vocals", "5342521036152", "22", "Sarawak"),
    MusicianDetail("Michael", "Blues", "Bassist", "152241021625", "35", "Johor")
};
int currentSize = 5;	//Pre-set data array size. Used for array loop functions involving list editing.

// Function prototypes
void AddMusicians(MusicianDetail musicians[], int& currentSize, int maxSize);
void DeleteMusicians(MusicianDetail musicians[], int& currentSize, int number);
void EditMusician(MusicianDetail musicians[], int currentSize, int number);
void DisplayMusicians(const MusicianDetail musicians[], int currentSize);
void DisplayMusiciansByCategory(const MusicianDetail musicians[], int currentSize);
void DisplayMusicianDetails(const MusicianDetail musicians[], int currentSize);
void CreateBand(MusicianDetail musicians[], int currentSize, Band* bands[], int& numBands);
void DisplayMainMenu();
void DisplayBandCreationMenu();


int main() {
	cout << "*-----------------------------------------*\n";
    cout << "| Welcome to Jam Oasis management system! |\n";
    cout << "*-----------------------------------------*\n";
    int option;
    int numBands = 0;
    int number = 0;
    Band* bands[maxBands]; // Changed the name to avoic conflict
    do {
        DisplayMainMenu();	// Displays the options list.
         do {
        	// If input is not an integer, repeat until true. To avoid infinite looping.
        	while (!(cin >> option)) {
            	cout << "\n< Invalid choice. Please try again. >\n";
            	DisplayMainMenu();
            	cin.clear(); // Clear the error flag
            	cin.ignore(256, '\n');
        	}
    	} while (false);

        switch (option) {
        case 1:
            AddMusicians(preSet, currentSize, maxMusicians);
            break;
        case 2:
            DisplayMusicians(preSet, currentSize);
            cout << "Enter the musician's number to be deleted: ";
            cin >> number;
            DeleteMusicians(preSet, currentSize, number);
            break;
        case 3:
            DisplayMusicians(preSet, currentSize);
            cout << "Enter the musician's number to be edited: ";
            cin >> number;
            EditMusician(preSet, currentSize, number);
            break;
        case 4:
        	DisplayMusicians(preSet, currentSize);
            break;
        case 5:
            DisplayMusiciansByCategory(preSet, currentSize);
            break;
        case 6:
            DisplayMusicianDetails(preSet, currentSize);
            break;
        case 7:
            CreateBand(preSet, currentSize, bands, numBands);
            break;
        case 8:
            Band::DisplayAllBands();
            break;
        case 9:
            cout << "\n< Exiting the program. Goodbye! >\n";
            break;
        default:
            cout << "\n< Invalid choice. Please try again. >" << endl;
        }
    } while (option != 9);

    return 0;
}

// Adds a musician to the musicians list
void AddMusicians(MusicianDetail musicians[], int& currentSize, int maxMusicians) {
    if (currentSize >= maxMusicians) {
        cout << "\n< Cannot add more musicians. Maximum capacity reached. >" << endl;
        return;
    }
    
    string GetName, GetCategory, GetInstrument, getic, GetAge, GetHometown; 
	
    cout << "\nEnter musician's name: ";
    cin.ignore(256, '\n');
    getline(cin, GetName);
    musicians[currentSize].SetName(GetName);

    cout << "Enter musician's category: ";
    getline(cin, GetCategory);
    musicians[currentSize].SetCategory(GetCategory);

    cout << "Enter musician's instrument: ";
    getline(cin, GetInstrument);
    musicians[currentSize].SetInstrument(GetInstrument);
	
    cout << "Enter musician's IC number: ";
    cin >> getic;
    musicians[currentSize].SeticNumber(getic);
    
    cout << "Enter musician's age: ";
    cin >> GetAge;
    musicians[currentSize].SetAge(GetAge);

    cout << "Enter musician's hometown: ";
    cin.ignore(256, '\n');
    getline(cin, GetHometown);
    musicians[currentSize].SetHometown(GetHometown);

    currentSize++;
    cout << "\n< Musician added successfully. >\n";
}

// Displays all musicians in the list
void DisplayMusicians(const MusicianDetail musicians[], int currentSize) {
    if (currentSize == 0) {
        cout << "< No musicians available. >" << endl;
        return;
    }

    cout << "\nList of Musicians:-\n\n";
    for (int i = 0; i < currentSize; ++i) {
        cout << "Musician (" << i + 1 << ")\n";
        musicians[i].DisplayDetails();
        cout << endl;
    }
}

// Deletes a musician from the list
void DeleteMusicians(MusicianDetail musicians[], int& currentSize, int number) {
    if (number <= 0 || number > currentSize) {
        cout << "\n< Invalid number. No musician deleted. >\n";
        return;
    }

    for (int i = number - 1; i < currentSize - 1; ++i) {
        musicians[i] = musicians[i + 1];
    }

    currentSize--;  // Increment by -1 to the list
    cout << "\n< Musician deleted successfully. >\n";
}

// Edits a musician on the list
void EditMusician(MusicianDetail musicians[], int currentSize, int number) {
    if (number <= 0 || number > currentSize) {
        cout << "< Invalid number. No musician edited. >\n";
        return;
    }
    
    string GetName, GetCategory, GetInstrument, getic, GetAge, GetHometown;  

    cout << "\nEnter new musician name: ";
    cin.ignore(256, '\n');
    getline(cin, GetName);
    musicians[number - 1].SetName(GetName);

    cout << "Enter new musician's category: ";
    getline(cin, GetCategory);
    musicians[number - 1].SetCategory(GetCategory);

    cout << "Enter new musician's instrument: ";
    getline(cin, GetInstrument);
    musicians[number - 1].SetInstrument(GetInstrument);

    cout << "Enter new musician's IC number: ";
    cin >> getic;
    musicians[number - 1].SeticNumber(getic);
	
    cout << "Enter new musician's age: ";
    cin >> GetAge;
    musicians[number - 1].SetAge(GetAge);

    cout << "Enter new musician's hometown: ";
    cin.ignore(256, '\n');
    getline(cin, GetHometown);
    musicians[number - 1].SetHometown(GetHometown);

    cout << "\n< Musician updated successfully. >\n";
}

// Displays available musicians in a category
void DisplayMusiciansByCategory(const MusicianDetail musicians[], int currentSize) {
    if (currentSize == 0) {
        cout << "< No musicians to display. >" << endl;
        return;
    }

    string categories[maxMusicians];
    int numCategories = 0;

    for (int i = 0; i < currentSize; ++i) {
        string category = musicians[i].GetCategory();
        bool isUnique = true;
        
        for (int j = 0; j < numCategories; ++j) {
            if (category == categories[j]) {
                isUnique = false;
                break;
            }
        }
        
        if (isUnique) {
            categories[numCategories] = category;
            numCategories++;
        }
    }
	cout << endl;
    for (int i = 0; i < numCategories; ++i) {
        cout << "Musicians in category \"" << categories[i] << "\":\n";

        for (int j = 0; j < currentSize; ++j) {
            if (categories[i] == musicians[j].GetCategory()) {
                musicians[j].DisplayDetails();
                cout << endl;
            }
        }
        cout << endl;
    }
}

// Displays detailed info of a musician
void DisplayMusicianDetails(const MusicianDetail musicians[], int currentSize) {
    cout << "\nList of Musicians:\n\n";
    for (int i = 0; i < currentSize; ++i) {
        cout << "Musician (" << i + 1 << ")\n";
        musicians[i].DisplayName();
        cout << endl;
    }

    int number;
    cout << "Enter the musician's number to display details: ";
    cin >> number;

    if (number <= 0 || number > currentSize) {
        cout << "\n < Invalid number. No musician found. >" << endl;
    } else {
        cout << "\nMusician " << number << " details:\n\n";
        musicians[number - 1].DisplayDetails();
        cout << endl;
    }
}

// Creates a band and adds musician to it.
void CreateBand(MusicianDetail musicians[], int currentSize, Band* bands[], int& numBands) {
    if (numBands >= maxBands) {
        cout << "< Cannot create more bands. Maximum limit reached. >\n" << endl;
        return;
    }

    string bandName;
    cout << "\nEnter band name: ";
    cin.ignore(); 
    getline(cin, bandName);
    bands[numBands++] = new Band(bandName);

    int choice;

    do {
        DisplayBandCreationMenu(); // Displays menu for band creation
        do {
        	// If input is not an integer, repeat until true. To avoid infinite looping.
        	while (!(cin >> choice)) {
            	cout << "\n< Invalid choice. Please try again. >\n";
            	cin.clear();
            	cin.ignore(256, '\n');
            	DisplayBandCreationMenu();
        	}
    	} while (false);

        switch (choice) {
        case 1: {
            cout << "\nList of Musicians:\n";
            for (int i = 0; i < currentSize; ++i) {
                cout << "Musician (" << i + 1 << ")\n";
                musicians[i].DisplayDetails();
                cout << endl;
            }

            int number;
            cout << "Enter the musician's number to be added to the band: ";
            cin >> number;

            if (number <= 0 || number > currentSize) {
                cout << "\n< Invalid number. No musician added. >\n";
            } else {
                bands[numBands - 1]->AddMusicianToBand(musicians[number - 1]); 
                cout << "\n< Musician added successfully. >\n";
            }
            break;
        }
        case 2:
            bands[numBands - 1]->DisplayBandDetails(); 
            break;
        case 3:
            cout << "\n< Exiting the band creation menu. Goodbye! >\n";
            break;
        default:
            cout << "< \nInvalid choice. Please try again. >" << endl;
        }
    } while (choice != 3);
}

// Displays the main menu
void DisplayMainMenu() {
    cout << "\nPlease select an option:\n";
    cout << "(1) Add a musician to the list\n";
    cout << "(2) Delete a musician from the list\n";
    cout << "(3) Edit a musician's details on the list\n";
    cout << "(4) Display all musicians in the list\n";
    cout << "(5) Display all musicians by category\n";
    cout << "(6) Display a musician's info\n";
    cout << "(7) Create a band\n";
    cout << "(8) Display all bands and their musicians\n";
    cout << "(9) Exit the program\n";
    cout << "Enter your choice: ";
}

// Displays the main menu for band creation
void DisplayBandCreationMenu () {
	cout << "\nPlease select from the following options:\n";
    cout << "1. Add a musician to the band\n";
    cout << "2. Display band details\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}
