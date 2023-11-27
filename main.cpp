/*
 * Dat Nguyen
 * CS-210
 * Module 5
 * Project Two
 * Purpose: Main program file for the Airgead Banking Investment Calculator application.
 *          This file handles user interaction, including reading input parameters for the investment
 *          (such as initial investment amount, monthly deposit, annual interest, and number of years),
 *          and displaying the investment growth reports. It utilizes the InvestmentCalculator class
 *          to perform the necessary calculations and report generation.
 */

#include "InvestmentCalculator.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <limits>

// Function declarations
void PrintHeader(); // Declares a function to print the header of the application
void GetUserInput(double& t_initialInvestment, double& t_monthlyDeposit, double& t_annualInterest, int& t_years); // Declares a function to get user inputs

// Main function - the entry point of the application
int main() {

    // Variables to hold user inputs
    double initialInvestment, monthlyDeposit, annualInterest;
    int years;

    // Get user inputs for investment parameters
    GetUserInput(initialInvestment, monthlyDeposit, annualInterest, years);

    // Create an instance of the InvestmentCalculator class
    InvestmentCalculator investmentCalculator;

    // Set user inputs to the investment calculator instance
    investmentCalculator.SetInitialInvestmentAmount(initialInvestment);
    investmentCalculator.SetMonthlyDepositAmount(monthlyDeposit);
    investmentCalculator.SetAnnualInterestRate(annualInterest);
    investmentCalculator.SetNumberOfYears(years);

    // Perform the investment growth calculations
    investmentCalculator.CalculateInvestmentGrowth();

    // Display the resulting investment reports
    investmentCalculator.DisplayInvestmentReports();

    return 0; // Indicates successful program termination
}

// PrintHeader function implementation
void PrintHeader() {
    // Print top border for the header
    std::cout << std::endl << std::string(60, '*') << std::endl;
    // Print header text
    std::cout << std::string(24, '*') << " Data Input " << std::string(24, '*') << std::endl;
}

// GetUserInput function implementation
void GetUserInput(double& t_initialInvestment, double& t_monthlyDeposit, double& t_annualInterest, int& t_years) {

    // Display the header
    PrintHeader();

    // Lambda function for reading and validating monetary input
    auto readMonetaryValue = [](const std::string& prompt) -> double {

        std::string input;
        double value;

        while (true) {
            std::cout << prompt; // Display the prompt
            std::cin >> input; // Read input
            // Remove non-numeric characters
            input.erase(std::remove_if(input.begin(), input.end(), [](char c) {
                return !std::isdigit(c) && c != '.';
            }), input.end());

            // Try to convert input to double and validate
            try {
                value = std::stod(input); // Convert to double
                if (value < 0) throw std::invalid_argument("Value must be non-negative.");
                break; // Break loop if valid
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid input. Please enter a positive number." << std::endl;
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
            }
        }
        return value; // Return the validated value
    };

    // Read and validate user inputs
    t_initialInvestment = readMonetaryValue("Initial Investment Amount: ");
    t_monthlyDeposit = readMonetaryValue("Monthly Deposit: ");
    t_annualInterest = readMonetaryValue("Annual Interest: ");

    // Get number of years input with validation
    std::cout << "Number of years: ";
    while (!(std::cin >> t_years) || t_years <= 0) {
        std::cerr << "Please enter a positive integer for the number of years." << std::endl;
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip bad input
    }

    // Prompt user to continue
    std::cout << std::endl << "Press any key to continue . . .";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cin.get(); // Wait for key press
}
