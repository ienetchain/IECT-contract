#include "vntlib.h"

// erc20合约代码
// Public variables of the token
KEY string owner;
KEY string name = "IECT";
KEY string symbol = "IECT";
KEY uint256 decimals = U256(18);
KEY uint256 totalSupply = U256(2000000000000000000000000000);

// This creates an array with all balances
KEY mapping(address, uint256) balanceOf;
KEY mapping(address, mapping(address, uint256)) _allowance;

// These are options for token restriction
// All locked up
KEY bool restricted = false;
// Only lock up specified accounts
KEY mapping(address, bool) restriction;

// // This generates a public event on the blockchain that will notify clients
EVENT Transfer(indexed address from, indexed address to, uint256 value);

// // This generates a public event on the blockchain that will notify clients
EVENT Approval(indexed address owner, indexed address spender, uint256 value);

/**
 * Constructor function
 *
 * Initializes contract with initial supply tokens to the creator of the
 * contract
 */
constructor IECT()
{
  owner = GetSender();
  balanceOf.key = owner;
  balanceOf.value = totalSupply; // Give the creator all initial tokens
}

/**
 * Internal transfer, only can be called by this contract
 */
void _transfer(address _from, address _to, uint256 _value)
{
  // Check if this contract is restricted
  Assert(!restricted, "contract is restricted");
  // Check if from address is restricted
  restriction.key = _from;
  Assert(!restriction.value, "from address is restricted");
  // Check if to address is restricted
  restriction.key = _to;
  Assert(!restriction.value, "to address is restricted");
  // Prevent transfer to 0x0 address. Use burn() instead
  Assert(!Equal(_to, Address("0x0")), "empty to address");
  // Check if the sender has enough
  balanceOf.key = _from;
  Assert(U256_Cmp(balanceOf.value, _value) != -1,
         "sender does not have enough token");
  // Check for overflows
  balanceOf.key = _to;
  Assert(U256_Cmp(U256_Add(balanceOf.value, _value), balanceOf.value) != -1,
         "overflows");
  // Save this for an assertion in the future
  // balanceOf.key = _from;
  // uint256 _from_balance = balanceOf.value;
  // balanceOf.key = _to;
  // uint256 _to_balance = balanceOf.value;
  // uint256 previousBalances = U256SafeAdd(_from_balance, _to_balance);
  // Subtract from the sender
  balanceOf.key = _from;
  balanceOf.value = U256SafeSub(balanceOf.value, _value);
  // Add the same to the recipient
  balanceOf.key = _to;
  balanceOf.value = U256SafeAdd(balanceOf.value, _value);
  Transfer(_from, _to, _value);
  // Asserts are used to use static analysis to find bugs in your code. They
  // should never fail
  // Assert(balanceOf[_from] + balanceOf[_to] == previousBalances);
}

/**
 * Transfer tokens
 *
 * Send `_value` tokens to `_to` from your account
 *
 * @param _to The address of the recipient
 * @param _value the amount to send
 */
MUTABLE
bool transfer(address _to, uint256 _value)
{
  _transfer(GetSender(), _to, _value);
  return true;
}

/**
 * Transfer tokens from other address
 *
 * Send `_value` tokens to `_to` on behalf of `_from`
 *
 * @param _from The address of the sender
 * @param _to The address of the recipient
 * @param _value the amount to send
 */
MUTABLE
bool transferFrom(address _from, address _to, uint256 _value)
{
  restriction.key = GetSender();
  Assert(!restriction.value, "Sender is restricted.");

  _allowance.key = _from;
  _allowance.value.key = GetSender();
  Assert(U256_Cmp(_value, _allowance.value.value) != 1,
         "sender does not have enought token"); // Check _allowance
  _allowance.key = _from;
  _allowance.value.key = GetSender();
  _allowance.value.value = U256SafeSub(_allowance.value.value, _value);
  _transfer(_from, _to, _value);
  return true;
}

/**
 * Set _allowance for other address
 *
 * Allows `_spender` to spend no more than `_value` tokens on your behalf
 *
 * @param _spender The address authorized to spend
 * @param _value the max amount they can spend
 */
MUTABLE
bool approve(address _spender, uint256 _value)
{
  _allowance.key = GetSender();
  _allowance.value.key = _spender;
  _allowance.value.value = _value;
  Approval(GetSender(), _spender, _value);
  return true;
}

/**
 * Precheck the ownership before doing some high level operation
*/
void onlyOwner() {
  Assert(Equal(GetSender(), owner), "Only contract owner can do this.");
}

/**
 * Edit restricted
 * This will change restricted to the opposite value
 */
MUTABLE
bool editRestricted() {
  onlyOwner();
  restricted = !restricted;
  return restricted;
}

/**
 * Edit restricted address
 * This will change the value of restricted address
 * to the opposite value
 */
MUTABLE
bool editRestrictedAddress(address _addr) {
  onlyOwner();
  restriction.key = _addr;
  bool orig = restriction.value;
  restriction.key = _addr;
  restriction.value = !orig;
  return !orig;
}

/**
 * Return restricted property
 */
UNMUTABLE
bool isRestricted() {
  return restricted;
}

/**
 * Check if an address is restricted
 */
UNMUTABLE
bool isRestrictedAddress(address _addr) {
  restriction.key = _addr;
  return restriction.value;
}

/**
 * Check allowance of specified owner and spender
 */
UNMUTABLE
uint256 allowance(address _owner, address _spender) {
  _allowance.key = _owner;
  _allowance.value.key = _spender;
  return _allowance.value.value;
}

UNMUTABLE
uint256 GetAmount(address addr)
{
  balanceOf.key = addr;
  return balanceOf.value;
}

UNMUTABLE
string GetTokenName() { return name; }

UNMUTABLE
string GetSymbol() { return symbol; }

UNMUTABLE
uint256 GetTotalSupply() { return totalSupply; }

UNMUTABLE
uint256 GetDecimals() { return decimals; }

_() {}
