/*
 * Dat Nguyen
 * CS-210
 * Module 5
 * Project Two
 * Purpose: Implementation file for the InvestmentCalculator class in the Airgead Banking Investment Calculator application.
 *          This file contains the definitions of the methods declared in InvestmentCalculator.h.
 *          It includes the logic for calculating investment growth, both with and without additional monthly deposits,
 *          and methods for displaying the investment growth reports to the user.
 */

#include "InvestmentCalculator.h"
#include <iostream>
#include <iomanip> // For std::setprecision

// Constants used in interest calculations
constexpr double PERCENTAGE_CONVERTER = 100.0; // Used to convert percentage to decimal
constexpr int MONTHS_IN_YEAR = 12;             // Number of months in a year

// Default constructor
InvestmentCalculator::InvestmentCalculator() = default; // Initializes a new instance of InvestmentCalculator

// Set initial investment amount
void InvestmentCalculator::SetInitialInvestmentAmount(double t_amount) {
    m_initialInvestmentAmount = t_amount; // Sets the initial investment amount
}

// Set monthly deposit amount
void InvestmentCalculator::SetMonthlyDepositAmount(double t_amount) {
    m_monthlyDepositAmount = t_amount; // Sets the monthly deposit amount
}

// Set annual interest rate
void InvestmentCalculator::SetAnnualInterestRate(double t_rate) {
    m_annualInterestRate = t_rate; // Sets the annual interest rate
}

// Set number of years for investment
void InvestmentCalculator::SetNumberOfYears(int t_years) {
    m_numberOfYears = t_years; // Sets the duration of the investment in years
}

// Calculate investment growth based on user inputs
void InvestmentCalculator::CalculateInvestmentGrowth() {
    CalculateGrowth(false); // Calculate growth without monthly deposit
    CalculateGrowth(true);  // Calculate growth with monthly deposit
}

// Display formatted investment reports to console
void InvestmentCalculator::DisplayInvestmentReports() const {
    // First, display the report without additional monthly deposits
    std::cout << "\n\n\tBalance and Interest Without Additional Monthly Deposits\n";
    std::cout << "========================================================================\n";
    std::cout << "  Year\t\tYear End Balance\tYear End Earned Interest\n";
    std::cout << "------------------------------------------------------------------------\n";
    for (int year = 1; year <= m_numberOfYears; ++year) {
        std::cout << std::setw(6) << year
                  << std::setw(26) << std::setprecision(2) << std::fixed << m_growthWithoutDeposit[year - 1].first
                  << std::setw(31) << m_growthWithoutDeposit[year - 1].second << "\n";
    }

    // Then, display the report with additional monthly deposits
    std::cout << "\n\n\tBalance and Interest With Additional Monthly Deposits\n";
    std::cout << "========================================================================\n";
    std::cout << "  Year\t\tYear End Balance\tYear End Earned Interest\n";
    std::cout << "------------------------------------------------------------------------\n";
    for (int year = 1; year <= m_numberOfYears; ++year) {
        std::cout << std::setw(6) << year
                  << std::setw(26) << std::setprecision(2) << std::fixed << m_growthWithDeposit[year - 1].first
                  << std::setw(31) << m_growthWithDeposit[year - 1].second << "\n";
    }
}

// Private method to calculate growth based on whether monthly deposit is included
void InvestmentCalculator::CalculateGrowth(bool t_includeMonthlyDeposit) {
    double balance = m_initialInvestmentAmount; // Start with initial investment amount
    // Choose the appropriate vector to store the growth data
    std::vector<std::pair<double, double>>& growthData = t_includeMonthlyDeposit ? m_growthWithDeposit : m_growthWithoutDeposit;

    // Loop through each year and calculate interest
    for (int year = 1; year <= m_numberOfYears; ++year) {
        double totalInterest = CalculateYearlyInterest(balance, t_includeMonthlyDeposit);
        growthData.emplace_back(balance, totalInterest); // Store the calculated data
    }
}

// Calculate monthly interest based on current balance and monthly interest rate
double InvestmentCalculator::CalculateMonthlyInterest(double t_balance, double t_monthlyRate) const {
    return t_balance * t_monthlyRate; // Returns the interest for the month
}

// Calculate total interest for a year, updating balance each month
double InvestmentCalculator::CalculateYearlyInterest(double& t_balance, bool t_includeMonthlyDeposit) {
    double totalInterest = 0.0;
    double monthlyRate = m_annualInterestRate / PERCENTAGE_CONVERTER / MONTHS_IN_YEAR; // Calculate monthly interest rate

    // Loop through each month and accumulate interest
    for (int month = 1; month <= MONTHS_IN_YEAR; ++month) {
        if (t_includeMonthlyDeposit) {
            t_balance += m_monthlyDepositAmount; // Add monthly deposit if applicable
        }
        double interest = CalculateMonthlyInterest(t_balance, monthlyRate);
        totalInterest += interest; // Accumulate interest for the year
        t_balance += interest; // Update balance with interest
    }
    return totalInterest; // Return the total interest accumulated in a year
}
