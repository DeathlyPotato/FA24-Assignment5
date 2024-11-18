/*
    Name: Chen, Isaac, 2002582920, CS 135 1001, Assignment 5
    Description: Creating a C++ program that takes in a file
    as input. The file which would contain traveler information
    would then be processed and info written to an output file.
    Input: travel info file
    Output: Conversions file, totals file
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

int main() {
    ifstream iFile;
    ofstream oFile;
    ofstream otFile;
    string fileName;


    // Final conversions variables
    string oCity;
    double numAmount = 0;
    double convAmount = 0;
    string oCurrency;

    // Flags that are true if there is no issues
    // will not output to conversions
    // if any of the requirements not met
    bool flag = true;
    bool currencyFlag = true;
    bool amountFlag = true;

    // tallying totals
    int goLand = 0;
    int goWorld = 0;
    int japan = 0, china = 0, mexico = 0, india = 0, egypt = 0,
        europe = 0, iran = 0;   
          
    // 
    int currentLine = 0;

    // Grabs file input
    do {
        cout << "Input File Name: ";
        cin >> fileName;
        iFile.open(fileName);

        if (!iFile.is_open()) {
            cout << "Invalid filename!" << endl;
        }
    } while (!iFile.is_open());

    oFile.open("conversions.txt");
    otFile.open("totals.txt");

    // Variables that split up the input
    string line, country, city, amount, currency, tempSubStr;
    int whereSpace = 0;

    // Goes through the files and grabs the entire line
    // Then goes through and finds the spacing
    // Cuts out the portion needed
    // Find the next space
    // Cuts out the next piece
    while (getline(iFile, line)) {
        currentLine++;

        whereSpace = line.find(' ');
        country = line.substr(0, whereSpace);
        tempSubStr = line.substr(whereSpace + 1);

        whereSpace = tempSubStr.find(' ');
        city = tempSubStr.substr(0, whereSpace);
        tempSubStr = tempSubStr.substr(whereSpace + 1);

        whereSpace = tempSubStr.find(' ');
        amount = tempSubStr.substr(0, whereSpace);
        tempSubStr = tempSubStr.substr(whereSpace + 1);

        currency = tempSubStr.substr(0);

        // Checks if it is an accepted city
        // if so, the code block after will
        // be allowed

        if (city == "Orlando") {
            oCity = "Walt Disney World"; 
            flag = true;
        } else if (city == "Anaheim") {
            oCity = "Disneyland";
            flag = true;
        } else {
            flag = false;
        }
        
        // Check if accepted currency
        currencyFlag = (currency == "JPY" || currency == "CNY" ||
                        currency == "MXN" || currency == "IRR" ||
                        currency == "INR" || currency == "EGP" || 
                        currency == "EUR");

        // Expands currency to full name
        if (currency == "JPY") {
            oCurrency = "YEN";
        } else if (currency == "CNY") {
            oCurrency = "YUAN";
        } else if (currency == "MXN") {
            oCurrency = "PESO";
        } else if (currency == "INR") {
            oCurrency = "INDIAN RUPEE";
        } else if (currency == "EGP") {
            oCurrency = "EGYPTIAN POUND";
        } else if (currency == "EUR") {
            oCurrency = "EURO";
        } else if (currency == "IRR") {
            oCurrency = "RIAL";
        }
         
        
        
        // Error checking to make sure
        // that each character in amount
        // is a digit that can be converted
        // to a double         
        for (char c : amount) {
            if (c >= '0' && c <= '9') {
                amountFlag = true;
            } else {
                amountFlag = false;
                break;
            }
        } 

        // If it was a valid number
        // convert it to a double
        if (amountFlag) {
            numAmount = stod(amount);
        }


        if (currency == "JPY") {
            convAmount = numAmount * 0.0067;
        } else if (currency == "CNY") {
            convAmount = numAmount * 0.14;
        } else if (currency == "MXN") {
            convAmount = numAmount * 0.052;
        } else if (currency == "INR") {
            convAmount = numAmount * 0.012;
        } else if (currency == "EGP") {
            convAmount = numAmount * 0.021;
        } else if (currency == "EUR") {
            convAmount = numAmount * 1.10;
        } else if (currency == "IRR") {
            convAmount = numAmount * 0.000024;
        }        
        
        oFile << fixed << setprecision(2);
        // Will only output if values of strings
        // were okay
        if (flag && currencyFlag && amountFlag) {

            // Tally up how many went where
            if (oCity == "Disneyland") {
                goLand++;
            } else if (oCity == "Walt Disney World") {
                goWorld++;
            }

            // Tally up where from
            if (country == "Japan") {
                japan++;
            } else if (country == "China") {
                china++;
            } else if (country == "Mexico") {
                mexico++;
            } else if (country == "India") {
                india++;
            } else if (country == "Egypt") {
                egypt++;
            } else if (country == "Europe" || country == "Spain") {
                europe++;
            } else if (country == "Iran") {
                iran++;
            }

            // Write to conversions
            if (!(currentLine == 1)) {
                oFile << endl << endl;
            }
            oFile << "From: " << country << endl;
            oFile << "To: " << oCity << endl;
            oFile << oCurrency << "->USD $" << convAmount;
            
            if (convAmount > 10000) {
                oFile << endl << "NEEDS TAX FORMS";
            }
        } else if (!flag) {
            cout << "invalid destination on line " << currentLine <<endl;
        } else if (!currencyFlag) {
            cout << "invalid currency type on line " <<currentLine<<endl;
        } else if (!amountFlag) {
            cout <<"invalid amount of money on line "<<currentLine<<endl;
        }
    }

    otFile << goLand << " families went to Disneyland" << endl;
    otFile << goWorld << " families went to Walt Disney World" << endl;

    otFile << japan << " families visited from Japan" << endl;
    otFile << china << " families visited from China" << endl;
    otFile << mexico << " families visited from Mexico" << endl;
    otFile << india << " families visited from India" << endl;
    otFile << egypt << " families visited from Egypt" << endl;
    otFile << europe << " families visited from Europe" << endl;
    otFile << iran << " families visited from Iran" << endl;


    iFile.close();
    oFile.close();
    otFile.close();

    
}