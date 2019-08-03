#include "vntlib.h"

                    
                                
KEY string owner;
KEY string name = "IECT";
KEY string symbol = "IECT";
KEY uint256 decimals = U256(18);
KEY uint256 totalSupply = U256(2000000000000000000000000000);

                                          
KEY mapping(address, uint256) balanceOf;
KEY mapping(address, mapping(address, uint256)) _allowance;

                                          
                
KEY bool restricted = false;
                                  
KEY mapping(address, bool) restriction;

                                                                              
EVENT Transfer(indexed address from, indexed address to, uint256 value);

                                                                              
EVENT Approval(indexed address owner, indexed address spender, uint256 value);

   
                       
  
                                                                        
           
   

void key6tso5m6w(){
AddKeyInfo( &balanceOf.value, 5, &balanceOf, 9, false);
AddKeyInfo( &balanceOf.value, 5, &balanceOf.key, 7, false);
AddKeyInfo( &_allowance.value.value, 5, &_allowance, 9, false);
AddKeyInfo( &_allowance.value.value, 5, &_allowance.key, 7, false);
AddKeyInfo( &_allowance.value.value, 5, &_allowance.value.key, 7, false);
AddKeyInfo( &owner, 6, &owner, 9, false);
AddKeyInfo( &symbol, 6, &symbol, 9, false);
AddKeyInfo( &name, 6, &name, 9, false);
AddKeyInfo( &totalSupply, 5, &totalSupply, 9, false);
AddKeyInfo( &decimals, 5, &decimals, 9, false);
AddKeyInfo( &restriction.value, 8, &restriction, 9, false);
AddKeyInfo( &restriction.value, 8, &restriction.key, 7, false);
AddKeyInfo( &restricted, 8, &restricted, 9, false);
}
constructor IECT()
{
key6tso5m6w();
InitializeVariables();
  owner = GetSender();
  balanceOf.key = owner;
  balanceOf.value = totalSupply;                                       
}

   
                                                         
   
void _transfer(address _from, address _to, uint256 _value)
{
                                         
  Assert(!restricted, "contract is restricted");
                                        
  restriction.key = _from;
  Assert(!restriction.value, "from address is restricted");
                                      
  restriction.key = _to;
  Assert(!restriction.value, "to address is restricted");
                                                        
  Assert(!Equal(_to, Address("0x0")), "empty to address");
                                   
  balanceOf.key = _from;
  Assert(U256_Cmp(balanceOf.value, _value) != -1,
         "sender does not have enough token");
                        
  balanceOf.key = _to;
  Assert(U256_Cmp(U256_Add(balanceOf.value, _value), balanceOf.value) != -1,
         "overflows");
                                             
                           
                                             
                         
                                           
                                                                        
                             
  balanceOf.key = _from;
  balanceOf.value = U256SafeSub(balanceOf.value, _value);
                                  
  balanceOf.key = _to;
  balanceOf.value = U256SafeAdd(balanceOf.value, _value);
  Transfer(_from, _to, _value);
                                                                            
                      
                                                                   
}

   
                  
  
                                                  
  
                                          
                                   
   
MUTABLE
bool transfer(address _to, uint256 _value)
{
key6tso5m6w();
  _transfer(GetSender(), _to, _value);
  return true;
}

   
                                     
  
                                                     
  
                                         
                                          
                                   
   
MUTABLE
bool transferFrom(address _from, address _to, uint256 _value)
{
key6tso5m6w();
  restriction.key = GetSender();
  Assert(!restriction.value, "Sender is restricted.");

  _allowance.key = _from;
  _allowance.value.key = GetSender();
  Assert(U256_Cmp(_value, _allowance.value.value) != 1,
         "sender does not have enought token");                    
  _allowance.key = _from;
  _allowance.value.key = GetSender();
  _allowance.value.value = U256SafeSub(_allowance.value.value, _value);
  _transfer(_from, _to, _value);
  return true;
}

   
                                   
  
                                                                         
  
                                                  
                                              
   
MUTABLE
bool approve(address _spender, uint256 _value)
{
key6tso5m6w();
  _allowance.key = GetSender();
  _allowance.value.key = _spender;
  _allowance.value.value = _value;
  Approval(GetSender(), _spender, _value);
  return true;
}

   
                                                                
  
void onlyOwner() {
  Assert(Equal(GetSender(), owner), "Only contract owner can do this.");
}

   
                  
                                                    
   
MUTABLE
bool editRestricted() {
key6tso5m6w();
  onlyOwner();
  restricted = !restricted;
  return restricted;
}

   
                          
                                                   
                        
   
MUTABLE
bool editRestrictedAddress(address _addr) {
key6tso5m6w();
  onlyOwner();
  restriction.key = _addr;
  bool orig = restriction.value;
  restriction.key = _addr;
  restriction.value = !orig;
  return !orig;
}

   
                             
   
UNMUTABLE
bool isRestricted() {
key6tso5m6w();
  return restricted;
}

   
                                    
   
UNMUTABLE
bool isRestrictedAddress(address _addr) {
key6tso5m6w();
  restriction.key = _addr;
  return restriction.value;
}

   
                                                 
   
UNMUTABLE
uint256 allowance(address _owner, address _spender) {
key6tso5m6w();
  _allowance.key = _owner;
  _allowance.value.key = _spender;
  return _allowance.value.value;
}

UNMUTABLE
uint256 GetAmount(address addr)
{
key6tso5m6w();
  balanceOf.key = addr;
  return balanceOf.value;
}

UNMUTABLE
string GetTokenName() {
key6tso5m6w(); return name; }

UNMUTABLE
string GetSymbol() {
key6tso5m6w(); return symbol; }

UNMUTABLE
uint256 GetTotalSupply() {
key6tso5m6w(); return totalSupply; }

UNMUTABLE
uint256 GetDecimals() {
key6tso5m6w(); return decimals; }

_() {
key6tso5m6w();}
