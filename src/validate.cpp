#include "common.hpp"

/* 
  function to validate user deposit, returns a boolean value
  uses the arguments provided to it for the calculation
  if the deposit amount is more than zero and the combined deposit plus what is present in the balance is less than 100, return true
*/
bool isValidDeposit(float depoAmt, float currentBalance) {
  return (depoAmt > 0) && ((depoAmt + currentBalance) <= MAX_LIMIT); 
}

/* 
  function to validate user wtihdrawal, returns a boolean value
  uses the arguments provided to it for the calculation
  if the withdrawal amount is more than zero and the withdrawl amount is less than the current balance, return true
*/
bool isValidWithdrawal(float withdrawAmt, float currentBalance) {
  return (withdrawAmt > 0) && (withdrawAmt <= currentBalance);    
}