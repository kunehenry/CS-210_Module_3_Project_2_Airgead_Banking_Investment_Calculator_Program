/*
 * Dat Nguyen
 * CS-210
 * Module 5
 * Project Two
 * Purpose: Header file for the InvestmentCalculator class in the Airgead Banking Investment Calculator application.
 *          This class defines the interface for calculating investment growth based on user inputs
 *          and displaying the results. It includes methods for setting investment parameters,
 *          performing calculations, and displaying reports.
 */

#ifndef AIRGEAD_INVESTMENT_CALCULATOR_H_
#define AIRGEAD_INVESTMENT_CALCULATOR_H_

#include <vector>  // Include vector library for using vectors
#include <utility> // Include utility library for using std::pair

// InvestmentCalculator class declaration
class InvestmentCalculator {
public:
    // Default constructor
    InvestmentCalculator();

    // Setters for setting initial investment parameters
    // t_amount is the amount to be set for each parameter
    void SetInitialInvestmentAmount(double t_amount); // Set initial investment amount
    void SetMonthlyDepositAmount(double t_amount);    // Set monthly deposit amount
    void SetAnnualInterestRate(double t_rate);        // Set annual interest rate
    void SetNumberOfYears(int t_years);               // Set number of years for investment

    // Method to perform the calculation of investment growth
    void CalculateInvestmentGrowth();

    // Method to display formatted investment reports on console
    void DisplayInvestmentReports() const;

private:
    // Member variables for storing the user input parameters
    double m_initialInvestmentAmount{0.0}; // Initial amount of investment
    double m_monthlyDepositAmount{0.0};    // Monthly deposit amount
    double m_annualInterestRate{0.0};      // Annual interest rate in percentage
    int m_numberOfYears{0};                // Number of years for the investment

    // Vectors to store the calculated growth data
    // Each pair stores year-end balance and year-end earned interest
    std::vector<std::pair<double, double>> m_growthWithoutDeposit{}; // Growth data without monthly deposit
    std::vector<std::pair<double, double>> m_growthWithDeposit{};    // Growth data with monthly deposit

    // Private helper methods for internal calculations
    void CalculateGrowth(bool t_includeMonthlyDeposit); // Calculate growth with or without monthly deposit
    double CalculateMonthlyInterest(double t_balance, double t_monthlyRate) const; // Calculate monthly interest
    double CalculateYearlyInterest(double& t_balance, bool t_includeMonthlyDeposit); // Calculate yearly interest
};

#endif // AIRGEAD_INVESTMENT_CALCULATOR_H_
