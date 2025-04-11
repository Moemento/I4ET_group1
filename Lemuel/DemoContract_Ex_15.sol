// SPDX-License-Identifier: Unlicenced 
pragma solidity >=0.5 <0.8.0;


contract DemoContract { 
    // *******************************
    // Exercise 15: DemoContract as provided with modifications
    // *******************************
    
    address public owner; 
    // Define a struct to hold receiver information.
    struct Receivers {  
        string name; 
        uint256 tokens; 
    } 
  
    // Mapping from address to Receivers.
    mapping(address => Receivers) public users; 
       
    // Modifier to restrict function access to only the owner.
    modifier onlyOwner() { 
        require(msg.sender == owner, "Only owner can call this function"); 
        _; 
    } 
    
    // Constructor sets the owner and gives the owner an initial supply of tokens.
    constructor() { 
        owner = msg.sender; 
        users[owner].tokens = 100;   
    } 
    
    // A simple helper function that doubles a value.
    function double(uint _value) public pure returns (uint){ 
        return _value * 2; 
    } 
       
    // Function to register a user with a name.
    function register(string memory _name) public { 
        users[msg.sender].name = _name; 
    } 
       
    // Function for the owner to transfer tokens to another address.
    function giveToken(address _receiver, uint256 _amount) public onlyOwner { 
        require(users[owner].tokens >= _amount, "Owner does not have enough tokens"); 
        users[owner].tokens -= _amount; 
        users[_receiver].tokens += _amount; 
    } 
    
    // *******************************
    // Additional Functionality for Exercise 15:
    // Allow users to purchase tokens with Ether.
    // 1 token costs 2 Ether.
    // The function checks that enough Ether is sent and that the owner has enough tokens.
    // *******************************
    function buyTokens() public payable {
         uint256 tokenPrice = 2 ether; // price per token
         uint256 tokensToBuy = msg.value / tokenPrice;
         require(tokensToBuy > 0, "Not enough Ether sent to buy any token");
         require(users[owner].tokens >= tokensToBuy, "Owner does not have enough tokens");
         // Transfer tokens from owner to buyer.
         users[owner].tokens -= tokensToBuy;
         users[msg.sender].tokens += tokensToBuy;
    }
    
    // Function to display the amount of Ether held in this smart contract.
    function getContractBalance() public view returns (uint256) {
         return address(this).balance;
    }
}
